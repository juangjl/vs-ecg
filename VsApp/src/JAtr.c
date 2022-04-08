/**
 * @file JAtr.h
 *
 *  JAtr.h ATR
 *
 * @version $Revision$
 * @author JL Juang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021,  VitalSigns Technology Co., LTD., all rights reserved.
 * @note
*/
#include "Global.h"

JAtrQueueType AtrQueue;

///----------------------------------------///
/// [JL] for console program of JCNN
///----------------------------------------///
const char * JAtrLabel[] =
{
  LABEL_NOTQRS	 ,  ///< 0 not-QRS (not a getann/putann code) 
  LABEL_NORMAL	 ,  ///< 1 normal beat 
  LABEL_LBBB		 ,  ///< 2 left bundle branch block beat 
  LABEL_RBBB		 ,  ///< 3 right bundle branch block beat 
  LABEL_ABERR		 ,  ///< 4 aberrated atrial premature beat 
  LABEL_PVC		   ,  ///< 5 premature ventricular contraction 
  LABEL_FUSION	 ,  ///< 6 fusion of ventricular and normal beat 
  LABEL_NPC		   ,  ///< 7 nodal (junctional) premature beat 
  LABEL_APC			 , 	///< 8 atrial premature contraction 
  LABEL_SVPB		 , 	///< 9 premature or ectopic supraventricular beat 
  LABEL_VESC		 , 	///< 10 ventricular escape beat 
  LABEL_NESC		 , 	///< 11 nodal (junctional) escape beat 
  LABEL_PACE		 , 	///< 12 paced beat 
  LABEL_UNKNOWN	 , 	///< 13 unclassifiable beat 
  LABEL_NOISE		 , 	///< 14 signal quality change 
  LABEL_ATR_15	 ,  ///< 15 ATR = 15
  LABEL_ARFCT		 , 	///< 16 isolated QRS-like artifact 
  LABEL_ATR_17	 ,  ///< 17 ATR = 17
  LABEL_STCH		 , 	///< 18 ST change 
  LABEL_TCH			 , 	///< 19 T-wave change 
  LABEL_SYSTOLE	 , 	///< 20 systole 
  LABEL_DIASTOLE , 	///< 21 diastole 
  LABEL_NOTE		 , 	///< 22 comment annotation 
  LABEL_MEASURE  , 	///< 23 measurement annotation 
  LABEL_PWAVE		 , 	///< 24 P-wave peak 
  LABEL_BBB			 , 	///< 25 left or right bundle branch block 
  LABEL_PACESP	 , 	///< 26 non-conducted pacer spike 
  LABEL_TWAVE		 , 	///< 27 T-wave peak 
  LABEL_RHYTHM	 , 	///< 28 rhythm change 
  LABEL_UWAVE		 , 	///< 29 U-wave peak 
  LABEL_LEARN		 , 	///< 30 learning 
  LABEL_FLWAV		 , 	///< 31 ventricular flutter wave 
  LABEL_VFON		 , 	///< 32 start of ventricular flutter/fibrillation 
  LABEL_VFOFF		 , 	///< 33 end of ventricular flutter/fibrillation 
  LABEL_AESC		 , 	///< 34 atrial escape beat 
  LABEL_SVESC		 , 	///< 35 supraventricular escape beat 
  LABEL_LINK     , 	///< 36 link to external data (aux contains URL) 
  LABEL_NAPC		 , 	///< 37 non-conducted P-wave (blocked APB) 
  LABEL_PFUS		 , 	///< 38 fusion of paced and normal beat 
  LABEL_WFON		 , 	///< 39 waveform onset 
  LABEL_WFOFF		 , 	///< 40 waveform end 
  LABEL_RONT		 ,  ///< 41 R-on-T premature ventricular contraction 
	LABEL_ATR_42	 ,  ///< 42
	LABEL_ATR_43	 ,  ///< 43
	LABEL_ATR_44	 ,  ///< 44
	LABEL_ATR_45	 ,  ///< 45
	LABEL_ATR_46	 ,  ///< 46
	LABEL_ATR_47	 ,  ///< 47
	LABEL_ATR_48	 ,  ///< 48
	LABEL_ATR_49	 ,  ///< 49

	LABEL_ATR_50	 ,  ///< 50
	LABEL_ATR_51	 ,  ///< 51
	LABEL_ATR_52	 ,  ///< 52
	LABEL_ATR_53	 ,  ///< 53 
	LABEL_ATR_54	 ,  ///< 54
	LABEL_ATR_55	 ,  ///< 55
	LABEL_ATR_56	 ,  ///< 56
	LABEL_ATR_57	 ,  ///< 57
	LABEL_ATR_58	 ,  ///< 58

  LABEL_ATR_SKIP ,  ///< 59 SKIP

	LABEL_ATR_NUM  ,  ///< 60 NUM 
	LABEL_ATR_SUB  ,  ///< 61 SUB
	LABEL_ATR_CHN  ,  ///< 62 CHN
	LABEL_ATR_AUX  ,  ///< 63 AUX
};

