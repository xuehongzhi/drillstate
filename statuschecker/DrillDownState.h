#pragma once
#include "DrillState.h"

class CDrillItem;
class CDrillDownState:public CDrillState
{
public:
	CDrillDownState(void);
	virtual ~CDrillDownState(void);

protected:
	using CDrillState::Match;
	virtual bool  Match(std::vector<CDrillItem>& items);
};




