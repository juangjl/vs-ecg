/**
 * @file Func.cpp
 *
 *  Function
 *
 * @version $Revision$
 * @author JLJuang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021, VitalSigns Technology Co., Ltd., all rights reserved.
 */
#include "Global.h"

#define JECG_SEGMENT_TIME (6)

JBOOL FuncBleOpenCheck(void)
{
	JINT iErrNo = NO_ERR;
	JINT iRet = 0;

	JBOOL bConnect = FALSE;

	///----------------------------------------------------------------///
	/// Connection
	///----------------------------------------------------------------///
	iErrNo = CmdMBleConnectStatus(&GlobalVar.bBleConnected);
	if(iRet != NO_ERR)
	{		
		GlobalVar.dwSysSta5 &= ~SYS_STA5_SERIAL_PORT_OPEN;		
		return FALSE;
	}
	return TRUE;
}

JBOOL FuncVSDongleOpen(char *strPortName)
{
	JBOOL bSerialOpen = FALSE;

	SERIAL_PORT_NAME_SET(strPortName);
	bSerialOpen = SERIAL_PORT_OPEN();
	if(bSerialOpen == TRUE)
	{
		GlobalVar.bSerialPortOpen = TRUE;		
	}
	else
	{
		GlobalVar.bSerialPortOpen = FALSE;
		return FALSE;
	}
	return TRUE;
}

JBOOL FuncVSDongleClose(void)
{
	JINT iErrNo = NO_ERR;
	JBOOL bRet = TRUE;

	JBOOL bConnect = FALSE;
	GlobalVar.bSerialPortOpen = FALSE;
	SERIAL_PORT_CLOSE();
	
	return bRet;
}

JBOOL FuncVSDongleVersionGet(void)
{
	JINT iErrNo = NO_ERR;
	
	iErrNo = CmdSysVersion();
	
	if(iErrNo != NO_ERR)
	{
		return FALSE;
	}
	return TRUE;
}

JBOOL FuncVSDongleTimeSet(void)
{
	JINT iErrNo = NO_ERR;
	time_t t = time(NULL);
	JTM jtm;
		
	UtilLocalTime(&jtm, t);
	iErrNo = CmdSysTimeSet(&jtm);	
	if(iErrNo != NO_ERR)
	{
		return FALSE;
	}
	return TRUE;
}

JBOOL FuncMBleScan(void)
{
	JINT iErrNo = NO_ERR;
	JINT i = 0;
	BleDeviceItemType *pItem = NULL;
	char msg[256];
	iErrNo = CmdMBleScan();
	JWORD wRSSI = 0;

	if(iErrNo == NO_ERR)
	{		
		sprintf(msg, "[MBLE] device count = %d \r\n", GlobalVar.BleDeviceList.iCnt);
		DBG_PRINTF(msg);
		for(i = 0 ; i < GlobalVar.BleDeviceList.iCnt; i = i + 1)
		{
			pItem =  &GlobalVar.BleDeviceList.BleDeviceItems[i];						
			if(pItem->bRSSI & 0x80)
			{
				wRSSI = 0xFF00 + *(JBYTE *)&pItem->bRSSI;
			}
			else
			{
				wRSSI =  *(JBYTE *)&pItem->bRSSI;
			}
			printf("\t#%-2d: %-24s, %02X-%02X-%02X-%02X-%02X-%02X, %02d db\r\n",  
							i,
							pItem->name,
							pItem->bAddr[0], pItem->bAddr[1], pItem->bAddr[2],
							pItem->bAddr[3], pItem->bAddr[4], pItem->bAddr[5],
							*(JSHORT *)&wRSSI);
		}
	}
	else
	{
		printf("\t [ERROR] Failed to scan device\r\n");
	}

	return TRUE;
}