JBOOL JAtrFileBinSave(char * strFileName, JINT idx, JINT A, JFLOAT fTimeSec)
{
  char msg[256];
  FILE *fp = NULL;

  if(idx == 0)
	{
		fp = fopen(strFileName, "wb+");
	}
	else
	{
		fp = fopen(strFileName, "ab+");
	}
	if(fp == NULL)
	{
		sprintf(msg, "[ERROR][JATR][SAVE] Failed to open %s\r\n", strFileName);
		DBG_PRINTF(msg);
    return FALSE;
	}
	fwrite(&A, 4, 1, fp);
	fwrite(&fTimeSec, 4, 1, fp);
	fclose(fp);
		
  return TRUE;
}

JBOOL JAtrFileCsvSave(char * strFileName, JINT idx, JDWORD A, JFLOAT fTimeSec, JFLOAT fDeltaSec)
{
	char strTime[256];
	char strNote[256];
	FILE * fp = NULL;
	
  if(idx == 0)
	{
		fp = fopen(strFileName, "w+");
		if(fp == NULL)
		{
			return FALSE;
		}
		fprintf(fp, "%s", "#,TIME,TSEC,DT,A,LABEL,NOTE\n");
    
	}
  else
  {
	  fp = fopen(strFileName, "a+");
  }
	if(fp == NULL)
	{
	  return FALSE;
	}
	
	UtilTimeStringGet(fTimeSec, strTime),
	strcpy(strNote, "");
		
	fprintf(fp, "%d,%s,%0.3f,%0.3f,%d,%s,%s\n",	 idx, strTime, fTimeSec, fDeltaSec, A,  JAtrLabel[A], strNote);

	fclose(fp);

  return TRUE;
}

void JAtrDataGet(JAtrType *pAtr, JINT *piAtr, JFLOAT *pfTimeSec)
{
  *pfTimeSec = (JFLOAT)pAtr->dwMS / 1000;
  *piAtr     = (JINT)pAtr->bAtr;
}

void JAtrDataPrint(JAtrType *pAtr)
{
  char msg[256];  
  JFLOAT fTimeSec = 0;
  char strTime[256];
  
  fTimeSec = (JFLOAT)pAtr->dwMS / 1000;
  UtilTimeStringGet(fTimeSec, strTime);

  //sprintf(msg, "\t [ATR][DATA] %-10s (%d) - %s\r\n", JAtrLabel[pAtr->bAtr], pAtr->bAtr, strTime);
  //DBG_PRINTF(msg);
}

void JAtrDataClean(JAtrType *pAtr)
{
  pAtr->bAtr  = ATR_NONE;
  pAtr->dwMS  = 0;  
}

JINT JAtrSizeGet(JAtrQueueType * pAtrQueue)
{
   return pAtrQueue->iAtrCnt;
}

