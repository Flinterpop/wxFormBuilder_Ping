#pragma once

#include <string>
#include <vector>

bool InitICMP();
bool ShutDownICMP();

void CreateScanList( std::vector<std::pair<std::string,std::string>> &IPNList);

void CreateScanList(std::vector<std::string> &IPList);
void CreateScanList();

void ScanIPList();

//void ShowScanListOnConsole();

bool PrepPing();


enum PINGSTATUS { NEVERPINGED, ALIVE, DEAD , ZOMBIE};

typedef struct _aNetDevice
{
    struct sockaddr_in sa;
    unsigned long ipaddr = INADDR_NONE;
    char IPtoPing[20];
    ULONG RoundTripTime = -1;
    int ADZ_status = 0; 
    int PingStatus = 0;
    int pingTries = 0;
    int pingCounter = 0;
    PINGSTATUS myStatus = NEVERPINGED;
	int jobNumber = 0;

	std::string endPointName;
    SYSTEMTIME st;

    bool wasAliveAtLeastOnce = false;


} aNetDevice;




