#include "stdafx.h"
#include "drillstate.h"
#include "drillItem.h"
#include <float.h>

CDrillState::CDrillState(DrillStatus statcode):m_pNext(NULL),m_Status(statcode)
{
	m_fDepthGap[0]=0;
	m_fDepthGap[1]=FLT_MAX;

	m_fSpp[0]=0;
	m_fSpp[1]=FLT_MAX;

	m_fWob[0]=0;
	m_fWob[1]=FLT_MAX;

	m_fWoh[0]=0;
	m_fWoh[1]=FLT_MAX;
}


CDrillState::~CDrillState(void)
{

}

void CDrillState::SetDepthGap(float fMin,float fMax)
{
	m_fDepthGap[0] = fMax;
	m_fDepthGap[1] = fMin;
}


void CDrillState::SetSpp(float fMin,float fMax)
{
	m_fSpp[0] = fMax;
	m_fSpp[1] = fMin;
}

void CDrillState::SetWob(float fMin,float fMax)
{
	m_fWob[0] = fMax;
	m_fWob[1] = fMin;
}

void CDrillState::SetWoh(float fMin,float fMax)
{
	m_fWoh[0] = fMax;
	m_fWoh[1] = fMin;
}

void CDrillState::AddNextState(CDrillState* pNext)
{
	m_pNext = pNext;
}

DrillStatus CDrillState::TestMatch(const CDrillItem& item)
{
	if (!Match(item)&&m_pNext!=NULL)
	{
		return m_pNext->TestMatch(item);
	}
	return m_Status; 
}

bool CDrillState::Match(const CDrillItem& item)
{
	return item.GetDepthGap()<=m_fDepthGap[1]
	       && item.GetDepthGap()>=m_fDepthGap[0]
		   && item.m_fSpp <=m_fSpp[1]
		   && item.m_fSpp >= m_fSpp[0]
		   && item.m_fWob <= m_fWob[1]
		   && item.m_fWob >= m_fWob[0]
		   && item.m_fBkh <= m_fWoh[1]
		   && item.m_fBkh >= m_fWoh[0];

}