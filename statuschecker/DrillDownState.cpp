#include "stdafx.h"
#include "DrillDownState.h"
#include "drillitem.h"

CDrillDownState::CDrillDownState(void):CDrillState(DRILL_DOWN)
{
}


CDrillDownState::~CDrillDownState()
{

}

bool CDrillDownState::Match(std::vector<CDrillItem>& items)
{
	int iSize = items.size();
	if (iSize<2)
	{
		return false;
	}
	return Match(items[iSize-1])&&Match(items[iSize-2])&&items[iSize-1].m_fBitDepth-items[iSize-2].m_fBitDepth>FLT_EPSILON;
}