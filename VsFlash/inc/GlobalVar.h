/**
 * @file GlobalVar.h
 *
 *  Global variable type
 *
 * @version $Revision$
 * @author JLJuang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021, VitalSigns Technology Co., Ltd., all rights reserved.
 * @note
*/

#ifndef __GLOBAL_VAR_H__
#define __GLOBAL_VAR_H__

#define BOOTCODE_MODEL_NAME    "Bootload"

#pragma pack(push)  /// push current alignment to stack
#pragma pack(1)     /// set alignment to 1 byte boundary

///---------------------------------------------------------------///
/// SYS_CTL5: SERIAL_PORT
///---------------------------------------------------------------///
#define SYS_CTL5_SERIAL_PORT_OPEN					        (1<<0)
#define SYS_CTL5_SERIAL_PORT_CLOSE				        (1<<1)

#define SYS_CTL5_FLASH_START    					      (1<<2)
#define SYS_CTL5_FLASH_CANCEL   					      (1<<3)

///---------------------------------------------------------------///
/// SYS_STA5: SERIAL_PORT
///---------------------------------------------------------------///
#define SYS_STA5_SERIAL_PORT_OPEN					        (1<<0)

///---------------------------------------------------------------///
/// BLE_STATE
///---------------------------------------------------------------///
#define JSTATE_INIT	  								            (0)
#define JSTATE_BOOTCODE							              (1)
#define JSTATE_RECONNECT						              (2)
#define JSTATE_DFU_START    				              (3)
#define JSTATE_DFU_WRITE							            (4)
#define JSTATE_DFU_END  							            (5)
#define JSTATE_ERROR  								            (6)
#define JSTATE_END	  								            (7)
#define JSTATE_NULL	  								            (8)

typedef struct GlobalVarSt
{  
  ///=========================================///
  /// System Information
  ///=========================================///
  JWORD   wStatus;

  char    strModelName[256];
  JINT    iVersion;

  
  ///=========================================///
  /// system control variables
  ///=========================================///
  JDWORD  dwSysCtl2; 
  JDWORD  dwSysCtl5;   ///< SERIAL PORT CONTROL : UI to Task
  
  JDWORD  dwSysSta5;   ///< SERIAL PORT STATUS 

  ///=========================================///
  /// APP
  ///=========================================///
  JBOOL   bAppExit;

	///=========================================///
  /// TIME
  ///=========================================///
  JTM  		jtm;
  JINT    iTimeZoneSec;

  ///=========================================///
  /// Timer Control
  ///=========================================///
  JINT    iTimeMS;
  
  JINT    iTimeSec;
  JINT    iTimeSecPre;

	/// Timer Event of software
  JINT    iTime100MS;  	///< 000 / 100 / 200 / 300 / 400 / 500 / 600 / 700 / 800 / 900
  JINT    iTime100MSPre;  

  JINT    iTime10MS;  		///< 00 / 10 / 20 / 30 / 40 / 50 / 60 / 70 / 80 / 90
  JINT    iTime10MSPre;  

  ///=========================================///
  /// Thread
  ///=========================================///
   pthread_t    tid0;
  
  ///=========================================///
  /// Serial Port
  ///=========================================///
  JBOOL   bSerialPortInitConnect;
  JBOOL   bSerialPortOpen;
  char    strSerialPortName[256];

  ///=========================================///
  /// State
  ///=========================================///
  JINT	 	iState;
  JINT    iStateWaitMS;
    
  ///=========================================///
  /// Data Save Path
  ///=========================================///
  char    strCurDir[256];  

  ///=========================================///
  /// Flash
  ///=========================================///  
  JBOOL   bFlashStart;
  char    strFlashMsg[256];

  JBYTE * pFileData;
  JINT    iFileSize;

  JBOOL   bDFUWriteOn;
  JFLOAT  fProgress;
  time_t  tDfuT0;
  time_t  tDfuT1;
  JINT    iDfuEclapse;
  
 } GlobalVarType;

#pragma pack(pop)  /// push current alignment to stack

#endif ///< __GLOBAL_VAR_H__

