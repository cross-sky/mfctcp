#include "StdAfx.h"
#include "recsocker.h"
//#include "mfctcpaDlg.h"

#include "mfctcpa.h"
#include "mfctcpaDlg.h"
#include "gprssjk.h"

//#define IP_ADDRES "127.0.0.1"
//#define SPort		12001

#pragma comment(lib, "ws2_32.lib")
//using namespace std;


extern CmfctcpaDlg *pm_Dlg;

recsocker::recsocker(void)
{

}


recsocker::~recsocker(void)
{
}

int recsocker::StartServer(HWND hwnd,UINT port)
{
	m_uPort=port;
	m_hWnd=hwnd;

	WSADATA Wsa;
	if(m_hSocket != NULL)
	{
		//����Ѿ��������׽����ȹر�ԭ����
		closesocket(m_hSocket);
		m_hSocket = NULL;
	}
	if(m_hSocket == NULL)
	{
		//�����µ��׽��֣������Ǵ����������͵��׽���
		if (WSAStartup(MAKEWORD(2,2), &Wsa) != 0)
		{
			//		cout<<"init failed"<<endl;
			return -1;
		}
		m_hSocket = socket(AF_INET, SOCK_STREAM,0);
		ASSERT(m_hSocket != NULL);
		
		//if(WSAAsyncSelect(m_hSocket, m_hWnd, SER_MESSAGE, FD_ACCEPT|FD_READ|FD_WRITE|FD_CLOSE)>0)
		//	AfxMessageBox(TEXT("error select"))		
	}
	m_addr.sin_family = AF_INET;
	m_addr.sin_addr.S_un.S_addr = INADDR_ANY;
	m_addr.sin_port = htons(m_uPort);
	
	int ret = 0;
	int error = 0;
	//��һ���׽��ֵ������ĵ�ַ
	ret = bind(m_hSocket, (LPSOCKADDR)&m_addr, sizeof(m_addr));

	if(ret == SOCKET_ERROR)
	{	//�󶨴���
		AfxMessageBox(TEXT("Binding Error"));
		return FALSE;
	}

	//��ʼһ���������̣��ȴ��ͻ�������
	
	if(WSAAsyncSelect(m_hSocket,hwnd,SER_MESSAGE,FD_ACCEPT|FD_READ|FD_WRITE|FD_CLOSE) >0)
		AfxMessageBox(TEXT("wsaasynclect Error"));

	ret = listen(m_hSocket, 5);    //����ĵڶ���������ʾ���֧�ֵĿͻ�������

	if(ret == SOCKET_ERROR)
	{	//listenʧ��
		AfxMessageBox(TEXT("Listen Error"));
		return FALSE;
	}
	//AfxGetApp()->m_pMainWnd->GetDlgItem(IDC_LINKSTATUS_EDIT8)->SetWindowTextW(_T("hello"));

	pm_Dlg->m_modushandle.m_nodenum = 0;
	CString onlink;
	onlink.Format(_T("%d"),pm_Dlg->m_modushandle.m_nodenum);
	pm_Dlg->m_editOnLink.SetWindowTextW(onlink);

	return TRUE;

}

void recsocker::WatchConnect(void)
{
	SOCKET clientSocket;
	sockaddr_in clientAddr;
	
	int addrlen = sizeof(clientAddr);
	//SOCKET_ARRAY m;
	while(true)
	{
		clientSocket = accept(m_hSocket,(SOCKADDR*)&clientAddr,&addrlen);
		if (clientSocket == INVALID_SOCKET)
		{
			break;
		}

	}
}

