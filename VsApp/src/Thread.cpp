/**
 * @file Thread.cpp
 *
 *  Thread function
 *
 * @version $Revision$
 * @author JLJuang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021, VitalSigns Technology Co., Ltd., all rights reserved.
 */
#include "Global.h"

void * ThreadVscMode(void *arg)
{		
	char msg[256];

	long 		iMS0 = 0;
	long 		iMS1 = 0;
	JINT 		iDeltaMS = 0;
	
	long 		iTimeStart   	= 0;
	long 		iTimeEnd		  = 0;
	JINT 		iTimeTotalMS 	= 0;
	
	JDWORD 	dwTimeCnt = 0;
	
	JFLOAT 	fTimeAvgMS 		= -1;
	JINT 		iTimeMaxMS		= -1;
	JINT 		iErrNo = NO_ERR;

	JFLOAT 	fTimeTotalCount  = 0;
	JFLOAT 	fTimeSumMS   		 = 0;
	
	while(1)
	{
		///---------------------------------------///
		/// get time of day 2
		///---------------------------------------///		
		iMS1	     = UtilMsGet();
		iDeltaMS   = (iMS1 - iMS0);
		if(iDeltaMS < 0)
		{
			iMS0 = iMS1;			
			continue;
		}

		if(iDeltaMS < 50)
		{
			UtilMsSleep(10);
			continue;
		}

		iTimeStart = UtilMsGet();		
		iErrNo = CmdSBleVscModeRead();
		iTimeEnd = UtilMsGet();

		// sprintf(msg, "[VSC]READ: END  , MS0 = %ld, MS1 = %ld -->%d\r\n", iMS0, iMS1, (JINT)(iTimeEnd - iTimeStart));
		// DBG_PRINTF(msg);

		if((iErrNo == ERR_VSC_MODE_IDX_INVALID) && (iErrNo != NO_ERR))
		{
			/// Device has no such id
			UtilMsSleep(5);
			continue;
		}
		else if(iErrNo != NO_ERR)
		{
			GlobalVar.dwSysCtl5|= SYS_CTL6_BLE_MASTER_CLOSE;
			GlobalVar.dwSysCtl7|= SYS_CTL7_MSG_SERIAL_PORT_OPEN_FAILED;
			sprintf(msg, "[VSC] Read Failed iErrNo= %d\r\n", iErrNo);
			DBG_PRINTF(msg);
			break;
		}

		iTimeEnd =  UtilMsGet();
		iMS0 = iTimeEnd;

		iTimeTotalMS = (iTimeEnd - iTimeStart);

		if(iTimeTotalMS > 200)
		{
			sprintf(msg, "[VSC] TOTAL_TIME > 200 = %d\r\n" , iTimeTotalMS);
			DBG_PRINTF(msg);
		}

		///---------------------------------------------------------------------------------------///
		/// AVG
		///---------------------------------------------------------------------------------------///
		if(dwTimeCnt == 0)
		{
			fTimeAvgMS = iTimeTotalMS;
		}
		else
		{			
			dwTimeCnt = dwTimeCnt + 1;	
		}

		fTimeTotalCount = fTimeTotalCount + 1;
		fTimeSumMS = (fTimeSumMS + iTimeTotalMS);
		//fTimeAvgMS = (fTimeAvgMS * 999 + iTimeTotalMS) / 1000;
		if(fTimeTotalCount <= 0)
		{
			fTimeSumMS = 0;
		}
		else
		{
			fTimeAvgMS = fTimeSumMS / fTimeTotalCount;
		}

		///---------------------------------------------------------------------------------------///
		/// MAX
		///---------------------------------------------------------------------------------------///
		if(iTimeMaxMS < iTimeTotalMS)
		{
			iTimeMaxMS = iTimeTotalMS;
		}

		///---------------------------------------------------------------------------------------///
		/// Print
		///---------------------------------------------------------------------------------------///
		if(dwTimeCnt % 10 == 0)
		{
			sprintf(msg, "[VSC] AVG_TIME = %0.3f ms MAX_TIME = %d ms, TOTAL_SEC = %d, sum = %0.0f cnt =%0.0f\r\n" ,
											 fTimeAvgMS, 
											 iTimeMaxMS, 
											 GlobalVar.dwVscModeSec, 
											 fTimeSumMS, 
											 fTimeTotalCount
											 );
			//DBG_PRINTF(msg);			
		}

		UtilMsSleep(5);
		
		if(GlobalVar.iBleState != BLE_STATE_VSC_MODE)
		{
			break;
		}
	}
	
	DBG_PRINTF("VSM Bye byte\r\n");

	GlobalVar.tid0 = NULL;
	pthread_exit(NULL);

	return NULL;
}

void * ThreadMainLoop(void *arg)
{
	MainLoop();	
	GlobalVar.tid1 = NULL;
	pthread_exit(NULL);
	return NULL;
}

void * ThreadSubLoop(void *arg)
{
	SubLoop();	
	GlobalVar.tid3 = NULL;
	pthread_exit(NULL);
	return NULL;
}

void * ThreadTimer(void *arg)
{
	static struct timeval tp;
	long iMS0 = 0;
	long iMS1 = 0;	
	while(1)
	{
		///---------------------------------------///
		/// get time of day 2
		///---------------------------------------///
		gettimeofday(&tp, NULL);
		iMS1 = tp.tv_sec * 1000 + tp.tv_usec / 1000;
		if((iMS1 % 1000) == 0)
		{
			break;
		}
		if(GlobalVar.bAppExit == TRUE)
		{
			break;
		}
	}

	while(1)
	{
		///---------------------------------------///
		/// get time of day 2
		///---------------------------------------///
		gettimeofday(&tp, NULL);
		iMS1 = tp.tv_sec * 1000 + tp.tv_usec / 1000;

		if(((iMS1 % TIMER_PERIOD_MS) == 0) && (iMS0 != iMS1))
		{
			TimerTick();
			iMS0 = iMS1;
		}
		else
		{		
			UtilUsSleep(10);
		}
		
		if(GlobalVar.bAppExit == TRUE)
		{
			break;
		}
	}
	GlobalVar.tid2 = NULL;
	pthread_exit(NULL);
	return NULL;
}
