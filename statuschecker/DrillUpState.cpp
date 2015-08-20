#include "stdafx.h"
#include "DrillUpState.h"
#include "drillitem.h"

CDrillUpState::CDrillUpState (void):CDrillState(DRILL_UP)
{
}


CDrillUpState::~CDrillUpState(void)
{

}


bool CDrillUpState::Match(std::vector<CDrillItem>& items)
{
	int iSize = items.size();
	if (iSize<2)
	{
		return false;
	}
	return Match(items[iSize-1])&&Match(items[iSize-2])&&items[iSize-2].m_fBitDepth-items[iSize-1].m_fBitDepth>FLT_EPSILON;
}