int recsocker::ReadFileData()
{
#ifdef vera

	string t_file = "test.txt";
	string tstring;
	m_infile.open(t_file.c_str(),ios::in);//
	if (!m_infile)
	{
		return -1;//file open error
	}

	char i=0;
	CString tbox;
	while(m_infile.peek() != EOF)
	{
		getline(m_infile,t_file);
		t_file += "\r\n";
		m_definelist.AddHead(t_file);
		tstring += t_file;
		i++;
	}

	pm_Dlg->m_editDisplayM.GetWindowTextW(tbox);
	//tbox2.Format(TEXT("%s"),tstring);
	CString tbox2(tstring.c_str());
	tbox +=tbox2;
	m_infile.close();
	pm_Dlg->m_editDisplayM.SetWindowText(tbox);

	return i;

#endif // vera

#ifdef verb

	//����set�ļ�
	string t_file = "set.txt";
	string tstring;
	m_infile.open(t_file.c_str(),ios::in);//
	if (!m_infile)
	{
		AfxMessageBox(TEXT("set.txt not find"));		
		return -1;//file open error
	}

	//���֮ǰ��socket��
	byte nlist=pm_Dlg->m_modushandle.m_modbuslist.GetCount();
	if (  nlist > 0 )
	{
		//pm_Dlg->m_modushandle.m_modbuslist.RemoveAll();
		modbus_data_t *m_point;

		for (byte i=0; i<nlist; i++)
		{
			m_point=&pm_Dlg->m_modushandle.m_modbuslist.GetAt(pm_Dlg->m_modushandle.m_modbuslist.FindIndex(i));
			if (m_point->socketData != 0)
			{
				closesocket(m_point->socketData);
			}
			
		}
		pm_Dlg->m_modushandle.m_modbuslist.RemoveAll();
	}

	char i=0;
	CString tbox;
	stringstream t_strstream;
	string t_str;
	modbus_data_t t_point;

	//�����ļ�
	while(m_infile.peek() != EOF)
	{
		memset(&t_point,0,sizeof(t_point));
		getline(m_infile,t_file);//��һ�У������س�ֹͣ

		t_strstream.clear();
		t_strstream.str("");
		t_strstream << t_file;
		t_strstream >> t_str;
		t_point.IDstr = t_str; //1.ʶ��� id0 id1 id��0��ʼ��[0]=faΪ�Զ����ʽ,����modbus(0a)

		t_strstream >> t_str;
		t_point.dbstr=t_str;//�������ݿ�����

		byte si=0;
		//�����ո�ֹͣ
		while(t_strstream >> t_str)
		{
			char*  tchar = (char*)t_str.c_str();
			pm_Dlg->m_modushandle.strtohex(t_point.senddata[si],(byte*)tchar,ModbusSendLegth*2);	
			//У����[0]��ʼ
			//��crc�������Զ����ʽ����modbus���˴�����
			int err = pm_Dlg->m_modushandle.Crc16(t_point.senddata[si++],ModbusSendLegth-2);//length������crcλ
			if (err < 0)
			{
				AfxMessageBox(TEXT("senddata crc error"));	
				m_infile.close();
				return -1;
			}
		}
		t_point.nodenum = si;
		pm_Dlg->m_modushandle.m_modbuslist.AddTail(t_point);
		
		t_file += "\r\n";
		//m_definelist.AddHead(t_file);
		tstring += t_file;
		i++;
	}


	m_infile.close();
	return i;
#endif // verb

}



ModbusHandle::ModbusHandle(void)
{

}

ModbusHandle::~ModbusHandle(void)
{

}


