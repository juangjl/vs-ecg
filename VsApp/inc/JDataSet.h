/**
 * @file JDataset.h
 *
 *   Dataset header
 *
 * @version $Revision$
 * @author JL Juang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021,  VitalSigns Technology CO., LTD., all rights reserved.
 * @note
*/
#ifndef __JDATASET_H__
#define __JDATASET_H__
#include "Global.h"

#define JDATA_SAMPLE_RATE				(500) ///< Hz
#define JDATA_MAX_SEC						(10) 	///< second
#define JDATA_MAX_CNT						(JDATA_SAMPLE_RATE * JDATA_MAX_SEC)

typedef struct JDataSetSt
{
	JINT 		idx;		
	JINT 		cnt;
	JFLOAT 	data[JDATA_MAX_CNT];
} JDataSet;

extern JBOOL 	JDataSetAdd(JDataSet *pThis, JINT  iData);
extern JINT 	JDataSetGetEx(JDataSet *pThis, JINT idx, JINT iQueueIdx);
extern JINT 	JDataSetGet(JDataSet *pThis, JINT  idx);
extern JVOID 	JDataSetReset(JDataSet *pThis);
extern JVOID 	JDataSetInit(JDataSet *pThis);

extern void 	JDataSetFIFOAdd(JDataSet *pThis, JFLOAT *pfData, JINT  iCount, JINT iMaxCount);

#endif ///< __JDATASET_H__

