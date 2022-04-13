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
#define SYS_CTL5_SERIAL_PORT_OPEN_FAIL		        (1<<2)

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

#define SYS_CTL6_BLE_MASTER_BIT_MODE_START				(1<<4)
#define SYS_CTL6_BLE_MASTER_BIT_MODE_STOP					(1<<5)

#define SYS_CTL6_BLE_MASTER_MONITOR_START					(1<<6)
#define SYS_CTL6_BLE_MASTER_MONITOR_STOP					(1<<7)

#define SYS_CTL6_BLE_MASTER_NOTIFY_MODE1_START		(1<<9)
#define SYS_CTL6_BLE_MASTER_NOTIFY_MODE1_STOP			(1<<10)

#define SYS_CTL6_BLE_MASTER_NOTIFY_MODE2_START		(1<<11)
#define SYS_CTL6_BLE_MASTER_NOTIFY_MODE2_STOP			(1<<12)

#define SYS_CTL6_BLE_MASTER_VSC_MODE_START				(1<<13)
#define SYS_CTL6_BLE_MASTER_VSC_MODE_STOP					(1<<14)

#define SYS_CTL6_BLE_MASTER_SSN_SET     					(1<<15)
#define SYS_CTL6_BLE_MASTER_SSN_GET     				  (1<<16)

#define SYS_CTL6_BLE_MASTER_FILE_CLEAR  					(1<<17) ///< File list clear
#define SYS_CTL6_BLE_MASTER_FILE_LIST_READ	      (1<<18) ///< File List Read
#define SYS_CTL6_BLE_MASTER_FILE_READ	            (1<<19) ///< File Read



#define SYS_CTL6_BLE_MASTER_BLE_TEST							(1<<20)

///---------------------------------------------------------------///
/// SYS_STA6: BLE
///---------------------------------------------------------------///
#define SYS_STA6_BLE_MASTER_SCAN_ON				        (1<<0)
#define SYS_STA6_BLE_MASTER_SCAN_UPDATED	        (1<<1)

#define SYS_STA6_BLE_MASTER_FILE_LIST_UPDATED	    (1<<8)  ///< update the file list UI

#define SYS_STA6_BLE_MASTER_FILE_READ_BLE       	(1<<9)  ///< read file
#define SYS_STA6_BLE_MASTER_FILE_READ_UART       	(1<<10) ///< read file

///---------------------------------------------------------------///
/// SYS_CTL7: BLE
///---------------------------------------------------------------///
#define SYS_CTL7_MSG_SERIAL_PORT_OPEN_FAILED			(1<<0)
#define SYS_CTL7_MSG_VSC_MODE_READ_FAILED	  			(1<<1)

///---------------------------------------------------------------///
/// BLE_STATE
///---------------------------------------------------------------///
#define BLE_STATE_CLOSE									(0)
#define BLE_STATE_WAIT									(1)
#define BLE_STATE_CONNECT_INIT  				(2)
#define BLE_STATE_CONNECTED							(3)
#define BLE_STATE_BIT_MODE							(4)
#define BLE_STATE_NOTIFY_MODE1					(5)
#define BLE_STATE_NOTIFY_MODE2					(6)
#define BLE_STATE_VSC_MODE							(7)


#define VSC_MODE_ARR_LEN                (60)
#define SSN_SIZE                        (32)

#define BLE_ECG_DATA_LEN                (1000)

///---------------------------------------------------------------///
/// BLE OPEN Check
///---------------------------------------------------------------///
#define BLE_OPEN_TIMEOUT                (10)


#pragma pack(push)  /// push current alignment to stack
#pragma pack(1)     /// set alignment to 1 byte boundary

