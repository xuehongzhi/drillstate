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

DrillStatus CDrillState::TestMatch(std::vector<CDrillItem>& items)
{
	if (!Match(items)&&m_pNext!=NULL)
	{
		return m_pNext->TestMatch(items);
	}
	return m_Status; 
}

bool  CDrillState::Match( CDrillItem& item)
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

bool CDrillState::Match(std::vector<CDrillItem>& items)
{
	if (items.size()==0)
	{
		return false;
	}
	return Match(items[items.size()-1]);
}