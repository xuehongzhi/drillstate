#pragma once
#include "DrillState.h"
#include <atlcomtime.h>

class CDrillItem;
class CAppendTubeState:public CDrillState
{
public:
	CAppendTubeState(void);
	virtual ~CAppendTubeState(void);

	void SetTimeSpan(int nMiniutes);
private:
	COleDateTimeSpan m_tmSpan;
};