///---------------------------------------------------------------///
/// ECG File Load
///---------------------------------------------------------------///
#define VSC_ATR_QUEUE_CNT            (20) ///< 20 * 200 = 4000 ms buffer of ATR
#define FILE_DATA_MAX_SIZE           (3600 * 3 * 500) ///< 3600 sec x 3 hours X 500 Hz
#define FILE_INFO_MAX_SIZE           (3600 * 3)       ///< 3600 sec x 3 hours X 1 Hz
typedef struct VscInfoSt
{
  JTM jtm;  

	/// VSC_MODE_INFO_TYPE0_TIME_UTC								(1)	
	JDWORD dwUTC;

	/// VSC_MODE_INFO_TYPE0_TEMP_T									(2)
	JFLOAT fTemp;
	
	/// VSC_MODE_INFO_TYPE0_ECG_HR									(3)
	JFLOAT fHRNow;

	/// VSC_MODE_INFO_TYPE0_ECG_LEAD_OFF						(4)
	JFLOAT fLeadOff;

	/// VSC_MODE_INFO_TYPE0_GSEN_X									(5)
	JFLOAT fGsenXNow;

	/// VSC_MODE_INFO_TYPE0_GSEN_Y									(6)
	JFLOAT fGsenYNow;

	/// VSC_MODE_INFO_TYPE0_GSEN_Z									(7)
	JFLOAT fGsenZNow;

	/// VSC_MODE_INFO_TYPE0_BATT_SOC								(8)
	JFLOAT fBattSoc;

	/// VSC_MODE_INFO_TYPE0_BATT_TOTAL_SEC					(9)
	JFLOAT fBattTotalSec;

	/// VSC_MODE_INFO_TYPE0_HRV_SDNN								(10)
	JFLOAT fHrvSDNN;
	
	/// VSC_MODE_INFO_TYPE0_HRV_NN50								(11)
	JFLOAT fHrvNN50;

	/// VSC_MODE_INFO_TYPE0_HRV_RMSSD								(12)
	JFLOAT fHrvRMSSD;

	/// VSC_MODE_INFO_TYPE0_HRV_RR									(13)
	JFLOAT fHrvRR;

	/// VSC_MODE_INFO_TYPE0_HRV_VLF									(14)
	JFLOAT fHrvVLF;

	/// VSC_MODE_INFO_TYPE0_HRV_LF									(15)
	JFLOAT fHrvLF;

	/// VSC_MODE_INFO_TYPE0_HRV_HF									(16)
	JFLOAT fHrvHF;
	
	/// TP																					(17)
	JFLOAT fHrvTP;	
	
	/// LF/TP																				(18)
	JFLOAT fHrvLFTP;	
	
	/// HF/TP																				(19)
	JFLOAT fHrvHFTP;	
	
	/// LF/HF																				(20)
	JFLOAT fHrvLFHF;

} VscInfoType;

