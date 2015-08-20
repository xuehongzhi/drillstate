#pragma once
#include <map>
#include <string>
#include <vector>
#include "drilldefine.h"
class CDrillItem;
class CDrillState;

class CDrillStateManager
{
public:
	CDrillStateManager(void);
	virtual ~CDrillStateManager(void);

	DrillStatus GetStatus(std::vector<CDrillItem>& items);

    CDrillState* GetState(TCHAR* szName);
	void Init();

	static CDrillStateManager& Instance();
private:
	std::map<std::string,CDrillState*> m_DrillStates;
};


