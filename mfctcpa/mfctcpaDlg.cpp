
// mfctcpaDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mfctcpa.h"
#include "mfctcpaDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CmfctcpaDlg *pm_Dlg;


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CmfctcpaDlg �Ի���




CmfctcpaDlg::CmfctcpaDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CmfctcpaDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//  m_editIpAddress = _T("");
	//  m_editPort = _T("");
	//  m_editOnLink = _T("");
	//  m_editLinkStatus = _T("");
	//	m_editSendContent = 0;
	//	m_editDisplay = _T("");
	//  m_editPort = 0;
	m_editStartTime = 0;
	m_editEndtime = 0;
}

void CmfctcpaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_IP_EDIT1, m_editIpAddress);
	//  DDV_MaxChars(pDX, m_editIpAddress, 15);
	//  DDX_Text(pDX, IDC_PORT_EDIT2, m_editPort);
	//  DDX_Text(pDX, IDC_ONLINK_EDIT7, m_editOnLink);
	//  DDX_Control(pDX, IDC_LINKSTATUS_EDIT8, m_editLinkStatus);
	//  DDX_Text(pDX, IDC_LINKSTATUS_EDIT8, m_editLinkStatus);
	DDX_Text(pDX, IDC_SENDCONTENT_EDIT13, m_editSendContent);
	//  DDX_Control(pDX, IDC_DISPLAY_EDIT12, m_editDisplay);
	//  DDX_Text(pDX, IDC_DISPLAY_EDIT12, m_editDisplay);
	DDX_Control(pDX, IDC_DISPLAY_EDIT12, m_editDisplayM);
	//  DDX_Text(pDX, IDC_PORT_EDIT2, m_editPort);
	DDX_Control(pDX, IDC_IP_EDIT1, m_editIp);
	DDX_Control(pDX, IDC_PORT_EDIT2, m_editPort);
	DDX_Control(pDX, IDC_LINKSTATUS_EDIT8, m_editLinkStatus);
	DDX_Control(pDX, IDC_PPARA1_EDIT5, m_editpara1);
	DDX_Control(pDX, IDC_PARA2_EDIT9, m_editpara2);
	DDX_Control(pDX, IDC_PARA3_EDIT10, m_editpara3);
	DDX_Control(pDX, IDC_PARA4_EDIT11, m_editpara4);
	DDX_Control(pDX, IDC_LINKSERVER_EDIT, m_editLinkserver);
	DDX_Control(pDX, IDC_ONLINK_EDIT7, m_editOnLink);
	DDX_Text(pDX, IDC_StartTimeEDIT1, m_editStartTime);
	DDX_Text(pDX, IDC_EndTimeEDIT2, m_editEndtime);
}

BEGIN_MESSAGE_MAP(CmfctcpaDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CmfctcpaDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_LINKSERVER_BUTTON1, &CmfctcpaDlg::OnBnClickedLinkserverButton1)
	ON_EN_CHANGE(IDC_DISPLAY_EDIT12, &CmfctcpaDlg::OnEnChangeDisplayEdit12)
//	ON_LBN_SELCHANGE(IDC_LIST1, &CmfctcpaDlg::OnLbnSelchangeList1)
	ON_EN_CHANGE(IDC_IP_EDIT1, &CmfctcpaDlg::OnEnChangeIpEdit1)
	ON_MESSAGE(SER_MESSAGE, &CmfctcpaDlg::OnserVerMessage)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CmfctcpaDlg ��Ϣ�������

BOOL CmfctcpaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
//	m_editDisplay.SetWindowTextW(_T(hello"));

	m_editDisplayM.SetWindowTextW(_T("......wait start......\r\n"));
	m_editDisplayM.SetWindowTextW(_T("......wait start1......\r\n"));
	m_editIp.SetWindowTextW(_T("127.0.0.1"));
	this->SetDlgItemTextW(IDC_PORT_EDIT2,_T("40000"));
	m_editStartTime = 8;
	m_editEndtime = 18;

	UpdateData(FALSE);
	pm_Dlg = this;


	InitWsaAsynSelect(); //start wsaasynselect

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CmfctcpaDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CmfctcpaDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CmfctcpaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CmfctcpaDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}

