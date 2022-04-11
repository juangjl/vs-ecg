/**
 * @file BleState.c
 *
 *  Ble State Machine Function
 *
 *
 * @version $Revision$
 * @author JL Juang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021,  VitalSigns Technology Co., LTD., all rights reserved.
 * @note
*/
#include "Global.h"

void BleState(void)
{
  JINT iBleState = 0;
	char msg[256];
	JINT iRet = NO_ERR;
	JBOOL bConnect = FALSE;

	///---------------------------------------------------------------///
	/// Check Com port connected
	///---------------------------------------------------------------///
	if((GlobalVar.dwSysSta5 & SYS_STA5_SERIAL_PORT_OPEN) == 0)
	{
		return;
	}

	///---------------------------------------------------------------///
	/// BLE State Check
	///---------------------------------------------------------------///
	if(GlobalVar.iBleState == BLE_STATE_CLOSE)
	{
		if((GlobalVar.dwSysCtl2 & SYS_CTL2_SEC_EVT) != 0)
		{
			if(FuncBleOpenCheck() == FALSE)
			{
				
			}
			if(GlobalVar.bBleConnected == TRUE)
			{
				GlobalVar.iBleState = BLE_STATE_CONNECTED;
			}
		}
	}
	else if(GlobalVar.iBleState == BLE_STATE_WAIT)
	{
		if((GlobalVar.dwSysCtl2 & SYS_CTL2_SEC_EVT) != 0)
		{
			FuncBleOpenCheck();			
			GlobalVar.iBleOpenSec = 	GlobalVar.iBleOpenSec + 1;
			if(GlobalVar.iBleOpenSec  == BLE_OPEN_TIMEOUT)
			{
				GlobalVar.iBleOpenSec  = 0;
				CmdMBleClose();
				GlobalVar.iBleState = BLE_STATE_CLOSE;
			}
			if(GlobalVar.bBleConnected == TRUE)
			{
				GlobalVar.iBleOpenSec  = 0;
				CmdSBleSysTimeSet();
				iRet = FuncSBleSysSsnGet();								
				iRet = FuncSBleSysVersionGet();			
				GlobalVar.iBleState = BLE_STATE_CONNECT_INIT;
			}
		}
	}
	else if(GlobalVar.iBleState == BLE_STATE_CONNECT_INIT)
	{
		iRet = CmdSBleMonitorMode(&GlobalVar.iBleMonitorMode);
		GlobalVar.iBleState = BLE_STATE_CONNECTED;
	}
	else if(GlobalVar.iBleState == BLE_STATE_CONNECTED)
	{
		if((GlobalVar.iTimeSec % 5) == 0)
		{
			if((GlobalVar.dwSysCtl2 & SYS_CTL2_000MS_EVT) != 0)
			{
				FuncBleOpenCheck();
				if(GlobalVar.bBleConnected == TRUE)
				{
					iRet = FuncSBleSysVersionGet();
				}
			}
		}
	}
	else if(GlobalVar.iBleState == BLE_STATE_VSC_MODE)
	{
		if((GlobalVar.dwSysCtl2 & SYS_CTL2_SEC_EVT) != 0)
		{
			GlobalVar.dwVscModeSec = 	GlobalVar.dwVscModeSec + 1;
		}					
		if(GlobalVar.tid0 == NULL)
		{			
			JINT iErr = 0;
			iErr = pthread_create(&GlobalVar.tid0, NULL, &ThreadVscMode, NULL);
			if(iErr != 0)
			{
				printf("can't create thread :[%s]\r\n", strerror(iErr));
			}
			pthread_detach(GlobalVar.tid0);							
		}									
	}

	///---------------------------------------------------------///
	/// BLE STATE Print
	///---------------------------------------------------------///
	if((GlobalVar.dwSysCtl2 & SYS_CTL2_SEC_EVT) != 0)
	{
		// sprintf(msg, "[BLE] BLE_STATE = %d \r\n", GlobalVar.iBleState);
		// DBG_PRINTF(msg);
	}
}
