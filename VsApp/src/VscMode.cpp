/**
 * @file VscMode.cpp
 *
 *   VscMode
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

VscModeControlType VscModeCtl;

void VscModeInfoParse(VscModeControlType *pVscMode)
{
	VscModeItemType *pItem = &pVscMode->item;
	JSHORT  	psGSData[2];
	
	JAtrType 	*pAtrRead = NULL;
	JAtrQueueType * pAtrQueue = &AtrQueue;
	
	/// VSC_MODE_INFO_TYPE0_TIME_UTC								(1)	
	UtilMemcpy((JBYTE *)&pVscMode->dwUTC, (JBYTE *)&pItem->fInfo[VSC_MODE_INFO_TYPE0_TIME_UTC], 4);
		
	/// VSC_MODE_INFO_TYPE0_TEMP_T									(2)
	pVscMode->fTemp = *(JFLOAT *)&pItem->fInfo[VSC_MODE_INFO_TYPE0_TEMP_T];	
	
	/// VSC_MODE_INFO_TYPE0_ECG_HR									(3)
	pVscMode->fHRNow = *(JFLOAT *)&pItem->fInfo[VSC_MODE_INFO_TYPE0_ECG_HR];	
	
	/// VSC_MODE_INFO_TYPE0_ECG_LEAD_OFF						(4)
	pVscMode->fLeadOff = *(JFLOAT *)&pItem->fInfo[VSC_MODE_INFO_TYPE0_ECG_LEAD_OFF];	
	
	/// VSC_MODE_INFO_TYPE0_GSEN_X									(5)
	pVscMode->fGsenXNow = *(JFLOAT *)&pItem->fInfo[VSC_MODE_INFO_TYPE0_GSEN_X];	
	
	/// VSC_MODE_INFO_TYPE0_GSEN_Y									(6)
	pVscMode->fGsenYNow = *(JFLOAT *)&pItem->fInfo[VSC_MODE_INFO_TYPE0_GSEN_Y];	
	
	/// VSC_MODE_INFO_TYPE0_GSEN_Z									(7)
	pVscMode->fGsenZNow = *(JFLOAT *)&pItem->fInfo[VSC_MODE_INFO_TYPE0_GSEN_Z];	

	/// VSC_MODE_INFO_TYPE0_BATT_SOC								(8)
	pVscMode->fBattSoc = *(JFLOAT *)&pItem->fInfo[VSC_MODE_INFO_TYPE0_BATT_SOC];	
	
	/// VSC_MODE_INFO_TYPE0_BATT_TOTAL_SEC					(9)
	pVscMode->fBattTotalSec = *(JFLOAT *)&pItem->fInfo[VSC_MODE_INFO_TYPE0_BATT_TOTAL_SEC];	
	
	/// VSC_MODE_INFO_TYPE0_HRV_SDNN								(10)
	pVscMode->fHrvSDNN = *(JFLOAT *)&pItem->fInfo[VSC_MODE_INFO_TYPE0_HRV_SDNN];	
	/// VSC_MODE_INFO_TYPE0_HRV_NN50								(11)
	pVscMode->fHrvNN50 = *(JFLOAT *)&pItem->fInfo[VSC_MODE_INFO_TYPE0_HRV_NN50];	
	
	/// VSC_MODE_INFO_TYPE0_HRV_RMSSD								(12)
	pVscMode->fHrvRMSSD = *(JFLOAT *)&pItem->fInfo[VSC_MODE_INFO_TYPE0_HRV_RMSSD];	
	
	/// VSC_MODE_INFO_TYPE0_HRV_RR									(13)
	pVscMode->fHrvRR = *(JFLOAT *)&pItem->fInfo[VSC_MODE_INFO_TYPE0_HRV_RR];	
	
	/// VSC_MODE_INFO_TYPE0_HRV_VLF									(14)
	pVscMode->fHrvVLF = *(JFLOAT *)&pItem->fInfo[VSC_MODE_INFO_TYPE0_HRV_VLF];	
	
	/// VSC_MODE_INFO_TYPE0_HRV_LF									(15)
	pVscMode->fHrvLF = *(JFLOAT *)&pItem->fInfo[VSC_MODE_INFO_TYPE0_HRV_LF];	
	
	/// VSC_MODE_INFO_TYPE0_HRV_HF									(16)
	pVscMode->fHrvHF = *(JFLOAT *)&pItem->fInfo[VSC_MODE_INFO_TYPE0_HRV_HF];		

	/// VSC_MODE_INFO_TYPE0_BAR                     (17)
	pVscMode->fBar = *(JFLOAT *)&pItem->fInfo[VSC_MODE_INFO_TYPE0_BAR];		

	/// VSC_MODE_INFO_TYPE0_BAR_TEMP                (18)
	pVscMode->fBarTemp = *(JFLOAT *)&pItem->fInfo[VSC_MODE_INFO_TYPE0_BAR_TEMP];		

	/// VSC_MODE_INFO_TYPE0_GSEN_DATA0              (19) ///< GS_X0 |  GS_Y0
	UtilMemcpy((JBYTE *)&psGSData[0], (JBYTE *)&pItem->fInfo[VSC_MODE_INFO_TYPE0_GSEN_DATA0], 4);
	pVscMode->sGSenX[0] = psGSData[0];
	pVscMode->sGSenY[0] = psGSData[1];
	
	/// VSC_MODE_INFO_TYPE0_GSEN_DATA1              (20) ///< GS_Z0 |  GS_X1
	UtilMemcpy((JBYTE *)&psGSData[0], (JBYTE *)&pItem->fInfo[VSC_MODE_INFO_TYPE0_GSEN_DATA1], 4);
	pVscMode->sGSenZ[0] = psGSData[0];
	pVscMode->sGSenX[1] = psGSData[1];
	
	/// VSC_MODE_INFO_TYPE0_GSEN_DATA2              (21) ///< GS_Y1 |  GS_Z1
	UtilMemcpy((JBYTE *)&psGSData[0], (JBYTE *)&pItem->fInfo[VSC_MODE_INFO_TYPE0_GSEN_DATA2], 4);
	pVscMode->sGSenY[1] = psGSData[0];
	pVscMode->sGSenZ[1] = psGSData[1];
	
	/// VSC_MODE_INFO_TYPE0_GSEN_DATA3              (22) ///< GS_X2 |  GS_Y2
	UtilMemcpy((JBYTE *)&psGSData[0], (JBYTE *)&pItem->fInfo[VSC_MODE_INFO_TYPE0_GSEN_DATA3], 4);
	pVscMode->sGSenX[2] = psGSData[0];
	pVscMode->sGSenY[2] = psGSData[1];
	
	/// VSC_MODE_INFO_TYPE0_GSEN_DATA4              (23) ///< GS_Z2 |  GS_X3
	UtilMemcpy((JBYTE *)&psGSData[0], (JBYTE *)&pItem->fInfo[VSC_MODE_INFO_TYPE0_GSEN_DATA4], 4);
	pVscMode->sGSenZ[2] = psGSData[0];
	pVscMode->sGSenX[3] = psGSData[1];

	/// VSC_MODE_INFO_TYPE0_GSEN_DATA5              (24) ///< GS_Y3 |  GS_Z3
	UtilMemcpy((JBYTE *)&psGSData[0], (JBYTE *)&pItem->fInfo[VSC_MODE_INFO_TYPE0_GSEN_DATA5], 4);
	pVscMode->sGSenY[3] = psGSData[0];
	pVscMode->sGSenZ[3] = psGSData[1];

	/// VSC_MODE_INFO_TYPE0_GSEN_DATA6              (25) ///< GS_X4 |  GS_Y4
	UtilMemcpy((JBYTE *)&psGSData[0], (JBYTE *)&pItem->fInfo[VSC_MODE_INFO_TYPE0_GSEN_DATA6], 4);
	pVscMode->sGSenX[4] = psGSData[0];
	pVscMode->sGSenY[4] = psGSData[1];

	/// VSC_MODE_INFO_TYPE0_GSEN_DATA7              (26) ///< GS_Z4 |  --
	UtilMemcpy((JBYTE *)&psGSData[0], (JBYTE *)&pItem->fInfo[VSC_MODE_INFO_TYPE0_GSEN_DATA7], 4);
	pVscMode->sGSenZ[4] = psGSData[0];

	/// VSC_MODE_INFO_TYPE0_ATR               			(27) ///< ATR	CODE		
	pAtrRead = &pVscMode->atrNow;	
	UtilMemcpy((JBYTE *)&pAtrRead->bAtr, (JBYTE *)&pItem->fInfo[VSC_MODE_INFO_TYPE0_ATR], 1);

	/// VSC_MODE_INFO_TYPE0_ATR_TIME               	(28) ///< ATR	TIME		
	pAtrRead = &pVscMode->atrNow;	
	UtilMemcpy((JBYTE *)&pAtrRead->dwMS, (JBYTE *)&pItem->fInfo[VSC_MODE_INFO_TYPE0_ATR_TIME], 4);

	if(pAtrRead->bAtr != ATR_NONE)
	{	
		///--------------------------------------------------------------------------------///	
		/// VSC ATR Data add into queue
		///--------------------------------------------------------------------------------///
		if(((GlobalVar.iVscAtrQueueTail + 1) % VSC_ATR_QUEUE_CNT) == GlobalVar.iVscAtrQueueHead)
		{
			/// Queue is full, do shift
			GlobalVar.iVscAtrQueueHead =  (GlobalVar.iVscAtrQueueHead + 1) % VSC_ATR_QUEUE_CNT;
		}
		UtilMemcpy((JBYTE *)&GlobalVar.vscAtrQueue[GlobalVar.iVscAtrQueueTail], (JBYTE *)pAtrRead, sizeof(JAtrType));	
		GlobalVar.iVscAtrQueueTail = (GlobalVar.iVscAtrQueueTail + 1) % VSC_ATR_QUEUE_CNT;

		//JAtrAddEx(pAtrQueue, pAtrRead);				
		GlobalVar.bVscAtrUpdated = TRUE;	
	}

	///--------------------------------------------------------------------------///
	/// HRV
	///--------------------------------------------------------------------------///

	/// TP	
	pVscMode->fHrvTP = (pVscMode->fHrvVLF + pVscMode->fHrvLF + pVscMode->fHrvHF);
	
	/// LF/TP	
	pVscMode->fHrvLFTP = 0;
	if(pVscMode->fHrvTP > 0)
	{
		pVscMode->fHrvLFTP = (pVscMode->fHrvLF / pVscMode->fHrvTP);
	}
	
	/// HF/TP	
	pVscMode->fHrvHFTP = 0;
	if(pVscMode->fHrvTP > 0)
	{
		pVscMode->fHrvHFTP = (pVscMode->fHrvHF / pVscMode->fHrvTP);
	}
	
	/// LF/HF		
	pVscMode->fHrvLFHF = 0;
	if(pVscMode->fHrvHF > 0)
	{
		pVscMode->fHrvLFHF = (pVscMode->fHrvLF / pVscMode->fHrvHF);
	}

	JTMLocalTimeGet(&pVscMode->jtm, 	pVscMode->dwUTC);
	pVscMode->jtm.iMS = ( pItem->wId % 5) * 200;	
}

void VscModeInfoHeaderSave(FILE *fp)
{
	/// YEAR
	fprintf(fp, "%s", "YEAR,");
	/// MONTH
	fprintf(fp, "%s", "MONTH,");
	/// DAY
	fprintf(fp, "%s", "DAY,");	
	/// HOUR
	fprintf(fp, "%s", "HOUR,");		
	/// MIN
	fprintf(fp, "%s", "MIN,");			
	/// SEC
	fprintf(fp, "%s", "SEC,");				
	/// MS
	fprintf(fp, "%s", "MS,");				

	/// VSC_MODE_INFO_TYPE0_TIME_UTC								(1)	
	fprintf(fp, "%s", "UTC,");				

	/// VSC_MODE_INFO_TYPE0_TEMP_T									(2)
	fprintf(fp, "%s", "TEMP,");				
	
	/// VSC_MODE_INFO_TYPE0_ECG_HR									(3)
	fprintf(fp, "%s", "HR_NOW,");				

	/// VSC_MODE_INFO_TYPE0_ECG_LEAD_OFF						(4)
	fprintf(fp, "%s", "LEAD_OFF,");				

	/// VSC_MODE_INFO_TYPE0_GSEN_X									(5)
	fprintf(fp, "%s", "GSEN_X_NOW,");				

	/// VSC_MODE_INFO_TYPE0_GSEN_Y									(6)
	fprintf(fp, "%s", "GSEN_Y_NOW,");				

	/// VSC_MODE_INFO_TYPE0_GSEN_Z									(7)
	fprintf(fp, "%s", "GSEN_Z_NOW,");				

	/// VSC_MODE_INFO_TYPE0_BATT_SOC								(8)
	fprintf(fp, "%s", "BATT_SOC,");				

	/// VSC_MODE_INFO_TYPE0_BATT_TOTAL_SEC					(9)
	fprintf(fp, "%s", "BATT_TOTAL_SEC,");				

	/// VSC_MODE_INFO_TYPE0_HRV_SDNN								(10)
	fprintf(fp, "%s", "HRV_SDNN,");				
	
	/// VSC_MODE_INFO_TYPE0_HRV_NN50								(11)
	fprintf(fp, "%s", "HRV_NN50,");				

	/// VSC_MODE_INFO_TYPE0_HRV_RMSSD								(12)
	fprintf(fp, "%s", "HRV_RMSSD,");				

	/// VSC_MODE_INFO_TYPE0_HRV_RR									(13)
	fprintf(fp, "%s", "HRV_RR,");				

	/// VSC_MODE_INFO_TYPE0_HRV_VLF									(14)
	fprintf(fp, "%s", "HRV_VLF,");				

	/// VSC_MODE_INFO_TYPE0_HRV_LF									(15)
	fprintf(fp, "%s", "HRV_LF,");				

	/// VSC_MODE_INFO_TYPE0_HRV_HF									(16)
	fprintf(fp, "%s", "HRV_HF,");		
	
	/// TP	
	fprintf(fp, "%s", "HRV_TP,");		
	
	/// LF/TP	
	fprintf(fp, "%s", "LFTP,");		
	
	/// HF/TP	
	fprintf(fp, "%s", "HFTP,");		
	
	/// LF/HF		
	fprintf(fp, "%s", "LFHF,");				

	fprintf(fp, "%s", "\n");				
}

void VscModeInfoDataSave(VscModeControlType *pVscMode, FILE *fp)
{
	/// YEAR
	fprintf(fp, "%04d,", pVscMode->jtm.iYear);
	/// MONTH
	fprintf(fp, "%02d,", pVscMode->jtm.iMonth);
	/// DAY
	fprintf(fp, "%02d,", pVscMode->jtm.iDay);
	/// HOUR
	fprintf(fp, "%02d,", pVscMode->jtm.iHour);
	/// MIN
	fprintf(fp, "%02d,", pVscMode->jtm.iMin);
	/// SEC
	fprintf(fp, "%02d,", pVscMode->jtm.iSec);
	/// MS
	fprintf(fp, "%03d,", pVscMode->jtm.iMS);
	/// VSC_MODE_INFO_TYPE0_TIME_UTC								(1)	
	fprintf(fp, "%d,", (JINT) pVscMode->dwUTC);

	/// VSC_MODE_INFO_TYPE0_TEMP_T									(2)
	fprintf(fp, "%0.3f,", pVscMode->fTemp);
	
	/// VSC_MODE_INFO_TYPE0_ECG_HR									(3)
	fprintf(fp, "%0.3f,", pVscMode->fHRNow);

	/// VSC_MODE_INFO_TYPE0_ECG_LEAD_OFF						(4)
	fprintf(fp, "%d,", (JINT)pVscMode->fLeadOff);

	/// VSC_MODE_INFO_TYPE0_GSEN_X									(5)
	fprintf(fp, "%0.3f,", pVscMode->fGsenXNow);

	/// VSC_MODE_INFO_TYPE0_GSEN_Y									(6)
	fprintf(fp, "%0.3f,", pVscMode->fGsenYNow);

	/// VSC_MODE_INFO_TYPE0_GSEN_Z									(7)
	fprintf(fp, "%0.3f,", pVscMode->fGsenZNow);

	/// VSC_MODE_INFO_TYPE0_BATT_SOC								(8)
	fprintf(fp, "%d,", (JINT)pVscMode->fBattSoc);

	/// VSC_MODE_INFO_TYPE0_BATT_TOTAL_SEC					(9)
	fprintf(fp, "%d,", (JINT)pVscMode->fBattTotalSec);

	/// VSC_MODE_INFO_TYPE0_HRV_SDNN								(10)
	fprintf(fp, "%0.3f,", pVscMode->fHrvSDNN);
	
	/// VSC_MODE_INFO_TYPE0_HRV_NN50								(11)
	fprintf(fp, "%0.3f,", pVscMode->fHrvNN50);

	/// VSC_MODE_INFO_TYPE0_HRV_RMSSD								(12)
	fprintf(fp, "%0.3f,", pVscMode->fHrvRMSSD);

	/// VSC_MODE_INFO_TYPE0_HRV_RR									(13)
	fprintf(fp, "%0.3f,", pVscMode->fHrvRR);

	/// VSC_MODE_INFO_TYPE0_HRV_VLF									(14)
	fprintf(fp, "%0.3f,", pVscMode->fHrvVLF);

	/// VSC_MODE_INFO_TYPE0_HRV_LF									(15)
	fprintf(fp, "%0.3f,", pVscMode->fHrvLF);

	/// VSC_MODE_INFO_TYPE0_HRV_HF									(16)
	fprintf(fp, "%0.3f,", pVscMode->fHrvHF);
	
	/// TP	
	fprintf(fp, "%0.3f,", pVscMode->fHrvTP);	
	
	/// LF/TP	
	fprintf(fp, "%0.3f,", pVscMode->fHrvLFTP);	
	
	/// HF/TP	
	fprintf(fp, "%0.3f,", pVscMode->fHrvHFTP);	
	
	/// LF/HF		
	fprintf(fp, "%0.3f,", pVscMode->fHrvLFHF);


	fprintf(fp, "%s", "\n");		
}

void VscModeInfoSave(VscModeControlType *pVscMode)
{
	char msg[256];
		
	FILE *fp = NULL;	
	JBOOL bHeaderGen = FALSE;

	if(UtilFileExisted(GlobalVar.strVscFileNameInfo) == FALSE)
	{
		bHeaderGen = TRUE;
	}
	
	fp  = fopen(GlobalVar.strVscFileNameInfo, "a+");
	if(fp == NULL)
	{
		sprintf(msg, "\t\t [VSC][ERROR][INFO] Failed to open %s\r\n", GlobalVar.strVscFileNameInfo);
		DBG_PRINTF(msg);		
		return;
	}
	
	if(bHeaderGen == TRUE)
	{
		VscModeInfoHeaderSave(fp);
	}

	VscModeInfoDataSave(pVscMode, fp);
		
	fclose(fp);
}

void VscModeGSensorDataSave(VscModeControlType *pVscMode)
{
	char msg[256];
	JINT i = 0;
		
	FILE *fp = NULL;	
	JBOOL bCreate = FALSE;

	if(UtilFileExisted(GlobalVar.strVscFileNameGSensor) == FALSE)
	{
		bCreate = TRUE;
	}
	if(bCreate == TRUE)
	{
		fp = fopen(GlobalVar.strVscFileNameGSensor, "w+");
	}
	else
	{
		fp = fopen(GlobalVar.strVscFileNameGSensor, "a+");
	}
	if(fp == NULL)
	{
		sprintf(msg, "\t\t [VSC][ERROR][GSENSOR] Failed to open %s\r\n", GlobalVar.strVscFileNameGSensor);
		DBG_PRINTF(msg);		
		return;
	}
	for(i = 0; i < 5 ; i = i + 1)
	{
		fprintf(fp, "%d,%d,%d\n", pVscMode->sGSenX[i], pVscMode->sGSenY[i], pVscMode->sGSenZ[i]);
	}
	fclose(fp);
}

void VscModeEcgDataParse(VscModeControlType *pVscMode)
{
	JINT i = 0;
	JINT iCH = 0;
	JINT iCnt = 0;
	JINT idx = 0;
	char msg[256];
	JFLOAT *pfData = NULL;	
	VscModeItemType *pItem = &pVscMode->item;

	FILE *fp = NULL;	

 	iCnt = (VSC_MODE_ITEM_DATA_SIZE / sizeof(JFLOAT) ) / VscModeCtl.iChannelCount;
 	
	pfData =(JFLOAT *) &pItem->bData[0];
	for(i = 0 ; i < iCnt; i = i + 1)
	{
		for(iCH = 0 ; iCH < VscModeCtl.iChannelCount; iCH = iCH + 1)
		{
			pVscMode->fValueCH[iCH][i] = pfData[idx];			
			idx = idx + 1;
		}
	}
}

void VscModeEcgDataSave(VscModeControlType *pVscMode)
{
	FILE *fp  = NULL;
	JINT 	i   = 0;	
	JINT iCH  = 0;
	JINT iCnt = 0;
	char 	msg[256];

	iCnt = (VSC_MODE_ITEM_DATA_SIZE / sizeof(JFLOAT)) / VscModeCtl.iChannelCount;

	for(iCH = 0 ; iCH< pVscMode->iChannelCount; iCH = iCH + 1)
	{
		fp = fopen (GlobalVar.strVscFileNameEcg[iCH], "a+");
		if(fp == NULL)
		{
			sprintf(msg, "\t\t [VSC][ERROR][ECG][%02d] Failed to open '%s'\r\n", iCH, (char *) &GlobalVar.strVscFileNameEcg[iCH]);
			DBG_PRINTF(msg);		
			continue;
		}

		for(i = 0 ; i < iCnt; i = i + 1)
		{		
			fprintf(fp, "%0.3f\n", pVscMode->fValueCH[iCH][i]);
		}
		fclose(fp);		
	}
}

void VscModeAtrBinSave(void)
{
	FILE *fp  = NULL;
	char msg[256];
	JINT idx = GlobalVar.iVscAtrCnt;
	JINT A = 0;
	JFLOAT fTimeSec = 0;
	JAtrType *pAtr = &GlobalVar.vscAtrNow;

	JAtrDataGet(pAtr, &A, &fTimeSec);
	JAtrFileBinSave(GlobalVar.strVscFileNameAtrBin, idx, A, fTimeSec);
}

void VscModeAtrCsvSave(void)
{
	FILE *fp  = NULL;
	char msg[256];
	JINT idx = GlobalVar.iVscAtrCnt;
	
	JINT A = 0;
	JFLOAT fTimeSec  = 0;

	JINT APre = 0;
	JFLOAT fTimeSecPre  = 0;

	JFLOAT fDeltaSec = 0;

	JAtrType *pAtrNow = &GlobalVar.vscAtrNow;
	JAtrType *pAtrPre = &GlobalVar.vscAtrPre;

	JAtrDataGet(pAtrNow, &A, &fTimeSec);
	JAtrDataGet(pAtrPre, &APre, &fTimeSecPre);

	if(pAtrPre->bAtr == ATR_NONE)
	{
		fDeltaSec = 0;
	}
	else
	{
		fDeltaSec = fTimeSec - fTimeSec;
		if(fDeltaSec > 1.5)
		{
			fDeltaSec = 0;
		}
		if(fDeltaSec <= 0 )
		{
			fDeltaSec = 0;
		}
	}
	JAtrFileCsvSave(GlobalVar.strVscFileNameAtrCsv, idx, A, fTimeSec, fDeltaSec);
}

void VscModeFileNameSet(VscModeControlType *pVscMode)
{
	JINT i = 0;
	char strFileName[256];
	FILE *fp = NULL;

	///----------------------------------------------------------------------///
	/// 1. Date folder Set
	///----------------------------------------------------------------------///
	sprintf((char *)&GlobalVar.strVscDateFolder[0], "%s/%04d%02d%02d", 
										GlobalVar.strVscBaseFolder,
										pVscMode->jtm.iYear,
										pVscMode->jtm.iMonth,
										pVscMode->jtm.iDay);

	if(UtilFolderExisted(GlobalVar.strVscDateFolder) == FALSE)
	{
		UtilFolderCreate(GlobalVar.strVscDateFolder);
	}

	///----------------------------------------------------------------------///
	/// 2. Hour folder Set
	///----------------------------------------------------------------------///
	sprintf((char *)&GlobalVar.strVscHourFolder[0], "%s/%02d", 
										GlobalVar.strVscDateFolder,
										pVscMode->jtm.iHour);

	if(UtilFolderExisted(GlobalVar.strVscHourFolder) == FALSE)
	{
		UtilFolderCreate(GlobalVar.strVscHourFolder);
	}

	///----------------------------------------------------------------------///
	/// 3. Set ECG Data
	///----------------------------------------------------------------------///
	for(i = 0 ; i < pVscMode->iChannelCount; i = i + 1)
	{	
		sprintf((char *)&strFileName[0], "%s/ch%d.reso", GlobalVar.strVscHourFolder, i);
		if(UtilFileExisted(strFileName) == FALSE)
		{
			fp = fopen(strFileName, "w+");
			if(fp != NULL)
			{
				fprintf(fp, "%0.3f", 1.0);
				fclose(fp);
			}
		}
		sprintf((char *)&GlobalVar.strVscFileNameEcg[i][0], "%s/ch%d.csv", GlobalVar.strVscHourFolder, i);		
	}

	///----------------------------------------------------------------------///
	/// 4. Set Info data
	///----------------------------------------------------------------------///
	sprintf((char *)&GlobalVar.strVscFileNameInfo[0], 			"%s/info.csv", GlobalVar.strVscHourFolder);	

	///----------------------------------------------------------------------///
	/// 5. Set GSensor data
	///----------------------------------------------------------------------///
	sprintf((char *)&GlobalVar.strVscFileNameGSensor[0], 		"%s/gsen.csv", GlobalVar.strVscHourFolder);	

	///----------------------------------------------------------------------///
	/// 6. Set ATR data
	///----------------------------------------------------------------------///
	sprintf((char *)&GlobalVar.strVscFileNameAtrBin[0], 		"%s/vsc.atr.bin", GlobalVar.strVscHourFolder);	
	sprintf((char *)&GlobalVar.strVscFileNameAtrCsv[0], 		"%s/vsc.atr.csv", GlobalVar.strVscHourFolder);	
}

void VscModeSave(VscModeControlType *pVscMode)
{
	char msg[256];
	VscModeItemType *pItem = &pVscMode->item;	

	/// File Set
	VscModeFileNameSet(pVscMode);

	if(strlen(GlobalVar.strVscFileNameInfo) == 0)
	{
		sprintf(msg, "[ERROR][!!!!][%d] GlobalVar.strVscFileNameInfo = '%s'\r\n",pVscMode->wId,  GlobalVar.strVscFileNameInfo);
		DBG_PRINTF(msg);
		return;
	}

	///------------------------------------------------///
	/// 1. ECG Data Save
	///------------------------------------------------///
	VscModeEcgDataSave(pVscMode);

	///------------------------------------------------///
	/// 2. GSensor Data Save
	///------------------------------------------------///
	VscModeGSensorDataSave(pVscMode);
	
	///------------------------------------------------///
	/// 3. GSensor information
	///------------------------------------------------///
	if((pItem->wId % 5) == 0)
	{
		VscModeInfoSave(pVscMode);
	}	
}

void VscModeDecode(JWORD wId, JWORD wLen, JBYTE *pbData)
{
	char msg[256];

	JFLOAT *pfData = NULL;
	JINT 		i = 0;
	JINT 		j = 0;
	JINT		idx = 0;
	
	VscModeControlType *pVscMode = &VscModeCtl;
	VscModeItemType *pItem = &pVscMode->item;	

	pItem->wId = wId;
	pItem->wLen= wLen;

	/// Ecg Data Copy
	UtilMemcpy((JBYTE *)&pItem->bData[0], (JBYTE *)&pbData[0], VSC_MODE_ITEM_DATA_SIZE);

	/// Info Data Copy
	UtilMemcpy((JBYTE *)&pItem->fInfo[0], (JBYTE *)&pbData[VSC_MODE_ITEM_DATA_SIZE], VSC_MODE_ITEM_INFO_SIZE);

	/// Info Data Parse
	VscModeInfoParse(pVscMode);
	
	/// Ecg Data Parse
	VscModeEcgDataParse(pVscMode);
	
	//sprintf(msg, "\t\t [VSC]  ID = %03d, SIZE=%d, IDX = %d\r\n", pItem->wId , pItem->wLen, idx);
	//DBG_PRINTF(msg);
}

void VscModeInit(char *pBaseFolder)	
{	
	JTM jtm;
	time_t t = time(NULL);
	JTMLocalTimeGet(&jtm, t);	
	VscModeControlType *pVscMode = &VscModeCtl;

	pVscMode->wId = 0;
	pVscMode->iChannelCount = VSC_MODE_CAHNNEL_COUNT; ///< 2 channel
	/// set the base folder size 
	strcpy(GlobalVar.strVscBaseFolder, pBaseFolder);

	///--------------------------------------------------------///
	/// VSC ATR Init
	///--------------------------------------------------------///
	FuncVscAtrInit();
}