void CmfctcpaDlg::InitWsaAsynSelect()
{
	m_definenum = m_server.ReadFileData();


	UpdateData(TRUE);
	if (m_server.StartServer(this->m_hWnd,GetDlgItemInt(IDC_PORT_EDIT2)) == FALSE)
	{
		return ;
	}
	else
	{
		//		m_bInit=TRUE;
		//		m_bClient=FALSE;

		if ( m_editStartTime < 0 && m_editStartTime >24)
		{
			m_editStartTime=8;
		}

		if ( m_editEndtime < 0 && m_editEndtime >24)
		{
			m_editEndtime=18;
		}
		if (m_editStartTime > m_editEndtime)
		{
			m_editStartTime=8;
			m_editEndtime=18;
		}


		m_editDisplayM.GetWindowTextW(m_outbox);
		//m_outbox+=_T("\r\n");
		m_outbox += "Server has been set ok!\r\n";
		m_editDisplayM.SetWindowTextW(m_outbox);
		m_outbox += "wait client1\r\n";
		m_outbox += "wait client2\r\n";
		m_outbox += "wait client3\r\n";
		m_outbox += "wait client4\r\n";
		m_outbox += "wait client5\r\n";
		m_outbox += "wait client6\r\n";
		//AfxMessageBox(TEXT("Listen Error"));
		m_editDisplayM.SetWindowTextW(m_outbox);

		m_editDisplayM.LineScroll(m_editDisplayM.GetLineCount());

		CString stemp;
		m_editIp.GetWindowTextW(stemp);
		m_editIp.SetWindowTextW(stemp);

		m_editPort.GetWindowTextW(stemp);
		this->SetDlgItemTextW(IDC_PORT_EDIT2,stemp);

		SetTimer(1, 5000, NULL);
		m_modushandle.m_newsocket = 0;

		m_editLinkserver.SetWindowTextW(_T("starting"));

		UpdateData(FALSE);
	}

}

void CmfctcpaDlg::OnBnClickedLinkserverButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CString decimal = _T(m_editPort);
	InitWsaAsynSelect();
}


void CmfctcpaDlg::OnEnChangeDisplayEdit12()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CmfctcpaDlg::OnLbnSelchangeList1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CmfctcpaDlg::OnEnChangeIpEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

#if 1
LRESULT CmfctcpaDlg::OnserVerMessage(WPARAM wParam,LPARAM lPram)
{
	SOCKET tsocket;
	int length,i;

	if (WSAGETASYNCERROR(lPram))
	{
		if ( m_modushandle.m_newsocket == wParam)
		{
			m_modushandle.m_newsocket = 0;
			return 0;
		}

		length = m_modushandle.m_modbuslist.GetCount();
		for(i=0; i<length; i++)
		{
			modbus_data_t *m_point = &m_modushandle.m_modbuslist.GetAt(m_modushandle.m_modbuslist.FindIndex(i));
			tsocket = (*m_point).socketData;
			if(tsocket == wParam)
			{
				(*m_point).status = -1;
				return 0;

			}
		}

		return -1;

	}

	switch(WSAGETSELECTEVENT(lPram))
	{
	case FD_ACCEPT:
		//socket = accept(m_server.m_hSocket,NULL,NULL);
		
		//m_connectionList.AddHead(socket);
		//m_modushandle.ModbusBind();
		{
			
#ifdef vera
			//struct  modbus_data_t *m_point = new modbus_data_t;
			modbus_data_t mpoint;
			memset(&mpoint,0,sizeof(mpoint));
			mpoint.addrLen = sizeof(mpoint.clientAddr);
			tsocket = accept(m_server.m_hSocket,(sockaddr*)&mpoint.clientAddr,&mpoint.addrLen);
			DWORD lasterr;
			if (tsocket == SOCKET_ERROR)
			{
				lasterr = GetLastError();
			}
			//socket = accept(m_server.m_hSocket,NULL,NULL);

			mpoint.socketData = tsocket;
			mpoint.status = 0;
			mpoint.index = 0;
			mpoint.flagSend = 0;
			//m_point->clientAddr = cliAddr;
			//m_point->addrLen = cliLen;
			m_modushandle.m_modbuslist.AddHead(mpoint);

			return 0;
#endif // vera

#ifdef verb
			m_modushandle.m_newaddrLen = sizeof(m_modushandle.m_newclientAddr);
			tsocket = accept(m_server.m_hSocket,(sockaddr*)&m_modushandle.m_newclientAddr,&m_modushandle.m_newaddrLen);
			DWORD lasterr;
			if (tsocket == SOCKET_ERROR)
			{
				lasterr = GetLastError();
			}
			
			if ( m_modushandle.m_newsocket == 0)//�ȴ���������һ��socket
			{
				m_modushandle.m_newsocket = tsocket;

			}
			else
				closesocket(tsocket);

			return 0;
#endif // verb
			
		}
		//return 0;
	case FD_READ:

#ifdef verb

		if (wParam == m_modushandle.m_newsocket)
		{
			byte tdata[5]={0};
			modbus_data_t tmodbus;
			m_modushandle.ModbusBind(&tmodbus, tdata);
			return 0;
		}
#endif // verb


		length = m_modushandle.m_modbuslist.GetCount();
		for(i=0; i<length; i++)
		{
			//socket = m_modushandle.m_modbuslist.GetAt(m_modushandle.m_modbuslist.FindIndex(i));
			tsocket = m_modushandle.m_modbuslist.GetAt(m_modushandle.m_modbuslist.FindIndex(i)).socketData;
			if (tsocket == wParam)
			{
				m_modushandle.ModbusRecv(i);
				return 0;
			}
		}
		return -1;

	case FD_WRITE:
		return 0;
	case FD_CLOSE:
		{
			length = m_modushandle.m_modbuslist.GetCount();
			for(i=0; i<length; i++)
			{
				modbus_data_t *m_point = &m_modushandle.m_modbuslist.GetAt(m_modushandle.m_modbuslist.FindIndex(i));
				tsocket = (*m_point).socketData;
				if(tsocket == wParam)
				{
					(*m_point).status = -1;
					return 0;

				}
			}
			//m_connectionList.RemoveHead();
			
			return 0;

		}

	default:
		{
			m_inbox = "";
			m_editDisplayM.GetWindowTextW(m_inbox);
			m_inbox += "an error has occured with a client\r\n";
			GetDlgItem(IDC_DISPLAY_EDIT12)->SetWindowTextW(m_inbox);
			m_editDisplayM.LineScroll(m_editDisplayM.GetLineCount());

			length = m_modushandle.m_modbuslist.GetCount();
			for(i=0; i<length; i++)
			{
				modbus_data_t *m_point = &m_modushandle.m_modbuslist.GetAt(m_modushandle.m_modbuslist.FindIndex(i));
				tsocket = (*m_point).socketData;
				if(tsocket == wParam)
				{
					(*m_point).status = -1;
					return 0;

				}
			}
			return 0;
		}

		
	}
}
#endif

