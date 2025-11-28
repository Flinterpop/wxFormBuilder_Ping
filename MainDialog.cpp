

#include "MainDialog.h"
#include "BG_ICMP.h"

extern int QueueSize;
extern std::vector<aNetDevice> ScanList;

void MainDialog::m_timer1OnTimer(wxTimerEvent& event)
{
	pme("Scan..");
	ScanIPList();
	ShowScanList();
}

void MainDialog::ShowScanList()
{
	int AliveCount = 0;
	int DeadCount = 0;
	int ZombieCount = 0;


	for (int x = 0; x < ScanList.size(); x++)
	{
		if (ScanList[x].myStatus == ALIVE) AliveCount++;
		else if (ScanList[x].myStatus == DEAD) DeadCount++;
		else if (ScanList[x].myStatus == ZOMBIE) ZombieCount++;

		char s = 'A';    // for alive
		if (ScanList[x].myStatus == ZOMBIE) s = 'Z';      //for zombie
		if (ScanList[x].myStatus == DEAD) s = 'D';      //for Dead

		//pme("%c Index: %03d  Ping Count %03d IP: %s reply: %ld Status: %d",s, x, ScanList[x].pingCounter, ScanList[x].IPtoPing, ScanList[x].RoundTripTime, ScanList[x].PingStatus);
		if (0 != ScanList[x].PingStatus) pme("%c Index: %03d  Ping Count %03d IP: %s reply: %ld Status: %d", s, x, ScanList[x].pingCounter, ScanList[x].IPtoPing, ScanList[x].RoundTripTime, ScanList[x].PingStatus);
		//int age = (int)ScanList[x].st.wSecond;


		SetRow(ScanList[x], x);
	}

	char buf[40];
	sprintf(buf, "%d", AliveCount);
	m_textCtrlAlive->SetValue(buf);
	sprintf(buf, "%d", DeadCount);
	m_textCtrlDead->SetValue(buf);
	sprintf(buf, "%d", ZombieCount);
	m_textCtrlZombie->SetValue(buf);

	//pme("Jobs in Queue: %d", QueueSize);

	//TP_POOL_STACK_INFORMATION SI;
	//bool val = QueryThreadpoolStackInformation(pool,&SI);
}

void MainDialog::pme(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	char buf[200];
	vsprintf(buf, fmt, args);
	m_textCtrlDebug->AppendText(buf);
	m_textCtrlDebug->AppendText("\r\n");
	va_end(args);
}

void MainDialog::SetRow(aNetDevice a, int row)
{
	char buf[40];

	if (NEVERPINGED == a.myStatus) {
		m_grid1->SetCellTextColour(row, 0, *wxBLACK);
		m_grid1->SetCellValue(row, 0, "N");
	}
	else if (ALIVE == a.myStatus)
	{
		m_grid1->SetCellTextColour(row, 0, *wxGREEN);
		m_grid1->SetCellValue(row, 0, "Alive");
	}
	else if (ZOMBIE == a.myStatus)
	{
		m_grid1->SetCellTextColour(row, 0, *wxGREEN);
		m_grid1->SetCellValue(row, 0, "Zombie");
	}
	else if (DEAD == a.myStatus)
	{
		m_grid1->SetCellTextColour(row, 0, *wxRED);
		m_grid1->SetCellValue(row, 0, "Dead"); //DEAD
	}

	m_grid1->SetCellValue(row, 1, a.IPtoPing);
	m_grid1->SetCellValue(row, 2, a.endPointName);


	sprintf(buf, "%03d", a.pingTries);
	m_grid1->SetCellValue(row, 3, buf);

	sprintf(buf, "%03d", a.pingCounter);
	m_grid1->SetCellValue(row, 4, buf);

	if (NEVERPINGED == a.myStatus) m_grid1->SetCellValue(row, 5, "-");
	else if ((ALIVE == a.myStatus) || (ZOMBIE == a.myStatus))
	{
		sprintf(buf, "%d", (int)a.RoundTripTime);
		m_grid1->SetCellValue(row, 5, buf);
	}
	else
	{
		m_grid1->SetCellValue(row, 5, "-");
	}

	//DTG
	if ((NEVERPINGED != a.myStatus) && (true == a.wasAliveAtLeastOnce))
	{
		sprintf(buf, "%04d-%02d-%02d at %02d:%02d:%02d", a.st.wYear, a.st.wMonth, a.st.wDay, a.st.wHour, a.st.wMinute, a.st.wSecond);
		m_grid1->SetCellValue(row, 6, buf);
	}

	//Status
	auto t = ICMP_Status.find(a.PingStatus);
	if (t != ICMP_Status.end())
	{
		std::string T = t->second;
		sprintf(buf, "%s", T.c_str());
		m_grid1->SetCellValue(row, 7, buf);
	}
	else
	{
		m_grid1->SetCellValue(row, 7, "no map");
	}

}