JBOOL FuncMBleSelect(void)
{
	JINT iNum = 0;
	JINT iRet = 0;
	char strBleDeviceName[256];
	char strBleDeviceMac[256];
	BleDeviceItemType *pBleDeviceItem = NULL;
	char msg[256];

	if(GlobalVar.BleDeviceList.iCnt < 0)
	{
		sprintf(msg, "\t\t [ERROR] There is no device scanned\r\n");
		return FALSE;
	}

	///------------------------------------------------------------///
	/// Select a device
	///------------------------------------------------------------///
	printf("Select a device (0 ~ %d): ", (GlobalVar.BleDeviceList.iCnt - 1));
	iRet = scanf("%d", &iNum);		
	if(iRet > 0)
	{
		if((iNum >= 0) && (iNum < GlobalVar.BleDeviceList.iCnt))
		{
			pBleDeviceItem = &GlobalVar.BleDeviceList.BleDeviceItems[iNum];

			sprintf(strBleDeviceName, "%s", pBleDeviceItem->name);
			sprintf(strBleDeviceMac, 	"%02X:%02X:%02X:%02X:%02X:%02X", 
							pBleDeviceItem->bAddr[0], pBleDeviceItem->bAddr[1], pBleDeviceItem->bAddr[2], 
							pBleDeviceItem->bAddr[3], pBleDeviceItem->bAddr[4], pBleDeviceItem->bAddr[5]);
			ConfigStrSet((char *)CONFIG_ITEM_BLE_DEVICE_NAME, strBleDeviceName);			
			ConfigStrSet((char *)CONFIG_ITEM_BLE_DEVICE_MAC, 	strBleDeviceMac); 	

			/// selected device information print
			sprintf(msg, "NAME : %s \r\n", strBleDeviceName);
			DBG_PRINTF(msg);
			sprintf(msg, "MAC  : %s \r\n", strBleDeviceMac);
			DBG_PRINTF(msg);

			return TRUE;		
		}
	}		
	
	sprintf(msg, "\t\t device selected\r\n");
	return FALSE;	
}

JBOOL FuncMBleOpen(void)
{
	JINT iErrNo = NO_ERR;
	
	JDWORD dwMacAddr[6];

	char strMacAddr[256];

	/// Get the name
	ConfigStrGet((char *)CONFIG_ITEM_BLE_DEVICE_NAME, &GlobalVar.strBleDeviceName[0]);

	/// Get the mac
	ConfigStrGet((char *)CONFIG_ITEM_BLE_DEVICE_MAC, 	&strMacAddr[0]);
		
	sscanf(strMacAddr, "%02X:%02X:%02X:%02X:%02X:%02X",
				(unsigned int *)&dwMacAddr[0], (unsigned int *)&dwMacAddr[1], (unsigned int *)&dwMacAddr[2],
				(unsigned int *)&dwMacAddr[3], (unsigned int *)&dwMacAddr[4], (unsigned int *)&dwMacAddr[5]);

	GlobalVar.bBleMacAddr[0] = (JBYTE)dwMacAddr[0];
	GlobalVar.bBleMacAddr[1] = (JBYTE)dwMacAddr[1];
	GlobalVar.bBleMacAddr[2] = (JBYTE)dwMacAddr[2];
	GlobalVar.bBleMacAddr[3] = (JBYTE)dwMacAddr[3];
	GlobalVar.bBleMacAddr[4] = (JBYTE)dwMacAddr[4];
	GlobalVar.bBleMacAddr[5] = (JBYTE)dwMacAddr[5];

	
	CmdMBleOpen(&GlobalVar.bBleMacAddr[0]);

	///------------------------------------------------------------///
	/// Connect Device
	///------------------------------------------------------------///

	return TRUE;
}

JBOOL FuncMBleOpenCheck(JINT iSec)
{
	JINT iErrNo = NO_ERR;	
	JINT iMS = 0;
	char msg[256];

	GlobalVar.bBleConnected = FALSE;
	
	sprintf(msg, "Device connect start\r\n");
	DBG_PRINTF(msg);

	while(1)
	{
		///----------------------------------------------------------------///
		/// Connection
		///----------------------------------------------------------------///
		iErrNo = CmdMBleConnectStatus(&GlobalVar.bBleConnected);
		if(iErrNo != NO_ERR)
		{			
			return FALSE;
		}

		if(GlobalVar.bBleConnected == TRUE)
		{
			sprintf(msg, "Device connected\r\n");
			DBG_PRINTF(msg);			
			return TRUE;
		}

		/// timeout check
		UtilMsSleep(100);
		iMS = iMS + 100;
		if(iMS >= iSec * 1000)
		{
			break;
		}

	}
	
	sprintf(msg, "Failed to connect device %s \r\n", GlobalVar.strBleDeviceName);
	DBG_PRINTF(msg);

	return TRUE;
}

JBOOL FuncMBleClose(void)
{
	JINT iErrNo = NO_ERR;

	/// BLE Close
	CmdMBleClose();

	return TRUE;
}

