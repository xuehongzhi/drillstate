#include "stdafx.h"
#include "AppendTubeState.h"
#include "drillitem.h"

CAppendTubeState::CAppendTubeState(void):CDrillState(APPEND_TUBE),m_tmSpan(0,0,10,0)
{

}


CAppendTubeState::~CAppendTubeState(void)
{

}

void CAppendTubeState::SetTimeSpan(int nMiniutes)
{
	m_tmSpan.SetDateTimeSpan(0,0,nMiniutes,0);
}

bool CAppendTubeState::Match(std::vector<CDrillItem>& items)
{
	int iSize = items.size();
	if (iSize<2)
	{
		return false;
	}
	CDrillItem&  item = items[iSize-1];
	if (!Match(item))
	{
		return false;
	}
	for (int i = iSize-2; i>=0; --i)
	{
		CDrillItem& item1 = items[i];
		COleDateTimeSpan tmSpan(item.m_curTime-item1.m_curTime);
		if (!Match(item1))
		{
			return true;
		}
		if (tmSpan>=m_tmSpan)
		{
			return false;
		}
	}

	return true;
}