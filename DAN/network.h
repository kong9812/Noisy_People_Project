//===================================================================================================================================
//�ynetwork.h�z
// [�쐬��]HAL����GP12A332 16 �� �F��
// [�쐬��]2019/12/05
// [�X�V��]2019/12/05
//===================================================================================================================================
#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

//===================================================================================================================================
//�y���C�u�����̃��[�h�z
//===================================================================================================================================
#include "Base.h"
#include <WinSock.h>
#include <conio.h>
#pragma comment(lib, "ws2_32.lib")

//===================================================================================================================================
//�y�萔��`�z
//===================================================================================================================================
const u_short port = 12345;
const char szServer[64] = "10.192.109.8"; //test

//===================================================================================================================================
//�y�\���́z
//===================================================================================================================================
typedef struct
{
	D3DXVECTOR3 tmpPos;
	int mun;
}PACKAGE;

//===================================================================================================================================
//�y�N���C�A���g�z
//===================================================================================================================================
class NETWORK_CLIENT
{
public:
	NETWORK_CLIENT();
	~NETWORK_CLIENT();

	void send();

private:
	WSADATA wsaData;
	SOCKET s;
	SOCKADDR_IN addrin;
	HOSTENT *lpHostEnt;
	unsigned int addr;
	int nRtn, nNo = 5;
};