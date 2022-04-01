/**
 * @file Timer.cpp
 *
 *  Timer and time function
 *
 * @version $Revision$
 * @author JLJuang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021, VitalSigns Technology Co., Ltd., all rights reserved.
 * @note
*/
///------------------------------------------///
///  Include Area
///------------------------------------------///
#include "Global.h"

void TimerTick(void)
{
	JINT iTime100MS = 0;
	JINT iTime10MS  = 0;
	JINT iTime00MS  = 0;

	time_t  t 		= time(NULL);
  struct tm tm 	= *localtime(&t);	
	GlobalVar.iTimeMS 	= GlobalVar.iTimeMS  + TIMER_PERIOD_MS;
	if(GlobalVar.iTimeMS < 0)
	{
		GlobalVar.iTimeMS = 0;	
	}
	if((GlobalVar.iTimeMS % 100) == 0)
	{
		///-----------------------------------------------------------------------///
		/// 000/ 100/ 200/ 300/ 400/ 500/ 600/ 700/ 800/ 900
		///-----------------------------------------------------------------------///
		GlobalVar.iTime100MS  = GlobalVar.iTime100MS  + 100;		
	}
	///-----------------------------------------------------------------------///
	/// 00/ 10/ 20 / 30/ 40/ 50/ 60/ 70/ 80
	///-----------------------------------------------------------------------///			
	if((GlobalVar.iTimeMS % 10) == 0)
	{		
		GlobalVar.iTime10MS = GlobalVar.iTime10MS + 10;			
	}
	if((GlobalVar.iTimeMS  % TASK_PERIOD_MS) == 0)
	{
		UtilLocalTime(&GlobalVar.jtm, t);
		GlobalVar.dwSysCtl2 |= SYS_CTL2_TASK_ISR;
	}
}

void TimerEventSet()
{
  ///----------------------------------------------------------------///
	/// 000/ 100 / 200 / 300 / 400 / 500 / 600 / 700 / 800/ 900
	///----------------------------------------------------------------///
	if(GlobalVar.iTime100MS != GlobalVar.iTime100MSPre)
	{
		GlobalVar.iTime100MSPre = GlobalVar.iTime100MS;	
		GlobalVar.dwSysCtl2 |= SYS_CTL2_TIMER_100MS_EVT;		
		if((GlobalVar.iTime100MS  % 1000) == 0)			
		{
			GlobalVar.dwSysCtl2 |= SYS_CTL2_SEC_EVT;
			GlobalVar.iTimeSec    = GlobalVar.iTimeSec + 1;	
			GlobalVar.iTimeSecPre = GlobalVar.iTimeSec;			
		}
		if((GlobalVar.iTime100MS % 1000) == 0)			
		{
			GlobalVar.dwSysCtl2 |= SYS_CTL2_000MS_EVT;
		}
		if((GlobalVar.iTime100MS % 1000) == 100)			
		{
			GlobalVar.dwSysCtl2 |= SYS_CTL2_100MS_EVT;
		}
		if((GlobalVar.iTime100MS % 1000) == 200)			
		{
			GlobalVar.dwSysCtl2 |= SYS_CTL2_200MS_EVT;
		}
		if((GlobalVar.iTime100MS % 1000) == 300)			
		{
			GlobalVar.dwSysCtl2 |= SYS_CTL2_300MS_EVT;
		}
		if((GlobalVar.iTime100MS % 1000) == 400)			
		{
			GlobalVar.dwSysCtl2 |= SYS_CTL2_400MS_EVT;
		}
		if((GlobalVar.iTime100MS % 1000) == 500)			
		{
			GlobalVar.dwSysCtl2 |= SYS_CTL2_500MS_EVT;
		}
		if((GlobalVar.iTime100MS % 1000) == 600)			
		{
			GlobalVar.dwSysCtl2 |= SYS_CTL2_600MS_EVT;
		}
		if((GlobalVar.iTime100MS  % 1000) == 700)			
		{
			GlobalVar.dwSysCtl2 |= SYS_CTL2_700MS_EVT;
		}
		if((GlobalVar.iTime100MS  % 1000) == 800)			
		{
			GlobalVar.dwSysCtl2 |= SYS_CTL2_800MS_EVT;
		}
		if((GlobalVar.iTime100MS  % 1000) == 900)			
		{
			GlobalVar.dwSysCtl2 |= SYS_CTL2_900MS_EVT;
		}    
	}
	
	///----------------------------------------------------------------///
	/// 20 / 40 / 60 / 80
	///----------------------------------------------------------------///
	if(GlobalVar.iTime10MS != GlobalVar.iTime10MSPre)			
	{
		GlobalVar.iTime10MSPre = GlobalVar.iTime10MS;
		GlobalVar.dwSysCtl2 |= SYS_CTL2_TIMER_10MS_EVT;				

		if((GlobalVar.iTime10MS  % 20) == 0)
		{
			GlobalVar.dwSysCtl2 |= SYS_CTL2_TIMER_20MS_EVT;				
		}

		if(GlobalVar.iTime10MS == 0)			
		{
			GlobalVar.dwSysCtl2 |= SYS_CTL2_00MS_EVT;
		}
		else if(GlobalVar.iTime10MS == 10)			
		{
			GlobalVar.dwSysCtl2 |= SYS_CTL2_10MS_EVT;
		}
		else if(GlobalVar.iTime10MS == 20)			
		{
			GlobalVar.dwSysCtl2 |= SYS_CTL2_20MS_EVT;
		}
		else if(GlobalVar.iTime10MS == 30)			
		{
			GlobalVar.dwSysCtl2 |= SYS_CTL2_30MS_EVT;
		}
		else if(GlobalVar.iTime10MS == 40)			
		{
			GlobalVar.dwSysCtl2 |= SYS_CTL2_40MS_EVT;
		}
		else if(GlobalVar.iTime10MS == 50)			
		{
			GlobalVar.dwSysCtl2 |= SYS_CTL2_50MS_EVT;
		}
		else if(GlobalVar.iTime10MS == 60)			
		{
			GlobalVar.dwSysCtl2 |= SYS_CTL2_60MS_EVT;
		}
		else if(GlobalVar.iTime10MS == 70)			
		{
			GlobalVar.dwSysCtl2 |= SYS_CTL2_70MS_EVT;
		}
		else if(GlobalVar.iTime10MS == 80)			
		{
			GlobalVar.dwSysCtl2 |= SYS_CTL2_80MS_EVT;
		}
		else if(GlobalVar.iTime10MS == 90)			
		{
			GlobalVar.dwSysCtl2 |= SYS_CTL2_90MS_EVT;
		}
	}
}

