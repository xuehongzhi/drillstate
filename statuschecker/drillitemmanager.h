#pragma once
#include <vector>
#include <string>
#include "drilldefine.h"
#include "drillItem.h"

class CDrillItemManager
{
public:
	CDrillItemManager();
	~CDrillItemManager();

	DrillStatus GetStatus(TCHAR* lpstrTime);
	DrillStatus GetStatus();
private:
	std::vector<CDrillItem> m_Items;
};
