#pragma once
#include "drilldefine.h"
class CDrillStateManager;
class CDrillItem
{
public:
	CDrillItem();
	~CDrillItem();

	float GetDepthGap() const { return m_fDepth-m_fBitDepth;} 

	float m_fDepth;    //����
	float m_fBitDepth; //��ͷ���
	float m_fSpp; //��ѹ
	float m_fWob; //��ѹ
	float m_fBkh; //�󹵸���
	time_t m_curTime;

	DrillStatus m_Status;
};

