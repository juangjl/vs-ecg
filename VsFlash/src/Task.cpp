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
	TimerTick();
	TimerEventSet();	
}

void TaskApp(void)
{
	if(gtk_events_pending())
	{
		gtk_main_iteration();
	}
}

void TaskSerialPort(void)
{
	char strComName[256];

	///---------------------------------------------------------------------------///
	/// AUTO CONNECT
	///---------------------------------------------------------------------------///
	ConfigStrGet((char *)CONFIG_ITEM_SERIAL_PORT, &strComName[0]);
	
	if(GlobalVar.bSerialPortInitConnect == TRUE)
	{
		GlobalVar.dwSysCtl5 |= SYS_CTL5_SERIAL_PORT_OPEN;
		GlobalVar.bSerialPortInitConnect = FALSE;		
	}

	///---------------------------------------------------------------------------///
	/// Serial Port Open
	///---------------------------------------------------------------------------///
	if(GlobalVar.dwSysCtl5 & SYS_CTL5_SERIAL_PORT_OPEN)
	{
		ConfigStrGet((char *)CONFIG_ITEM_SERIAL_PORT, &strComName[0]);
		SERIAL_PORT_NAME_SET(strComName);
		if(SERIAL_PORT_OPEN() == TRUE)
		{
			GlobalVar.dwSysSta5 |= SYS_STA5_SERIAL_PORT_OPEN;						
			strcpy(GlobalVar.strSerialPortName, strComName);
		}
		else
		{
			GlobalVar.dwSysSta5 &= ~SYS_STA5_SERIAL_PORT_OPEN;
		}

		GlobalVar.dwSysCtl5 &= ~SYS_CTL5_SERIAL_PORT_OPEN;
	}

	///---------------------------------------------------------------------------///
	/// Serial Port Close
	///---------------------------------------------------------------------------///
	if(GlobalVar.dwSysCtl5 & SYS_CTL5_SERIAL_PORT_CLOSE)
	{
		GlobalVar.dwSysSta5 &= ~SYS_STA5_SERIAL_PORT_OPEN;
		SERIAL_PORT_CLOSE();

		GlobalVar.dwSysCtl5 &= ~SYS_CTL5_SERIAL_PORT_CLOSE;
	}
}

void TaskControl(void)
{
	JControlCheck();
	JControlAction();
}

void TaskState(void)
{
	JStateMain();
}

void TaskRoundEnd(void)
{
	if(GlobalVar.dwSysCtl2 & SYS_CTL2_TIMER_10MS_EVT)
	{
		UtilMsSleep(7);
	}
	else
	{
		UtilUsSleep(50);
	}
	TimerEventClear();
}
