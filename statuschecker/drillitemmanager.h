#pragma once
#include <vector>
#include <string>
#include "drilldefine.h"
#include "drillItem.h"
#include "drilldefine.h"
class CMyDatabase;
class CDrillItemManager
{
public:
	CDrillItemManager();
	~CDrillItemManager();

	DrillStatus GetStatus(CMyDatabase* pDatabase,TCHAR* szWell,time_t beginTime,time_t endTime);
	DrillStatus GetStatus();
private:
	std::vector<CDrillItem> m_Items;
};
