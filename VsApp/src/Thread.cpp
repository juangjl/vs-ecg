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

	long iMS0;
	long iMS1;

	JINT iDeltaMS = 0;

	///---------------------------------------///
	/// get time of day 2
	///---------------------------------------///
	gettimeofday(&tp, NULL);
	iMS0 = tp.tv_sec * 1000 + tp.tv_usec / 1000;

	iMS0 = iMS0;
	if((iMS0 - GlobalVar.iVscModeMSPre) < 50)
	{
		GlobalVar.tid0 = NULL;
		pthread_exit(NULL);
		return NULL;
	}

	if(GlobalVar.bVscModeReadOn == TRUE)
	{
		GlobalVar.tid0 = NULL;
		pthread_exit(NULL);
		return NULL;
	}
	GlobalVar.bVscModeReadOn = TRUE;

	CmdSBleVscModeRead();

	GlobalVar.bVscModeReadOn = FALSE;
	GlobalVar.iVscModeMSPre = iMS0;

	///---------------------------------------///
	/// get time of day 2
	///---------------------------------------///
	gettimeofday(&tp, NULL);
	iMS1 = tp.tv_sec * 1000 + tp.tv_usec / 1000;

	iDeltaMS = (iMS1 - iMS0);

	GlobalVar.tid0 = NULL;
	pthread_exit(NULL);
	return NULL;
}
