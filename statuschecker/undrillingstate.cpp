#include "stdafx.h"
#include "undrillingstate.h"
#include "reamingoffstate.h"
#include "circulationstate.h"

UnDrillingState::UnDrillingState(void):CDrillState(UNKOWN)
{

}


UnDrillingState::~UnDrillingState(void)
{
}

void UnDrillingState::AddState(CDrillState* pState)
{
	m_DrillStates.push_back(pState);
}

bool UnDrillingState::Match(const CDrillItem& item)
{
	int i=0;
	DrillStatus status;
	bool bSuc = false;
	for ( ;i<m_DrillStates.size(); ++i)
	{
		if (m_DrillStates[i]->Match(item))
		{
			bSuc = true;
			status = m_DrillStates[i]->GetStatus(); 
		}
	}
	return bSuc;
}