JBOOL JAtrFullCheck(JAtrQueueType * pAtrQueue)
{
  if(((pAtrQueue->iAtrQueueTail + 1) % ATR_QUEUE_CNT) == pAtrQueue->iAtrQueueHead)
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

JBOOL JAtrDelete(JAtrQueueType * pAtrQueue)
{
  char msg[256];
  JAtrType *pAtr = NULL;
  if(pAtrQueue->iAtrCnt == 0)
  {
    sprintf(msg,"%s", "[ATR][ERROR] CANNOT DELETE EMPTY QUEUE\r\n");
    DBG_PRINTF(msg);
    return FALSE;
  }
  pAtr = &pAtrQueue->pAtrData[pAtrQueue->iAtrQueueHead];
  JAtrDataClean(pAtr);

  pAtrQueue->iAtrQueueHead = (pAtrQueue->iAtrQueueHead + 1)  % ATR_QUEUE_CNT;
  pAtrQueue->iAtrCnt =  pAtrQueue->iAtrCnt - 1; 
  
  return TRUE;
}

void JAtrRead(JAtrQueueType * pAtrQueue,  JAtrType *pAtrRead)
{
  JAtrType *pAtr = NULL;
  pAtr = &pAtrQueue->pAtrData[pAtrQueue->iAtrQueueHead];

  pAtrRead->bAtr = pAtr->bAtr;
  pAtrRead->dwMS = pAtr->dwMS;  
}

void JAtrReadOut(JAtrQueueType * pAtrQueue,  JAtrType *pAtrRead)
{
  /// ATR READ
  JAtrRead(pAtrQueue, pAtrRead);

  /// ATR DELETE
  JAtrDelete(pAtrQueue);
}

void JAtrAdd(JAtrQueueType * pAtrQueue, JINT  iAtr, JFLOAT fTimeSec)
{
  char    msg[256];
  JBYTE   bAtr     = (JBYTE)iAtr;
  JDWORD  dwTimeMS = (JDWORD)(fTimeSec * 1000);
  JAtrType *pAtr = NULL;
  if(JAtrFullCheck(pAtrQueue) == TRUE)
  {
    sprintf(msg, "%s", "[ATR] QUEUE FULL\r\n");
    DBG_PRINTF(msg);
    JAtrDelete(pAtrQueue);
  }
  pAtr = &pAtrQueue->pAtrData[pAtrQueue->iAtrQueueTail];
  pAtr->bAtr = bAtr;
  pAtr->dwMS = dwTimeMS;

  pAtrQueue->iAtrQueueTail = (pAtrQueue->iAtrQueueTail + 1) % ATR_QUEUE_CNT;
  pAtrQueue->iAtrCnt =  pAtrQueue->iAtrCnt + 1;
}

void JAtrAddEx(JAtrQueueType * pAtrQueue, JAtrType *pAtrNew)
{
  char      msg[256];
  JAtrType *pAtr = NULL;

  if(JAtrFullCheck(pAtrQueue) == TRUE)
  {
    sprintf(msg, "%s", "[ATR] QUEUE FULL\r\n");
    DBG_PRINTF(msg);
    JAtrDelete(pAtrQueue);
  }

  pAtr = &pAtrQueue->pAtrData[pAtrQueue->iAtrQueueTail];
  pAtr->bAtr = pAtrNew->bAtr;
  pAtr->dwMS = pAtrNew->dwMS;

  pAtrQueue->iAtrQueueTail = (pAtrQueue->iAtrQueueTail + 1) % ATR_QUEUE_CNT;
  pAtrQueue->iAtrCnt =  pAtrQueue->iAtrCnt + 1;
}

void JAtrInit(JAtrQueueType * pAtrQueue)
{  
  JINT i = 0;
  JAtrType * pAtr = NULL;
  pAtrQueue->iAtrQueueHead = 0;
  pAtrQueue->iAtrQueueTail = 0;
  pAtrQueue->iAtrCnt = 0;
  for(i = 0;i < ATR_QUEUE_CNT; i = i + 1)
  {
    pAtr = &pAtrQueue->pAtrData[i];
    /// ATR Clear
    JAtrDataClean(pAtr);    
  }
}
