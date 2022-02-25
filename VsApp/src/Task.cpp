/**
 * @file task.cpp
 *
 *   task function
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

void TaskRoundInit(void)
{
	
}

void TaskApp(void)
{
	if(gtk_events_pending())
	{
		gtk_main_iteration();
	}
}

void TaskVsDongleOpen(void)
{
	JBOOL bRet = FALSE;
	char strSerialPort[256];
	char msg[256];
	
	sprintf(msg, "[TASK] VS DONGLE OPEN\r\n");
	DBG_PRINTF(msg);

	///-----------------------------------------------------------------------------///
	/// 1. VsDongle name set
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
	/// 2. VsDongle Open
	///-----------------------------------------------------------------------------///
	bRet = FuncVSDongleOpen(strSerialPort);
	if(bRet == FALSE)
	{
		sprintf(msg, "[ERROR] Failed to open the serial port: %s\r\n", strSerialPort);
		DBG_PRINTF(msg);
		return;
	}

	///-----------------------------------------------------------------------------///
	/// 3. Version Get
	///-----------------------------------------------------------------------------///
	bRet = FuncVSDongleVersionGet();
	if(bRet == FALSE)
	{
		sprintf(msg, "%s", "[ERROR] Failed to get VS Dongle version\r\n");
		DBG_PRINTF(msg);
		return;
	}

	///-----------------------------------------------------------------------------///
	/// 4. Time Set
	///-----------------------------------------------------------------------------///
	bRet = FuncVSDongleTimeSet();
	if(bRet == FALSE)
	{
		sprintf(msg, "%s", "[ERROR] Failed to set VS Dongle Time\r\n");
		DBG_PRINTF(msg);
		return;
	}
}

void TaskVSH101Open(void)
{
	JBOOL bRet = FALSE;

	char msg[256];
	
	sprintf(msg, "[TASK] VSH101 OPEN\r\n");
	DBG_PRINTF(msg);

	///-----------------------------------------------------------------------------///
	/// 1. BLE scan start
	///-----------------------------------------------------------------------------///
	bRet = FuncMBleScan();

	///-----------------------------------------------------------------------------///
	/// 2. BLE device select
	///-----------------------------------------------------------------------------///
	bRet = FuncMBleSelect();

	///-----------------------------------------------------------------------------///
	/// 3. BLE connection open
	///-----------------------------------------------------------------------------///
	bRet = FuncMBleOpen();

	///-----------------------------------------------------------------------------///
	/// 4. BLE connection open Check
	///-----------------------------------------------------------------------------///
	bRet = FuncMBleOpenCheck(10);

	///-----------------------------------------------------------------------------///
	/// 5. BLE Device Version Read
	///-----------------------------------------------------------------------------///
	bRet = FuncSBleVersionGet();
}


void TaskVSH101Read(void)
{
	JBOOL bRet = FALSE;
	JINT  iSec = 10;

	char msg[256];

	sprintf(msg, "[TASK] VSH101 READ\r\n");
	DBG_PRINTF(msg);

	///----------------------------------------------------------------------///
	/// 1. check VSH101 connected
	///----------------------------------------------------------------------///
	if(GlobalVar.bBleConnected == FALSE)
	{
		sprintf(msg, "\t [ERROR] VSH101 is not connected\r\n");
		DBG_PRINTF(msg);
	}
	
	///----------------------------------------------------------------------///
	/// 2. Ecg measurement start
	///----------------------------------------------------------------------///
	FuncVscModeStart();

	///----------------------------------------------------------------------///
	/// 3. Ecg data save folder init
	///----------------------------------------------------------------------///
	FuncVscModeInit();

	///----------------------------------------------------------------------///
	/// 4. Ecg data  read for 60 seconds
	///----------------------------------------------------------------------///
	FuncVscModeRead(iSec);

	///----------------------------------------------------------------------///
	/// 5. Ecg measurement stop
	///----------------------------------------------------------------------///
	FuncVscModeStop();
}

void TaskVSH101Close(void)
{
	JBOOL bRet = FALSE;

	char msg[256];
	
	sprintf(msg, "[TASK] VSH101 CLOSE\r\n");
	DBG_PRINTF(msg);

	///-----------------------------------------------------------------------------///
	/// 11. BLE connect close
	///-----------------------------------------------------------------------------///
	bRet = FuncMBleClose();
}

void TaskVsDongleClose(void)
{
	JBOOL bRet = FALSE;
	char msg[256];

	sprintf(msg, "[TASK] VS DONGLE CLOSE\r\n");
	DBG_PRINTF(msg);

	///-----------------------------------------------------------------------------///
	/// 1. VsDongle Close
	///-----------------------------------------------------------------------------///
	bRet = FuncVSDongleClose();
	if(bRet == FALSE)
	{
		sprintf(msg, "%s", "[ERROR] Failed to close the Dongle\r\n");
		DBG_PRINTF(msg);
		return;
	}
}

void TaskRoundEnd(void)
{

}
