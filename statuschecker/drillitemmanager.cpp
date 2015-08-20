#include "stdafx.h"
#include "drillitemmanager.h"
#include <sstream>
#include <ATLComTime.h>
#include "mydatabase.h"
#include "myrecordset.h"
#include "drillstatemanager.h"


CDrillItemManager::CDrillItemManager():m_nTimeSpan(30)
{

}

CDrillItemManager::~CDrillItemManager()
{

}

DrillStatus CDrillItemManager::GetStatus(CMyDatabase* pDatabase,TCHAR* szWell,TCHAR* lpszTime)
{
	COleDateTime beginTime;
	if (!beginTime.ParseDateTime(lpszTime))
	{
		return UNKOWN;
	}

	COleDateTime endTime = beginTime+COleDateTimeSpan(0,0,0,m_nTimeSpan);
	return GetStatus(pDatabase,szWell,beginTime,endTime);
}

DrillStatus CDrillItemManager::GetStatus(CMyDatabase* pDatabase,TCHAR* szWell,COleDateTime& beginTime,COleDateTime& endTime)
{
	
	std::stringstream ss;
	ss<<"select time,depth as 最大井深,bitdepth as 钻头深度,spp as 泵压,wob as 钻压,woh as 大钩负荷 from LTD_";
	ss<<szWell;
	ss<<" where time between '"<<beginTime.Format("%Y-%m-%d %H:%M:%S")<<"' and '"<< endTime.Format("%Y-%m-%d %H:%M:%S")<<"' order by time";

	CMyRecordset rs;
	if (!rs.Open(CString(ss.str().c_str()),pDatabase))
	{
		return UNKOWN;
	}
	
   
	while (!rs.IsEOF())
	{
		CDrillItem item;
		std::string szTime;
		rs.GetValue("time",szTime);
		COleDateTime dtTime;
		dtTime.ParseDateTime(szTime.c_str());
		item.m_curTime = dtTime.m_dt;

		rs.GetValue("最大井深",	item.m_fDepth);
		rs.GetValue("钻头深度",	item.m_fBitDepth);
		rs.GetValue("泵压",	item.m_fSpp);
		rs.GetValue("钻压",	item.m_fWob);
		rs.GetValue("大钩负荷",	item.m_fBkh);

	
		m_Items.push_back(item);
		rs.MoveNext();
	}


	return CDrillStateManager::Instance().GetStatus(m_Items);
}

