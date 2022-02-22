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
	/// Init Variable
	VarInit();	

	/// init print
	printf("\r\n\r\n");
	printf("--------------------------------------------------------------\r\n");
	printf(" VSDongle (V1.0) programmed by JL JUANG \r\n");
	printf("--------------------------------------------------------------\r\n\r\n");
}

JINT main(int argc, char *argv[])
{ 
	MainInit(); 	
	Mainloop();	
  return 0;
}

///------------------------------------------///
///  Function Area
///------------------------------------------///
void Mainloop()
{
	char msg[256];
	char strSerialPort[256];
	JBOOL bRet = FALSE;
	
	///-----------------------------------------------------------------------------///
	/// 1. Config Load
	///-----------------------------------------------------------------------------///
	ConfigLoad();

	///-----------------------------------------------------------------------------///
	/// 2. VsDongle name set
	/// 		# for macOS
	/// 		$ ls /dev/cu.usbserial*
	///
	/// 		# for ubuntu
	/// 		$ ls /dev/ttyUSB*
	///
	///-----------------------------------------------------------------------------///
	ConfigStrGet((char *)CONFIG_ITEM_SERIAL_PORT, strSerialPort);
	sprintf(msg, "VSDongle : %s\r\n", strSerialPort);
	DBG_PRINTF(msg);

	///-----------------------------------------------------------------------------///
	/// 3. VsDongle Open
	///-----------------------------------------------------------------------------///
	bRet = FuncVSDongleOpen(strSerialPort);
	if(bRet == FALSE)
	{
		sprintf(msg, "[ERROR] Failed to open the serial port: %s\r\n", strSerialPort);
		DBG_PRINTF(msg);
		return;
	}

	///-----------------------------------------------------------------------------///
	/// 4. Version Get
	///-----------------------------------------------------------------------------///
	bRet = FuncVSDongleVersionGet();
	if(bRet == FALSE)
	{
		sprintf(msg, "%s", "[ERROR] Failed to get VS Dongle version\r\n");
		DBG_PRINTF(msg);
		return;
	}

	///-----------------------------------------------------------------------------///
	/// 5. Time Set
	///-----------------------------------------------------------------------------///
	bRet = FuncVSDongleTimeSet();
	if(bRet == FALSE)
	{
		sprintf(msg, "%s", "[ERROR] Failed to set VS Dongle Time\r\n");
		DBG_PRINTF(msg);
		return;
	}

	///-----------------------------------------------------------------------------///
	/// 6. VsDongle Close
	///-----------------------------------------------------------------------------///
	bRet = FuncVSDongleClose();

	///-----------------------------------------------------------------------------///
	/// 7. Config Save
	///-----------------------------------------------------------------------------///
	ConfigSave();

	printf("\r\nbyebye\r\n");
	return;
}

