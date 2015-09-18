#ifndef __SOCKET_RECEIVE_H
#define __SOCKET_RECEIVE_H


#include "winsock2.h"
//#include "windows.h"
#include <iostream>
#include <string>

#define IP_ADDRES "127.0.0.1"
#define SPort		12001

using namespace std;

class RecSocket
{
public:
	RecSocket();
	~RecSocket();
	int DataDeal(SOCKADDR_IN servAddr, unsigned int port);
	static DWORD WINAPI ClientThread(LPVOID ipParameter);
	int  MainThread();
	int StartServer();

private:
};


#endif