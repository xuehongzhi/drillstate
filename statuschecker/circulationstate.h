#pragma once
#include "drillstate.h"
class CDrillItem;

class CCirculationState:public CDrillState
{
public:
	CCirculationState(void);
	virtual ~CCirculationState(void);
protected:
	using CDrillState::Match;
	virtual bool  Match(std::vector<CDrillItem>& items);
};


