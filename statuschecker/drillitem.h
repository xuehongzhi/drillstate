#pragma once
#include "drilldefine.h"
class CDrillStateManager;
class CDrillItem
{
public:
	CDrillItem();
	~CDrillItem();

	float GetDepthGap() const { return m_fDepth-m_fBitDepth;} 

	float m_fDepth;    //测深
	float m_fBitDepth; //钻头深度
	float m_fSpp; //钻压
	float m_fWob; //泵压
	float m_fBkh; //大沟负荷
	time_t m_curTime;

	DrillStatus m_Status;
};

