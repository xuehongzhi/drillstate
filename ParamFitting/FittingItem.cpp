#include "stdafx.h"
#include "FittingItem.h"
#include <math.h>
#include <boost/math/constants/constants.hpp>

const  float CFittingItemManager::pi  = boost::math::constants::pi<float>();

CFittingItem::CFittingItem(float iLow, float iUpper) :m_fLower(iLow), m_fUpper(iUpper)
{
}


CFittingItem::~CFittingItem()
{
}


float CFittingItem::GetValue(float fVal)
{
	//return fabs((fVal - m_fLower) / (m_fUpper - m_fLower));
	return fVal;
}

CFittingItemManager::CFittingItemManager()
{

}

CFittingItemManager::~CFittingItemManager()
{

}

int CFittingItemManager::GetColumnCount()
{
	int iCount =  2 * fititems.size();
	for (int i = 0; i < fititems.size(); ++i)
	{
		for (int j = i + 1; j < fititems.size(); ++j)
		{
			iCount++;
		}
	}
	return iCount;
}

float CFittingItemManager::GetValue(const char* strName, float fVal)
{
	
	std::map<std::string,CFittingItem>::iterator it = fititems.find(std::string(strName));
	if (it==fititems.end())
	{
		return FLT_MAX;
	}
	return (*it).second.GetValue(fVal);
}

void CFittingItemManager::LoadMatrix(ublas::matrix<float>& mat, int iIndex1, int iIndex2)
{


	
}


float CFittingItemManager::MaxMin(ublas::matrix<float>& mat, int iColum,float& fMax, float& fMin)
{
	ublas::matrix<float>::iterator2 b = mat.begin2();
	b += iColum*mat.size2();
	
	ublas::matrix<float>::iterator2  e = b;
	e += mat.size2();
	
	std::pair<ublas::matrix<float>::iterator2, ublas::matrix<float>::iterator2> pr = std::minmax_element(b, e);
	fMin = (*pr.first);
	fMax = (*pr.second);

	return fMin;
}


void CFittingItemManager::LoadMatrix(ublas::matrix<float>& mat)
{
	

	for (int j = 0; j < mat.size2(); ++j)
	{
		float fMax, fMin;
		MaxMin(ublas::matrix<float>(ublas::trans(mat)), j,fMax,fMin);
		
		for (int i = 0; i < mat.size1(); ++i)
		{
			if (fMax!=fMin)
			{
				mat(i, j) = float(mat(i, j) - fMin) / float(fMax - fMin);
			}
		}
		
	}

}

void CFittingItemManager::AddItem(const char* strName, CFittingItem& item)
{
	fititems.insert(std::make_pair(std::string(strName), item));
}


float CFittingItemManager::GetK(float fInc,float fAz,float fPreInc)  //È¡ÔìÐ±ÂÊ
{
	return acos(cos(fInc*CFittingItemManager::pi / 180) * cos(fPreInc*CFittingItemManager::pi / 180) +
		sin(fInc*CFittingItemManager::pi / 180) * sin(fPreInc*CFittingItemManager::pi / 180) * cos(fAz*pi / 180));
}