JBOOL FuncSBleSysVersionGet(void)
{
	JINT iErrNo = NO_ERR;
	JINT i = 0;
	JINT iCnt = 1;
	char msg[256];

	JINT iBleVersion;
  char strBleDeviceName[256];

	if(GlobalVar.bBleConnected == FALSE)
	{
		return FALSE;
	}

	///----------------------------------------------------------///
	/// Read version
	///----------------------------------------------------------///
	iErrNo = CmdSBleSysVersionGet((char *)&strBleDeviceName[0], &iBleVersion);
	if(iErrNo != NO_ERR)
	{			
		sprintf(msg, "[ERROR] Version Read Failed\r\n");
		DBG_PRINTF(msg);		
		return  FALSE;
	}

	GlobalVar.iBleVersion = iBleVersion;
	strcpy((char *)&GlobalVar.strBleModelName[0], (char *)&strBleDeviceName[0]);

	sprintf(msg, "\t\t Model Name    = %s\r\n", GlobalVar.strBleModelName);
	DBG_PRINTF(msg);
	sprintf(msg, "\t\t Model Version = %d\r\n", GlobalVar.iBleVersion);
	DBG_PRINTF(msg);
		
	return TRUE;
}

JBOOL FuncSBleSysSsnGet(void)
{
	JINT iErrNo = NO_ERR;
	JINT i = 0;
	JINT iCnt = 1;
	char msg[256];

  char strSsn[256];

	if(GlobalVar.bBleConnected == FALSE)
	{
		return FALSE;
	}
	
	///----------------------------------------------------------///
	/// Read version
	///----------------------------------------------------------///
	iErrNo = CmdSBleSysSsnGet((char *)&strSsn[0]);
	if(iErrNo != NO_ERR)
	{			
		sprintf(msg, "[ERROR] SSN GetFailed\r\n");
		DBG_PRINTF(msg);		
		return  FALSE;
	}

	strcpy((char *)&GlobalVar.strSSN[0], (char *)&strSsn[0]);
		
	return TRUE;
}

JBOOL FuncVscModeCreateFolder(JTM jtm)
{
	char msg[256];
	char strFolderName[512];

	sprintf(strFolderName, "%s/VS",	(char *)&GlobalVar.strDataDir[0]);
	UtilFolderCreate(strFolderName);
	if(UtilFolderExisted(strFolderName) == FALSE)
	{
		DBG_PRINTF("[ERROR] Folder create failed, permisssion denied - 01");		
	}

	/// Create SNN
	sprintf(strFolderName, "%s/VS/%s", 
						(char *)&GlobalVar.strDataDir[0], 
						(char *)&GlobalVar.strSSN[0]);
	UtilFolderCreate(strFolderName);
	if(UtilFolderExisted(strFolderName) == FALSE)
	{
		DBG_PRINTF("[ERROR] Folder create failed, permisssion denied - 02");	
	}

	/// Create YYYY-MM-DD
	sprintf(strFolderName, "%s/VS/%s/%04d%02d%02d_%02d%02d%02d",
						(char *)&GlobalVar.strDataDir[0], 
						(char *)&GlobalVar.strSSN[0], 
						jtm.iYear, jtm.iMonth, jtm.iDay,
						jtm.iHour, jtm.iMin, jtm.iSec);
	UtilFolderCreate(strFolderName);
	if(UtilFolderExisted(strFolderName) == FALSE)
	{
		DBG_PRINTF("[ERROR] Folder create failed, permisssion denied - 02");	
	}
	sprintf(msg, "[VSC][INIT] Folder = '%s'\r\n, ", strFolderName);
	DBG_PRINTF(msg);
	
 	strcpy(GlobalVar.strVscBaseFolder, strFolderName);
	return TRUE;
}

JBOOL FuncVscModeInit(void)
{
	char strFolderName[256];
	
	JTM jtm;	
	time_t t = time(NULL);

	GlobalVar.bVscModeReadOn = FALSE;

	///-------------------------------------------------------------------------///
	/// Folder Create
	///-------------------------------------------------------------------------///
	
	/// Get local time
	JTMLocalTimeGet(&jtm, t);

	if(GlobalVar.bVscModeSave == TRUE)
	{
		/// Create VS folder
		sprintf(strFolderName, "%s/data/VS", 
							(char *)&GlobalVar.strCurDir[0]);
		UtilFolderCreate(strFolderName);

		/// Create SNN
		sprintf(strFolderName, "%s/data/VS/%s", 
							(char *)&GlobalVar.strCurDir[0], 
							(char *)&GlobalVar.strSSN[0]);
		UtilFolderCreate(strFolderName);

		/// Create YYYY-MM-DD
		sprintf(strFolderName, "%s/data/VS/%s/%04d%02d%02d_%02d%02d%02d",
							(char *)&GlobalVar.strCurDir[0], 
							(char *)&GlobalVar.strSSN[0], 
							jtm.iYear, jtm.iMonth, jtm.iDay,
							jtm.iHour, jtm.iMin, jtm.iSec);
		UtilFolderCreate(strFolderName);
	}

	VscModeInit((char *)&strFolderName[0]);	

	///------------------------------------------------------------///
	/// Data Set Reset
	///------------------------------------------------------------///
	GlobalVar.iDataSetTime[DATASET_MONITOR_ECG_DS0] = 0;
	GlobalVar.iDataSetTime[DATASET_MONITOR_ECG_DS1] = 0;
	GlobalVar.iDataSetTime[DATASET_MONITOR_ECG_DS2] = 0;

	JDataSetReset(&GlobalVar.dataSet[DATASET_MONITOR_ECG_DS0]);
	JDataSetReset(&GlobalVar.dataSet[DATASET_MONITOR_ECG_DS1]);
	JDataSetReset(&GlobalVar.dataSet[DATASET_MONITOR_ECG_DS2]);
	
	return TRUE;
}