int  ModbusHandle::ModbusSend(int gprsnode)
{
	
#ifdef vera


	//HWND m_hwnd = hwnd;
	modbus_data_t *m_point = &m_modbuslist.GetAt(m_modbuslist.FindIndex(gprsnode));
	//���͸�ʽ�� ID ������ ������ʼ��ַ�� ������ʼ��ַ�� ���ݳ��ȸ� ���ݳ��ȵ� crc�� crc��
	//POSITION pos = m_modbuslist.FindIndex(i);

	if ((*m_point).status < 0)
	{
		closesocket((*m_point).socketData);
		//m_modbuslist.FreeNode();
		m_modbuslist.RemoveAt(m_modbuslist.FindIndex(gprsnode));
		//delete m_point;
		return -1;
	}

	if ((*m_point).status == 0)
	{
		return -1;
	}

	int t_flagsend = (*m_point).flagSend;
	int t_lastindex =(*m_point).index;



	if (t_flagsend >= 1)
	{
		t_lastindex++;
		if (t_lastindex >= m_point->nodenum)
		{
			t_lastindex=0;
		}

		//�����־λ
		int err = Crc16((*m_point).senddata[t_lastindex],ModbusSendLegth-2);//length������crcλ
		if (err < 0)
		{
			return -1;
		}

		if (t_lastindex == 0)
		{
			SaveData(m_point);
		}

		send((*m_point).socketData,(char*)(*m_point).senddata[t_lastindex],ModbusSendLegth,0);
		(*m_point).index = t_lastindex;
		(*m_point).flagSend = 1 ;//��Ƿ���
		(*m_point).flagrec[t_lastindex][0]=1;

	}
	else
	{
		send((*m_point).socketData,(char*)(*m_point).senddata[t_lastindex],ModbusSendLegth,0);
		(*m_point).flagSend++;//����+1
		(*m_point).flagrec[t_lastindex][0]=1;
		//(*m_point).flagrec[trdata[0]-1][0] = 2
	}

	return 0;

#endif // vera

#ifdef verb

	modbus_data_t *m_point = &m_modbuslist.GetAt(m_modbuslist.FindIndex(gprsnode));
	//���͸�ʽ�� ID ������ ������ʼ��ַ�� ������ʼ��ַ�� ���ݳ��ȸ� ���ݳ��ȵ� crc�� crc��
	//POSITION pos = m_modbuslist.FindIndex(i);

	if (m_newsocket != 0)
	{
		//����tcp���ӣ����η���pos��senddata[1]
		//��һ��������Ϊ�ɼ�������crcУ�飬�������Զ����ʽ���˴������ж�
		if ( (*m_point).status == 0)
		{
			send(m_newsocket,(char*)(*m_point).senddata[0],ModbusSendLegth,0);
			return 0;
		}
	}

	if ((*m_point).status < 0)//sock�رգ����socket
	{
		closesocket((*m_point).socketData);
		//m_modbuslist.RemoveAt(m_modbuslist.FindIndex(gprsnode));
		m_point->socketData = 0;
		m_point->status = 0;
		m_point->index = 0;
		m_point->flagSend=0;

		pm_Dlg->m_modushandle.m_nodenum--;
		CString onlink;
		onlink.Format(_T("%d"),pm_Dlg->m_modushandle.m_nodenum);
		pm_Dlg->m_editOnLink.SetWindowTextW(onlink);

		//�豸�Բɼ�����������Ϊ״̬���������Զ����ʽ���˴������жϣ��жϵ�1λ״̬
		if (m_point->senddata[0][1] == 1)
		{
			pm_Dlg->m_editLinkStatus.SetWindowTextW(_T("unlinked"));
			

		}

		return -1;
	}


	if ((*m_point).status == 0)
	{
		return -1;
	}


	int t_flagsend = (*m_point).flagSend;
	int t_lastindex =(*m_point).index;

	if (t_lastindex == m_point->nodenum-1)
	{
		SaveData(m_point);
	}

	if (t_flagsend >= 0)
	{
		//���ұ��ڵ���һ���豸
		t_lastindex++;
		if (t_lastindex >= m_point->nodenum)
		{
			t_lastindex=0;
		}

		if (m_point->senddata[t_lastindex][0] == ProtocalSelf)
		{
			(*m_point).index = t_lastindex;
			(*m_point).flagSend = 1 ;//��Ƿ���
			(*m_point).flagrec[t_lastindex][0]=1;

			//Ŀǰֻ������һ���Զ����Э�飬�ɼ���������洢���¶����ݣ������������Զ���Э������ģ�
			send((*m_point).socketData,(char*)(*m_point).senddata[t_lastindex],ProtocalSelfSendLen,0);

			return 0;

		}

		//��һ�ζ���set�ļ���У�飬�������Ͳ���У��
		//�����־λ
		//int err = Crc16((*m_point).senddata[t_lastindex],ModbusSendLegth-2);//length������crcλ
		//if (err < 0)
		//{
		//	return -1;
		//}		
		//������senddata[][1]��ʼ
		//Ĭ�ϵ�modbus����Э���ʽ 01 03 00 02 00 01 crcl crch��8�ֽ�
		send((*m_point).socketData,(char*)(*m_point).senddata[t_lastindex],ModbusSendLegth,0);
		(*m_point).index = t_lastindex;
		(*m_point).flagSend = 1 ;//��Ƿ���
		(*m_point).flagrec[t_lastindex][0]=1;

	}
	else
	{
		send((*m_point).socketData,(char*)(*m_point).senddata[t_lastindex],ModbusSendLegth,0);
		(*m_point).flagSend++;//����+1
		(*m_point).flagrec[t_lastindex][0]=1;
		//(*m_point).flagrec[trdata[0]-1][0] = 2
	}

	return 0;

#endif // verb

}

