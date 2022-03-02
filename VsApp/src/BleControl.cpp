/**
 * @file blestate.c
 *
 *  ble.h 
 *
 *
 * @version $Revision$
 * @author JL Juang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021,  VitalSigns Technology Co., LTD., all rights reserved.
 * @note
*/
#include "Global.h"

void BleControlCheck(void)
{
	JINT errNo = NO_ERR;
	char strMacAddr[128];
	char msg[256];
	JDWORD dwMacAddr[6];
	char strSSN[32];

	char strFolderName[512];

	if((GlobalVar.dwSysSta5 & SYS_STA5_SERIAL_PORT_OPEN) == 0)
	{
		return;
	}

	///---------------------------------------------------------------------------///
	/// BLE Master Scan Start
	///---------------------------------------------------------------------------///
	if(GlobalVar.dwSysCtl6 & SYS_CTL6_BLE_MASTER_SCAN_START)
	{
		GlobalVar.dwSysSta6 |= SYS_STA6_BLE_MASTER_SCAN_ON;
		DBG_PRINTF("[BLE][MASTER]SCAN START\r\n");
		GlobalVar.dwSysCtl6 &= ~SYS_CTL6_BLE_MASTER_SCAN_START;
	}

	///---------------------------------------------------------------------------///
	/// BLE Master Scan Stop
	///---------------------------------------------------------------------------///
	if(GlobalVar.dwSysCtl6 & SYS_CTL6_BLE_MASTER_SCAN_STOP)
	{
		GlobalVar.dwSysSta6 &= ~SYS_STA6_BLE_MASTER_SCAN_ON;
		DBG_PRINTF("[BLE][MASTER]SCAN STOP\r\n");
		GlobalVar.dwSysCtl6 &= ~SYS_CTL6_BLE_MASTER_SCAN_STOP;
	}

	///---------------------------------------------------------------------------///
	/// BLE Open
	///---------------------------------------------------------------------------///
	if(GlobalVar.dwSysCtl6 & SYS_CTL6_BLE_MASTER_OPEN)
	{
		/// Get the mac
		ConfigStrGet((char *)CONFIG_ITEM_BLE_DEVICE_MAC, &strMacAddr[0]);
		sscanf(strMacAddr, "%02X:%02X:%02X:%02X:%02X:%02X",
					 (unsigned int *)&dwMacAddr[0], (unsigned int *)&dwMacAddr[1], (unsigned int *)&dwMacAddr[2],
					 (unsigned int *)&dwMacAddr[3], (unsigned int *)&dwMacAddr[4], (unsigned int *)&dwMacAddr[5]);

		GlobalVar.bBleMacAddr[0] = (JBYTE)dwMacAddr[0];
		GlobalVar.bBleMacAddr[1] = (JBYTE)dwMacAddr[1];
		GlobalVar.bBleMacAddr[2] = (JBYTE)dwMacAddr[2];
		GlobalVar.bBleMacAddr[3] = (JBYTE)dwMacAddr[3];
		GlobalVar.bBleMacAddr[4] = (JBYTE)dwMacAddr[4];
		GlobalVar.bBleMacAddr[5] = (JBYTE)dwMacAddr[5];

		/// BLE Open
		CmdMBleOpen(&GlobalVar.bBleMacAddr[0]);

		GlobalVar.iBleState = BLE_STATE_WAIT;
		GlobalVar.iBleOpenSec	= 0;

		sprintf(msg, "STR = %s\r\n", strMacAddr);
		DBG_PRINTF(msg);

		/// print
		sprintf(msg, "[BLE][MASTER] OPEN MAC = %02X:%02X:%02X:%02X:%02X:%02X\r\n",
						GlobalVar.bBleMacAddr[0], GlobalVar.bBleMacAddr[1], GlobalVar.bBleMacAddr[2],
						GlobalVar.bBleMacAddr[3], GlobalVar.bBleMacAddr[4], GlobalVar.bBleMacAddr[5]);
		DBG_PRINTF(msg);

		GlobalVar.dwSysCtl6 &= ~SYS_CTL6_BLE_MASTER_OPEN;
	}

	///---------------------------------------------------------------------------///
	/// BLE Close
	///---------------------------------------------------------------------------///
	if(GlobalVar.dwSysCtl6 & SYS_CTL6_BLE_MASTER_CLOSE)
	{
		GlobalVar.iBleState = BLE_STATE_CLOSE;

		/// BLE Open
		CmdMBleClose();

		DBG_PRINTF("[BLE][MASTER] CLOSE\r\n");
		GlobalVar.dwSysCtl6 &= ~SYS_CTL6_BLE_MASTER_CLOSE;
	}

	///---------------------------------------------------------------------------///
	/// BLE VSC MODE start
	///---------------------------------------------------------------------------///
	if(GlobalVar.dwSysCtl6 & SYS_CTL6_BLE_MASTER_VSC_MODE_START)
	{
		FuncVscModeInit();
		FuncVscModeStart();
		GlobalVar.dwSysCtl6 &= ~SYS_CTL6_BLE_MASTER_VSC_MODE_START;
	}

	///---------------------------------------------------------------------------///
	/// BLE VSC MODE Stop
	///---------------------------------------------------------------------------///
	if(GlobalVar.dwSysCtl6 & SYS_CTL6_BLE_MASTER_VSC_MODE_STOP)
	{
		/// BLE measurement start
		CmdSBleVscModeStop();
		if(errNo == NO_ERR)
		{
			GlobalVar.iBleState = BLE_STATE_CONNECTED;
		}		
		DBG_PRINTF("[TASK][BLE] VSC_MODE STOP\r\n");
		GlobalVar.dwSysCtl6 &= ~SYS_CTL6_BLE_MASTER_VSC_MODE_STOP;
	}

	///---------------------------------------------------------------------------///
	/// BLE SSN SET
	///---------------------------------------------------------------------------///
	if(GlobalVar.dwSysCtl6 & SYS_CTL6_BLE_MASTER_SSN_SET)
	{
		if(GlobalVar.iBleState == BLE_STATE_CONNECTED)
		{
			UtilMemset((JBYTE *)&strSSN[0], 0x00, SSN_SIZE);
			ConfigStrGet((char *)CONFIG_ITEM_SSN, strSSN);
			CmdSBleSysSsnSet(strSSN);
			CmdSBleSysSsnGet();
			GlobalVar.dwSysCtl6 &= ~SYS_CTL6_BLE_MASTER_SSN_SET;
		}
	}	
}

void BleControlAction(void)
{
  JINT errNo = NO_ERR;

  ///---------------------------------------------------------------------------///
	/// BLE Control Action
	///---------------------------------------------------------------------------///
	if((GlobalVar.dwSysCtl2 & SYS_CTL2_SEC_EVT) == 0)
	{
		return;
	}

	/// BLE scan table fetch
	if(GlobalVar.dwSysSta6 & SYS_STA6_BLE_MASTER_SCAN_ON)
	{
		errNo = CmdMBleScan();
		if(errNo != NO_ERR)
		{
			printf("[ERROR][BLE][CMD] Scan Failed\r\n");
		}
		else
		{
			/// set for UI table update
			GlobalVar.dwSysSta6 |= SYS_STA6_BLE_MASTER_SCAN_UPDATED;
		}
	}
}