JBOOL FuncVscModeStart(void)
{
	JINT iErrNo = NO_ERR;
	char msg[256];	

	/// VSH101 VSC MODE Start
	iErrNo = CmdSBleVscModeStart();
	if(iErrNo != NO_ERR)
	{			
		sprintf(msg, "[ERROR] VSC Mode start failed\r\n");
		DBG_PRINTF(msg);		
		return  FALSE;
	}		

	GlobalVar.bVscModeReadOn = FALSE;
	GlobalVar.iBleState = BLE_STATE_VSC_MODE;
	

	GlobalVar.dwVscModeSec =  0;

	return TRUE;
}

JBOOL FuncVscModeStop(void)
{
	JINT iErrNo = NO_ERR;
	char msg[256];	

	/// VSH101 VSC MODE Start
	iErrNo = CmdSBleVscModeStop();
	if(iErrNo != NO_ERR)
	{			
		sprintf(msg, "[ERROR] VSC Mode start failed\r\n");
		DBG_PRINTF(msg);		
		return  FALSE;
	}		
	return TRUE;
}

JBOOL FuncVscModeRead(JINT iSecTotal)
{	
	JINT t0 = 0;
	JINT t1 = 0;
	JINT iSecNow= 0;
	JINT iSecPre= 0;
	char msg[256];
	JINT i = 0;

	printf("VSC MODE READ  total = %d \r\n", iSecTotal);

	/// inital delay  2 seconds for wait 
	UtilMsSleep(2000);

	t0 = (JINT)time(NULL);
	t1 = (JINT)time(NULL);

  while(1)
	{		
		iSecNow = t1 - t0;
		if(iSecNow >= iSecTotal)
		{
			sprintf(msg, "\t VSC MODE READ -> (now / total) =  %-3d / %-3d SEC \r\n", iSecNow, iSecTotal);
			DBG_PRINTF(msg);
			break;
		}
		if(iSecNow != iSecPre)
		{		
			sprintf(msg, "\t VSC MODE READ -> (now / total) =  %-3d / %-3d SEC \r\n", iSecNow, iSecTotal);
			DBG_PRINTF(msg);
			iSecPre = iSecNow;
		}
		CmdSBleVscModeRead();
		
		UtilMsSleep(40);	
		t1 = (JINT)time(NULL);		
	}
	
	return TRUE;
}

#ifdef FEATURE_JGATT
JBOOL FuncJGattVscModeStart(void)
{
	JINT errNo = NO_ERR;	
	
	JTM jtm;	
	time_t t = time(NULL);
	VscModeControlType *pVscMode = &VscModeCtl;
	char msg[256];
	char strFolderName[512];
	
	///-------------------------------------------------------------------------///
	/// Folder Create
	///-------------------------------------------------------------------------///
	JTMLocalTimeGet(&jtm, t);

	/// Create VS folder
	if(GlobalVar.bVscModeSave == TRUE)
	{
		FuncVscModeCreateFolder(jtm);
		sprintf(msg, "[VSC][INIT][GATT] Folder = '%s'\r\n, ", GlobalVar.strVscBaseFolder);
		DBG_PRINTF(msg);
	}

	///-------------------------------------------------------------------------///
	/// Vsc Mode Init
	///-------------------------------------------------------------------------///
	VscModeInit(GlobalVar.strVscBaseFolder);		

		
	///------------------------------------------------------------///
	/// Data Set Reset
	///------------------------------------------------------------///
	GlobalVar.iDataSetTime[DATASET_MONITOR_ECG_DS0] = 0;
	GlobalVar.iDataSetTime[DATASET_MONITOR_ECG_DS1] = 0;
	GlobalVar.iDataSetTime[DATASET_MONITOR_ECG_DS2] = 0;

	JDataSetReset(&GlobalVar.dataSet[DATASET_MONITOR_ECG_DS0]);
	JDataSetReset(&GlobalVar.dataSet[DATASET_MONITOR_ECG_DS1]);
	JDataSetReset(&GlobalVar.dataSet[DATASET_MONITOR_ECG_DS2]);


	///------------------------------------------------------------///
	/// VSC ATR INIT
	///------------------------------------------------------------///
	FuncVscAtrInit();
			
	DBG_PRINTF("[TASK][GATT] VSC_MODE START\r\n");			
	return TRUE;
}
#endif ///< for FEATURE_JGATT

