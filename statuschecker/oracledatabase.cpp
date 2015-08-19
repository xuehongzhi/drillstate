#include "stdafx.h"
#include "DatabaseUtility.h"
#include "OracleDatabase.h"

COracleDatabase::COracleDatabase(void)
{
	m_nPort=1521;
	m_strDefaultServer=_T("localhost");
}

COracleDatabase::~COracleDatabase(void)
{
}

ADODB::_CommandPtr  COracleDatabase::GetCommandPointer()
{
	ADODB::_CommandPtr spCommand;
	if (spCommand == NULL)
	{
		HRESULT hr = spCommand.CreateInstance(__uuidof(ADODB::Command));
		if (FAILED(hr))
		{
			return NULL;
		}
		m_pConnection->CursorLocation = ADODB::adUseClient;
		spCommand->ActiveConnection = m_pConnection;
		spCommand->CommandType = ADODB::adCmdStoredProc;
	}
	return spCommand;
}

BOOL COracleDatabase::Open()
{
	TCHAR strFileName[MAX_PATH]={0};

	::GetModuleFileName(NULL,strFileName,MAX_PATH);
	TCHAR* pEnd = _tcsrchr(strFileName,_T('\\'));
	if (pEnd!=NULL)
	{
		*pEnd=_T('\0');
	}
	if (_tcschr(strFileName,_T(')'))!=NULL)
	{
		AfxMessageBox(_T("路径中含有),驱动程序无法正确解析,请选择没有)的路径重新安装"));
		return FALSE;
	}

	if(IsOpen())
	{
		Close();
	}

	if(m_strConnect.IsEmpty())
		return FALSE;

	try
	{
		CString strConnect=m_strConnect;
		strConnect.Trim();

		CString strDatasource;
		CString strDatabase;

		int l=strConnect.GetLength();
		if(l<7) return FALSE;
		for(int i=0;i<l;i++)
		{
			if(strConnect.GetAt(i)=='\\')
			{
				strDatasource=strConnect.Mid(1,i-2);
				strDatabase=strConnect.Mid(i+2,l-i-3);
				break;
			}
		}

		if (strDatasource.IsEmpty())
		{
			strDatasource=m_strDefaultServer;
		}
		CString str;
      
		str.Format(_T("Provider=OraOLEDB.Oracle.1;")
			_T("User ID=%s;Password=%s;")
			_T("Data Source=(DESCRIPTION=(ADDRESS_LIST=(ADDRESS=(PROTOCOL=TCP)(HOST=%s)(PORT=%d)))(CONNECT_DATA=(SERVICE_NAME='%s')));") 
			_T("Persist Security Info=true"),m_strUserName,m_strPassword,strDatasource,m_nPort,strDatabase);
		
		m_pConnection->Open(_bstr_t(str),_bstr_t(m_strUserName),_bstr_t(m_strPassword),ADODB::adModeUnknown);

		if(!IsOpen())
		{
			m_pConnection.Release();
			return FALSE;
		}
		UpdateInformation();
	}	
	catch(_com_error &e)
	{

		AfxMessageBox(e.Description());
		return FALSE;
	}
	catch(...)
	{
		AfxMessageBox(_T("Unknown Error!"));
		return FALSE;
	}

	return TRUE;
}

