#include "stdafx.h"
#include "drillstatemanager.h"
#include "DrillingState.h"
#include "DrillUpState.h"
#include "DrillDownState.h"
#include "circulationstate.h"
#include "reamingoffstate.h"
#include "AppendTubeState.h"
#include "undrillingstate.h"


CDrillStateManager::CDrillStateManager(void)
{
}


CDrillStateManager::~CDrillStateManager(void)
{
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


void CDrillStateManager::Init()
{
	CDrillState* pState1 = NULL;
	CDrillState* pState = new CDrillingState();
	m_DrillStates["���"] = pState;

	pState1 = pState;
	pState = new CDrillUpState();
	m_DrillStates["����"] = pState;
	pState1->AddNextState(pState);

	pState1 = pState;
	pState = new CDrillDownState();
	m_DrillStates["����"] = pState;
	pState1->AddNextState(pState);

	pState1 = pState;
	pState =  new UnDrillingState;
	pState1->AddNextState(pState);

	pState1 = pState;
	pState = new CCirculationState();
	m_DrillStates["ѭ��"] = pState;
	((UnDrillingState*)pState1)->AddState(pState);


	pState = new CReamingOffState();
	m_DrillStates["����"] = pState;
	((UnDrillingState*)pState1)->AddState(pState);

	pState = new CAppendTubeState();
	m_DrillStates["�ӵ���"] = pState;
	pState1->AddNextState(pState);

}
