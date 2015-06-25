#include "stdafx.h"
#include "myrecordset.h"
#include "mydatabase.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//class CMyRecordset

CMyRecordset::CMyRecordset():m_pRecordset(nullptr)
{

}
CMyRecordset::~CMyRecordset()
{
}

void CMyRecordset::SetRecordSet(ADODB::_RecordsetPtr pRecordset)
{
	m_pRecordset = pRecordset;
}

int CMyRecordset::GetRecordCount()
{
	return m_pRecordset->RecordCount;
}

BOOL CMyRecordset::Open(CString sql,CMyDatabase* pDatabase)
{
	Close();

		try
		{
			m_pRecordset.CreateInstance(__uuidof(ADODB::Recordset));
			ADODB::LockTypeEnum lockMethod = ADODB::adLockOptimistic;
			m_pRecordset->CursorLocation = ADODB::adUseClient;

			m_pRecordset->Open(_bstr_t(sql), _variant_t((IDispatch *)pDatabase->GetConnection(), true), ADODB::adOpenKeyset, lockMethod, ADODB::adCmdText);

			if ((m_pRecordset->State&ADODB::adStateOpen) == 0)
			{
				m_pRecordset.Release();
				return FALSE;
			}
			if (m_pRecordset->GetRecordCount() < 0)
			{
				m_pRecordset->Close();
				m_pRecordset.Release();
				return FALSE;
			}
			return TRUE;
		}
		catch (_com_error &e)
		{
			if (m_pRecordset != NULL)
			{
				if (m_pRecordset->State&ADODB::adStateOpen)
					m_pRecordset->Close();
				m_pRecordset.Release();
			}
			return FALSE;
		}
		catch (...)
		{
			if (m_pRecordset != NULL)
			{
				if (m_pRecordset->State&ADODB::adStateOpen)
					m_pRecordset->Close();
				m_pRecordset.Release();
			}
			return FALSE;
		}

}

BOOL CMyRecordset::GetValue(LPCSTR fieldname, std::string &strValue)
{
	USES_CONVERSION;
	try
	{
		_variant_t var=m_pRecordset->GetCollect(_variant_t(fieldname));
		if(var.vt==VT_EMPTY || var.vt==VT_NULL)
			return FALSE;

		if(var.vt==VT_BOOL)
		{
			if(var.boolVal) 
				strValue="TRUE";
			else
				strValue="FALSE";
			return TRUE;
		}

		var.ChangeType(VT_BSTR);
		strValue=OLE2A(var.bstrVal);
	}
	catch(_com_error& )
	{

	}
	return  TRUE;
}
BOOL CMyRecordset::GetValue(LPCSTR fieldname, float& dValue)
{
	dValue =FLT_MAX;
	double dTemp = dValue;
	if (!GetValue(fieldname,dTemp))
	{
		return FALSE;
	}
	dValue = (float)dTemp;
	return TRUE;
}

BOOL CMyRecordset::GetValue(LPCSTR fieldname, double& dValue)
{
	USES_CONVERSION;
	try
	{
		_variant_t var=m_pRecordset->GetCollect(_variant_t(fieldname));
		if(var.vt!=VT_R8)
		{
			var.ChangeType(VT_R8);
		}
		dValue = var.dblVal;
		return TRUE;
	}
	catch(_com_error& )
	{
	}
	return FALSE;
}


BOOL CMyRecordset::GetValue(LPCSTR fieldname, bool& bValue)
{
	USES_CONVERSION;
	try
	{
		_variant_t var = m_pRecordset->GetCollect(_variant_t(fieldname));
		if (var.vt != VT_BOOL)
		{
			var.ChangeType(VT_BOOL);
		}
		bValue = var.boolVal;
		return TRUE;
	}
	catch (_com_error&)
	{
	}

	return FALSE;
}

BOOL CMyRecordset::GetValue(LPCSTR fieldname, COleDateTime& timeValue)
{
	timeValue.SetStatus(COleDateTime::null);
	try
	{
		_variant_t var=m_pRecordset->GetCollect(_variant_t(fieldname));
		if(var.vt==VT_EMPTY || var.vt==VT_NULL)
			return FALSE;

		if (var.vt != VT_DATE)
		{
			var.ChangeType(VT_DATE);
		}
	
		timeValue = var.date;
		return TRUE;
	
	}
	catch(_com_error& )
	{
	
	}
	return FALSE;
}

BOOL CMyRecordset::GetValue(LPCSTR fieldname, short& iValue)
{
	long l;
	if(!GetValue(fieldname,l))
		return FALSE;
	iValue=(short)l;
	return TRUE;
}
BOOL CMyRecordset::GetValue(LPCSTR fieldname, int& iValue)
{
	long l;
	if(!GetValue(fieldname,l))
		return FALSE;
	iValue=(int)l;
	return TRUE;
}
BOOL CMyRecordset::GetValue(LPCSTR fieldname, long& iValue)
{
	try
	{
		_variant_t var=m_pRecordset->GetCollect(_variant_t(fieldname));
		var.ChangeType(VT_I4);
		iValue=var.lVal;
		return TRUE;
	}
	catch(_com_error& )
	{
	
	}
	return FALSE;
}

bool CMyRecordset::MoveFirst()
{
	m_pRecordset->MoveFirst();
	return true;
}

bool CMyRecordset::MoveNext()
{
    m_pRecordset->MoveNext();
	return true;
}

BOOL CMyRecordset::IsEOF()
{
	return m_pRecordset->adoEOF;
}


void CMyRecordset::Close()
{
	if (m_pRecordset==nullptr)
	{
		return;
	}

	if (m_pRecordset->State & ADODB::adStateOpen)
	{
		m_pRecordset->Close();
	}
	m_pRecordset.Release();

}