#if 0

LRESULT CmfctcpaDlg::OnserVerMessage(WPARAM wParam,LPARAM lPram)
{
	SOCKET socket;
	static int length,i;
	CString str = _T("");
	CString in;
	CEdit* output = NULL;
	char s[20][400];
	static char ch[20][20];
	int len;
	switch(lPram)
	{
		case FD_ACCEPT:
			socket = accept(m_server.m_hSocket,NULL,NULL);
			m_connectionList.AddHead(socket);
			return 0;
			case FD_READ:
			length = m_connectionList.GetCount();
			for(i=0; i<length; i++)
			{
				socket = m_connectionList.GetAt(m_connectionList.FindIndex(i));
				if (socket == wParam)
				{
				len=recv(socket,s[i],1024,0);
				s[i][len]=NULL;
				strncpy(ch[i],s[i],16);
				ch[i][16] = '\0';
				m_name = ch[i];
				m_data = s[i]+16;
				CTime time=CTime::GetCurrentTime();
				CString m_writetime = time.Format("%Y-%m-%d %H:%M:%S");
			//
			//..............
				in=m_writetime;
				in+="|";
				in+=m_name;
				in+="|";
				in+=m_data;
				in+="\r\n";
				m_inbox+=in;
				GetDlgItem(IDC_DISPLAY_EDIT12)->SetWindowTextW(m_inbox);
				m_editDisplayM.LineScroll(m_editDisplayM.GetLineCount());
				return 0;
		}
		}
		return 0;

		case FD_WRITE:
		return 0;
		case FD_CLOSE:
		{
		length = m_connectionList.GetCount();
		for(i=0; i<length; i++)
		{
		socket = m_connectionList.GetAt(m_connectionList.FindIndex(i));
		if(socket == wParam)
		{
		m_connectionList.RemoveAt(m_connectionList.FindIndex(i));
		closesocket(socket);
		return 0;

		}
		}
		//m_connectionList.RemoveHead();

		return 0;

		}

		default:
		m_inbox += "an error has occured with a client\r\n";
		GetDlgItem(IDC_DISPLAY_EDIT12)->SetWindowTextW(m_inbox);
		m_editDisplayM.LineScroll(m_editDisplayM.GetLineCount());
		return 0;
	}
}

#endif

void CmfctcpaDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	int hour=CTime::GetCurrentTime().GetHour();
	static int time_flag=0;
	if (hour>=m_editStartTime  && hour < m_editEndtime)
	{
		time_flag = 3;
	}
	else 
		time_flag++;

	if (time_flag == 3)
	{
		int length = m_modushandle.m_modbuslist.GetCount();
		for (int i=0 ; i<length; i++)
		{		
			m_modushandle.ModbusSend(i);
		}
		time_flag = 0;
	}

	CDialogEx::OnTimer(nIDEvent);

}
