
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <iphlpapi.h>
#include <icmpapi.h>
#include <stdio.h>
#include <Ws2tcpip.h>     //for inet_pton()

#include <vector>

#include "BG_ICMP.h"

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")  //remove if covered by another unit

//forward declarations
static PINGSTATUS DoPingWS2Struct(HANDLE hIcmpFile, aNetDevice* nd);
static void DoPing(aNetDevice* nd);


//variables available to other units
int QueueSize = 0;
std::vector<aNetDevice> ScanList;

//file scope variables
static bool debug = true;
static const int NUMTHREADS = 10;
static PTP_POOL pool = NULL;
static PTP_CLEANUP_GROUP cleanupgroup = NULL;
static HANDLE hIcmpFile;
static int JobNumber = 0;


static bool PrepBGThreadPool() //returns true if error
{
    BOOL bRet = FALSE;
    PTP_WORK work = NULL;
    PTP_TIMER timer = NULL;

    pool = CreateThreadpool(NULL);
    if (NULL == pool) {
		if (debug) printf("CreateThreadpool failed. LastError: %u\n", GetLastError());
        return true;
    }

    SetThreadpoolThreadMaximum(pool, NUMTHREADS);
    bRet = SetThreadpoolThreadMinimum(pool, 1);
    if (FALSE == bRet) {
        if (debug) printf("SetThreadpoolThreadMinimum failed. LastError: %u\n", GetLastError());
        CloseThreadpool(pool);
        return true;
    }

    // Create a cleanup group for this thread pool.
    cleanupgroup = CreateThreadpoolCleanupGroup();
    if (NULL == cleanupgroup) {
        if (debug) printf("CreateThreadpoolCleanupGroup failed. LastError: %u\n", GetLastError());
        CloseThreadpool(pool);
        return true;
    }
    return false;
}

static VOID CleanUpBGPool()
{
    // Wait for all callbacks to finish.
    // CloseThreadpoolCleanupGroupMembers also releases objects
    // that are members of the cleanup group, so it is not necessary
    // to call close functions on individual objects
    // after calling CloseThreadpoolCleanupGroupMembers.
    //CloseThreadpoolCleanupGroupMembers(cleanupgroup, FALSE, NULL);
    //CloseThreadpoolCleanupGroup(cleanupgroup);
    CloseThreadpool(pool);
    return;
}



VOID CALLBACK BGWorkCallback(PTP_CALLBACK_INSTANCE Instance, PVOID Parameter, PTP_WORK Work)
{
    UNREFERENCED_PARAMETER(Instance);
    UNREFERENCED_PARAMETER(Work);
    aNetDevice *f = (aNetDevice*)Parameter;
    f->jobNumber = JobNumber;
	DoPing(f);
    QueueSize--;
    return;
}


static void DoPing(aNetDevice* nd)
{
	inet_pton(AF_INET, (PCSTR)(nd->IPtoPing), &(nd->sa.sin_addr));

    PINGSTATUS CurrentStatus = DoPingWS2Struct(hIcmpFile, nd);
	if (CurrentStatus == ALIVE)
    {
        if (nd->myStatus == DEAD) nd->myStatus = ZOMBIE; //previous state was dead, now alive -> ZOMBIE
		else nd->myStatus = ALIVE;
		GetSystemTime(&nd->st);
    }
    else nd->myStatus = DEAD;
}