int ModbusHandle::ModbusRecv(int gprsnode)
{

#ifdef vera

	//POSITION pos = m_modbuslist.FindIndex(i);
	//Point m_point = 

	modbus_data_t *m_point = &m_modbuslist.GetAt(m_modbuslist.FindIndex(gprsnode));
	//modbus_data_t *mdat=&m_modbuslist.GetAt(m_modbuslist.FindIndex(gprsnode));


	if ((*m_point).status < 0)
	{

		//m_modbuslist.FreeNode(m_point);

		return -1;
	}
	else if ((*m_point).status == 0)
	{
		byte temp[10];
		int len = recv((*m_point).socketData,(char*)temp,10,0);
		ModbusBind(m_point,temp);


#if 0
		byte temp[10];

		int len = recv((*m_point).socketData,(char*)temp,10,0);

		switch(temp[1])
		{
		case 1:
			{
				int i;
				for (i =0; i<8; i++)
				{
					if (temp[i] != info1[i])
					{
						break;
					}

				}




				if (i==8)
				{
					(*m_point).status = 1;
					pm_Dlg->m_editLinkStatus.SetWindowTextW(_T("linked"));
					memccpy((*m_point).senddata[gprsnode],ID1dress1,8,sizeof(ID1dress1));
					(*m_point).ID = temp[1];
					return 0;

				}
				else
					(*m_point).status =-1;
				return -1;
			}		

		default: return 0;
		}	
#endif

	}
	else	//
	{

		int t_flagsend = (*m_point).flagSend;
		//int t_lastindex =(*m_point).index;
		byte  t_lastindex;


		byte trdata[DatModbus];
		int len = recv((*m_point).socketData,(char*)trdata,50,0);

		for (byte i=0; i< (*m_point).nodenum; i++)
		{
			if (trdata[0] == (*m_point).senddata[i][0])
			{
				t_lastindex =i;
				break;
			}
		}


		if (len <= 0)
		{
			//����ʧ��
			return -1;

		}
		//              senddata[i][1];


		if (trdata[1] != (*m_point).senddata[t_lastindex][1])//modbus �����쳣
		{
			//�쳣��ʾ
			return -1;
		}

		// ID(1) ������(1)(�쳣ʱ���λ��1) ���ݸ���(1) ����1 ����2 ......У�����λ У�����λ

		int err = Crc16(trdata, len -2);//[2]

		if (err < 0)
		{
			//crc error
			return -1;
		}


		else
		{
			//���ݴ���
			memcpy((*m_point).recvdata[t_lastindex],trdata,len);
			(*m_point).flagSend = 5;
			(*m_point).flagrec[t_lastindex][0] = 2;


			byte m_ID = trdata[0];
			switch(m_ID)
			{
			case 1:
				//�ɼ���
				{

					char datalen = trdata[2];
					byte *updata = &trdata[3];
					USHORT tdata[10];
					for (int i=0;i<datalen;i++ )
					{
						tdata[i]= (((*updata)&0xff)<<8)|(*(updata+1)&0xff);
						updata+=2;
					}
					CString st;
					CString tstr;
					pm_Dlg->m_editDisplayM.GetWindowText(tstr);
					tstr += (*m_point).IDstr.c_str();
					tstr += ":";

					//st.Format(TEXT("%x"),m_ID);
					//pm_Dlg->m_editpara1.SetWindowText(st);
					//tstr += st;

					tstr += "ID:";
					st.Format(TEXT("%x"),trdata[0]);
					pm_Dlg->m_editpara1.SetWindowText(st);
					tstr += st;
					tstr += ":";


					st.Format(TEXT("%x"),tdata[0]);
					pm_Dlg->m_editpara1.SetWindowText(st);
					tstr += st;

					st.Format(TEXT("%x"),tdata[1]);
					pm_Dlg->m_editpara2.SetWindowText(st);
					tstr += st;

					st.Format(TEXT("%x"),tdata[2]);
					pm_Dlg->m_editpara3.SetWindowText(st);
					tstr += st;

					st.Format(TEXT("%x"),tdata[3]);
					pm_Dlg->m_editpara4.SetWindowText(st);
					tstr += st;

					tstr += "\r\n";
					pm_Dlg->m_editDisplayM.SetWindowText(tstr);
					pm_Dlg->m_editDisplayM.LineScroll(pm_Dlg->m_editDisplayM.GetLineCount());

					return 0;
				}
			case 2:
				//�����¶�
				return 0;
			case 3:
				//�����
				return 0;
			case 4:
				//
				return 0;

			case 5:
				//
				return 0;

			default:
				return 0;

			}

		}
	}
	//display


#endif // vera
	 

#ifdef verb

	modbus_data_t *m_point = &m_modbuslist.GetAt(m_modbuslist.FindIndex(gprsnode));

	if ((*m_point).status < 0)
	{
		return -1;
	}
	else if ((*m_point).status == 0)
	{
		return -1;
		//byte temp[10];
		//int len = recv((*m_point).socketData,(char*)temp,10,0);
		//ModbusBind(m_point,temp);

	}
	else	//
	{

		int t_flagsend = (*m_point).flagSend;
		byte  t_lastindex;


		byte trdata[DatModbus];
		int len = recv((*m_point).socketData,(char*)trdata,DatModbus,0);

		for (byte i=0; i< (*m_point).nodenum; i++)//�ҵ���Ӧ��index
		{
			if (trdata[0] == (*m_point).senddata[i][0])//��1λΪʶ��ţ����ͽ�����ͬ
			{
				t_lastindex =i;
				break;
			}
		}

		if (len <= 0)
		{
			//����ʧ��
			return -1;
		}
		
		//�Զ���Э����գ�ֱ�Ӳ�ѯ�ǲ����Զ���Э�飬���ǻ��߽��մ���ת�����洦��(�˳�)
		if (trdata[0] == ProtocalSelf)
		{
	
			//���������¶����ݣ�5b, 01 0x34(�ֽ���) t0(4��3) cr 
			char tdisp[50]={0};
			memcpy((*m_point).recvdata[t_lastindex],trdata,ProtocalSelfRecvLen);
			(*m_point).flagSend = 5;
			(*m_point).flagrec[t_lastindex][0] = 2;
			hextostr((byte*)tdisp,trdata,ProtocalSelfRecvLen);
				
			CString tstrdisp;
			pm_Dlg->m_editDisplayM.GetWindowText(tstrdisp);
			tstrdisp += tdisp;
			tstrdisp +="\r\n";
			pm_Dlg->m_editDisplayM.SetWindowText(tstrdisp);

			return 0;
			
		}

		//    senddata[i][1];
		if (trdata[1] != (*m_point).senddata[t_lastindex][1])//modbus �����쳣��//��1λΪ״̬��
		{
			//�쳣��ʾ
			return -1;
		}

		// ID(1) ������(1)(�쳣ʱ���λ��1) ���ݸ���(1) ����1 ����2 ......У�����λ У�����λ

		int err = Crc16(trdata, len -2);//crc�����ж��ǲ����Զ����ʽ

		if (err < 0)
		{
			//crc error
			return -1;
		}
		else
		{
			//���ݴ��� ��������			
			//��ǽ���
			(*m_point).flagSend = 5;
			(*m_point).flagrec[t_lastindex][0] = 2;
			memcpy((*m_point).recvdata[t_lastindex],trdata,len);


			byte m_ID = trdata[0];//����10Ϊ����
			switch(m_ID)
			{
			case 1:
				//�ɼ���
				{

					char datalen = trdata[2];
					byte *updata = &trdata[3];
					USHORT tdata[10];
					for (int i=0;i<datalen;i++ )
					{
						tdata[i]= (((*updata)&0xff)<<8)|(*(updata+1)&0xff);
						updata+=2;
					}
					CString st;
					CString tstr;
					pm_Dlg->m_editDisplayM.GetWindowText(tstr);

					if (tstr.GetLength() > 1000)
					{
						tstr="";
					}

					tstr += (*m_point).IDstr.c_str();
					tstr += ":";


					tstr += "ID:";
					st.Format(TEXT("%x"),trdata[0]);
					pm_Dlg->m_editpara1.SetWindowText(st);
					tstr += st;
					tstr += ":";


					st.Format(TEXT("%x"),tdata[0]);
					pm_Dlg->m_editpara1.SetWindowText(st);
					tstr += st;

					st.Format(TEXT("%x"),tdata[1]);
					pm_Dlg->m_editpara2.SetWindowText(st);
					tstr += st;

					st.Format(TEXT("%x"),tdata[2]);
					pm_Dlg->m_editpara3.SetWindowText(st);
					tstr += st;

					st.Format(TEXT("%x"),tdata[3]);
					pm_Dlg->m_editpara4.SetWindowText(st);
					tstr += st;

					tstr += "\r\n";
					pm_Dlg->m_editDisplayM.SetWindowText(tstr);
					pm_Dlg->m_editDisplayM.LineScroll(pm_Dlg->m_editDisplayM.GetLineCount());

					return 0;
				}
			case 2:
				//�����¶�
				return 0;
			case 3:
				//�����
				return 0;
			case 4:
				//
				return 0;

			case 5:
				//
				return 0;

			default:
				return 0;

			}

		}
	}
	//display

#endif // verb

}

