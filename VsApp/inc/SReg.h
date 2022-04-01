/**
 * @file SReg.h
 *
 *  Software Register
 *
 *
 * @version $Revision$
 * @author JLJuang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021, VitalSigns Technology, all rights reserved.
 * @note
*/
#ifndef __SREG_H__
#define __SREG_H__

#include "Global.h"

#define SREG_DEVICE_NAME            "SREG_DEVICE_NAME"
#define SREG_DEVICE_RESET           "SREG_DEVICE_RESET"
#define SREG_DEVICE_SSN             "SREG_DEVICE_SSN"
#define SREG_MEAS_ZERO_BASE         "SREG_MEAS_ZERO_BASE"
#define SREG_MEAS_LEAD_OFF          "SREG_MEAS_LEAD_OFF"
#define SREG_MEAS_LEAD_OFF_COMP_TH  "SREG_MEAS_LEAD_OFF_COMP_TH"
#define SREG_MEAS_LEAD_OFF_CURR     "SREG_MEAS_LEAD_OFF_CURR"
#define SREG_MEAS_MOTION_MODE       "SREG_MEAS_MOTION_MODE"

///---------------------------------------------------------------------------------------------------------------///
///
/// 
///
///---------------------------------------------------------------------------------------------------------------///

#pragma pack(push)
#pragma pack(1)

#define SREG_ACT_READ				  (0)
#define SREG_ACT_WRITE			  (1)

///----------------------------------------------------------------------------------///
/// SREG TYPE
///----------------------------------------------------------------------------------///
#define SREG_NAME_SIZE 			(32)
#define SREG_DATA_SIZE 			(64)
#define SREG_SIZE     			(SREG_NAME_SIZE + SREG_DATA_SIZE)
typedef struct SRegSt
{ 	
  char  strName[SREG_NAME_SIZE];
	JBYTE bData[SREG_DATA_SIZE];  
} SRegType;

///----------------------------------------------------------------------------------///
/// SREG ACTION
///----------------------------------------------------------------------------------///
typedef struct SRegActSt
{
  char  strName[SREG_NAME_SIZE];  
  JBOOL (*act)(SRegType *, JBYTE);
} SRegActType;

///----------------------------------------------------------------------------------///
/// SREG APP : for APP REG data saving
///----------------------------------------------------------------------------------///
#define SREG_DATA_DEVICE_NAME_SIZE          (32)
#define SREG_DATA_DEVICE_SSN_SIZE           (32)
#define SREG_DATA_MEAS_ZERO_BASE_SIZE       (1)
#define SREG_DATA_MEAS_LEAD_OFF_SIZE        (1)
#define SREG_DATA_MEAS_LEAD_COMP_TH_SIZE    (4)
#define SREG_DATA_MEAS_LEAD_OFF_CURR_SIZE   (1)
#define SREG_DATA_MEAS_MOTION_ACTIVATE_SIZE (1)

typedef struct SRegAppSt
{
  JBYTE DEVICE_NAME[SREG_DATA_DEVICE_NAME_SIZE];
  JBYTE DEVICE_SSN[SREG_DATA_DEVICE_SSN_SIZE];
  JBYTE MEAS_ZERO_BASE[SREG_DATA_MEAS_ZERO_BASE_SIZE];  
  JBYTE MEAS_LEAD_OFF[SREG_DATA_MEAS_LEAD_OFF_SIZE];  
  JBYTE MEAS_LEAD_OFF_COMP_TH[SREG_DATA_MEAS_LEAD_COMP_TH_SIZE];  
  JBYTE MEAS_LEAD_OFF_CURR[SREG_DATA_MEAS_LEAD_OFF_CURR_SIZE];
  JBYTE MEAS_MOTION_MODE[SREG_DATA_MEAS_MOTION_ACTIVATE_SIZE];
} SRegAppType;

#pragma pack(pop)

extern SRegAppType SRegApp;

extern void SRegRead(SRegType *pSReg);
extern void SRegWrite(SRegType *pSReg);

extern void SRegInit(void);


extern SRegActType SRegActArr[];
#endif ///< __SREG_H__

