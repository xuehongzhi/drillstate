#pragma once
#include "DrillState.h"

class CDrillItem;
class CDrillUpState:public CDrillState
{
public:
	CDrillUpState(void);
	virtual ~CDrillUpState(void);
protected:
	using CDrillState::Match;
	virtual bool  Match(std::vector<CDrillItem>& items);
};




