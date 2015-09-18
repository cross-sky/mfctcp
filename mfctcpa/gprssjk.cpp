// gprssjk.h : Cgprssjk 类的实现



// Cgprssjk 实现

// 代码生成在 2015年8月24日, 16:04

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
//#error 安全问题：连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
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
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[time]"), m_writetime);
	RFX_Text(pFX, _T("[name]"), m_names);
	RFX_Text(pFX, _T("[data1]"), m_data1);
	RFX_Text(pFX, _T("[data2]"), m_data2);


}
/////////////////////////////////////////////////////////////////////////////
// Cgprssjk 诊断

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


