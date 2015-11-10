
// mfctcpaDlg.h : 头文件
//

#pragma once

#include "recsocker.h"

#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

//1
#define SER_MESSAGE WM_USER + 103

#include <afxtempl.h>
typedef CList <SOCKET,SOCKET&> SOCKET_ARRAY;



// CmfctcpaDlg 对话框
class CmfctcpaDlg : public CDialogEx
{
// 构造
public:
	CmfctcpaDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFCTCPA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
//	CString m_editIpAddress;
//	CString m_editPort;
//	CString m_editOnLink;
//	CEdit m_editLinkStatus;
//	CString m_editLinkStatus;
	afx_msg void OnBnClickedLinkserverButton1();
	CString m_editSendContent;
//	CEdit m_editDisplay;
//	CEdit m_editDisplay;
	afx_msg void OnEnChangeDisplayEdit12();
	CEdit m_editDisplayM;

//	BOOL m_bClient;
//	BOOL m_bInit;
	CString m_outbox;
	CString m_inbox;
	recsocker m_server;
	ModbusHandle m_modushandle;
//	SOCKET_ARRAY m_connectionList;
	CString m_name;
	CString m_data;
	int	m_linknum;
	int m_definenum;
	//2
	afx_msg LRESULT OnserVerMessage(WPARAM wParam,LPARAM lPram);


	afx_msg void OnLbnSelchangeList1();
	CEdit m_editIp;
	CEdit m_editPort;
	afx_msg void OnEnChangeIpEdit1();
	CEdit m_editLinkStatus;


	CEdit m_editpara1;
	CEdit m_editpara2;
	CEdit m_editpara3;
	CEdit m_editpara4;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnStnClickedPara1Static();
	CEdit m_editLinkserver;
	CEdit m_editOnLink;
	int m_editStartTime;
	int m_editEndtime;

	void InitWsaAsynSelect(void);
};
