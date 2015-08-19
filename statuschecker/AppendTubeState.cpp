#include "stdafx.h"
#include "AppendTubeState.h"


CAppendTubeState::CAppendTubeState(void):CDrillState(APPEND_TUEBE),m_tmSpan(0,0,10,0)
{

}


CAppendTubeState::~CAppendTubeState(void)
{

}


void CAppendTubeState::SetTimeSpan(int nMiniutes)
{
	m_tmSpan.SetDateTimeSpan(0,0,nMiniutes,0);
}