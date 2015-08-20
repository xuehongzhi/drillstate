#include "stdafx.h"
#include "drillstate.h"
#include "drillItem.h"
#include <float.h>

using namespace boost::icl;
CDrillState::CDrillState(DrillStatus statcode):m_pNext(NULL)
	,m_Status(statcode)
	,m_DepthInterval(0,FLT_MAX,interval_bounds::closed())
	,m_SppInterval(0,FLT_MAX,interval_bounds::closed())
	,m_WobInterval(0,FLT_MAX,interval_bounds::closed())
	,m_WohInterval(0,FLT_MAX,interval_bounds::closed())

{
	
}


CDrillState::~CDrillState(void)
{
}


bool CDrillState::LoadBounds(INTERVAL_TYPE inttype,	boost::icl::interval_bounds&  bounds)
{
	switch (inttype)
	{
	case OPEN_INTERVAL:
		bounds = boost::icl::interval_bounds::open();
		break;
	case RIGHT_INTERVAL:
		bounds = boost::icl::interval_bounds::right_open();
		break;
	case LEFT_INTERVAL:
		bounds = boost::icl::interval_bounds::left_open();
		break;
	case CLOSED_INTERVAL:
		bounds = boost::icl::interval_bounds::closed();
		break;
	default:
		break;
	}
	return true;
}

void CDrillState::SetDepthGap(float fMin,float fMax,INTERVAL_TYPE inttype)
{

	boost::icl::interval_bounds  bounds;
	LoadBounds(inttype,bounds);
	m_DepthInterval = boost::icl::construct<boost::icl::continuous_interval<float>>(fMin,fMax,bounds);

}


void CDrillState::SetSpp(float fMin,float fMax,INTERVAL_TYPE inttype)
{

	boost::icl::interval_bounds  bounds;
	LoadBounds(inttype,bounds);

	m_SppInterval = boost::icl::construct<boost::icl::continuous_interval<float>>(fMin,fMax,bounds);

}

void CDrillState::SetWob(float fMin,float fMax,INTERVAL_TYPE inttype)
{


	boost::icl::interval_bounds  bounds;
	LoadBounds(inttype,bounds);

	m_WobInterval = boost::icl::construct<boost::icl::continuous_interval<float>>(fMin,fMax,bounds);
}

void CDrillState::SetWoh(float fMin,float fMax,INTERVAL_TYPE inttype)
{

	boost::icl::interval_bounds  bounds;
	LoadBounds(inttype,bounds);

	m_WohInterval = boost::icl::construct<boost::icl::continuous_interval<float>>(fMin,fMax,bounds);
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
	return  boost::icl::contains(m_DepthInterval,item.GetDepthGap())
		&& boost::icl::contains(m_SppInterval,item.m_fSpp)
		&& boost::icl::contains(m_WobInterval,item.m_fWob)
		&& boost::icl::contains(m_SppInterval,item.m_fBkh);

}

bool CDrillState::Match(std::vector<CDrillItem>& items)
{
	if (items.size()==0)
	{
		return false;
	}
	return Match(items[items.size()-1]);
}