/**
 * @file Main.cpp
 *
 *   Main Code
 *
 * @version $Revision$
 * @author JLJuang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021, VitalSigns Technology Co., Ltd., all rights reserved.
 * @note
*/
///------------------------------------------///
///  Include Area
///------------------------------------------///
#include "Global.h"

GlobalVarType GlobalVar;

void VarInit(void)
{
	JINT i = 0;
	GlobalVar.tid0 = NULL;
	GlobalVar.tid1 = NULL;
	GlobalVar.tid2 = NULL;
	GlobalVar.tid3 = NULL;
	
	GlobalVar.bBleCmdOn = FALSE;
	
	GlobalVar.iBleState = BLE_STATE_CLOSE;
	
	///-------------------------------------------///
	/// DataSet Init
	///-------------------------------------------///
	for(i = 0 ; i < DATASET_COUNT; i = i + 1)
	{
		JDataSetInit(&GlobalVar.dataSet[i] );
	}
	
		
	/// set social security number
	sprintf((char *)&GlobalVar.strSSN[0], "%s", "000-00-0000");
		
	///-------------------------------------------///
	/// VSC ATR
	///-------------------------------------------///
	GlobalVar.bVscAtrUpdated = FALSE;
	///--------------------------------------------------------///
	/// VSC ATR Init
	///--------------------------------------------------------///
	FuncVscAtrInit();
	
	///-------------------------------------------///
	/// SREG
	///-------------------------------------------///
	SRegInit();
	

	GlobalVar.iFileTimeMSNow = -1;
	GlobalVar.iVscInfoCnt    = 0;	
}

void MainInit(void)
{
	char strFolderName[512];    
	char strSerialPortName[256];
	char strValue[256];
	
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
	printf(" VS-APP programmed by JL JUANG 										    \r\n");
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
		else
		{
			UtilMsSleep(20);
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
