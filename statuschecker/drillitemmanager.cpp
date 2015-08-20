#include "stdafx.h"
#include "drillitemmanager.h"
#include <sstream>
#include <ATLComTime.h>
#include "mydatabase.h"
#include "myrecordset.h"

DrillStatus CDrillItemManager::GetStatus(CMyDatabase* pDatabase,TCHAR* szWell,time_t beginTime,time_t endTime)
{
	
	std::stringstream ss;
	ss<<"select time,depth as �����,bitdepth as ��ͷ���,spp as ��ѹ,wob as ��ѹ,woh as �󹳸��� from LTD_";
	ss<<szWell;
	ss<<" where time between "<<COleDateTime(beginTime).Format("%Y-%m_%d %H-%M-%S")<<" and "<< COleDateTime(endTime).Format("%Y-%m_%d %H-%M-%S");

	CMyRecordset rs;
	if (!rs.Open(CString(ss.str().c_str()),pDatabase))
	{
		return UNKOWN;
	}

	while (!rs.IsEOF())
	{
		CDrillItem item;
		COleDateTime dtTime;
		rs.GetValue("time",dtTime);

		item.m_curTime = dtTime.m_dt;

		rs.GetValue("�����",	item.m_fDepth);
		rs.GetValue("��ͷ���",	item.m_fBitDepth);
		rs.GetValue("��ѹ",	item.m_fSpp);
		rs.GetValue("��ѹ",	item.m_fWob);
		rs.GetValue("�󹳸���",	item.m_fBkh);

	
		m_Items.push_back(item);
		rs.MoveNext();
	}


	return UNKOWN;
}

DrillStatus CDrillItemManager::GetStatus()
{
	return UNKOWN;
}