void MainDialog::BuildScanList(void)
{
	int numRows = m_grid1->GetNumberRows();
	// Begin a batch operation for performance, especially with many rows
	m_grid1->BeginBatch();
	// Iterate backward and delete each row
	for (int i = numRows - 1; i >= 0; --i) {
		m_grid1->DeleteRows(i, 1); // Delete 1 row starting at index i
	}
	m_grid1->EndBatch();

	m_textCtrlAlive->SetValue("0");
	m_textCtrlDead->SetValue("0");
	m_textCtrlZombie->SetValue("0");



	std::vector<std::pair<std::string, std::string>> ipNlist;


	auto t = m_comboBoxSites->GetValue();

	if ("22 Wing" == t)
	{
		ipNlist.push_back(std::make_pair("1.3.129.1", "ARISTA 7200"));
		ipNlist.push_back(std::make_pair("1.3.129.2", "ARISTA 720"));
		ipNlist.push_back(std::make_pair("1.3.129.3", "Taclane CT"));
		ipNlist.push_back(std::make_pair("8.8.8.8", "Google"));
	}
	if ("3 Wing" == t)
	{
		ipNlist.push_back(std::make_pair("1.3.37.1", "ARISTA 7200"));
		ipNlist.push_back(std::make_pair("1.3.37.2", "ARISTA 720"));
		ipNlist.push_back(std::make_pair("1.3.37.3", "Taclane CT"));
		ipNlist.push_back(std::make_pair("8.8.8.8", "Google"));
	}
	if ("4 Wing" == t)
	{
		ipNlist.push_back(std::make_pair("1.3.56.1", "ARISTA 7200"));
		ipNlist.push_back(std::make_pair("1.3.56.2", "ARISTA 720"));
		ipNlist.push_back(std::make_pair("1.3.56.3", "Taclane CT"));
		ipNlist.push_back(std::make_pair("8.8.8.8", "Google"));
	}
	if ("TSIL" == t)
	{
		ipNlist.push_back(std::make_pair("192.168.123.1", "BATS-D"));
		ipNlist.push_back(std::make_pair("192.168.1.1", "ARISTA"));

	}
	if ("RSIL" == t)
	{
		ipNlist.push_back(std::make_pair("192.168.1.1", "ASUS"));
		ipNlist.push_back(std::make_pair("192.168.2.1", "Bell"));
		ipNlist.push_back(std::make_pair("192.168.1.7", "Lair?"));
		ipNlist.push_back(std::make_pair("192.168.1.8", "T-Link8"));
		ipNlist.push_back(std::make_pair("192.168.1.9", "T-Link9"));
		ipNlist.push_back(std::make_pair("192.168.1.18", "HP Printer"));
		ipNlist.push_back(std::make_pair("192.168.1.19", "Printer"));
		ipNlist.push_back(std::make_pair("192.168.1.121", "ESX"));
		ipNlist.push_back(std::make_pair("192.168.1.136", "ADS-B"));

		ipNlist.push_back(std::make_pair("192.168.1.200", "NAS"));
		ipNlist.push_back(std::make_pair("192.168.1.251", "NTP"));

		ipNlist.push_back(std::make_pair("192.168.1.196", "Legion"));
		ipNlist.push_back(std::make_pair("8.8.8.8", "Google"));
	}

	if ("436Sqn" == t)
	{
		ipNlist.push_back(std::make_pair("192.168.1.24", "This PC"));
		ipNlist.push_back(std::make_pair("192.168.1.1", "Local Router"));
		ipNlist.push_back(std::make_pair("192.168.1.22", "TSS"));
		ipNlist.push_back(std::make_pair("192.168.1.123", "JTRS Rack MIC/MAC"));
		ipNlist.push_back(std::make_pair("10.33.94.16", "JTRS Rack HMIG"));
		ipNlist.push_back(std::make_pair("24.1.7.16", "JTRS Support Port"));
	}




	CreateScanList(ipNlist);
	numRows = ipNlist.size();

	m_grid1->AppendRows(numRows);
	//delete m_grid2;
	//m_grid2->CreateGrid(numRows, 8);


	int i = 0;
	for (auto a : ScanList)  SetRow(a, i++);

	bSizer1->Fit(this); // Size the dialog to fit its content
	pme("Created Scan List");
}
