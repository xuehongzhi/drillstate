#include "stdafx.h"
#include "reamingoffstate.h"
#include "drillitem.h"

CReamingOffState::CReamingOffState(void):CDrillState(REAMING_OFF)
{
}


CReamingOffState::~CReamingOffState(void)
{
}

bool CReamingOffState::Match(std::vector<CDrillItem>& items)
{
	int iSize = items.size();
	if (iSize<2)
	{
		return false;
	}
	return Match(items[iSize-1])&&Match(items[iSize-2])&&fabs(items[iSize-1].m_fBitDepth-items[iSize-2].m_fBitDepth)>FLT_EPSILON;
}