JBOOL FuncSRegRead(char *strRegName)
{
	SRegType *pSReg = &GlobalVar.SReg;
	if(GlobalVar.bSRegOn == TRUE)
	{
		return FALSE;
	}
	/// Set name
	UtilMemset((JBYTE *)&pSReg->strName[0], 0x00, SREG_NAME_SIZE);
	strcpy(pSReg->strName, strRegName);

	GlobalVar.bSRegOn		 = TRUE;
	GlobalVar.bSRegWrite = FALSE;
	return TRUE;
}

JBOOL FuncSRegWrite(char *strRegName, JBYTE *pbData)
{
	SRegType *pSReg = &GlobalVar.SReg;
	if(GlobalVar.bSRegOn == TRUE)
	{		
		return FALSE;
	}
	
	/// Set name
	UtilMemset((JBYTE *)&pSReg->strName[0], 0x00, SREG_NAME_SIZE);
	strcpy(pSReg->strName, strRegName);

	/// Copy data for write
	UtilMemcpy((JBYTE *)&pSReg->bData[0], (JBYTE *)&pbData[0], SREG_DATA_SIZE);

	
	GlobalVar.bSRegOn		 = TRUE;
	GlobalVar.bSRegWrite = TRUE;
	return TRUE;
}

JBOOL FuncSerialPortDetect(void)
{
	char strFileName[256];
	char strCmd[256];
	FILE * fp = NULL;
	char line[256];
	JINT iRet = 0;
	char str[256];
	JINT i = 0;	
	JINT iCnt = 0;

	sprintf(strFileName, "%s/data/ports.txt", GlobalVar.strCurDir);
	/// remove previous saved file
	sprintf(strCmd, "rm -f %s", strFileName);
	system(strCmd);

	if(GlobalVar.iOSType == OS_TYPE_MAC_OS)
	{
		sprintf(strCmd, "ls /dev/cu.usbserial* > %s", strFileName);
		system(strCmd);				
	}
	if(GlobalVar.iOSType == OS_TYPE_UBUNTU)
	{
		sprintf(strCmd, "ls /dev/ttyUSB* > %s", strFileName);
		system(strCmd);				
	}
	if(GlobalVar.iOSType == OS_TYPE_WINDOWS)
	{
#if OS_TYPE == OS_TYPE_WINDOWS
		HANDLE handle = INVALID_HANDLE_VALUE;
		char port[256];
		JINT com_check_flag = 0;
 		printf("Detecting port...\n");    
   	for(i = 0; i < 256; i = i + 1)
    {
			sprintf(port, "\\\\.\\COM%d", i);

			handle = CreateFile(port, GENERIC_READ | GENERIC_WRITE,0,0, OPEN_EXISTING, 0, 0);
			if(handle==INVALID_HANDLE_VALUE)
			{
				continue;
			}
			else
			{
				CloseHandle(handle);				
				handle = INVALID_HANDLE_VALUE;
				sprintf(line , "COM%d",i);												
				strcpy(&GlobalVar.strSerialPortArr[iCnt][0], line);
				iCnt = iCnt + 1;
			}
	  }
		GlobalVar.iSerialPortArrCnt = iCnt;	
#endif ///< for 		OS_TYPE_WINDOWS
	}	
	
	if(GlobalVar.iOSType != OS_TYPE_WINDOWS)
	{
		iCnt = 0;
		fp = fopen(strFileName , "r");
		if(fp == NULL)
		{
			return FALSE;
		}
		while(1)
		{
			iRet = fscanf(fp, "%[^\n]\n", line);
			if(iRet<= 0)
			{
				break;
			}
			sprintf(str, "%s\n", line);		
			if(i < 10)
			{
				strcpy(&GlobalVar.strSerialPortArr[iCnt][0], line);
				iCnt = iCnt + 1;
			}
		}
		fclose(fp);
		GlobalVar.iSerialPortArrCnt = iCnt;	
	}
	return TRUE;
}