static PINGSTATUS DoPingWS2Struct(HANDLE hIcmpFile, aNetDevice* nd)
{
    DWORD dwRetVal = 0;
    char SendData[32] = "RCS Pinger Buffer";
    char mReplyBuffer[100];
    
    nd->pingTries++;
    // The IcmpSendEcho2 and IcmpSendEcho2Ex functions are enhanced version of IcmpSendEcho that support asynchronous operation.
    // The IcmpSendEcho2Ex function also allows the source IP address to be specified. This feature is useful on computers with multiple network interfaces.
    dwRetVal = IcmpSendEcho(hIcmpFile, (IPAddr)nd->sa.sin_addr.S_un.S_addr, SendData, sizeof(SendData), NULL, mReplyBuffer, 100, 1000);//last param is timeout in ms
    if (dwRetVal != 0) {
        PICMP_ECHO_REPLY pEchoReply = (PICMP_ECHO_REPLY)mReplyBuffer;
        struct in_addr ReplyAddr;
		ReplyAddr.S_un.S_addr = pEchoReply->Address;

		if (debug)
		{
			printf("\t////////////////Sent icmp message # %d to %s\n", nd->pingCounter, nd->IPtoPing);
		if (dwRetVal > 1) {
			printf("\tReceived %ld icmp message responses\n", dwRetVal);
			printf("\tInformation from the first response:\n");
		}
		else {
			printf("\tReceived %ld icmp message response\n", dwRetVal);
			printf("\tInformation from this response:\n");
		}
			printf("\t  Received from %s\n", inet_ntoa(ReplyAddr));
			printf("\t  Status = %ld\n", pEchoReply->Status);
			printf("\t  Roundtrip time = %ld milliseconds\n", pEchoReply->RoundTripTime);
		}

 		nd->RoundTripTime = pEchoReply->RoundTripTime;
		//nd->ADZ_status = pEchoReply->Status;
        nd->PingStatus = pEchoReply->Status;
		nd->pingCounter++;
        nd->wasAliveAtLeastOnce = true;
		return ALIVE;
	}
	else 
    {  //dwRetVal was 0
        nd->PingStatus = GetLastError();
		//printf("\tCall to IcmpSendEcho failed.\n");
		//printf("\tIcmpSendEcho returned error: %ld\n", GetLastError());
        return DEAD;
    }
}







//uses file scoped HANDLE
bool PrepPing()
{
	int t=0;
	hIcmpFile = IcmpCreateFile();//opens a handle on which ICMP Echo Requests can be issued.

    if (hIcmpFile == INVALID_HANDLE_VALUE) {
		if (debug)
		{
			printf("\tUnable to open handle.\n");
			printf("IcmpCreatefile returned error: %ld\n", GetLastError());
		}
		return true;
	}
	return false;
}



static int SubmitScanIPToPool(aNetDevice* bg_Param)
{
    QueueSize++;
    if (debug) printf("ScanIP, Submit Ping to ThreadPool for: %s\r\n", bg_Param->IPtoPing);
    PTP_WORK work = NULL;
    work = CreateThreadpoolWork(BGWorkCallback, (PVOID)bg_Param, NULL);// &CallBackEnviron);
    SubmitThreadpoolWork(work);
    return 0;
}

void ScanIPList()
{
    for (int x = 0; x < ScanList.size(); x++) SubmitScanIPToPool(&ScanList[x]);
}


void CreateScanList(std::vector<std::string> &IPList)
{
	for (auto s: IPList)
	{
		aNetDevice ipl;    //push_back() appends a copy of value to the end of the container.
		sprintf_s(ipl.IPtoPing, "%s", s.c_str());
		ipl.ADZ_status = 0;
		ScanList.push_back(ipl);
	}
}


void CreateScanList( std::vector<std::pair<std::string,std::string>> &IPNList)
{
    ScanList.clear();
	for (auto s: IPNList)
	{
		aNetDevice ipl;    //push_back() appends a copy of value to the end of the container.
		sprintf_s(ipl.IPtoPing, "%s", s.first.c_str());
        ipl.endPointName = s.second;
		ipl.ADZ_status = 0;
		ScanList.push_back(ipl);
	}
}



//creates a default scan list for the 192.168.1.0/24 subnet
void CreateScanList()
{
	for (int i = 1; i < 255; i++)
	{
		aNetDevice ipl;    //push_back() appends a copy of value to the end of the container.
		sprintf_s(ipl.IPtoPing, "192.168.1.%d", i);
		ipl.ADZ_status = 0;
		ScanList.push_back(ipl);
	}
}

//returns true if error
bool InitICMP()
{
	bool retVal = PrepBGThreadPool();
	if (retVal) return true;  //means error
	return PrepPing();
}


bool ShutDownICMP()
{
	CleanUpBGPool();
    return false;
}



