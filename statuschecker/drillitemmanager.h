#pragma once
#include <vector>
#include <string>
#include "drilldefine.h"
#include "drillItem.h"

class CMyDatabase;

namespace ATL
{
	class COleDateTime;	// forward reference (see atlcomtime.h)
}
using namespace  ATL;
class CDrillItemManager
{
public:
	CDrillItemManager();
	~CDrillItemManager();

	DrillStatus GetStatus(CMyDatabase* pDatabase,TCHAR* szWell,COleDateTime& beginTime,COleDateTime& endTime);
	DrillStatus GetStatus(CMyDatabase* pDatabase,TCHAR* szWell,TCHAR* lpszTime);
private:
	std::vector<CDrillItem> m_Items;
	int m_nTimeSpan; //in seconds
};
