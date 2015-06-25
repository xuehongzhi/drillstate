#pragma once
#include <string>
#include <ATLComTime.h>
#import "msado60.tlb" rename ("EOF", "adoEOF")
#import "c:\program files\common files\system\ado\msadox.dll"
class CMyDatabase;

class  CMyRecordset 
{
public:
	CMyRecordset();
	~CMyRecordset();

	
	BOOL Open(CString sql, CMyDatabase* pDatabase);
	void SetRecordSet(ADODB::_RecordsetPtr pRecordset);
	int GetRecordCount();

	BOOL GetValue(LPCSTR fieldname,std::string& strValue);
	BOOL GetValue(LPCSTR fieldname, double& dValue);
	BOOL GetValue(LPCSTR fieldname, bool& bValue);
	BOOL GetValue(LPCSTR fieldname, COleDateTime& timeValue);
	BOOL GetValue(LPCSTR fieldname, short& iValue);
	BOOL GetValue(LPCSTR fieldname, int& iValue);
	BOOL GetValue(LPCSTR fieldname, long& iValue);
	BOOL GetValue(LPCSTR fieldname, float& fValue);

	bool MoveFirst();
	bool MoveNext();
	BOOL IsEOF();
	void Close();

private:
	ADODB::_RecordsetPtr m_pRecordset;
};
