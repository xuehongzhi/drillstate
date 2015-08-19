#pragma once
#include "drillstate.h"
#include <vector>

class CDrillItem;

class UnDrillingState:public  CDrillState
{
public:
	UnDrillingState(void);
	virtual ~UnDrillingState(void);

	void AddState(CDrillState* pState);
	virtual bool  Match(const CDrillItem& item);
private:
	std::vector<CDrillState*> m_DrillStates;
};


