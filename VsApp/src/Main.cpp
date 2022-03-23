/**
 * @file main.cpp
 *
 *   Main Code
 *
 * @version $Revision$
 * @author JLJuang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021, VitalSigns Technology Co., Ltd.,, all rights reserved.
 * @note
*/
///------------------------------------------///
///  Include Area
///------------------------------------------///
#include "Global.h"
GlobalVarType GlobalVar;

void VarInit(void)
{	
	/// set social security number
	sprintf((char *)&GlobalVar.strSSN[0], "%s", "000-00-0000");

	GlobalVar.iFileTimeMSNow = -1;
	GlobalVar.iVscInfoCnt    = 0;
}

void MainInit(void)
{
	char strFolderName[256];
	char strValue[256];
	char strSerialPortName[256];
	
	///-------------------------------------------------------------------------///
	/// OS Type Get
	///-------------------------------------------------------------------------///
	UtilOSTypeGet(&GlobalVar.iOSType);

	///-------------------------------------------------------------------------///
	/// Config Load
	///-------------------------------------------------------------------------///
	ConfigLoad();

	///-------------------------------------------------------------------------///
	/// Variable Init
	///-------------------------------------------------------------------------///
	VarInit();	

	///-------------------------------------------------------------------------///
	/// Hello Print
	///-------------------------------------------------------------------------///
	printf("\r\n");
	printf("\r\n");	
	printf("--------------------------------------------------------------\r\n");
	printf(" VS-APP (V1.0) programmed by JL JUANG 										    \r\n");
	printf("--------------------------------------------------------------\r\n");
	printf("\r\n");

	///-------------------------------------------------------------------------///
	/// DATA DIR Set
	///-------------------------------------------------------------------------///
	UtilCurDirGet((char *)&GlobalVar.strCurDir[0]);
	/// Create folder
	sprintf(strFolderName, "%s/data", (char *)&GlobalVar.strCurDir[0]);
	ConfigStrSet((char *)CONFIG_ITEM_DATA_ROOT, strFolderName);			
	UtilFolderCreate(strFolderName);


	///-----------------------------------------------------------------------------///
	/// serial port init
	///-----------------------------------------------------------------------------///	
	ConfigStrGet((char *)CONFIG_ITEM_SERIAL_PORT, &strSerialPortName[0]);
	SERIAL_PORT_INIT();
	SERIAL_PORT_NAME_SET(strSerialPortName);

	///-------------------------------------------------------------------------///
	/// VscMode Save
	///-------------------------------------------------------------------------///
	ConfigStrGet((char *)CONFIG_ITEM_VSC_MODE_SAVE, strValue);			
	if(UtilMemcmp((JBYTE *)&strValue[0], (JBYTE *)("ON"), 2) == MEMCMP_SAME)
	{
		GlobalVar.bVscModeSave = TRUE;
	}
	else
	{
		GlobalVar.bVscModeSave = FALSE;
	}

	///-------------------------------------------------------------------------///
	/// APP UI Init
	///-------------------------------------------------------------------------///
	AppInit();	
}

JINT main(int argc, char *argv[])
{ 
	gtk_init(&argc, &argv);

	MainInit(); 		
	TimerStart();
	MainLoopStart();	
	SubLoopStart();	
	while(1)
	{
		if(gtk_events_pending())
		{
			gtk_main_iteration();
		}

		if(GlobalVar.bAppExit == TRUE)
		{
			break;
		}
	}
	
  ConfigSave();
	DBG_PRINTF("bye bye\r\n");

  return 0;
}
