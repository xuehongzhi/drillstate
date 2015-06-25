#pragma once
#import "msado60.tlb" rename ("EOF", "adoEOF")
#import "c:\program files\common files\system\ado\msadox.dll"
#include <string>
class CMyRecordset;
// CMyDatabase command target
class  CMyDatabase
{
public:
	CMyDatabase();
	virtual ~CMyDatabase();
//Attributes

//Operations
public:

	void SetPort(int iPort) { m_nPort = iPort; }
	int GetPort(){ return m_nPort; }

	void SetDatabase(LPCSTR strConnect);

	LPCSTR GetUserName();
	void SetUserName(LPCSTR strUserName);

	LPCSTR GetPassword();
	void SetPassword(LPCSTR strPassword);

	void SetServer(LPCSTR strServer);

	bool IsOpen();
	BOOL Open();
	void Close();
	
	ADODB::_ConnectionPtr GetConnection(){ return m_pConnection; }
	BOOL ExecuteQuery(LPCSTR strSQL,CMyRecordset& rs);
private:
	std::string m_strUserName;
	std::string m_strPassword;
	int m_nPort;
	std::string  m_strServer;
	std::string m_strDatabase;

	ADODB::_ConnectionPtr m_pConnection;
};


