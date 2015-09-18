#include "socket-receive.h"

#include "stdafx.h"
#pragma comment(lib, "ws2_32.lib")

using namespace std;

RecSocket::RecSocket()
{
//	cout<<"................"<<endl;
}

RecSocket::~RecSocket()
{

}

int RecSocket::DataDeal(SOCKADDR_IN servAddr, unsigned int sport)
{
	char recvbuf[5][200];
	char sendbuf[5][200];
//	SOCKET sServer;
	SOCKET sockfd;
//	sockaddr_in servAddr;
//	unsigned int port = 8000;
	for (int i=0; i<5; i++)
	{
		memset(recvbuf[i], 0, 200);
		memset(sendbuf[i], 0, 200);
	}

	//step 1
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2,2), &wsa) != 0)
	{
//		cout<<"wsa init failed"<<endl;
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
//		cout<<"invalid socket"<<endl;
		return 0;
	}

	//step 2
	//bzero()
	//memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(sport);
	servAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
//	cout<<"tcp server start at port: "<<sport<<endl;
//	cout<<"seraddr.sin_addr.S_un.S_addr is:"<<servAddr.sin_addr.S_un.S_addr<<endl;

	if (bind(sockfd, (SOCKADDR*)&servAddr, sizeof(SOCKADDR)) != 0)
	{
		closesocket(sockfd);
		cout<<"bind error";
		return 0;
	}

	//step 3
	if (listen(sockfd, 5) != 0)
	{
		closesocket(sockfd);
//		cout<<"listen timeout"<<endl;
		return 0;
	}

//	cout<<"wait client..."<<endl;
	SOCKADDR_IN addrClint;
	SOCKET sockConn;
	int len = sizeof(SOCKADDR);
	int lastport;
	sockConn = accept(sockfd,(SOCKADDR*)&addrClint, &len);
	while(1)
	{
		

		sprintf(sendbuf[0],"welcome %s to here ", inet_ntoa(addrClint.sin_addr));
		send(sockConn, sendbuf[0],strlen(sendbuf[0]+1),0);

		recv(sockConn, recvbuf[0],200,0);
		cout<<recvbuf[0]<<endl;

		lastport = addrClint.sin_port;
		Sleep(100);
		
	}
	closesocket(sockConn);
	WSACleanup();

}


DWORD WINAPI RecSocket::ClientThread(LPVOID ipParameter)
{
	SOCKET ClientSocket = (SOCKET)ipParameter;
	int Ret = 0;
	char RecvBuffer[MAX_PATH];
	char sendbuf[MAX_PATH];
	

	while(true)
	{
		memset(RecvBuffer,0,sizeof(RecvBuffer));
		Ret = recv(ClientSocket, RecvBuffer, MAX_PATH,0);

		if (Ret == 0||Ret == SOCKET_ERROR)
		{
//			cout<<"failed, exit"<<endl;
			break;
		}
//		cout<<"recv wellcom:"<<RecvBuffer[0]<<":"<<RecvBuffer<<endl;

		memset(sendbuf,0, sizeof(sendbuf));
		sprintf(sendbuf,"%x welcome %d :",0xff,RecvBuffer[0]);
		send(ClientSocket,sendbuf,strlen(sendbuf)+1,0);
	}
	return 0;
}

int RecSocket::MainThread()
{
	WSADATA Wsa;
	SOCKET severSocket, clientSocket;
	struct sockaddr_in localAddr,clientAddr;
	int addrLen = 0;
	HANDLE hTread = NULL;
	int Ret = 0;

	//1
	if (WSAStartup(MAKEWORD(2,2), &Wsa) != 0)
	{
//		cout<<"init failed"<<endl;
		return -1;
	}

	severSocket = socket(AF_INET, SOCK_STREAM,0);
	if (severSocket == INVALID_SOCKET)
	{
//		cout<<"creat failed"<<GetLastError()<<endl;
		return -1;
	}

	//2
	localAddr.sin_family = AF_INET;
	localAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	localAddr.sin_port = htons(SPort);
	memset(localAddr.sin_zero, 0, 8);

	Ret = bind(severSocket, (SOCKADDR*)&localAddr,sizeof(localAddr));
	if (Ret != 0)
	{
//		cout<<"bind error"<<endl;
		return -1;
	}
	Ret = listen(severSocket, 5);
	if (Ret != 0)
	{
//		cout<<"listen error"<<endl;
		return -1;
	}

//	cout<<"server started"<<endl;
//	cout<<"server linked"<<inet_ntoa(localAddr.sin_addr)<<"."<<localAddr.sin_port<<endl;

	//cout<<inet_addr(IP_ADDRES)<<":"<<localAddr.sin_port<<endl;

	while(true)
	{
		addrLen = sizeof(clientAddr);
		clientSocket = accept(severSocket, (SOCKADDR*)&clientAddr, &addrLen);

		//cout<<clientAddr.sin_addr.S_un.S_addr<<":"<<clientAddr.sin_port<<endl;

		if (clientSocket == INVALID_SOCKET)
		{
	//		cout<<"accept failed"<<endl;
			break;
		}

		//cout<<"client linked"<<inet_ntoa(clientAddr.sin_addr)<<"."<<clientAddr.sin_port<<endl;
		hTread = CreateThread(NULL,0,ClientThread,(LPVOID)clientSocket,0,NULL);
		if (hTread == NULL)
		{
			//cout<<"creat thread failed"<<endl;
			break;
		}
		CloseHandle(hTread);
	}
	closesocket(severSocket);
	closesocket(clientSocket);
	WSACleanup();
	return 0;
	

}

int RecSocket::StartServer()
{
	WSADATA Wsa;
	SOCKET severSocket, clientSocket;
	struct sockaddr_in localAddr,clientAddr;
	int addrLen = 0;
	HANDLE hTread = NULL;
	int Ret = 0;

	//1
	if (WSAStartup(MAKEWORD(2,2), &Wsa) != 0)
	{
		//cout<<"init failed"<<endl;
		return -1;
	}

	severSocket = socket(AF_INET, SOCK_STREAM,0);
	if (severSocket == INVALID_SOCKET)
	{
		//cout<<"creat failed"<<GetLastError()<<endl;
		return -1;
	}

	//2
	localAddr.sin_family = AF_INET;
	localAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	localAddr.sin_port = htons(SPort);
	memset(localAddr.sin_zero, 0, 8);

	Ret = bind(severSocket, (SOCKADDR*)&localAddr,sizeof(localAddr));
	if (Ret != 0)
	{
		//cout<<"bind error"<<endl;
		return -1;
	}
	Ret = listen(severSocket, 5);
	if (Ret != 0)
	{
		//cout<<"listen error"<<endl;
		return -1;
	}

	//cout<<"server started"<<endl;
	//cout<<"server linked"<<inet_ntoa(localAddr.sin_addr)<<"."<<localAddr.sin_port<<endl;

}