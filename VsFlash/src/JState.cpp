/**
 * @file JState.c
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

void JStateMain(void)
{
	char 		msg[256];
	JBOOL 	bRet = FALSE;

	JINT iTimeOutSec = 0;
	JINT iErr = 0;
	

	///---------------------------------------------------------------///
	/// Check Com port connected
	///---------------------------------------------------------------///
	if(GlobalVar.bFlashStart == FALSE)
	{
		return;
	}

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
	if(GlobalVar.iState == JSTATE_INIT)
	{
		DBG_PRINTF("[STATE] INIT\r\n");
		bRet = FuncDfuFileRead();
		if(bRet == FALSE)
		{
			sprintf(GlobalVar.strFlashMsg, "%s", "[ERROR] Failed to open the file\r\n");
			GlobalVar.iState = JSTATE_ERROR;
		}
		GlobalVar.tDfuT0 = time(NULL);		
		GlobalVar.fProgress   = 0;
		GlobalVar.bDFUWriteOn = FALSE;
		GlobalVar.tid0 = NULL;

		GlobalVar.iState = JSTATE_BOOTCODE;
	}
	else if(GlobalVar.iState == JSTATE_BOOTCODE)
	{
		DBG_PRINTF("[STATE] BOOTCODE ENTER\r\n");

		bRet = CmdBootSysVersion();		
		if(bRet == FALSE)
		{
			sprintf(GlobalVar.strFlashMsg, "%s", "[ERROR] Failed to enter boot code - 1\r\n");
			GlobalVar.iState = JSTATE_ERROR;
		}

		if(strncmp(GlobalVar.strModelName, BOOTCODE_MODEL_NAME, strlen(BOOTCODE_MODEL_NAME)) == 0)
		{
			GlobalVar.iState = JSTATE_DFU_START;
			return;
		}

		bRet = FuncBootCodeEnter();		
		if(bRet == FALSE)
		{
			sprintf(GlobalVar.strFlashMsg, "%s", "[ERROR] Failed to enter boot code\r\n");
			GlobalVar.iState = JSTATE_ERROR;
		}
		GlobalVar.iStateWaitMS = 500;
		GlobalVar.iState = JSTATE_RECONNECT;
	}
	else if(GlobalVar.iState == JSTATE_RECONNECT)
	{
		if(GlobalVar.dwSysCtl2 & SYS_CTL2_TIMER_100MS_EVT)
		{	
			GlobalVar.iStateWaitMS = GlobalVar.iStateWaitMS - 100;
		}		
		if(GlobalVar.iStateWaitMS <= 0)
		{
			GlobalVar.iStateWaitMS = 0;
			GlobalVar.iState = JSTATE_BOOTCODE;		
		}
	}
	else if(GlobalVar.iState == JSTATE_DFU_START)
	{
		DBG_PRINTF("[STATE] DFU_START\r\n");
		bRet =FuncDfuStart();
		if(bRet == FALSE)
		{
			sprintf(GlobalVar.strFlashMsg, "%s", "[ERROR] Failed to start DFU\r\n");
			GlobalVar.iState = JSTATE_ERROR;
			
		}
		else
		{
			/// Boot code has a delay 1000 after DFU_START			
			sprintf(msg, "%s", "[STATE] DFU_START\r\n");
			DBG_PRINTF(msg);
			///----------------------------------------------///
			/// [JL]: For Bootcode WAIT_FOR_DATA
			///----------------------------------------------///
			sprintf(msg, "\t FLUSH DATA\r\n");
			DBG_PRINTF(msg);
			SERIAL_PORT_FLUSH(32);
			GlobalVar.iState = JSTATE_DFU_WRITE;
		}
	}
	else if(GlobalVar.iState == JSTATE_DFU_WRITE)
	{		
		if(GlobalVar.bDFUWriteOn == FALSE)
		{
			DBG_PRINTF("[STATE] DFU_WRITE\r\n");
			if(GlobalVar.tid0 == NULL)
			{				
				iErr = pthread_create(&GlobalVar.tid0, NULL, &ThreadDFUWrite, NULL);
				if(iErr != 0)
				{
					printf("can't create thread :[%s]\r\n", strerror(iErr));
				}
				pthread_detach(GlobalVar.tid0);
			}
		}		
	}
	else if(GlobalVar.iState == JSTATE_DFU_END)
	{
		DBG_PRINTF("[STATE] DFU_END\r\n");
		bRet = FuncDfuEnd();
		if(bRet == FALSE)
		{
			sprintf(GlobalVar.strFlashMsg, "%s", "[ERROR] Failed to end DFU\r\n");
			GlobalVar.iState = JSTATE_ERROR;
		}
		GlobalVar.iState = JSTATE_END;
	}
	else if(GlobalVar.iState == JSTATE_ERROR)
	{
		DBG_PRINTF("[STATE] ERROR\r\n");
		DBG_PRINTF(GlobalVar.strFlashMsg);
		JViewDialogMessageShow(GlobalVar.strFlashMsg);
		GlobalVar.iState = JSTATE_END;
	}
	else if(GlobalVar.iState == JSTATE_END)
	{
		DBG_PRINTF("[STATE] END\r\n");		
		GlobalVar.bFlashStart = FALSE;
		GlobalVar.bDFUWriteOn = FALSE;

		///----------------------------------------------///
		/// [JL]: For Bootcode: transferCompleteStr
		///----------------------------------------------///		
		SERIAL_PORT_FLUSH(64);

		GlobalVar.iState = JSTATE_NULL;
	}
	GlobalVar.tDfuT1 = time(NULL);
	GlobalVar.iDfuEclapse =  (JINT)(GlobalVar.tDfuT1 - GlobalVar.tDfuT0);		
}
