/**
 * @file Thread.cpp
 *
 *  Thread function
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

void * ThreadVscMode(void *arg)
{		
	char msg[256];
	static struct timeval tp;

	long 		iMS0 = 0;
	long 		iMS1 = 0;
	
	long 		iTimeStart   	= 0;
	long 		iTimeEnd		  = 0;
	JINT 		iTimeTotalMS 	= 0;
	
	JDWORD 	dwTimeCnt = 0;
	
	JFLOAT 	fTimeAvgMS 		= -1;
	JINT 		iTimeMaxMS		= -1;
	JINT 		iErrNo = NO_ERR;
	
	while(1)
	{
		///---------------------------------------///
		/// get time of day 2
		///---------------------------------------///
		gettimeofday(&tp, NULL);
		iTimeStart = tp.tv_sec * 1000 + tp.tv_usec / 1000;
		iMS1	 = iTimeStart;
		if(abs(iMS1 - iMS0) < 50)
		{
			UtilMsSleep(5);
			continue;
		}

		iErrNo = CmdSBleVscModeRead();
		if((iErrNo == ERR_VSC_MODE_IDX_INVALID) && (iErrNo != NO_ERR))
		{
			/// Device has no such id
			UtilMsSleep(5);
			continue;
		}
		else if(iErrNo != NO_ERR)
		{
			sprintf(msg, "[VSC] Read Failed iErrNo= %d\r\n", iErrNo);
			DBG_PRINTF(msg);
			break;
		}

		///---------------------------------------///
		/// get time of day 2
		///---------------------------------------///
		iMS0 = iMS1;
		
		///---------------------------------------///
		/// get time of day 2
		///---------------------------------------///
		gettimeofday(&tp, NULL);
		iTimeEnd = tp.tv_sec * 1000 + tp.tv_usec / 1000;

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
			fTimeAvgMS = (fTimeAvgMS * 999 + iTimeTotalMS) / 1000;
			dwTimeCnt = dwTimeCnt + 1;
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
		if(dwTimeCnt % 50 == 0)
		{
			sprintf(msg, "[VSC] AVG_TIME = %0.3f ms MAX_TIME = %d ms, TOTAL_SEC = %d\r\n" ,
											 fTimeAvgMS, 
											 iTimeMaxMS, 
											 GlobalVar.dwVscModeSec);
			//DBG_PRINTF(msg);			
		}
		
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
