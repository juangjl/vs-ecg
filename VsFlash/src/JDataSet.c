/**
 * @file DataSet.c
 * @brief Data Set API
 * @version $Revision$
 * @author JL JUANG
 * @note Copyright 2021, VitalSigns Technology CO., LTD., all rights reserved.
 * @note
*/ 

#include "Global.h"

JINT JDataSetGet(JDataSet *pThis, JINT  idx)
{
	return pThis->data[idx];
}

JINT JDataSetGetEx(JDataSet *pThis, JINT idx, JINT iQueueIdx)
{
	return pThis->data[idx];
}

JBOOL JDataSetAdd(JDataSet *pThis, JINT  iData)
{
	JINT idx = pThis->idx;
	JINT cnt =pThis->cnt;
	if(cnt >= JDATA_MAX_CNT)
	{
		return FALSE;
	}

	pThis->data[idx] = iData;

 	pThis->idx =  pThis->idx + 1;
	pThis->cnt =  pThis->cnt + 1;
	return TRUE;
}

JVOID JDataSetReset(JDataSet *pThis)
{
	pThis->idx= 0;
	pThis->cnt= 0;
}

JVOID JDataSetInit(JDataSet *pThis)
{
	JDataSetReset(pThis);
}

void JDataSetFIFOAdd(JDataSet *pThis, JFLOAT *pfData, JINT iCount, JINT iFIFOSize)
{
	JINT i = 0;
	JINT iCntAdded = 0;

	///-------------------------------------------///
	/// shift N count
	///-------------------------------------------///
	if(pThis->cnt >= iFIFOSize)
	{
		for(i = 0 ;i < (iFIFOSize - iCount); i = i + 1)
		{	
			pThis->data[i] = pThis->data[iCount + i]; 
		}
		pThis->cnt = pThis->cnt - iCount;
	}

	///-------------------------------------------///
	/// Add N data
	///-------------------------------------------///
	for(i = 0  ;i < iCount ; i = i + 1)
	{
		pThis->data[pThis->cnt + i] = pfData[i]; 
	}	

	pThis->cnt = pThis->cnt + iCount;

	pThis->idx = 0;
}


