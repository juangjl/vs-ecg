/**
 * @file AtrCtl.cpp
 *
 *   AtrCtl
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

AtrCtlType AtrCtl;
AtrCtlType AtrCtlBle;

const char * strAtrAbbrev[] =
{
  ABBREV_NOTQRS	  ,   ///< 0 not-QRS (not a getann/putann code) 
  ABBREV_NORMAL	  ,   ///< 1 normal beat 
  ABBREV_LBBB		  ,   ///< 2 left bundle branch block beat 
  ABBREV_RBBB		  ,   ///< 3 right bundle branch block beat 
  ABBREV_ABERR		,   ///< 4 aberrated atrial premature beat 
  ABBREV_PVC		  ,   ///< 5 premature ventricular contraction 
  ABBREV_FUSION	  ,   ///< 6 fusion of ventricular and normal beat 
  ABBREV_NPC		  ,   ///< 7 nodal (junctional) premature beat 
  ABBREV_APC			, 	///< 8 atrial premature contraction 
  ABBREV_SVPB		  , 	///< 9 premature or ectopic supraventricular beat 
  ABBREV_VESC		  , 	///< 10 ventricular escape beat 
  ABBREV_NESC		  , 	///< 11 nodal (junctional) escape beat 
  ABBREV_PACE		  , 	///< 12 paced beat 
  ABBREV_UNKNOWN	, 	///< 13 unclassifiable beat 
  ABBREV_NOISE		, 	///< 14 signal quality change 
  ABBREV_ATR_15	  ,   ///< 15 ATR = 15
  ABBREV_ARFCT		, 	///< 16 isolated QRS-like artifact 
  ABBREV_ATR_17	  ,   ///< 17 ATR = 17
  ABBREV_STCH		  , 	///< 18 ST change 
  ABBREV_TCH			, 	///< 19 T-wave change 
  ABBREV_SYSTOLE	, 	///< 20 systole 
  ABBREV_DIASTOLE , 	///< 21 diastole 
  ABBREV_NOTE		  , 	///< 22 comment annotation 
  ABBREV_MEASURE  , 	///< 23 measurement annotation 
  ABBREV_PWAVE		, 	///< 24 P-wave peak 
  ABBREV_BBB			, 	///< 25 left or right bundle branch block 
  ABBREV_PACESP	  , 	///< 26 non-conducted pacer spike 
  ABBREV_TWAVE		, 	///< 27 T-wave peak 
  ABBREV_RHYTHM	  , 	///< 28 rhythm change 
  ABBREV_UWAVE		, 	///< 29 U-wave peak 
  ABBREV_LEARN		, 	///< 30 learning 
  ABBREV_FLWAV		, 	///< 31 ventricular flutter wave 
  ABBREV_VFON		  , 	///< 32 start of ventricular flutter/fibrillation 
  ABBREV_VFOFF		, 	///< 33 end of ventricular flutter/fibrillation 
  ABBREV_AESC		  , 	///< 34 atrial escape beat 
  ABBREV_SVESC		, 	///< 35 supraventricular escape beat 
  ABBREV_LINK     , 	///< 36 link to external data (aux contains URL) 
  ABBREV_NAPC		  , 	///< 37 non-conducted P-wave (blocked APB) 
  ABBREV_PFUS		  , 	///< 38 fusion of paced and normal beat 
  ABBREV_WFON		  , 	///< 39 waveform onset 
  ABBREV_WFOFF		,   ///< 40 waveform end 
  ABBREV_RONT		  ,   ///< 41 R-on-T premature ventricular contraction 
	ABBREV_ATR_42	  ,   ///< 42
	ABBREV_ATR_43	  ,   ///< 43
	ABBREV_ATR_44	  ,   ///< 44
	ABBREV_ATR_45	  ,   ///< 45
	ABBREV_ATR_46	  ,   ///< 46
	ABBREV_ATR_47	  ,   ///< 47
	ABBREV_ATR_48	  ,   ///< 48
	ABBREV_ATR_49	  ,   ///< 49

	ABBREV_ATR_50	  ,   ///< 50
	ABBREV_ATR_51	  ,   ///< 51
	ABBREV_ATR_52	  ,   ///< 52
	ABBREV_ATR_53	  ,   ///< 53 
	ABBREV_ATR_54	  ,   ///< 54
	ABBREV_ATR_55	  ,   ///< 55
	ABBREV_ATR_56	  ,   ///< 56
	ABBREV_ATR_57	  ,   ///< 57
	ABBREV_ATR_58	  ,   ///< 58

  ABBREV_ATR_SKIP ,   ///< 59 SKIP

	ABBREV_ATR_NUM  ,   ///< 60 NUM 
	ABBREV_ATR_SUB  ,   ///< 61 SUB
	ABBREV_ATR_CHN  ,   ///< 62 CHN
	ABBREV_ATR_AUX  ,   ///< 63 AUX
};

JBOOL AtrAbbrevGet(JDWORD dwA, char * pAbbrev, JDWORD *pdwColor)
{
  *pdwColor = COLOR_BLUE_MIDNIGHTBLUE;
  if(dwA > 64)
  {
    strcpy(pAbbrev, "??");    
  }
  else
  {
    strcpy(pAbbrev, strAtrAbbrev[dwA]);
  }
  if(dwA != ATR_NORMAL)
  {
    *pdwColor = COLOR_ORANGE_CORAL;
  }
  return TRUE;
}

JBOOL AtrCsvFileSave(char * strFileName, JINT idx, JDWORD A, JFLOAT fTimeSec, JFLOAT fDeltaSec)
{
	JBOOL bRet = FALSE;	
	bRet = AtrWrite(idx, A, fTimeSec, fDeltaSec, (char *) &strFileName[0]);		
	return bRet;
}

JBOOL AtrBinFileSave(char * strFileName, JINT idx, JDWORD A, JFLOAT fTimeSec, JFLOAT fDeltaSec)
{
	JBOOL bRet = FALSE;
	FILE *fp = NULL;
	char msg[256];  

	if(idx == 1)
	{
		fp = fopen(strFileName, "wb+");
	}
	else
	{
		fp = fopen(strFileName, "ab+");
	}
	if(fp == NULL)
	{
		sprintf(msg, "[ERROR][ATR][SAVE] Failed to open %s\r\n", strFileName);
		DBG_PRINTF(msg);
	}
	else
	{
		fwrite(&A, 4, 1, fp);
		fwrite(&fTimeSec, 4, 1, fp);
		fclose(fp);
	}			
	return bRet;
}

JBOOL AtrCtlLoad(AtrCtlType *pAtrCtl, char * strFileName)
{
  FILE *fp = NULL;
  JINT iRet = 0;
  JDWORD dwA = 0;
  JFLOAT fTimeSec = 0;
  char msg[256];
  static JINT iAtrFileSizePre = -1;
  JINT iAtrFileSize = 0;

  AtrCtlInit(pAtrCtl);

  iAtrFileSize = UtilFileSizeGet(strFileName);
  if(iAtrFileSize == iAtrFileSizePre)
  {
    return TRUE;
  }

  fp = fopen(strFileName, "rb");
  if(fp == NULL)
  {
    sprintf(msg, "[ATR][LOAD][ERROR] cannot open file %s\r\n", strFileName);
    DBG_PRINTF(msg);
    return FALSE;
  }
    
  while(1)
  {
    /// read A
    iRet = fread(&dwA, 4, 1, fp);
    if(iRet <= 0)
    {
      break;
    }
    /// read Time
    iRet = fread(&fTimeSec, 4, 1, fp);
    if(iRet <= 0)
    {
      break;
    }
    AtrCtlAdd(pAtrCtl, dwA, fTimeSec);
  }
  fclose(fp);

  //sprintf(msg, "[ATR][LOAD] Data Count %d\r\n",  pAtrCtl->iAtrDataCnt);
  //DBG_PRINTF(msg);

  return TRUE;
}

JBOOL AtrCtlFind(AtrCtlType *pAtrCtl, AtrFindType *pAtrFind)
{
  JINT i = 0;
  JINT iFindIdx = -1;
  JINT iFindCnt = 0;
  JINT iAtrDataCnt  = pAtrCtl->iAtrDataCnt;
  AtrDataType *pAtrData = NULL;  
  char msg[256];

  for(i = 0 ; i < iAtrDataCnt; i = i + 1)
  {
    pAtrData = &pAtrCtl->atrData[i];

    if((pAtrData->fTimeSec >= pAtrFind->fTimeSec0) && 
       (pAtrData->fTimeSec <  pAtrFind->fTimeSec1))
    {
      if(iFindIdx == -1)
      {
        iFindIdx = i;
      }
      //sprintf(msg, "\t [ATR][FIND] %02d: A = %d, %0.3f\r\n", i, pAtrData->dwA, pAtrData->fTimeSec);
      //DBG_PRINTF(msg);
      iFindCnt = iFindCnt + 1;
    } 
    else if(pAtrData->fTimeSec > pAtrFind->fTimeSec1)
    {
      break;
    }
    //if(iAtrDataCnt < 20)
    //{
    //  sprintf(msg, "%02d: A =%d, %0.3f\r\n", i, pAtrData->dwA, pAtrData->fTimeSec);
    //  DBG_PRINTF(msg);
    //}
  }

  pAtrFind->iIdx = iFindIdx;
  pAtrFind->iCnt = iFindCnt;

  ///---------------------------------///
  /// MSG
  ///---------------------------------///
  //sprintf(msg, "[ATR][FIND] FIND_IDX = %d, FIND_CNT = %d, TOTAL = %d\r\n", iFindIdx, iFindCnt, pAtrCtl->iAtrDataCnt);
  //DBG_PRINTF(msg);

  return TRUE;
}
      
JBOOL AtrCtlVscModeAdd(AtrCtlType *pAtrCtl, JDWORD dwA, JFLOAT fTimeSec)
{
  JINT idx = pAtrCtl->iAtrDataCnt;
  AtrDataType *pAtrData = NULL;
  AtrDataType *pAtrData2 = NULL;
  JINT i = 0;
  JINT cnt  = 0;
  
  if(pAtrCtl->iAtrDataCnt < ATR_DATA_CNT)
  {
    pAtrData =  &pAtrCtl->atrData[idx];
    pAtrData->dwA      = dwA;
    pAtrData->fTimeSec = fTimeSec;
    pAtrCtl->iAtrDataCnt = pAtrCtl->iAtrDataCnt  + 1; 
  }
  else
  {
    cnt = ATR_DATA_CNT / 2;
    idx = ATR_DATA_CNT / 2;
    
    /// remove 1/2 atr data
    for(i = 0; i < cnt; i = i + 1)  
    {
      pAtrData  = &pAtrCtl->atrData[i];
      pAtrData2 = &pAtrCtl->atrData[idx];
      pAtrData->dwA      = pAtrData2->dwA;
      pAtrData->fTimeSec = pAtrData2->fTimeSec;   
      idx = idx + 1;
    }
    /// add new data
    pAtrData =  &pAtrCtl->atrData[i];
    pAtrData->dwA      = dwA;
    pAtrData->fTimeSec = fTimeSec;
    i = i + 1;
    pAtrCtl->iAtrDataCnt = i; 
    
  }
  return TRUE;
}

JBOOL AtrCtlAdd(AtrCtlType *pAtrCtl, JDWORD dwA, JFLOAT fTimeSec)
{
  JINT idx = pAtrCtl->iAtrDataCnt;
  AtrDataType *pAtrData = NULL;
  if(pAtrCtl->iAtrDataCnt < ATR_DATA_CNT)
  {
    pAtrData =  &pAtrCtl->atrData[idx];
    pAtrData->dwA      = dwA;
    pAtrData->fTimeSec = fTimeSec;
    pAtrCtl->iAtrDataCnt = pAtrCtl->iAtrDataCnt  + 1; 
  }
  else
  {
    return FALSE;
  }
  return TRUE;
}

JBOOL AtrCtleEmpty(AtrCtlType *pAtrCtl)
{
   pAtrCtl->iAtrDataCnt = 0;
  return TRUE;
}

JBOOL AtrCtlInit(AtrCtlType *pAtrCtl)
{
  pAtrCtl->iAtrDataCnt = 0;
  return TRUE;
}