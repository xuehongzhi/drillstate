#pragma once
#include <map>
#include <string>
class CDrillItem;
class CDrillState;

class CDrillStateManager
{
public:
	CDrillStateManager(void);
	virtual ~CDrillStateManager(void);

    CDrillState* GetState(TCHAR* szName);


	void Init();
private:
	std::map<std::string,CDrillState*> m_DrillStates;
};


