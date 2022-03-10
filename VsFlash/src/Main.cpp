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
void Mainloop(void);

GlobalVarType GlobalVar;

void VarInit(void)
{	

}

void MainInit(void)
{
	char strFolderName[256];
	char strValue[256];
	char strSerialPortName[256];
	
	///-----------------------------------------------------------------------------///
	/// Config Load
	///-----------------------------------------------------------------------------///
	ConfigLoad();

	///-----------------------------------------------------------------------------///
	/// Variable Init
	///-----------------------------------------------------------------------------///
	VarInit();	

	///-----------------------------------------------------------------------------///
	/// Hello Print
	///-----------------------------------------------------------------------------///
	printf("\r\n");
	printf("\r\n");	
	printf("--------------------------------------------------------------\r\n");
	printf(" VS-FLASH (V1.0) programmed by JL JUANG 											\r\n");
	printf("--------------------------------------------------------------\r\n");
	printf("\r\n");

	///-----------------------------------------------------------------------------///
	/// DATA ROOT Set
	///-----------------------------------------------------------------------------///
	UtilCurDirGet((char *)&GlobalVar.strCurDir[0]);
	/// Create folder
	sprintf(strFolderName, "%s/data", (char *)&GlobalVar.strCurDir[0]);
	ConfigStrSet((char *)CONFIG_ITEM_DATA_ROOT, strFolderName);			
	UtilFolderCreate(strFolderName);

	///-----------------------------------------------------------------------------///
	/// Load time zone offset in seconds
	///-----------------------------------------------------------------------------///
  ConfigIntGet((char *)CONFIG_ITEM_TIME_ZONE_SEC, &GlobalVar.iTimeZoneSec);

	///-----------------------------------------------------------------------------///
	/// Load time zone offset in seconds
	///-----------------------------------------------------------------------------///
  ConfigStrGet((char *)CONFIG_ITEM_INIT_CONNECT, &strValue[0]);
	if(strcmp(strValue, "TRUE") == 0)
	{
		GlobalVar.bSerialPortInitConnect = TRUE;
	}
	else
	{
		sprintf(strValue, "%s", "FALSE");
		ConfigStrSet((char *)CONFIG_ITEM_INIT_CONNECT, &strValue[0]);
		GlobalVar.bSerialPortInitConnect = FALSE;
	}
	
	GlobalVar.pFileData = NULL;

	///-----------------------------------------------------------------------------///
	/// serial port init
	///-----------------------------------------------------------------------------///	
	ConfigStrGet((char *)CONFIG_ITEM_SERIAL_PORT, &strSerialPortName[0]);
	SERIAL_PORT_INIT();
	SERIAL_PORT_NAME_SET(strSerialPortName);

	///-----------------------------------------------------------------------------///
	/// APP UI Init
	///-----------------------------------------------------------------------------///
	AppInit();
}

JINT main(int argc, char *argv[])
{ 
	gtk_init(&argc, &argv);

	MainInit(); 	
	Mainloop();	
  return 0;
}

///------------------------------------------///
///  Function Area
///------------------------------------------///
void Mainloop()
{
	while(1)
	{
		TaskRoundInit();
		
		TaskApp();

		TaskSerialPort();

		TaskControl();

		TaskState();		

		TaskRoundEnd();		
		
		if(GlobalVar.bAppExit == TRUE)
		{
			break;
		}
	}
	if(GlobalVar.pFileData!= NULL)
	{
		free(GlobalVar.pFileData);
	}

	ConfigSave();

	printf("\r\nbyebye\r\n");
	return;
}
