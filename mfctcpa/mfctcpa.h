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
// mfctcpa.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CmfctcpaApp:
// �йش����ʵ�֣������ mfctcpa.cpp
//

class CmfctcpaApp : public CWinApp
{
public:
	CmfctcpaApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CmfctcpaApp theApp;


//#endif
