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


#pragma pack(push)  /// push current alignment to stack
#pragma pack(1)     /// set alignment to 1 byte boundary

///---------------------------------------------------------------///
/// SSN
///---------------------------------------------------------------///
#define SSN_SIZE                        (32)

///---------------------------------------------------------------///
/// DATA SET 
///---------------------------------------------------------------///
#define DATASET_DS0					(0)
#define DATASET_DS1					(1)
#define DATASET_DS2					(2)
#define DATASET_DS3					(3)
#define DATASET_DS4					(4)
#define DATASET_DS5					(5)
#define DATASET_DS6					(6)
#define DATASET_DS7					(7)
#define DATASET_DS8					(8)
#define DATASET_DS9					(9)
#define DATASET_DS10				(10)
#define DATASET_DS11				(11)
#define DATASET_DS12				(12)
#define DATASET_DS13				(13)
#define DATASET_DS14				(14)
#define DATASET_DS15				(15)

#define DATASET_COUNT	(16)

#define DATASET_LOAD_ECG_DS0		    (DATASET_DS0)

#define DATASET_MONITOR_ECG_DS0			(DATASET_DS3)
#define DATASET_MONITOR_ECG_DS1			(DATASET_DS4)
#define DATASET_MONITOR_ECG_DS2			(DATASET_DS5)

#define DATASET_MONITOR_GSENSOR_X 	(DATASET_DS6)
#define DATASET_MONITOR_GSENSOR_Y 	(DATASET_DS7)
#define DATASET_MONITOR_GSENSOR_Z 	(DATASET_DS8)


///---------------------------------------------------------------///
/// SYS_CTL5: SERIAL_PORT
///---------------------------------------------------------------///
#define SYS_CTL5_SERIAL_PORT_OPEN					        (1<<0)
#define SYS_CTL5_SERIAL_PORT_CLOSE				        (1<<1)

///---------------------------------------------------------------///
/// SYS_STA5: SERIAL_PORT
///---------------------------------------------------------------///
#define SYS_STA5_SERIAL_PORT_OPEN					        (1<<0)

///---------------------------------------------------------------///
/// SYS_CTL6: BLE
///---------------------------------------------------------------///
#define SYS_CTL6_BLE_MASTER_SCAN_START						(1<<0)
#define SYS_CTL6_BLE_MASTER_SCAN_STOP							(1<<1)


#define SYS_CTL6_BLE_MASTER_OPEN									(1<<2)
#define SYS_CTL6_BLE_MASTER_CLOSE									(1<<3)

///---------------------------------------------------------------///
/// SYS_STA6: BLE
///---------------------------------------------------------------///
#define SYS_STA6_BLE_MASTER_SCAN_ON				        (1<<0)
#define SYS_STA6_BLE_MASTER_SCAN_UPDATED	        (1<<1)

#define SYS_CTL6_BLE_MASTER_VSC_MODE_START				(1<<13)
#define SYS_CTL6_BLE_MASTER_VSC_MODE_STOP					(1<<14)

#define SYS_CTL6_BLE_MASTER_SSN_SET     					(1<<15)
#define SYS_CTL6_BLE_MASTER_SSN_GET     				  (1<<16)

///---------------------------------------------------------------///
/// BLE_STATE
///---------------------------------------------------------------///
#define BLE_STATE_CLOSE									          (0)
#define BLE_STATE_WAIT									          (1)
#define BLE_STATE_CONNECT_INIT  				          (2)
#define BLE_STATE_CONNECTED							          (3)
#define BLE_STATE_BIT_MODE							          (4)
#define BLE_STATE_NOTIFY_MODE1					          (5)
#define BLE_STATE_NOTIFY_MODE2					          (6)
#define BLE_STATE_VSC_MODE						          	(7)

///---------------------------------------------------------------///
/// BLE OPEN Check
///---------------------------------------------------------------///
#define BLE_OPEN_TIMEOUT             (10)

typedef struct GlobalVarSt
{  
  ///=========================================///
  /// System Information
  ///=========================================///
  JWORD wStatus;
  JWORD wVersion;   
  
  ///=========================================///
  /// system control variables
  ///=========================================///
  JDWORD dwSysCtl1; 
  JDWORD dwSysCtl2; 
  JDWORD dwSysCtl5;   ///< SERIAL PORT CONTROL : UI to Task
  JDWORD dwSysCtl6;   ///< BLE CONTROL : UI to Task 

  JDWORD dwSysSta5;   ///< SERIAL PORT STATUS 
  JDWORD dwSysSta6;   ///< BLE STATUS

  ///=========================================///
  /// APP
  ///=========================================///
  JBOOL bAppExit;

	///=========================================///
  /// TIME
  ///=========================================///
  JTM  		jtm;
  JINT    iTimeZoneSec;

  ///=========================================///
  /// Timer Control
  ///=========================================///
  JINT iTimeMS;
  
  JINT iTimeSec;
  JINT iTimeSecPre;

	/// Timer Event of software
  JINT iTime100MS;  	///< 000 / 100 / 200 / 300 / 400 / 500 / 600 / 700 / 800 / 900
  JINT iTime100MSPre;  

  JINT iTime10MS;  		///< 00 / 10 / 20 / 30 / 40 / 50 / 60 / 70 / 80 / 90
  JINT iTime10MSPre;  

  ///=========================================///
  /// Thread
  ///=========================================///
   pthread_t    tid0;
  
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

  JINT    iBleOpenSec;

  ///=========================================///
	///	DataSet for charts
  ///=========================================///
	JDataSet 	dataSet[DATASET_COUNT];
  JINT      iDataSetTime[DATASET_COUNT];

  ///=========================================///
  /// VSC Mode
  ///=========================================///
  JBOOL   bVscMode;
  JBOOL   bVscModeAdded;
  JINT    iVscModeArrIdxRead;
  JINT    iVscModeArrIdx;  
  VscModeControlType vscModeArr[VSC_MODE_ARR_LEN];

  JBOOL         bVscModeReadOn;
  long          iVscModeMSPre;

  JDWORD        dwVscModeSec; ///< VSC total run seconds
  
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