unsigned int ModbusHandle::Crc16(byte *updata, char len)
{
//	POSITION pos = m_modbuslist.FindIndex(i);

	if (*updata == ProtocalSelf)
	{
		return 0;
	}

	byte uchCRCHi=0xff; 
	byte uchCRCLo=0xff;
	byte uindex;
	unsigned int crcvalue;
	while(len--)
	{
		uindex=uchCRCHi^*updata++;
		uchCRCHi=uchCRCLo^auchCRCHi[uindex];
		uchCRCLo=auchCRCLo[uindex];
	}
	crcvalue = uchCRCHi<<8|uchCRCLo;
	if (uchCRCHi == *updata && uchCRCLo == *(updata+1))
	{
		//crc ok;
		return 0;

	}

	else 
		return -1;
	
}


int ModbusHandle::ModbusBind(modbus_data_t *t_point,byte *recIDdata)
{
#ifdef vera
	stringstream tistr;
	CString tbox,tbox2;
	string tstring = "";
	string tlist;
	string recstr;

	tistr.str("");
	tistr.clear();

	for(int i=0;i<ModbusInfoLen;i++)
	{
		tistr<<*(recIDdata++);
	}
	tistr>>recstr;
	tistr<<recstr;

	pm_Dlg->m_editDisplayM.GetWindowTextW(tbox);
	StringArray* t_modbuslist= 	&pm_Dlg->m_server.m_definelist;
	//	ModBusTcpArray* t_modbushandle = &pm_Dlg->m_modushandle.m_modbuslist;

	POSITION pos = (*t_modbuslist).GetTailPosition();

	while(pos !=NULL)
	{
		tistr.str("");
		tistr.clear();
		tlist = (*t_modbuslist).GetPrev(pos);
		tstring += tlist;
		tstring += "\r\n";

		tistr<<tlist;
		tistr>>tlist;

		if (recstr == tlist)
		{
			//�ҵ����ϵ�id
			byte i=0;
			tistr>>tlist;
			(*t_point).IDstr = tlist;

			CTime strTime=CTime::GetCurrentTime();
			int nyear = strTime.GetYear();
			int nmonth = strTime.GetMonth();
			int nday = strTime.GetDay();

			m_savestr.str("");
			m_savestr.clear();
			m_savestr<<"logs\\"<<tlist<<"-"<<nyear<<"-"<<nmonth<<"-"<<nday<<".txt";
			m_savestr>>tlist;
			ofstream t_ofile(tlist.c_str());
			(*t_point).logname = tlist;


			while(tistr>>tlist)
			{
				char*  tchar = (char*)tlist.c_str();
				strtohex(t_point->senddata[i],(byte*)tchar,ModbusSendLegth*2);
				i++;
			}

			t_point->nodenum = i;
			tbox2 = tstring.c_str();
			tbox += tbox2;
			pm_Dlg->m_editDisplayM.SetWindowText(tbox);
			(*t_point).status = 1;
			//pm_Dlg->m_editLinkStatus.SetWindowTextW(_T("linked"));
			//memccpy((*m_point).senddata[gprsnode],ID1dress1,8,sizeof(ID1dress1));
			return 0;

		}
	}

	(*t_point).status =-1;
	return -1; //δ�ҵ�

#endif // vera

#ifdef verb

	byte *rdata=recIDdata;//���ã����Ӽ���


	byte trdata[DatModbus];//recv hex
	int len = recv(m_newsocket,(char*)trdata,DatModbus,0);

	if (len <= 0)
	{
		//����ʧ��
		return -1;
	}

	int err = Crc16(trdata, len -2);//[2]
	if (err < 0)
	{
		//crc error
		return -1;
	}

	int listlength = pm_Dlg->m_modushandle.m_modbuslist.GetCount();
	//modbus_data_t *t_point

	for (int i=0; i<listlength;i++)
	{
		t_point=&pm_Dlg->m_modushandle.m_modbuslist.GetAt(pm_Dlg->m_modushandle.m_modbuslist.FindIndex(i));
		if ((t_point->status == 0) && (t_point->senddata[0][0] == trdata[0]))
		{
			
			t_point->status = 1;				//���status ���m_newsocket,
			t_point->socketData = m_newsocket;
			memcpy(t_point->recvdata[0],trdata,len);
			m_newsocket = 0;
			t_point->clientAddr = m_newclientAddr;
			t_point->addrLen = m_newaddrLen;
			t_point->flagSend = 5;
			t_point->flagrec[0][0] = 2;


			CTime strTime=CTime::GetCurrentTime();
			int nyear = strTime.GetYear();
			int nmonth = strTime.GetMonth();
			int nday = strTime.GetDay();
			string tlist=t_point->IDstr;

			m_savestr.str("");
			m_savestr.clear();
			m_savestr<<"logs\\"<<tlist<<"-"<<nyear<<"-"<<nmonth<<"-"<<nday<<".txt";
			m_savestr>>tlist;
			ofstream t_ofile(tlist.c_str());
			(*t_point).logname = tlist;

			if (trdata[0] == 1)
			{
				CString onlink(t_point->IDstr.c_str());
				
				pm_Dlg->m_editLinkStatus.SetWindowTextW(onlink);

			}



			pm_Dlg->m_modushandle.m_nodenum++;
			CString onlink;
			onlink.Format(_T("%d"),pm_Dlg->m_modushandle.m_nodenum);
			pm_Dlg->m_editOnLink.SetWindowTextW(onlink);



			return 1;
		}
	}

	closesocket(m_newsocket);
	m_newsocket = 0;//δ֪tcp���ӣ��ر�֮
	return -1; //


#endif // verb

}

