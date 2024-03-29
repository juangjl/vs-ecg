/**
 * @file task.cpp
 *
 *   task function
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

void TaskRoundInit(void)
{
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
			GlobalVar.iBleState = BLE_STATE_CLOSE;
			/// set serial port open failed
			//GlobalVar.dwSysCtl7 |= SYS_CTL7_MSG_SERIAL_PORT_OPEN_FAILED;
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

void TaskGattControl(void)
{	
#ifdef FEATURE_JGATT
	JGattControl();
#endif ///< for	FEATURE_JGATT
}

void TaskBleState(void)
{
	///----------------------------------------------------------------------///
	/// Ble State Machine Control
	///----------------------------------------------------------------------///
	BleState();
}

void TaskRoundEnd(void)
{
	TimerEventClear();
	while(1)
	{
		if(GlobalVar.dwSysCtl2 & SYS_CTL2_TASK_ISR)
		{
			break;
		}
		UtilUsSleep(50);
	}
	GlobalVar.dwSysCtl2 &=~ SYS_CTL2_TASK_ISR;
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
/// MainLoop
///------------------------------------------///
void MainLoop()
{
	while(1)
	{
		TaskRoundInit();
		
		TaskSerialPort();

		TaskBleSReg();
		
		TaskBleControl();

		TaskGattControl();
		
		TaskBleState();
		
		TaskRoundEnd();		
		
		if(GlobalVar.bAppExit == TRUE)
		{
			break;
		}	
		UtilMsSleep(2);	
	}
	return;
}

///----------------------------------------------------------------------------------------///
/// Sub-Task
///----------------------------------------------------------------------------------------///
void SubVscModeGatt(void)
{
#ifdef FEATURE_JGATT	
	char msg[256];
	
	JGattCtlType *pJGattCtl = JGattCtlPtr;
	
	JDataSet *pDS0 	 = &GlobalVar.dataSet[DATASET_MONITOR_ECG_DS0];
	JDataSet *pDS1 	 = &GlobalVar.dataSet[DATASET_MONITOR_ECG_DS1];

	JDataSet *pDS2 	 = &GlobalVar.dataSet[DATASET_MONITOR_GSENSOR_X];
	JDataSet *pDS3 	 = &GlobalVar.dataSet[DATASET_MONITOR_GSENSOR_Y];
	JDataSet *pDS4 	 = &GlobalVar.dataSet[DATASET_MONITOR_GSENSOR_Z];
	
	JINT *pDSTimeMS0 = &GlobalVar.iDataSetTime[DATASET_MONITOR_ECG_DS0];
	JINT *pDSTimeMS1 = &GlobalVar.iDataSetTime[DATASET_MONITOR_ECG_DS1];

	JINT *pDSTimeMS2 = &GlobalVar.iDataSetTime[DATASET_MONITOR_ECG_DS1];
	JINT *pDSTimeMS3 = &GlobalVar.iDataSetTime[DATASET_MONITOR_ECG_DS1];
	JINT *pDSTimeMS4 = &GlobalVar.iDataSetTime[DATASET_MONITOR_ECG_DS1];

	VscModeControlType *pVscMode = NULL;

	JINT 		i = 0;
	JFLOAT 	fGSenX[VSC_MODE_GSENSOR_DATA_COUNT];
	JFLOAT 	fGSenY[VSC_MODE_GSENSOR_DATA_COUNT];
	JFLOAT 	fGSenZ[VSC_MODE_GSENSOR_DATA_COUNT];

	if(pJGattCtl->bVscModeAdded == FALSE)
	{
		return;
	}

	pJGattCtl->bVscModeAdded = FALSE;
	while(1)
	{
		if(pJGattCtl->iVscModeQueueHead == pJGattCtl->iVscModeQueueTail)
		{
			break;
		}
		pVscMode = &pJGattCtl->vscModeQueue[pJGattCtl->iVscModeQueueHead];
		
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
		JDataSetFIFOAdd(pDS0, (JFLOAT *)&pVscMode->fValueCH[0], VSC_MODE_CHANNEL_DATA_COUNT, 3000);
		JDataSetFIFOAdd(pDS1, (JFLOAT *)&pVscMode->fValueCH[1], VSC_MODE_CHANNEL_DATA_COUNT, 3000);

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

		///------------------------------------------------------------------------------------------///
		///   BLE ECG Data Set
		///------------------------------------------------------------------------------------------///
		/// copy CH[0] data
		//UtilMemcpy((JBYTE *)&GlobalVar.fBleEcgData[0], (JBYTE *)&pVscMode->fValueCH[0], VSC_MODE_CHANNEL_DATA_COUNT * sizeof(JFLOAT));
		//GlobalVar.iBleEcgDataCnt = VSC_MODE_CHANNEL_DATA_COUNT;
		//GlobalVar.bBleEcgSet     = TRUE;
		if((pVscMode->wId % 5) == 0)
		{
			UtilMemcpy((JBYTE *)&VscModeCtl, (JBYTE *)pVscMode, sizeof(VscModeControlType));
		}
		pJGattCtl->iVscModeQueueHead = (pJGattCtl->iVscModeQueueHead + 1) % VSC_MODE_QUEUE_SIZE;	
	}
#endif ///< for FEATURE_JGATT	
}

void SubBleVscMode(void)
{
	char msg[256];
	
	JDataSet *pDS0 	 = &GlobalVar.dataSet[DATASET_MONITOR_ECG_DS0];
	JDataSet *pDS1 	 = &GlobalVar.dataSet[DATASET_MONITOR_ECG_DS1];

	JDataSet *pDS2 	 = &GlobalVar.dataSet[DATASET_MONITOR_GSENSOR_X];
	JDataSet *pDS3 	 = &GlobalVar.dataSet[DATASET_MONITOR_GSENSOR_Y];
	JDataSet *pDS4 	 = &GlobalVar.dataSet[DATASET_MONITOR_GSENSOR_Z];
	
	JINT *pDSTimeMS0 = &GlobalVar.iDataSetTime[DATASET_MONITOR_ECG_DS0];
	JINT *pDSTimeMS1 = &GlobalVar.iDataSetTime[DATASET_MONITOR_ECG_DS1];

	JINT *pDSTimeMS2 = &GlobalVar.iDataSetTime[DATASET_MONITOR_ECG_DS1];
	JINT *pDSTimeMS3 = &GlobalVar.iDataSetTime[DATASET_MONITOR_ECG_DS1];
	JINT *pDSTimeMS4 = &GlobalVar.iDataSetTime[DATASET_MONITOR_ECG_DS1];

	VscModeControlType *pVscMode = NULL;

	JINT 		i = 0;
	JFLOAT 	fGSenX[VSC_MODE_GSENSOR_DATA_COUNT];
	JFLOAT 	fGSenY[VSC_MODE_GSENSOR_DATA_COUNT];
	JFLOAT 	fGSenZ[VSC_MODE_GSENSOR_DATA_COUNT];

	JINT 		iSegId      = 0;
	JINT 		iSegTimeMS  = 0;
	JFLOAT 	fSegTimeSec = 0;
	char  	strTimeSec[256];

	if(GlobalVar.bVscModeAdded == FALSE)
	{
		return;
	}

	GlobalVar.bVscModeAdded = FALSE;
	while(1)
	{
		if(GlobalVar.iVscModeQueueHead == GlobalVar.iVscModeQueueTail)
		{
			break;
		}
		pVscMode = &GlobalVar.vscModeQueue[GlobalVar.iVscModeQueueHead];
		
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
		JDataSetFIFOAdd(pDS0, (JFLOAT *)&pVscMode->fValueCH[0], VSC_MODE_CHANNEL_DATA_COUNT, 3000);
		JDataSetFIFOAdd(pDS1, (JFLOAT *)&pVscMode->fValueCH[1], VSC_MODE_CHANNEL_DATA_COUNT, 3000);

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

		///------------------------------------------------------------------------------------------///
		///  Segment time
		///------------------------------------------------------------------------------------------///
		iSegTimeMS = *pDSTimeMS0;		
		if((iSegTimeMS % 4000) == 0)
		{						
			iSegId 			= (JINT)((iSegTimeMS / 4000) - 1);
			fSegTimeSec = (JFLOAT)(iSegId * 4);
			UtilTimeStringGet(fSegTimeSec, strTimeSec);
			sprintf(msg, "\t -------- SEC[%d][%d][%s] -------- VSM-TIME = %04d/%02d/%02d-%02d:%02d:%02d \r\n", 
													iSegId, iSegTimeMS, strTimeSec,													
													pVscMode->jtm.iYear,
													pVscMode->jtm.iMonth,
													pVscMode->jtm.iDay,
													pVscMode->jtm.iHour,
													pVscMode->jtm.iMin,
													pVscMode->jtm.iSec); 
			DBG_PRINTF(msg);
		}

		GlobalVar.iVscModeQueueHead = (GlobalVar.iVscModeQueueHead + 1) % VSC_MODE_ARR_LEN;
	}
}

void SubBleVscAtr(void)
{	
	char msg[256];
	AtrCtlType * pAtrCtl = &AtrCtlBle;	
	JAtrType *pAtrRead = NULL;
	JINT A = 0;
	JFLOAT fTimeSec = 0;
	JAtrType *pAtr = NULL;

	char strFileName[256];

	if(GlobalVar.bVscAtrUpdated == FALSE)
	{
		return;
	}

	while(1)
	{
		if(GlobalVar.iVscAtrQueueHead == GlobalVar.iVscAtrQueueTail)
		{
			break;
		}
		pAtrRead = &GlobalVar.vscAtrQueue[GlobalVar.iVscAtrQueueHead];

		UtilMemcpy((JBYTE *)&GlobalVar.vscAtrPre, (JBYTE *)&GlobalVar.vscAtrNow,  sizeof(JAtrType));	
		UtilMemcpy((JBYTE *)&GlobalVar.vscAtrNow, (JBYTE *)pAtrRead,  sizeof(JAtrType));		
    
		JAtrDataPrint(&GlobalVar.vscAtrNow);		

		GlobalVar.iVscAtrCntPre = GlobalVar.iVscAtrCnt;
		GlobalVar.iVscAtrCnt    = GlobalVar.iVscAtrCnt + 1;
    
		JAtrDataGet(&GlobalVar.vscAtrNow, &A, &fTimeSec);

    AtrCtlAddEx(pAtrCtl, A, fTimeSec);

    /// check the atr data save  
		if(GlobalVar.bVscModeSave == TRUE)
		{
			VscModeAtrBinSave();	
			VscModeAtrCsvSave();	
		}

		GlobalVar.iVscAtrQueueHead  = (GlobalVar.iVscAtrQueueHead  + 1) % VSC_ATR_QUEUE_CNT;
	}				
  
 // sprintf(msg, "\t [ATR][AtrCtlBle]%d\r\n", pAtrCtl->iAtrDataCnt);
 /// DBG_PRINTF(msg);

	GlobalVar.bVscAtrUpdated  = FALSE;	
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
/// SubLoop  (Slow Task Loop)
///------------------------------------------///
void SubLoop(void)
{
	while(1)
	{		
		SubBleVscMode();

		SubVscModeGatt();

		SubBleVscAtr();

		UtilMsSleep(5);

		if(GlobalVar.bAppExit == TRUE)
		{
			break;
		}							
	}
}