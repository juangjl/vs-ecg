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

void TaskSerialPort(void)
{
	char strComName[256];

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
			FuncVSDongleVersionGet();
			FuncVSDongleTimeSet();
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

void TaskBleSReg(void)
{
	char msg[256];
	SRegType *pSReg = &GlobalVar.SReg;

	if(GlobalVar.bSRegOn == FALSE)
	{
		return;
	}

	if((GlobalVar.dwSysSta5 & SYS_STA5_SERIAL_PORT_OPEN) == 0)
	{
		sprintf(msg, "%s",  "[SREG] Serial port is closed\r\n");
		GlobalVar.bSRegOn = FALSE;
		DBG_PRINTF(msg);
		return;
	}

	if(GlobalVar.bSRegWrite == TRUE)
	{
		sprintf(msg, "SREG_WRITE -> %s\r\n", pSReg->strName);
		
		DBG_PRINTF(msg);
		SRegWrite(pSReg);
	}
	else
	{		
		SRegRead(pSReg);		
		
		sprintf(msg, "SREG_READ -> %s\r\n", pSReg->strName);
		DBG_PRINTF(msg);
	}	
	GlobalVar.bSRegOn = FALSE;
}


void TaskBleControl(void)
{
	///----------------------------------------------------------------------///
	/// Control Event Check
	///----------------------------------------------------------------------///
	BleControlCheck();

	///----------------------------------------------------------------------///
	/// Control Action
	///----------------------------------------------------------------------///
	BleControlAction();
}

void TaskBleState(void)
{
	///----------------------------------------------------------------------///
	/// Ble State Machine Control
	///----------------------------------------------------------------------///
	BleState();
}

void TaskBleVscMode(void)
{
	char msg[256];
	
	JDataSet *pDS0 	 = &GlobalVar.dataSet[DATASET_MONITOR_ECG_DS1];
	JDataSet *pDS1 	 = &GlobalVar.dataSet[DATASET_MONITOR_ECG_DS0];

	JDataSet *pDS2 	 = &GlobalVar.dataSet[DATASET_MONITOR_GSENSOR_X];
	JDataSet *pDS3 	 = &GlobalVar.dataSet[DATASET_MONITOR_GSENSOR_Y];
	JDataSet *pDS4 	 = &GlobalVar.dataSet[DATASET_MONITOR_GSENSOR_Z];
	
	JINT *pDSTimeMS0 = &GlobalVar.iDataSetTime[DATASET_MONITOR_ECG_DS0];
	JINT *pDSTimeMS1 = &GlobalVar.iDataSetTime[DATASET_MONITOR_ECG_DS1];

	JINT *pDSTimeMS2 = &GlobalVar.iDataSetTime[DATASET_MONITOR_ECG_DS1];
	JINT *pDSTimeMS3 = &GlobalVar.iDataSetTime[DATASET_MONITOR_ECG_DS1];
	JINT *pDSTimeMS4 = &GlobalVar.iDataSetTime[DATASET_MONITOR_ECG_DS1];

	VscModeControlType *pVscMode = NULL;

	JINT i = 0;
	JFLOAT fGSenX[VSC_MODE_GSENSOR_DATA_COUNT];
	JFLOAT fGSenY[VSC_MODE_GSENSOR_DATA_COUNT];
	JFLOAT fGSenZ[VSC_MODE_GSENSOR_DATA_COUNT];

	if(GlobalVar.bVscModeAdded == FALSE)
	{
		return;
	}

	GlobalVar.bVscModeAdded = FALSE;
	while (1)
	{
		if(GlobalVar.iVscModeArrIdxRead == GlobalVar.iVscModeArrIdx)
		{
			break;
		}
		pVscMode = &GlobalVar.vscModeArr[GlobalVar.iVscModeArrIdxRead];

		///------------------------------------------------------------------------------------------///
		///  Save VscMode Data
		///------------------------------------------------------------------------------------------///
		if(GlobalVar.bVscModeSave == TRUE)
		{
			VscModeSave(pVscMode);		
		}

		///------------------------------------------------------------------------------------------///
		///  Chart Data of ECG Set
		///------------------------------------------------------------------------------------------///
		JDataSetFIFOAdd(pDS0, (JFLOAT *)&pVscMode->fValueCH[0], VSC_MODE_CAHNNEL_DATA_COUNT, 3000);
		JDataSetFIFOAdd(pDS1, (JFLOAT *)&pVscMode->fValueCH[1], VSC_MODE_CAHNNEL_DATA_COUNT, 3000);

		///------------------------------------------------------------------------------------------///
		///  Chart Data of Gsensor Set
		///------------------------------------------------------------------------------------------///
		for(i = 0 ; i < VSC_MODE_GSENSOR_DATA_COUNT; i = i + 1)
		{
			fGSenX[i] = (JFLOAT)pVscMode->sGSenX[i] / 100;
			fGSenY[i] = (JFLOAT)pVscMode->sGSenY[i] / 100;
			fGSenZ[i] = (JFLOAT)pVscMode->sGSenZ[i] / 100;
		}

		JDataSetFIFOAdd(pDS2, &fGSenX[0], VSC_MODE_GSENSOR_DATA_COUNT, 150);
		JDataSetFIFOAdd(pDS3, &fGSenY[0], VSC_MODE_GSENSOR_DATA_COUNT, 150);
		JDataSetFIFOAdd(pDS4, &fGSenZ[0], VSC_MODE_GSENSOR_DATA_COUNT, 150);

		*pDSTimeMS0 = *pDSTimeMS0 + 200;
		*pDSTimeMS1 = *pDSTimeMS1 + 200;

		GlobalVar.iVscModeArrIdxRead = (GlobalVar.iVscModeArrIdxRead + 1) % VSC_MODE_ARR_LEN;
	}
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

///------------------------------------------///
/// MainLoop Start
///------------------------------------------///
void MainLoopStart(void)
{
	JINT iErr = 0;

	///--------------------------------------------------------------------------------///
	/// Seperate APP and Function 
	///--------------------------------------------------------------------------------///
	iErr = pthread_create(&GlobalVar.tid1, NULL, &ThreadMainLoop, NULL);	
	if(iErr != 0)
	{
		printf("can't create thread :[%s]\r\n", strerror(iErr));
	}
	else
	{		
		pthread_detach(GlobalVar.tid1);		
	}
}
///------------------------------------------///
/// SubLoop Start
///------------------------------------------///
void SubLoopStart(void)
{
	JINT iErr = 0;

	///--------------------------------------------------------------------------------///
	/// Seperate APP and Function 
	///--------------------------------------------------------------------------------///
	iErr = pthread_create(&GlobalVar.tid3, NULL, &ThreadSubLoop, NULL);	
	if(iErr != 0)
	{
		printf("can't create thread :[%s]\r\n", strerror(iErr));
	}
	else
	{		
		pthread_detach(GlobalVar.tid3);		
	}
}

///------------------------------------------///
/// MainLoop
///------------------------------------------///
void MainLoop(void)
{
	while(1)
	{
		TaskRoundInit();
				
		TaskSerialPort();

		TaskBleSReg();

		TaskBleControl();

		TaskBleState();

		TaskBleVscMode();

		TaskRoundEnd();		
		
		if(GlobalVar.bAppExit == TRUE)
		{
			break;
		}
	}

	ConfigSave();

	printf("\r\nbyebye\r\n");
	return;
}

///------------------------------------------///
/// SubLoop
///------------------------------------------///
void SubLoop(void)
{
	while(1)
	{		
		TaskBleVscMode();		

		UtilMsSleep(5);

		if(GlobalVar.bAppExit == TRUE)
		{
			break;
		}							
	}
}