JBOOL FuncEcgFileDataGet(JINT iTimeMS, JDataSet *pDataSet)
{	
	JINT iSampleRate  = JDATA_SAMPLE_RATE;
	JINT iDataIdx = iTimeMS / (1000 / iSampleRate);
	JINT iDataCnt = 0;
	char msg[256];
	if(GlobalVar.iFileDataCnt <= 0)
	{
		return FALSE;
	}

	if((GlobalVar.iFileDataCnt - iDataIdx) >=  3000)
	{
		iDataCnt = 3000;
	}
	else
	{	
		iDataCnt = (GlobalVar.iFileDataCnt - iDataIdx);
	}

	if(iDataCnt <= 0)
	{
		sprintf(msg, "[LOAD][ERROR] IDX = %d, TOTAL_DATA_CNT = %d\r\n",
							iDataIdx, GlobalVar.iFileDataCnt);
		DBG_PRINTF(msg);
		return FALSE;
	}

	JDataSetReset(pDataSet);
	UtilMemcpy((JBYTE *)&pDataSet->data[0], (JBYTE *)&GlobalVar.fFileData[iDataIdx], iDataCnt * sizeof(JFLOAT));	
	pDataSet->cnt = iDataCnt;
	return TRUE;
}

JBOOL FuncEcgFileDataLoad(char *pFilePath)
{
	char msg[256];
	FILE 	* fp = NULL;
	JFLOAT 	fValue = 0;
	JINT iRet = 0;
	JINT iSampleRate = JDATA_SAMPLE_RATE;
	JFLOAT fResolution = 1;

	JINT i = 0;
	char line[256];
	char strFolderName[256];
	char strFileName[256];
	char strResoFilePath[256];	
	JINT iLen = 0;
	///------------------------------------------------------------------------------------///
	/// Check file existed
	///------------------------------------------------------------------------------------///
	if(UtilFileExisted(pFilePath) == FALSE)
	{
		sprintf(msg, "[LOAD][DATA][ERROR] %s is not existed\r\n", pFilePath);
		DBG_PRINTF(msg);
		return FALSE;
	}

	///------------------------------------------------------------------------------------///
	/// Resolution file load
	///------------------------------------------------------------------------------------///
	UtilFileFolderGet(pFilePath, (char *)&strFolderName[0]);
	UtilFileNameGet(pFilePath, (char *)&strFileName[0]);

	if(strlen(strFolderName) == 0)
	{
		sprintf(msg, "%s", "[LOAD][DATA][ERROR] Folder is not existed\r\n");
		DBG_PRINTF(msg);
		return FALSE;
	}

	if(strlen(strFileName) <= 4)
	{
		sprintf(msg, "%s", "[LOAD][DATA][ERROR] FileName is not existed\r\n");
		DBG_PRINTF(msg);
		return FALSE;
	}
	iLen = strlen(strFileName);

	strFileName[iLen - 4] = 0;

	sprintf(strResoFilePath, "%s/%s.reso", strFolderName, strFileName);
	
	fp = fopen(strResoFilePath, "r");
	if(fp != NULL)
	{
		fscanf(fp, "%f", &fResolution);
		fclose(fp);
		sprintf(msg, "[LOAD][DATA] RESOLUTION = %0.3f\r\n", fResolution);
		DBG_PRINTF(msg);
	}

	///------------------------------------------------------------------------------------///
	/// File open
	///------------------------------------------------------------------------------------///
	fp = fopen(pFilePath, "r");
	if(fp == NULL)
	{
		sprintf(msg, "[LOAD][DATA][ERROR] %s open failed\r\n", pFilePath);
		DBG_PRINTF(msg);
		return FALSE;
	}
	GlobalVar.iFileDataCnt = 0;
	while(1)
	{
		iRet = fscanf(fp, "%[^\n]\n", &line[0]);
		if(iRet <=0)
		{
			break;
		}
		iLen = strlen(line);
		for(i = 0; i < iLen; i = i + 1)
		{
			if(line[i] == ',')
			{
				line[i] = 0;
			}
			if(line[i] == ' ')
			{
				line[i] = 0;
			}
			if(line[i] == '\t')
			{
				line[i] = 0;
			}
		}
		iRet = sscanf(line, "%f", &fValue);
		if(iRet <=0)
		{
			break;
		}
		if(GlobalVar.iFileDataCnt < FILE_DATA_MAX_SIZE)
		{
			GlobalVar.fFileData[GlobalVar.iFileDataCnt] = fValue * fResolution;
			GlobalVar.iFileDataCnt = GlobalVar.iFileDataCnt  + 1;
		}
		else
		{
			DBG_PRINTF("[LOAD][ERROR] File Size overflow !!!! \r\n");
			break;
		}
	}	
	fclose(fp);
	
	///------------------------------------------------------------------------------------///
	///  Set total time
	///------------------------------------------------------------------------------------///
	GlobalVar.iFileTimeMSNow 	 = 0;
	GlobalVar.iFileTimeMSTotal = GlobalVar.iFileDataCnt  * 1000 / iSampleRate;

	sprintf(msg, "[LOAD][DATA] TOTAL_COUNT = %d \r\n", GlobalVar.iFileDataCnt);
	DBG_PRINTF(msg);
	sprintf(msg, "[LOAD][DATA] TOTAL_TIME = %0.3f sec\r\n", (JFLOAT)GlobalVar.iFileTimeMSTotal / 1000.0);
	DBG_PRINTF(msg);


	return TRUE;
}

