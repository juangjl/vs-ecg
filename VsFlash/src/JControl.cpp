/**
 * @file JState.c
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

void JControlCheck(void)
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
	/// DOWNLOAD START
	///---------------------------------------------------------------------------///
	if(GlobalVar.dwSysCtl5 & SYS_CTL5_FLASH_START)
	{
		GlobalVar.bFlashStart = TRUE;
		GlobalVar.iState = JSTATE_INIT;
		GlobalVar.dwSysCtl5 &= ~SYS_CTL5_FLASH_START;
	}

	///---------------------------------------------------------------------------///
	/// DOWNLOAD CANCEL
	///---------------------------------------------------------------------------///
	if(GlobalVar.dwSysCtl5 & SYS_CTL5_FLASH_CANCEL)
	{
		GlobalVar.bFlashStart = FALSE;
		GlobalVar.iState = JSTATE_INIT;
		GlobalVar.dwSysCtl5 &= ~SYS_CTL5_FLASH_CANCEL;
	}
}

void JControlAction(void)
{
  JINT errNo = NO_ERR;

  ///---------------------------------------------------------------------------///
	/// BLE Control Action
	///---------------------------------------------------------------------------///
	if((GlobalVar.dwSysCtl2 & SYS_CTL2_SEC_EVT) == 0)
	{
		return;
	}
}