int ModbusHandle::strtohex(byte *dct,byte *string,byte len)
{
	if (len %2 !=0)
	{
		return -1;
	}

	byte high,low;
	byte didx=0,sidx;
	for(sidx=0; sidx<len;sidx+=2)
	{
		high = string[sidx];
		low = string[sidx+1];

		if (high>='0' && high<='9')
		{
			high -= '0';
		}
		else if (high>='A'&& high<='F')
		{
			high = high - 'A' + 10;
		}
		else if (high>='a'&&high<='f')
		{
			high = high-'a'+10;
		}
		else
			return -1;


		if (low>='0' && low<='9')
		{
			low -= '0';
		}
		else if (low>='A'&&low<='F')
		{
			low = low - 'A' + 10;
		}
		else if (low>='a'&&low<='f')
		{
			low = low-'a'+10;
		}
		else
			return -1;

		*(dct++) = high<<4 | low;
	}
	return 0;

}


int ModbusHandle::SaveData(modbus_data_t *m_point)
{
	m_savefile.open((*m_point).logname.c_str(),ios::app);
	if (!m_savefile)
	{
		AfxMessageBox(TEXT("logs file open error"));
		return -1;
	}
	
	string strdata;
	byte tlen;

	CTime strTime=CTime::GetCurrentTime();
	int nhour = strTime.GetHour();
	int nminute = strTime.GetMinute();
	int nsecond = strTime.GetSecond();
	m_savefile<<nhour<<":"<<nminute<<":"<<nsecond<<": ";

	
	vector<string> vtsrt;
	char tdct[50];
	

	for(char i=0; i< m_point->nodenum;i++)
	{
		char t=(*m_point).flagrec[i][0];
		if ( t== 2)
		{
			tlen = (*m_point).recvdata[i][2]+5;
			
			if (m_point->recvdata[i][0] == ProtocalSelf)
			{
				tlen = ProtocalSelfRecvLen;

			}
			//
			hextostr((byte*)tdct,&(*m_point).recvdata[i][0],tlen);
			m_savefile<<tdct;
			m_savefile<<" ";
			vtsrt.push_back(tdct);

		}
		else
		{
			m_savefile<<" "<<" ";
			vtsrt.push_back("0");
		}
	}
	parameter_float fpada;

	SaveParatoMdb(m_point,&fpada);

	m_savefile<<"\r\n";
	m_savefile.close();
	CString m_data0(vtsrt[0].c_str());
	CString m_data1(vtsrt[1].c_str());
	//CString m_ma1
	CString m_writetime=strTime.Format("%Y-%m-%d %H:%M:%S");

	CDatabase database;
	database.Open(NULL,FALSE,FALSE,_T("ODBC;DSN=gprs;server=127.0.0.1;Database=dbgprs;UID=natsuki;PWD=2009..summerwar"));
	if (!database.IsOpen())
	{
		AfxMessageBox(TEXT("mysql open error"));

	}

	CString strsql;
	//................//
	CString dbstr(m_point->dbstr.c_str());

	CString strFormat = _T("INSERT INTO %s(writetime,ma1, ma2, mv1, mv2, data1, data2,t1,t2,t3) \
						VALUES('%s','%.2f', '%.2f','%.2f','%.2f','%s', '%s','%.2f','%.2f','%.2f')");
	strsql.Format(strFormat,dbstr,m_writetime,fpada.ma[0],fpada.ma[1],fpada.ma[2],fpada.ma[3],m_data0,m_data1,fpada.tem[0],fpada.tem[1],fpada.tem[2]);

	database.ExecuteSQL(strsql);
	database.Close();

	return 0;

}