void TimerEventClear(void)
{
	///----------------------------------------------------------------///
	/// 000 / 100 / 200 / 300 / 400 / 500 / 600
	///----------------------------------------------------------------///
	GlobalVar.dwSysCtl2 &=~(SYS_CTL2_000MS_EVT);
	GlobalVar.dwSysCtl2 &=~(SYS_CTL2_100MS_EVT);
	GlobalVar.dwSysCtl2 &=~(SYS_CTL2_200MS_EVT);
	GlobalVar.dwSysCtl2 &=~(SYS_CTL2_300MS_EVT);
	GlobalVar.dwSysCtl2 &=~(SYS_CTL2_400MS_EVT);
	GlobalVar.dwSysCtl2 &=~(SYS_CTL2_500MS_EVT);
	GlobalVar.dwSysCtl2 &=~(SYS_CTL2_600MS_EVT);
	GlobalVar.dwSysCtl2 &=~(SYS_CTL2_700MS_EVT);
	GlobalVar.dwSysCtl2 &=~(SYS_CTL2_800MS_EVT);
	GlobalVar.dwSysCtl2 &=~(SYS_CTL2_900MS_EVT);

	///----------------------------------------------------------------///
	/// 00 / 10 / 20 / 30 / 40 / 50 / 60 / 70 / 80 / 90 
	///----------------------------------------------------------------///
	GlobalVar.dwSysCtl2 &=~(SYS_CTL2_00MS_EVT);
	GlobalVar.dwSysCtl2 &=~(SYS_CTL2_10MS_EVT);
	GlobalVar.dwSysCtl2 &=~(SYS_CTL2_20MS_EVT);
	GlobalVar.dwSysCtl2 &=~(SYS_CTL2_30MS_EVT);
	GlobalVar.dwSysCtl2 &=~(SYS_CTL2_40MS_EVT);
	GlobalVar.dwSysCtl2 &=~(SYS_CTL2_50MS_EVT);
	GlobalVar.dwSysCtl2 &=~(SYS_CTL2_60MS_EVT);
	GlobalVar.dwSysCtl2 &=~(SYS_CTL2_70MS_EVT);
	GlobalVar.dwSysCtl2 &=~(SYS_CTL2_80MS_EVT);
	GlobalVar.dwSysCtl2 &=~(SYS_CTL2_90MS_EVT);

	///----------------------------------------------------------------///
	/// Timer : 100ms  / 10 ms
	///----------------------------------------------------------------///
	GlobalVar.dwSysCtl2 &= ~(SYS_CTL2_TIMER_100MS_EVT);				
	GlobalVar.dwSysCtl2 &= ~(SYS_CTL2_TIMER_10MS_EVT);	`			
	GlobalVar.dwSysCtl2 &= ~(SYS_CTL2_TIMER_20MS_EVT);																				
}

void TimerStart(void)
{
	JINT iErr = 0;

	///--------------------------------------------------------------------------------///
	/// Seperate APP and Function 
	///--------------------------------------------------------------------------------///
	iErr = pthread_create(&GlobalVar.tid2, NULL, &ThreadTimer, NULL);	
	if(iErr != 0)
	{
		printf("can't create thread :[%s]\r\n", strerror(iErr));
	}
	else
	{		
		pthread_detach(GlobalVar.tid2);		
	}
}
