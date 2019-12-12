//===================================================================================================================================
//ynetwork.hz
// [์ฌา]HALGP12A332 16 ไ๏ F
// [์ฌ๚]2019/12/05
// [XV๚]2019/12/05
//===================================================================================================================================
#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

//===================================================================================================================================
//yCuฬ[hz
//===================================================================================================================================
#include "Base.h"
#include "networkServer.h"

#include <WinSock.h>
#include <conio.h>
#pragma comment(lib, "ws2_32.lib")

//===================================================================================================================================
//y่่`z
//===================================================================================================================================
const char szServer[64] = "ths80214"; //test

//===================================================================================================================================
//yNCAgz
//===================================================================================================================================
class NETWORK_CLIENT
{
public:
	NETWORK_CLIENT();
	~NETWORK_CLIENT();

	void send(float time);
	void outputGUI();
	static void setSendTreeTable(const TreeTable inTreeTable);
private:
	int packageID;
	WSADATA wsaData;
	SOCKET s;
	SOCKADDR_IN addrin;
	HOSTENT *lpHostEnt;
	unsigned int addr;
	int nRtn, nNo = 5;

	static TreeTable *treeTable;
	static int treeNum;
};
