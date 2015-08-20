// ParamFitting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "mydatabase.h"
#include "myrecordset.h"
//#include "checkitem.h"
#include <iostream>
#include "drillstatemanager.h"
#include "drillitemmanager.h"
#include "drillstate.h"


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
	
	CDrillStateManager::Instance().Init();

	CDrillState* pState = CDrillStateManager::Instance().GetState("×ê½ø");
	pState->SetDepthGap(0,0.1);


	CDrillItemManager dirllitemmgr;
	
	std::cout<<dirllitemmgr.GetStatus(&database,"±±201_8","2015-06-08 21:05:00")<<std::endl;

	database.Close();

	::CoUninitialize();

	return 0;
}