JBOOL FuncVscInfoDataParse(VscInfoType *pVscInfo, char *line)
{
	char *pStr = NULL;
	
	/// YEAR
	pStr = strtok(line, ",");
	sscanf(pStr, "%d,", &pVscInfo->jtm.iYear);

	/// MONTH
	pStr = strtok(NULL, ",");
	sscanf(pStr, "%d,", &pVscInfo->jtm.iMonth);

	/// DAY
	pStr = strtok(NULL, ",");
	sscanf(pStr, "%d,", &pVscInfo->jtm.iDay);

	/// HOUR
	pStr = strtok(NULL, ",");
	sscanf(pStr, "%d,", &pVscInfo->jtm.iHour);

	/// MIN
	pStr = strtok(NULL, ",");
	sscanf(pStr, "%d,", &pVscInfo->jtm.iMin);

	/// SEC
	pStr = strtok(NULL, ",");
	sscanf(pStr, "%d,", &pVscInfo->jtm.iSec);

	/// MS
	pStr = strtok(NULL, ",");
	sscanf(pStr, "%d,", &pVscInfo->jtm.iMS);

	/// VSC_MODE_INFO_TYPE0_TIME_UTC								(1)	
	pStr = strtok(NULL, ",");
	sscanf(pStr, "%d,", &pVscInfo->dwUTC);

	/// VSC_MODE_INFO_TYPE0_TEMP_T									(2)
	pStr = strtok(NULL, ",");
	sscanf(pStr, "%f,", &pVscInfo->fTemp);
	
	/// VSC_MODE_INFO_TYPE0_ECG_HR									(3)
	pStr = strtok(NULL, ",");
	sscanf(pStr, "%f,", &pVscInfo->fHRNow);

	/// VSC_MODE_INFO_TYPE0_ECG_LEAD_OFF						(4)
	pStr = strtok(NULL, ",");
	sscanf(pStr, "%f,", 	&pVscInfo->fLeadOff);

	/// VSC_MODE_INFO_TYPE0_GSEN_X									(5)
	pStr = strtok(NULL, ",");
	sscanf(pStr, "%f,", &pVscInfo->fGsenXNow);

	/// VSC_MODE_INFO_TYPE0_GSEN_Y									(6)
	pStr = strtok(NULL, ",");
	sscanf(pStr, "%f,", &pVscInfo->fGsenYNow);

	/// VSC_MODE_INFO_TYPE0_GSEN_Z									(7)
	pStr = strtok(NULL, ",");
	sscanf(pStr, "%f,", &pVscInfo->fGsenZNow);

	/// VSC_MODE_INFO_TYPE0_BATT_SOC								(8)
	pStr = strtok(NULL, ",");
	sscanf(pStr, "%f,", 	&pVscInfo->fBattSoc);

	/// VSC_MODE_INFO_TYPE0_BATT_TOTAL_SEC					(9)
	pStr = strtok(NULL, ",");
	sscanf(pStr, "%f,", 	&pVscInfo->fBattTotalSec);

	/// VSC_MODE_INFO_TYPE0_HRV_SDNN								(10)
	pStr = strtok(NULL, ",");
	sscanf(pStr, "%f,", &pVscInfo->fHrvSDNN);
	
	/// VSC_MODE_INFO_TYPE0_HRV_NN50								(11)
	pStr = strtok(NULL, ",");
	sscanf(pStr, "%f,", &pVscInfo->fHrvNN50);

	/// VSC_MODE_INFO_TYPE0_HRV_RMSSD								(12)
	pStr = strtok(NULL, ",");
	sscanf(pStr, "%f,", &pVscInfo->fHrvRMSSD);

	/// VSC_MODE_INFO_TYPE0_HRV_RR									(13)
	pStr = strtok(NULL, ",");
	sscanf(pStr, "%f,", &pVscInfo->fHrvRR);

	/// VSC_MODE_INFO_TYPE0_HRV_VLF									(14)
	pStr = strtok(NULL, ",");
	sscanf(pStr, "%f,", &pVscInfo->fHrvVLF);

	/// VSC_MODE_INFO_TYPE0_HRV_LF									(15)
	pStr = strtok(NULL, ",");
	sscanf(pStr, "%f,", &pVscInfo->fHrvLF);

	/// VSC_MODE_INFO_TYPE0_HRV_HF									(16)
	pStr = strtok(NULL, ",");
	sscanf(pStr, "%f,", &pVscInfo->fHrvHF);
	
	/// TP																					(17)
	pStr = strtok(NULL, ",");												
	sscanf(pStr, "%f,", &pVscInfo->fHrvTP);	
	
	/// LF/TP																				(18)
	pStr = strtok(NULL, ",");												
	sscanf(pStr, "%f,", &pVscInfo->fHrvLFTP);	
	
	/// HF/TP																				(19)
	pStr = strtok(NULL, ",");												
	sscanf(pStr, "%f,", &pVscInfo->fHrvHFTP);	
	
	/// LF/HF																				(20)
	pStr = strtok(NULL, ",");											
	sscanf(pStr, "%f,", &pVscInfo->fHrvLFHF);
	
	return TRUE;
}

