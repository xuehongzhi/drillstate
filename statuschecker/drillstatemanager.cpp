#include "stdafx.h"
#include "drillstatemanager.h"
#include "DrillingState.h"
#include "DrillUpState.h"
#include "DrillDownState.h"
#include "circulationstate.h"
#include "reamingoffstate.h"
#include "AppendTubeState.h"



CDrillStateManager::CDrillStateManager(void)
{
}


CDrillStateManager::~CDrillStateManager(void)
{
}


CDrillStateManager& CDrillStateManager::Instance()
{
	static CDrillStateManager mgr;
	return mgr;
}

CDrillState* CDrillStateManager::GetState(TCHAR* szName)
{
	CDrillState* pStates = NULL;
	std::map<std::string,CDrillState*>::iterator it 
		= m_DrillStates.find((std::string)szName);

	if (it!=m_DrillStates.end())
	{
		pStates = m_DrillStates[szName] ;
	}
	return pStates;
}

DrillStatus CDrillStateManager::GetStatus(std::vector<CDrillItem>& items)
{
	return m_DrillStates["钻进"]->TestMatch(items);
}

void CDrillStateManager::Init()
{
	CDrillState* pState1 = NULL;
	CDrillState* pState = new CDrillingState();
	m_DrillStates["钻进"] = pState;

	pState1 = pState;
	pState = new CDrillUpState();
	m_DrillStates["起钻"] = pState;
	pState1->AddNextState(pState);

	pState1 = pState;
	pState = new CDrillDownState();
	m_DrillStates["下钻"] = pState;
	pState1->AddNextState(pState);


	pState1 = pState;
	pState = new CCirculationState();
	m_DrillStates["循环"] = pState;
	pState1->AddNextState(pState);

	pState1 = pState;
	pState = new CReamingOffState();
	m_DrillStates["划眼"] = pState;
	pState1->AddNextState(pState);

    pState1 = pState;
	pState = new CAppendTubeState();
	m_DrillStates["接单根"] = pState;
	pState1->AddNextState(pState);

}