void ModbusHandle::hextostr(byte *dct,byte *str,byte len)
{


	byte h,l;

	for (int i=0;i<len;i++)
	{
		
		h=(0xf0&(*str))>>4;
		l=(0x0f&(*str));

		if (h<10)
		{
			*(dct)=h+'0';
		}
		else
		{
			*(dct)=h+'a'-10;
		}

		if (l<10)
		{
			*(dct+1)=l+'0';
		}
		else
		{
			*(dct+1)=l+'a'-10;
		}
		str++;
		dct+=2;

	}
	*dct = '\0';

}
void ModbusHandle::SaveParatoMdb(modbus_data_t* t_point, parameter_float *fdata)
{
	short int t_data[NumModbusNode];
	byte *updata,lendata; 
	byte t_id;
	
	for(byte i=0; i< t_point->nodenum;i++)
	{
		
		updata = t_point->recvdata[i];
		t_id = *updata % 10; //����10Ϊ��������
		lendata = *(updata+2)/2;
				
		if (t_point->recvdata[i][0] == ProtocalSelf)
		{
			updata+=10;//��Чλ��ʼ
			for (byte k=0;k<3;k++)
			{
				t_data[k]= ((*(updata+2)&0xff)<<8)|(*(updata+1)&0xff);				
				fdata->tem[k]=(float)t_data[k]/10.0;
				updata+=3;
			}
			continue;
		}

		updata+=3;
		switch(t_id)
		{
		case 1:
			{	//01 03 08 ff ff ff ff ff ff ff ff crcl crch
				for (byte k=0; k<lendata; k++ )
				{
					t_data[k]= (((*updata)&0xff)<<8)|(*(updata+1)&0xff);
					updata += 2;
					if (k< 2)
						(*fdata).ma[k] = ((float)t_data[k]/0x7fff)*24.0;
					else
						fdata->ma[k] = ((float)t_data[k]/0x7fff)*60.0;	
				}


				break;

			}
		case 2:
			{
				
				break;
			}
		case 3:
			{
				break;
			}

		default:
			{
				break;
			}
		}

	}
}