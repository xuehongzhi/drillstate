#pragma once
#include <map>
#include <string>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>

namespace ublas = boost::numeric::ublas;

class CFittingItem
{
public:
	CFittingItem(float iLow, float iUpper);
	~CFittingItem();

	void SetUpper(float fUpper) { m_fUpper = fUpper; }
	void SetLow(float fUpper) { m_fLower = fUpper; }

	float GetValue(float fVal);
private:
	float m_fLower;
	float m_fUpper;
};

class CFittingItemManager
{
public:
	CFittingItemManager();
	~CFittingItemManager();

	float GetValue(const char* strName, float fVal);
	int GetColumnCount();
	void LoadMatrix(ublas::matrix<float>& mat);
	void LoadMatrix(ublas::matrix<float>& mat, int iIndex1, int iIndex2);

	float GetK(float fInc, float fAz,float fPreInc=0);  //»°‘Ï–±¬ 

	float MaxMin(ublas::matrix<float>& mat, int iColum,float& fMax,float& fMin);

	void AddItem(const char* strName, CFittingItem& item);
private:
	static const  float pi;
	std::map<std::string, CFittingItem>  fititems;
};