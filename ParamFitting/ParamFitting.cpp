// ParamFitting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "mydatabase.h"
#include "myrecordset.h"
#include "polyfit.hpp"
#include "FittingItem.h"
#include <iostream>
#include <boost/numeric/ublas/io.hpp>
namespace ublas = boost::numeric::ublas;

int _tmain(int argc, _TCHAR* argv[])
{
	::CoInitialize(NULL);
	CMyDatabase database;
	database.SetServer("name1");
	database.SetUserName("YTSJ_LJ");
	database.SetPassword("jqjy2808");
	database.SetDatabase("WYZX");
	database.SetPort(1521);
	
	database.Open();

	CFittingItemManager fitmanager;
	CMyRecordset rs;
	if (database.ExecuteQuery("select azs04_1.jh as jh,azs04_1.cdsd,azs04_1.JXJ,azs04_1.fwj,azy01.ZY,azy01.nj,azg01.ylxs,azg01.mqjs from azs04_1,azy01,azg01  where azs04_1.jh=azy01.jh and azs04_1.CDSD=azy01.JS  and azs04_1.jh = azg01.jh and nj is not null and ylxs is not null and abs(azg01.mqjs - azs04_1.cdsd) = (select min(abs(azg01.mqjs - azs04_1.cdsd))  from azg01 where azg01.jh = azs04_1.jh and ylxs is not null) order by azs04_1.jh, cdsd, ylxs", rs))
	{
		ublas::matrix<float> xMat(rs.GetRecordCount(),4);
		ublas::matrix<float> yMat(rs.GetRecordCount(), 1);

		
		int iRow = 0;
		std::string strPreWell;
		float fPreInc = 0;
		while (!rs.IsEOF())
		{
			std::string strWell;
			rs.GetValue("jh",strWell);


			float stress;
			rs.GetValue("zy", stress);

			xMat(iRow, 0) = stress;

			float nj;
			rs.GetValue("nj", nj);
			xMat(iRow, 1) = nj;

			float ylxs;
			rs.GetValue("ylxs", ylxs);
			xMat(iRow, 2) = ylxs;

			xMat(iRow, 3) = 1.25;

			float fwj;
			rs.GetValue("fwj", fwj);
	

			float jxj;
			rs.GetValue("jxj", jxj);
	
			if (strPreWell != strWell)
			{
				fPreInc = 0;
			}
			else
			{
				fPreInc = fwj;
			}

			yMat(iRow, 0) = fitmanager.GetK(fwj, jxj, fPreInc);

			strPreWell = strWell;

			iRow++;
			rs.MoveNext();
		}
// 		std::cout << xMat << std::endl;
// 		std::cout << yMat << std::endl;
		 
		fitmanager.LoadMatrix(xMat);
		fitmanager.LoadMatrix(yMat);
		
		std::cout << xMat << std::endl;
// 		std::cout << yMat << std::endl;

		std::vector<float> vVal = polyfit(xMat,yMat);

		for (int i = 0; i < vVal.size(); ++i)
		{
			std::cout << vVal[i] << " ";
		}
		std::cout << std::endl;
	}

	rs.Close();
	::CoUninitialize();

	return 0;
}

