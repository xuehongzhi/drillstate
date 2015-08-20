#pragma once
#include "drilldefine.h"
#include <vector>
#include <boost/icl/continuous_interval.hpp>

class CDrillItem;
class CDrillState
{
public:
	CDrillState(DrillStatus statcode);
	virtual ~CDrillState(void);


	DrillStatus GetStatus(){return m_Status;}
	void SetDepthGap(float fMin,float fMax,INTERVAL_TYPE inttype=OPEN_INTERVAL);
	void SetSpp(float fMin,float fMax,INTERVAL_TYPE inttype=OPEN_INTERVAL);
	void SetWob(float fMin,float fMax,INTERVAL_TYPE inttype=OPEN_INTERVAL);
	void SetWoh(float fMin,float fMax,INTERVAL_TYPE inttype=OPEN_INTERVAL);

	void AddNextState(CDrillState* pNext);

	DrillStatus TestMatch(std::vector<CDrillItem>& items);
	virtual bool  Match(std::vector<CDrillItem>& items);

protected:
	bool  Match( CDrillItem& items);
	
	bool LoadBounds(INTERVAL_TYPE inttype,	boost::icl::interval_bounds&  bounds);


	boost::icl::continuous_interval<float> m_DepthInterval;
	boost::icl::continuous_interval<float> m_SppInterval; //×êÑ¹
	boost::icl::continuous_interval<float> m_WobInterval;//±ÃÑ¹
	boost::icl::continuous_interval<float> m_WohInterval;//´ó¹µ¸ººÉ
private:
	CDrillState* m_pNext;
	DrillStatus m_Status;
};


