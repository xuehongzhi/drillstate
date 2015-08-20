#include "stdafx.h"
#include "drillitemmanager.h"
#include <sstream>
#include <ATLComTime.h>
#include "mydatabase.h"
#include "myrecordset.h"

DrillStatus CDrillItemManager::GetStatus(CMyDatabase* pDatabase,TCHAR* szWell,time_t beginTime,time_t endTime)
{
	
	std::stringstream ss;
	ss<<"select time,depth as 最大井深,bitdepth as 钻头深度,spp as 泵压,wob as 钻压,woh as 大钩负荷 from LTD_";
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

		rs.GetValue("最大井深",	item.m_fDepth);
		rs.GetValue("钻头深度",	item.m_fBitDepth);
		rs.GetValue("泵压",	item.m_fSpp);
		rs.GetValue("钻压",	item.m_fWob);
		rs.GetValue("大钩负荷",	item.m_fBkh);

	
		m_Items.push_back(item);
		rs.MoveNext();
	}


	return UNKOWN;
}

DrillStatus CDrillItemManager::GetStatus()
{
	return UNKOWN;
}
