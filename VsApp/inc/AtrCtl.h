/**
 * @file AtrDataCtl.h
 *
 *  Atr Data Control Function
 *
 * @version $Revision$
 * @author JLJuang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021, VitalSigns Technology Co., Ltd., all rights reserved.
 * @note
*/
#ifndef __ATR_DATA_CTL_H__
#define __ATR_DATA_CTL_H__ 
#pragma pack(push)  /// push current alignment to stack
#pragma pack(1)     /// set alignment to 1 byte boundary

typedef struct AtrDataSt
{
	JWORD 	dwA;
	JFLOAT 	fTimeSec;
} AtrDataType;

typedef struct AtrSearchSt
{
	JFLOAT			fTimeSec0; 	///< search AtrSec >= fTimeSec0 && AtrSec < fTimeSec1
	JFLOAT			fTimeSec1;	///<
	JINT 				iIdx;		  	///< 1st 	Atr Data Idx in atrData (-1)
	JINT 				iCnt;				///< Last Atr Data Idx in atrData (-1)
} AtrFindType;

#define ATR_DATA_CNT		(60 * 3 * 200) ///< 60 min x 3 hours X 200 BPM
typedef struct AtrCtlSt
{
	JINT 				iAtrDataCnt;	
	AtrDataType atrData[ATR_DATA_CNT];
} AtrCtlType;

#pragma pack(pop)


extern AtrCtlType AtrCtl;			///< load from file
extern AtrCtlType AtrCtlBle;	///< run time 

extern JBOOL AtrCtlLoad(AtrCtlType *pAtrCtl, char * strFileName);

extern JBOOL AtrAbbrevGet(JDWORD dwA, char * pAbbrev, JDWORD *pdwColor);

extern JBOOL AtrCtlFind(AtrCtlType *pAtrCtl, AtrFindType *pAtrFind);
extern JBOOL AtrCtlAdd(AtrCtlType  *pAtrCtl, JDWORD A, JFLOAT fTimeSec);
extern JBOOL AtrCtlVscModeAdd(AtrCtlType *pAtrCtl, JDWORD dwA, JFLOAT fTimeSec);
extern JBOOL AtrCtlInit(AtrCtlType *pAtrCtl);

#endif ///<  __ATR_DATA_CTL_H__