JBOOL FuncVscInfoDataLoad(char *pFilePath)
{
	char msg[256];
	FILE *fp = NULL;
	JINT i = 0;	
	JINT iLen = 0;
	
	char line[1024];
	JINT iLineCnt = 0;
	JINT iRet = 0;
	VscInfoType *pFileInfo = NULL;

	///------------------------------------------------------------------------------------///
	/// Check file existed
	///------------------------------------------------------------------------------------///
	if(UtilFileExisted(pFilePath) == FALSE)
	{
		sprintf(msg, "[LOAD][INFO] %s is not existed\r\n", pFilePath);
		DBG_PRINTF(msg);
		return FALSE;
	}

	///------------------------------------------------------------------------------------///
	/// Info file load
	///------------------------------------------------------------------------------------///
	fp = fopen(pFilePath, "r");
	if(fp == NULL)
	{
		sprintf(msg, "[LOAD][INFO][ERROR] %s open failed\r\n", pFilePath);
		DBG_PRINTF(msg);
		return FALSE;
	}

	GlobalVar.iVscInfoCnt = 0;
	while(1)
	{
		iRet = fscanf(fp, "%[^\n]\n", &line[0]);
		if(iRet <=0)
		{
			break;
		}
		iLineCnt = iLineCnt + 1;
		if(iLineCnt == 1)
		{
			continue;			
		}
		pFileInfo = &GlobalVar.VscInfoArr[GlobalVar.iVscInfoCnt ];
		FuncVscInfoDataParse(pFileInfo, line);
		GlobalVar.iVscInfoCnt = GlobalVar.iVscInfoCnt  + 1;
	}

	fclose(fp);
	
	sprintf(msg, "[LOAD][INFO] INFO_COUNT = %d (sec)\r\n", GlobalVar.iVscInfoCnt );
	DBG_PRINTF(msg);

	return TRUE;
}

JBOOL FuncAtrDataLoad(AtrCtlType *pAtrCtl, char *pFilePath)
{
	char msg[256];

	///------------------------------------------------------------------------------------///
	/// Check file existed
	///------------------------------------------------------------------------------------///
	if(UtilFileExisted(pFilePath) == FALSE)
	{
		sprintf(msg, "[LOAD][ATR] %s is not existed\r\n", pFilePath);
		DBG_PRINTF(msg);
		return FALSE;
	}
	
	sprintf(msg, "%s", "[ATR] hihi\r\n");
	DBG_PRINTF(msg);

	AtrCtlLoad(pAtrCtl, pFilePath);

	return TRUE;
}

JBOOL FuncVscAtrInit(void)
{
	AtrCtlInit(&AtrCtlBle);
	GlobalVar.iVscAtrCnt     = 0;
	GlobalVar.bVscAtrUpdated = FALSE;

	return TRUE;
}
