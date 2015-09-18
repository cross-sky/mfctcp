//#ifndef __MFCTCP_H
//#define __MFCTCP_H
//
//#include <WinSock2.h>
//#include <iostream>
//#include <Windows.h>
//#include <string>
//
//using namespace std;


//#pragma comment(lib,"ws2_32.lib")
// mfctcpa.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CmfctcpaApp:
// 有关此类的实现，请参阅 mfctcpa.cpp
//

class CmfctcpaApp : public CWinApp
{
public:
	CmfctcpaApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CmfctcpaApp theApp;


//#endif
