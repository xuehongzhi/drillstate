#pragma once
#include "drilldefine.h"
class CDrillItem;
class CDrillState
{
public:
	CDrillState(DrillStatus statcode);
	virtual ~CDrillState(void);


	DrillStatus GetStatus(){return m_Status;}
	void SetDepthGap(float fMin,float fMax);
	void SetSpp(float fMin,float fMax);
	void SetWob(float fMin,float fMax);
	void SetWoh(float fMin,float fMax);

	void AddNextState(CDrillState* pNext);

	DrillStatus TestMatch(const CDrillItem& item);
	virtual bool  Match(const CDrillItem& item);
protected:
	float m_fDepthGap[2];
	float m_fSpp[2]; //×êÑ¹
	float m_fWob[2]; //±ÃÑ¹
	float m_fWoh[2]; //´ó¹µ¸ººÉ
private:
	CDrillState* m_pNext;
	DrillStatus m_Status;
};


