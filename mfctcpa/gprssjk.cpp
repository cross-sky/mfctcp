// gprssjk.h : Cgprssjk ���ʵ��



// Cgprssjk ʵ��

// ���������� 2015��8��24��, 16:04

#include "stdafx.h"
#include "gprssjk.h"
IMPLEMENT_DYNAMIC(Cgprssjk, CRecordset)

Cgprssjk::Cgprssjk(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_writetime = L"";
	m_names = L"";
	m_data1 = L"";
	m_data2 = L"";
	m_nFields = 5;
	m_nDefaultType = dynaset;
}
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString Cgprssjk::GetDefaultConnect()
{
	return _T("DBQ=C:\\Users\\apple\\Documents\\Visual Studio 2010\\Projects\\mfctcpa\\mfctcpa\\liyaa.mdb;DefaultDir=C:\\Users\\apple\\Documents\\Visual Studio 2010\\Projects\\mfctcpa\\mfctcpa;Driver={Driver do Microsoft Access (*.mdb)};DBQ=path to mdb/accdb file;DriverId=25;FIL=MS Access;FILEDSN=C:\\Users\\apple\\Documents\\Visual Studio 2010\\Projects\\mfctcpa\\mfctcpa\\ssda.dsn;MaxBufferSize=2048;MaxScanRows=8;PageTimeout=5;SafeTransactions=0;Threads=3;UID=admin;UserCommitSync=Yes;");
}

CString Cgprssjk::GetDefaultSQL()
{
	return _T("[gprssjk]");
}

void Cgprssjk::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[time]"), m_writetime);
	RFX_Text(pFX, _T("[name]"), m_names);
	RFX_Text(pFX, _T("[data1]"), m_data1);
	RFX_Text(pFX, _T("[data2]"), m_data2);


}
/////////////////////////////////////////////////////////////////////////////
// Cgprssjk ���

#ifdef _DEBUG
void Cgprssjk::AssertValid() const
{
	CRecordset::AssertValid();
}

void Cgprssjk::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


