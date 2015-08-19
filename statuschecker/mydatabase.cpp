// MyDatabase.cpp : implementation file
//

#include "stdafx.h"

#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <iostream>
#include "MyDatabase.h"
#include "myrecordset.h"
// CMyDatabase

CMyDatabase::CMyDatabase()
{   //¹¹Ôìº¯Êý
	m_nPort = 1521;
	m_strServer = "localhost";
	m_pConnection = NULL;
}

CMyDatabase::~CMyDatabase()
{
    Close();
	if (m_pConnection != NULL)
	{
		m_pConnection.Release();
		m_pConnection = NULL;
	}
}



void CMyDatabase::SetDatabase(LPCSTR strConnect)
{


	Close();

	m_strDatabase=strConnect;

}

LPCSTR CMyDatabase::GetUserName()
{
	return m_strUserName.c_str();
}

void CMyDatabase::SetUserName(LPCSTR strUserName)
{
	m_strUserName=strUserName;
}

LPCSTR CMyDatabase::GetPassword()
{
	return m_strPassword.c_str();
}

void CMyDatabase::SetPassword(LPCSTR strPassword)
{
	m_strPassword=strPassword;
}


BOOL CMyDatabase::Open()
{
	TCHAR strFileName[MAX_PATH] = { 0 };

	::GetModuleFileName(NULL, strFileName, MAX_PATH);
	TCHAR* pEnd = _tcsrchr(strFileName, _T('\\'));
	if (pEnd != NULL)
	{
		*pEnd = _T('\0');
	}
	if (_tcschr(strFileName, _T(')')) != NULL)
	{
		return FALSE;
	}

	if (IsOpen())
	{
		Close();
	}

	try
	{
		m_pConnection.CreateInstance(__uuidof(ADODB::Connection));

		boost::format fomatter("Provider=OraOLEDB.Oracle.1;"
			"User ID=%1%;Password=%2%;"
			"Data Source=(DESCRIPTION=(ADDRESS_LIST=(ADDRESS=(PROTOCOL=TCP)(HOST=%3%)(PORT=%4%)))(CONNECT_DATA=(SERVICE_NAME='%5%')));"
			"Persist Security Info=true");

		fomatter %m_strUserName.c_str() % m_strPassword.c_str()
			% m_strServer.c_str() %m_nPort %m_strDatabase.c_str();

		HRESULT hr = m_pConnection->Open(_bstr_t(fomatter.str().c_str()), _bstr_t(m_strUserName.c_str()), _bstr_t(m_strPassword.c_str()), ADODB::adModeUnknown);

		return SUCCEEDED(hr);

	}
	catch (_com_error &e)
	{
		std::wcout << (LPCWSTR)e.Description() << std::endl;
	}
	catch (...)
	{
	}
	return FALSE;
}

void CMyDatabase::SetServer(LPCSTR strServer)
{
	m_strServer = strServer;
}

void CMyDatabase::Close()
{
	if (m_pConnection)
	{
		if (IsOpen())
		{
			m_pConnection->Close();
		}
	}
}
bool CMyDatabase::IsOpen()
{
	if (m_pConnection)
		if (m_pConnection->GetState() != ADODB::adStateClosed)
            return true;

	return false;
}



BOOL CMyDatabase::ExecuteQuery(LPCSTR strSQL,CMyRecordset& rs)
{
	try
	{
		if(m_pConnection)
		{
			return rs.Open(strSQL,this);
		}
	}
	catch (_com_error&)
	{
	}
	return FALSE;
}
