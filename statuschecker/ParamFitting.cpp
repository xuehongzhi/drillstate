// ParamFitting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "mydatabase.h"
#include "myrecordset.h"
//#include "checkitem.h"
#include <iostream>
#include <boost/numeric/interval.hpp>


int _tmain(int argc, _TCHAR* argv[])
{
	::CoInitialize(NULL);
	CMyDatabase database;
	database.SetServer("name1");
	database.SetUserName("YTSJ_LJ");
	database.SetPassword("jqjy2808");
	database.SetDatabase("WYZX");
	database.SetPort(1521);
	
	if (!database.Open())
	{
		return 0;
	}
	


	::CoUninitialize();

	return 0;
}