typedef struct GlobalVarSt
{  
  ///=========================================///
  /// System Information
  ///=========================================///
  JWORD         wStatus;
  
  JINT          iBleVersion;    
  char          strBleModelName[256];    
  
  JINT          iOSType;
  
  ///=========================================///
  /// System control variables
  ///=========================================///
  JDWORD        dwSysCtl1;   ///< Basic system control
  JDWORD        dwSysCtl2;   ///< Time control
  JDWORD        dwSysCtl3;   ///< ECG control 
  JDWORD        dwSysCtl5;   ///< SERIAL PORT CONTROL : UI to Task
  JDWORD        dwSysCtl6;   ///< BLE CONTROL : UI to Task 
  JDWORD        dwSysCtl7;   ///< Message Box

  JDWORD        dwSysSta5;   ///< SERIAL PORT STATUS 
  JDWORD        dwSysSta6;   ///< BLE STATUS

  ///=========================================///
  /// APP
  ///=========================================///
  JBOOL         bAppExit;

  ///=========================================///
  /// Serial Port
  ///=========================================///
  JINT          iSerialPortArrCnt;
  char          strSerialPortArr[10][32];

	///=========================================///
  /// TIME
  ///=========================================///
  JTM  		      jtm;
  JINT          iTimeZoneSec;

  ///=========================================///
  /// Timer Control
  ///=========================================///
  JINT          iTimeMS;
  
  JINT          iTimeSec;
  JINT          iTimeSecPre;

	/// Timer Event of software
  JINT          iTime100MS;  	///< 000 / 100 / 200 / 300 / 400 / 500 / 600 / 700 / 800 / 900
  JINT          iTime100MSPre;  

  JINT          iTime10MS;  		///< 00 / 10 / 20 / 30 / 40 / 50 / 60 / 70 / 80 / 90
  JINT          iTime10MSPre;  

  ///=========================================///
  /// Thread
  ///=========================================///
   pthread_t    tid0; ///< 
   pthread_t    tid1; ///< MainLoop
   pthread_t    tid2; ///< Timer
   pthread_t    tid3; ///< SubLoop
  
  ///=========================================///
  /// Serial Port
  ///=========================================///
  JBOOL         bSerialPortOpen;

  ///=========================================///
  /// BLE
  ///=========================================///
  JBOOL         bBleConnected;
  JINT	 	      iBleState;
  JBYTE 	      bBleMacAddr[6];
  JBOOL 	      bBleScan;

  char          strBleDeviceName[256];

  JINT 		      iBleMeasMode;
  JINT 		      iBleMonitorMode;  

	BleDeviceListType BleDeviceList;

	JBOOL 	      bBleCmdOn;

  JINT          iBleOpenSec;

  ///=========================================///
	///	DataSet for charts
  ///=========================================///
	JDataSet      dataSet[DATASET_COUNT];
  JINT          iDataSetTime[DATASET_COUNT];

  ///=========================================///
  /// VSC Mode
  ///=========================================///  
  JBOOL         bVscModeAdded;
  JINT          iVscModeQueueHead;
  JINT          iVscModeQueueTail;  
  VscModeControlType vscModeQueue[VSC_MODE_ARR_LEN];

  JBOOL         bVscModeReadOn;
  long          iVscModeMSPre;

  JDWORD        dwVscModeSec; ///< VSC total run seconds

  JBOOL         bVscModeSave;  
  
  /// VSC Mode file and folder
  char 		      strVscBaseFolder[256];					///< YYMMDD_HHmmSS
  char 		      strVscDateFolder[256];					///< YYMMDD
	char 		      strVscHourFolder[256];					///< 00,01 ... 23	

  char 		      strVscFileNameInfo[256];				///< info file name
	char 		      strVscFileNameGSensor[256];		  ///< GSensor File Name
	char 		      strVscFileNameEcg[VSC_MODE_CAHNNEL_COUNT][256];	///< Ecg Data
	char 		      strVscFileNameAtrBin[256];			///< ATR BIN File Name
	char 		      strVscFileNameAtrCsv[256];			///< ATR CSV File Name

	///=========================================///
  /// VSC ATR
  ///=========================================///
  JINT		      iVscAtrCnt;
  JINT		      iVscAtrCntPre;
  JAtrType      vscAtrNow;
  JAtrType      vscAtrPre;
  JBOOL         bVscAtrUpdated;

  /// for ATR Save, it needs a queue to prevent the VSC mode delayed
  JINT          iVscAtrQueueHead;
  JINT          iVscAtrQueueTail;
  JAtrType      vscAtrQueue[VSC_ATR_QUEUE_CNT];

  ///=========================================///
  /// Data Save Path
  ///=========================================///
  char          strCurDir[256];
  char          strDataDir[256];
  char          strFileDataDir[256];

  ///=========================================///
  /// Social Security Number of Patient
  ///=========================================///
  char          strSSN[SSN_SIZE];

  ///=========================================///
  /// ECG CHART
  ///=========================================///
  JBOOL         bChartEcgRun;
  JBOOL         bChartEcgReverse;
    
  ///=========================================///
  /// Ecg Data load
  ///=========================================///
  char          strFileName[256];
  char          strFolderName[256];
  JINT          iFileDataCnt;
  JFLOAT        fFileData[FILE_DATA_MAX_SIZE]; ///< 3 hours data most
  JINT          iFileTimeMSNow;
  JINT          iFileTimeMSTotal;

  
  ///=========================================///
  /// Vsm Info File load
  ///=========================================///
  JINT          iVscInfoCnt;
  VscInfoType   VscInfoArr[FILE_INFO_MAX_SIZE];  

  ///=========================================///
  /// SREG
  ///=========================================///
  SRegType      SReg;
  JBOOL         bSRegOn;
  JBOOL         bSRegWrite;

 } GlobalVarType;

#pragma pack(pop)  /// push current alignment to stack

#endif ///< __GLOBAL_VAR_H__

