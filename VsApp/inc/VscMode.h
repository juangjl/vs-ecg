/**
 * @file VscMode.h
 *
 *  VscMode Function
 *
 * @version $Revision$
 * @author JLJuang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021, VitalSigns Technology Co., Ltd., all rights reserved.
 * @note
*/
#ifndef __VSC_MODE_H__
#define __VSC_MODE_H__ 

#define VSC_MODE_INFO_TYPE													(0)

#define VSC_MODE_INFO_TYPE0_TIME_UTC								(1)
#define VSC_MODE_INFO_TYPE0_TEMP_T									(2)
#define VSC_MODE_INFO_TYPE0_ECG_HR									(3)
#define VSC_MODE_INFO_TYPE0_ECG_LEAD_OFF						(4)
#define VSC_MODE_INFO_TYPE0_GSEN_X									(5)
#define VSC_MODE_INFO_TYPE0_GSEN_Y									(6)
#define VSC_MODE_INFO_TYPE0_GSEN_Z									(7)
#define VSC_MODE_INFO_TYPE0_BATT_SOC								(8)
#define VSC_MODE_INFO_TYPE0_BATT_TOTAL_SEC					(9)
#define VSC_MODE_INFO_TYPE0_HRV_SDNN								(10)
#define VSC_MODE_INFO_TYPE0_HRV_NN50								(11)
#define VSC_MODE_INFO_TYPE0_HRV_RMSSD								(12)
#define VSC_MODE_INFO_TYPE0_HRV_RR									(13)
#define VSC_MODE_INFO_TYPE0_HRV_VLF									(14)
#define VSC_MODE_INFO_TYPE0_HRV_LF									(15)
#define VSC_MODE_INFO_TYPE0_HRV_HF									(16)

#define VSC_MODE_INFO_TYPE0_BAR                     (17)
#define VSC_MODE_INFO_TYPE0_BAR_TEMP                (18)

#define VSC_MODE_INFO_TYPE0_GSEN_DATA0              (19) ///< GS_X0 |  GS_Y0
#define VSC_MODE_INFO_TYPE0_GSEN_DATA1              (20) ///< GS_Z0 |  GS_X1
#define VSC_MODE_INFO_TYPE0_GSEN_DATA2              (21) ///< GS_Y1 |  GS_Z1
#define VSC_MODE_INFO_TYPE0_GSEN_DATA3              (22) ///< GS_X2 |  GS_Y2
#define VSC_MODE_INFO_TYPE0_GSEN_DATA4              (23) ///< GS_Z2 |  GS_X3
#define VSC_MODE_INFO_TYPE0_GSEN_DATA5              (24) ///< GS_Y3 |  GS_Z3
#define VSC_MODE_INFO_TYPE0_GSEN_DATA6              (25) ///< GS_X4 |  GS_Y4
#define VSC_MODE_INFO_TYPE0_GSEN_DATA7              (26) ///< GS_Z4 |  --

#define VSC_MODE_INFO_TYPE0_ATR				              (27) ///< ATR CODE
#define VSC_MODE_INFO_TYPE0_ATR_TIME	              (28) ///< ATR TIME



#define VSC_MODE_IDX_INVALID				 (8000)
#define VSC_MODE_IDX_MAX						 (1000)

#define VSC_MODE_ITEM_DATA_SIZE      (800)  ///< 200 ms 
#define VSC_MODE_ITEM_INFO_SIZE      (168)  ///< 42 information

#define VSC_MODE_ITEM_INFO_COUNT     (VSC_MODE_ITEM_INFO_SIZE / 4)  ///< 168 / 4 =  42

typedef struct VscModeItemType
{
	JWORD 	wId;																		///< Packet Idx
	JWORD 	wLen;																		///< Packet Idx	
  JBYTE 	bData[VSC_MODE_ITEM_DATA_SIZE] ; 				///< 800 bytes channels' data
	JFLOAT 	fInfo[VSC_MODE_ITEM_INFO_COUNT]; 				///< 104 bytes  for information 26 x 4 = 104
} VscModeItemType;

#define 	VSC_MODE_CAHNNEL_COUNT							(2)
#define 	VSC_MODE_CAHNNEL_DATA_COUNT					(100)	///< 200ms @ 500 hz =  100
#define 	VSC_MODE_GSENSOR_DATA_COUNT					(5)		///< 200ms @ 25  hz =  5
typedef struct VscModeControlSt
{
	JWORD 	wId;
	JDWORD 	dwPacketCnt;
	JINT 		iChannelCount;	
	
	JINT		iTimeBase;
	
	///------------------------------------------------///
	/// File related function
	///------------------------------------------------///
	char 		strBaseFolder[256];			///<  YYMMDD_HHmmSS
	char 		strDateFolder[256];			///<	YYMMDD
	char 		strHourFolder[256];			///<	00,01 ... 23	
	char 		strFileNameInfo[512];
	char 		strFileNameGSensor[512];
	char 		strFileNameData[VSC_MODE_CAHNNEL_COUNT][512];
	JFLOAT 	fValueCH[VSC_MODE_CAHNNEL_COUNT][VSC_MODE_CAHNNEL_DATA_COUNT];

	VscModeItemType item;
	
	JTM 		jtm;						///< 0 :
	JDWORD 	dwUTC;					///< 1 :
	JFLOAT 	fTemp;					///< 2 :
	JFLOAT 	fHRNow;					///< 3 :
	JFLOAT 	fLeadOff;				///< 4 :
	JFLOAT 	fGsenXNow;			///< 5 :
	JFLOAT 	fGsenYNow;			///< 6 : 
	JFLOAT 	fGsenZNow;			///< 7 : 
	JFLOAT 	fBattSoc;				///< 8 : 
	JFLOAT 	fBattTotalSec;	///< 9 : 
	JFLOAT 	fHrvSDNN;				///< 10 : 
	JFLOAT 	fHrvNN50;				///< 11 : 
	JFLOAT 	fHrvRMSSD;			///< 12 : 
	JFLOAT 	fHrvRR;					///< 13 : 

	JFLOAT 	fHrvVLF;				///< 14 : 
	JFLOAT 	fHrvLF;					///< 15 : 
	JFLOAT 	fHrvHF;					///< 16 : 
	
	JFLOAT 	fHrvLFHF;				///<
	JFLOAT 	fHrvTP;					///<
	JFLOAT 	fHrvLFTP;				///<
	JFLOAT 	fHrvHFTP;				///<

	JFLOAT 	fBar;						///< 17 :
	JFLOAT 	fBarTemp;				///< 18 :

	JSHORT  sGSenX[5];			///< 19~26 :
	JSHORT  sGSenY[5];			///< 19~26 : 
	JSHORT  sGSenZ[5];			///< 19~26 : 

	JAtrType atrNow;				///< 27 :	
} VscModeControlType;

extern VscModeControlType VscModeCtl;

extern void VscModeFileNameSet(VscModeControlType *pVscMode);
extern void VscModeSave(VscModeControlType *pVscMode);
extern void VscModeDecode(JWORD wId, JWORD wLen, JBYTE *pbData);
extern void VscModeInit(char *pBaseFolder);

extern void VscModeAtrBinSave(void);
extern void VscModeAtrCsvSave(void);

#endif ///<  __VSC_MODE_H__

