#include "stdafx.h"
#include "circulationstate.h"
#include "drillitem.h"

CCirculationState::CCirculationState(void):CDrillState(CIRCULATION)
{
}


CCirculationState::~CCirculationState(void)
{
}

bool CCirculationState::Match(std::vector<CDrillItem>& items)
{
	int iSize = items.size();
	if (iSize<2)
	{
		return false;
	}
	return Match(items[iSize-1])&&Match(items[iSize-2])&&fabs(items[iSize-1].m_fBitDepth-items[iSize-2].m_fBitDepth)<FLT_EPSILON;
}

