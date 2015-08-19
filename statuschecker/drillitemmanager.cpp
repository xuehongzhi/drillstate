#include "stdafx.h"
#include "drillitemmanager.h"

DrillStatus CDrillItemManager::GetStatus(TCHAR* lpstrTime)
{
	return UNKOWN;
}

DrillStatus CDrillItemManager::GetStatus()
{
	int i=m_Items.size()-1;
	CDrillItem& item1 = m_Items[i];
	DrillStatus st = GetStatus();
	if (st!=UNKOWN&&st!=APPEND_TUEBE)
	{
		return st;
	}

	for ( ; i>=0; --i)
	{
		st = item1.GetStatus(m_Items[i-1]);
		if (st!=UNKOWN&&st!=APPEND_TUEBE)
		{
			return st;
		}
	}
	return st;
}
