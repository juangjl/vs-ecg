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


//#define SERIAL_PORT  "/dev/cu.usbserial-113430"
#define SERIAL_PORT  "/dev/cu.usbserial-113430"

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
	/// 1. Serial Port Set
	///-----------------------------------------------------------------------------///
	sprintf(strSerialPort, "%s", SERIAL_PORT);

	///-----------------------------------------------------------------------------///
	/// 2. Serial Port Open
	///-----------------------------------------------------------------------------///
	bRet = FuncSerialPortOpen(strSerialPort);
	if(bRet == FALSE)
	{
		sprintf(msg, "[ERROR] Failed to open the serial port: %s\r\n", strSerialPort);
		DBG_PRINTF(msg);
		return;
	}

	///-----------------------------------------------------------------------------///
	/// 3. Version Get
	///-----------------------------------------------------------------------------///
	bRet = FuncVsDongleVersionGet();
	if(bRet == FALSE)
	{
		sprintf(msg, "%s", "[ERROR] Failed to get VsDongle version\r\n");
		DBG_PRINTF(msg);
		return;
	}

	///-----------------------------------------------------------------------------///
	/// 4. Time Set
	///-----------------------------------------------------------------------------///
	bRet = FuncVsDongleTimeSet();
	if(bRet == FALSE)
	{
		sprintf(msg, "%s", "[ERROR] Failed to set VsDongle Time\r\n");
		DBG_PRINTF(msg);
		return;
	}

	///-----------------------------------------------------------------------------///
	/// 5. Serial Port Close
	///-----------------------------------------------------------------------------///
	bRet = FuncSerialPortClose();

	sprintf(msg, "%s", "byebye\r\n");
	DBG_PRINTF(msg);
	return;
}

