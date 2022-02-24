/**
 * @file TypeDef.h
 *
 *  TypeDef.h define variable type
 *
 * @version $Revision$
 * @author JLJuang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021, VitalSigns Technology Co., Ltd., all rights reserved.
 * @note
*/

#ifndef __GLOBAL_VAR_H__
#define __GLOBAL_VAR_H__


#pragma pack(push)  /// push current alignment to stack
#pragma pack(1)     /// set alignment to 1 byte boundary

#define SSN_SIZE                        (32)

typedef struct GlobalVarSt
{  
  ///=========================================///
  /// System Information
  ///=========================================///
  JWORD wStatus;
  JWORD wVersion;   
  
  ///=========================================///
  /// Serial Port
  ///=========================================///
  JBOOL bSerialPortOpen;

  ///=========================================///
  /// BLE
  ///=========================================///
  JBOOL 	bBleConnected;
  JINT	 	iBleState;
  JBYTE 	bBleMacAddr[6];
  JBOOL 	bBleScan;

  char    strBleDeviceName[256];

  JINT 		iBleMeasMode;
  JINT 		iBleMonitorMode;  

	BleDeviceListType BleDeviceList;

	JBOOL 	bBleCmdOn;

  ///=========================================///
  /// VSC Mode
  ///=========================================///
  JBOOL   bVscMode;
  JBOOL   bVscModeAdded;
  JINT    iVscModeArrIdxRead;
  JINT    iVscModeArrIdx;  
  VscModeControlType vscModeArr[VSC_MODE_ARR_LEN];
  
  ///=========================================///
  /// Data Save Path
  ///=========================================///
  char    strCurDir[256];
  char    strDataDir[256];
  char    strFileDataDir[256];

  ///=========================================///
  /// Social Security Number of Patient
  ///=========================================///
  char    strSSN[SSN_SIZE];
  
 } GlobalVarType;

#pragma pack(pop)  /// push current alignment to stack

#endif ///< __GLOBAL_VAR_H__

