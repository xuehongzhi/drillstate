#pragma once
#include "drillstate.h"
class CDrillItem;

class CReamingOffState:public  CDrillState
{
public:
	CReamingOffState(void);
	virtual ~CReamingOffState(void);
protected:
	using CDrillState::Match;
	virtual bool  Match(std::vector<CDrillItem>& items);
};


