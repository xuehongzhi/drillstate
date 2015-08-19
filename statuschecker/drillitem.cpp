#include "stdafx.h"
#include "drillitem.h"
#include <math.h>
#include <iostream>
#include <atlcomtime.h>


CDrillItem::CDrillItem()
{

}
CDrillItem::~CDrillItem()
{

}

DrillStatus CDrillItem::GetStatus()
{
// 	if (m_lastStatus!=NOTCHECKED)
// 	{
// 		return m_lastStatus;
// 	}
// 	if (InDepthGap())
// 	{
// 		if (m_fBkh<=m_pParent->GetBKH()) 
// 		{
// 			if (fabs(m_fWob)<FLT_EPSILON && fabs(m_fSpp)>FLT_EPSILON)
// 			{
// 				return APPEND_TUEBE;
// 			}
// 		}
// 	}
// 	else if (LessThanGap())
// 	{
// 		if (m_fWob>FLT_EPSILON && m_fSpp>FLT_EPSILON)
// 		{
// 			return DRILLING;
// 		}
// 	}


	return UNKOWN;
}


DrillStatus CDrillItem::GetStatus(CDrillItem& another)
{

// 	if (InDepthGap())
// 	{
// 		if (fabs(m_fWob)>FLT_EPSILON )
// 		{
// 			if (fabs(m_fBitDepth-another.m_fBitDepth)>FLT_EPSILON)
// 			{
// 				return REAMING_OFF;
// 			}
// 			else
// 			{
// 				return CIRCULATION;
// 			}
// 		}
// 		else if (m_lastStatus==APPEND_TUEBE&&another.GetStatus()==APPEND_TUEBE)
// 		{
// 			COleDateTimeSpan span(m_curTime-another.m_curTime);
// 			if (span.GetTotalSeconds()>10)
// 			{
// 				return UNKOWN;
// 			}
// 		}
// 
// 	}
// 	else if (GreatThanGap()&&another.GreatThanGap())
// 	{
// 		if (fabs(m_fWob)<FLT_EPSILON && fabs(m_fSpp)>FLT_EPSILON)
// 		{
// 			if (fabs(m_fDepth-another.m_fDepth)<FLT_EPSILON)
// 			{
// 				return (m_fBitDepth>another.m_fBitDepth)?DRILL_DOWN:DRILL_UP;
// 			}
// 		}
// 	}

	return UNKOWN;
}