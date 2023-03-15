/**
 * @file JGatt.h
 *
 *  JGATT
 *
 * @version $Revision$
 * @author JL Juang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2022,  VitalSigns Technology Co., LTD., all rights reserved.
 * @note
*/
#ifndef __JGATT_H__
#define __JGATT_H__

#if OS_TYPE == OS_TYPE_UBUNTU
#define FEATURE_JGATT
#endif //< for OS_TYPE_UBUNTU

//#define FEATURE_JGATT ///< for ubuntu only

#ifdef FEATURE_JGATT
#include "VscMode.h"

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/epoll.h>

#include "lib/bluetooth.h"
#include "lib/hci.h"
#include "lib/hci_lib.h"
#include "lib/l2cap.h"
#include "lib/uuid.h"


/// ATT protocol opcodes 
#define BT_ATT_OP_ERROR_RSP							(0x01)
#define BT_ATT_OP_MTU_REQ								(0x02)
#define BT_ATT_OP_MTU_RSP								(0x03)
#define BT_ATT_OP_FIND_INFO_REQ					(0x04)
#define BT_ATT_OP_FIND_INFO_RSP					(0x05)
#define BT_ATT_OP_FIND_BY_TYPE_REQ			(0x06)
#define BT_ATT_OP_FIND_BY_TYPE_RSP			(0x07)
#define BT_ATT_OP_READ_BY_TYPE_REQ			(0x08)
#define BT_ATT_OP_READ_BY_TYPE_RSP			(0x09)
#define BT_ATT_OP_READ_REQ							(0x0a)
#define BT_ATT_OP_READ_RSP							(0x0b)
#define BT_ATT_OP_READ_BLOB_REQ					(0x0c)
#define BT_ATT_OP_READ_BLOB_RSP					(0x0d)
#define BT_ATT_OP_READ_MULT_REQ					(0x0e)
#define BT_ATT_OP_READ_MULT_RSP					(0x0f)
#define BT_ATT_OP_READ_BY_GRP_TYPE_REQ	(0x10)
#define BT_ATT_OP_READ_BY_GRP_TYPE_RSP	(0x11)
#define BT_ATT_OP_WRITE_REQ							(0x12)
#define BT_ATT_OP_WRITE_RSP							(0x13)
#define BT_ATT_OP_WRITE_CMD							(0x52)
#define BT_ATT_OP_SIGNED_WRITE_CMD			(0xD2)
#define BT_ATT_OP_PREP_WRITE_REQ				(0x16)
#define BT_ATT_OP_PREP_WRITE_RSP				(0x17)
#define BT_ATT_OP_EXEC_WRITE_REQ				(0x18)
#define BT_ATT_OP_EXEC_WRITE_RSP				(0x19)
#define BT_ATT_OP_HANDLE_VAL_NOT				(0x1B)
#define BT_ATT_OP_HANDLE_VAL_IND				(0x1D)
#define BT_ATT_OP_HANDLE_VAL_CONF				(0x1E)

///--------------------------------------------------------------------------------------------------///
///
///  JGATT DEFINED VARIABLE
///
///--------------------------------------------------------------------------------------------------///
#define JGATT_HCI_DEV_ID_INVALID                    (-1)

#define JGATT_SOCKET_INVALID                        (-1)
#define JGATT_HANDLE_INVALID                        (0xFFFF)

///--------------------------------------------------------------------------------------------------///
///
/// Header
///
///--------------------------------------------------------------------------------------------------///
#include "Global.h"

///--------------------------------------------------------------------------------------------------///
/// AD DATA TYPE
///--------------------------------------------------------------------------------------------------///
#define AD_TYPE_FLAG																(0x01)
#define AD_TYPE_16BITS_UUID_INC											(0x02)
#define AD_TYPE_16BITS_UUID													(0x03)
#define AD_TYPE_32BITS_UUID_INC											(0x04)
#define AD_TYPE_32BITS_UUID													(0x05)
#define AD_TYPE_128BITS_UUID_INC										(0x06)
#define AD_TYPE_128BITS_UUID												(0x07)
#define AD_TYPE_SHORTNAME														(0x08)
#define AD_TYPE_NAME																(0x09)
#define AD_TYPE_TX_POWER														(0x0A)  	///< 1 byte, 0xXX: -127 to +127 dBm 
#define AD_TYPE_DEVICE_CLASS												(0x0D)		///< 3 bytes 
#define AD_TYPE_PAIRING_HASH_C									  	(0x0E)		///< 16 bytes 
#define AD_TYPE_PAIRING_HASH_RANDOMIZE_R 						(0x0F)		///< 16 bytes 
#define AD_TYPE_EXTENDED_INQUIRY_RESPONSE_RECORD		(0x10)	
#define AD_TYPE_MFA_INFO     												(0xFF)

/// AD DATA NAME SIZE
#define AD_BLE_NAME_SIZE                            (24)

#define ATT_CID					(4)
#define ATT_PSM					(31)

///-----------------------------------------------------------------------------------------------///
///
///  ATT
///
///-----------------------------------------------------------------------------------------------///
#define JATT_TYPE_UUID_PRIMARY_SERVICE                   (0x2800)
#define JATT_TYPE_UUID_SECONDARY_SERVICE                 (0x2801)
#define JATT_TYPE_UUID_INCLUDE                           (0x2802)
#define JATT_TYPE_UUID_CHARACTERISTIC                    (0x2803)
#define JATT_TYPE_UUID_CHARACTERISTIC_EXTEND             (0x2900)
#define JATT_TYPE_UUID_CHARACTERISTIC_DESC               (0x2901)
#define JATT_TYPE_UUID_CLIENT_CHARACTERISTIC_CONFIG      (0x2902)
#define JATT_TYPE_UUID_SERVER_CHARACTERISTIC_CONFIG      (0x2903)
#define JATT_TYPE_UUID_CHARACTERISTIC_PS_FORMAT          (0x2904)
#define JATT_TYPE_UUID_CHARACTERISTIC_AGG_FORMAT         (0x2905)

///--------------------------------------------------------------------------------------------------///
/// SCAN
///--------------------------------------------------------------------------------------------------///
#define JGATT_SCAN_STATUS_OFF                       (0)
#define JGATT_SCAN_STATUS_ON                        (1)
#define JGATT_SCAN_STATUS_STOP                      (2)

///--------------------------------------------------------------------------------------------------///
/// GATT TX / RX Flag
///--------------------------------------------------------------------------------------------------///
#define GATT_STATUS_TX_INIT                         (0)
#define GATT_STATUS_TX_OK                           (1)
#define GATT_STATUS_TX_WRITE_ERROR                  (2)
#define GATT_STATUS_TX_ATT_ERROR                    (3)

#define GATT_STATUS_RX_INIT                         (0)
#define GATT_STATUS_RX_OK                           (1)
#define GATT_STATUS_RX_OVERFLOW                     (2)
#define GATT_STATUS_RX_READING                      (3)

///--------------------------------------------------------------------------------------------------///
/// GATT Response
///--------------------------------------------------------------------------------------------------///
#define JGATT_CB_RESP_NONE                          (0)
#define JGATT_CB_RESP_CHAR_RX_OK                    (1)
#define JGATT_CB_RESP_CHAR_TX_OK                    (2)
#define JGATT_CB_RESP_NOTIFY_REGISTER_OK            (1)
#define JGATT_CB_RESP_NOTIFY_REGISTER_FAILED        (2)


///--------------------------------------------------------------------------------------------------///
///
///--------------------------------------------------------------------------------------------------///
#define BLE_MAC_ADDR_SIZE                           (6)
#define ADAPTER_INFO_SIZE                           (256)

///--------------------------------------------------------------------------------------------------///
/// Scan device item
///--------------------------------------------------------------------------------------------------///
#define GATT_SCAN_PERIOD                            (50)  ///< 50 ms
#define GATT_SCAN_ITEM_NAME_SIZE                    (64)
#define GATT_SCAN_VALID_COUNT                       (200)
typedef struct JGattScanItemSt
{
  char  strName[GATT_SCAN_ITEM_NAME_SIZE];
  JBYTE bAddr[BLE_MAC_ADDR_SIZE];
  JINT  iRSSI;
  JINT  iValidCnt;
} JGattScanItemType;


///-----------------------------------------------------------------------------------------------///
///
///  EPOLL
///
///-----------------------------------------------------------------------------------------------///
#define EPOLL_FP_INIT   (0)

typedef struct EPollEventSt
{
  JINT    iValid;
  JINT    fd;
  JDWORD  dwEvent;
} EpollEventType;

///-----------------------------------------------------------------------------------------------///
///
///  SERVICE
///
///-----------------------------------------------------------------------------------------------///
typedef struct JGattServiceSt
{
  JWORD wStart;
  JWORD wEnd;
  JBYTE bUuid[16];
  JBYTE bUuidLen; ///< 2 or 16
} JGattServiceType;

#define JGATT_SERVICE_MAX_COUNT     (20)

                        
///-----------------------------------------------------------------------------------------------///
///
///  CHARACTER
///
///-----------------------------------------------------------------------------------------------///
typedef struct JGattCharacteristicSt
{
  JWORD wStart;  
  JWORD wEnd;
  JWORD wHandle;
  JBYTE bUuid[16];
  JBYTE bUuidLen; ///< 2 or 16
  JBYTE bProperty;  
} JGattCharacteristicType;

#define JGATT_CHARACTERISTIC_MAX_COUNT     (20)


///--------------------------------------------------------------------------------------------------///
/// JGATT State
///--------------------------------------------------------------------------------------------------///
#define JGATT_STATE_INIT                      (0)
#define JGATT_STATE_CLOSE                     (1)
#define JGATT_STATE_OPEN_INIT                 (2)
#define JGATT_STATE_OPEN                      (3)
#define JGATT_STATE_SERVICE_FIND              (4)
#define JGATT_STATE_SERVICE_FINDING           (5)
#define JGATT_STATE_CHARACTERISTIC_FIND       (5)

#define JGATT_STATE_NOTIFY_REGISTER           (6)

#define JGATT_STATE_OPENING                   (8)

#define JGATT_STATE_OPEN_OK                   (11)
#define JGATT_STATE_OPEN_FAILED               (12)

#define JGATT_STATE_SCAN_START                (13)
#define JGATT_STATE_SCAN_STOP                 (14)
#define JGATT_STATE_SCAN_RESULT               (15)

#define JGATT_STATE_VSC_MODE_INIT             (16)
#define JGATT_STATE_VSC_MODE_START            (17)
#define JGATT_STATE_VSC_MODE_READ             (18)
#define JGATT_STATE_VSC_MODE_STOP             (19)

#define JGATT_STATE_END                       (1000)

///--------------------------------------------------------------------------------------------------///
/// JGATT state timer
///--------------------------------------------------------------------------------------------------///
#define JGATT_TIMER_MS                        (5)

///--------------------------------------------------------------------------------------------------///
/// JGATT OPEN STATUS
///--------------------------------------------------------------------------------------------------///
#define JGATT_STATUS_OPEN_INIT                (0)
#define JGATT_STATUS_OPEN_OK                  (1)
#define JGATT_STATUS_OPEN_FAILED              (-1)

///--------------------------------------------------------------------------------------------------///
/// JGATT SERVICE Find
///--------------------------------------------------------------------------------------------------///
#define JGATT_SERVICE_FIND_INIT               (0)
#define JGATT_SERVICE_FIND                    (1)
#define JGATT_SERVICE_FINDING                 (2)
#define JGATT_SERVICE_FIND_OK                 (3)

///--------------------------------------------------------------------------------------------------///
/// JGATT CHARACTERISTIC
///--------------------------------------------------------------------------------------------------///
#define JGATT_CHARACTERISTIC_FIND_INIT        (0)
#define JGATT_CHARACTERISTIC_FIND             (1)
#define JGATT_CHARACTERISTIC_FINDING          (2)
#define JGATT_CHARACTERISTIC_FIND_OK          (3)

///--------------------------------------------------------------------------------------------------///
/// JGATT Notify
///--------------------------------------------------------------------------------------------------///
#define JGATT_NOTIFY_REGISTER_INIT            (0)
#define JGATT_NOTIFY_REGISTER_ON              (1)
#define JGATT_NOTIFY_REGISTER_OK              (2)

///--------------------------------------------------------------------------------------------------///
/// JGATT COMMAND
///--------------------------------------------------------------------------------------------------///
#define JGATT_CMD_STATUS_IDLE                 (0)
#define JGATT_CMD_STATUS_SEND                 (1)
#define JGATT_CMD_STATUS_SEND_OK              (2)
#define JGATT_CMD_STATUS_DATA_OK              (3)
#define JGATT_CMD_STATUS_DONE                 (4)

///--------------------------------------------------------------------------------------------------///
/// JGattCtl object
///--------------------------------------------------------------------------------------------------///
#define JGATT_SCAN_ITEM_CNT                   (30)
#define JGATT_RX_BUF_MAX_SIZE                 (8192)

typedef struct JGattCtlSt
{
  /// HCI Adpater Device Id
  JINT  iHciDevId;
  JINT  iDD;
 
  /// HCI Adapter Mac Address
  JBYTE bHciDevMacAddr[BLE_MAC_ADDR_SIZE];

  char  strBusName[ADAPTER_INFO_SIZE];
  char  strInterfaceName[ADAPTER_INFO_SIZE];
  char  strAdPathName[ADAPTER_INFO_SIZE];

  /// BLE scan status 
  JINT  iScanStatus;
  JBOOL bScanUIUpdate;
  
  /// BLE Scanned items
  JINT iScanItemCnt;
  JGattScanItemType ScanItems[JGATT_SCAN_ITEM_CNT];

  /// BLE mac 
  JBYTE bBleDevMacAddr[BLE_MAC_ADDR_SIZE];

  /// Gatt
  JINT  iSocket;
  struct bt_att  * att;
  struct gatt_db * db;
	struct bt_gatt_client * gatt;

  
  ///----------------------------------------------------------------///
  /// Thread
  ///----------------------------------------------------------------///
  pthread_t    tidScan;
  
  ///----------------------------------------------------------------///
  /// Scan  time
  ///----------------------------------------------------------------///
  time_t  iScanTimeT0;
  time_t  iScanTimeT1;
  JINT    iScanTimeSec;

  ///----------------------------------------------------------------///
  /// GattState
  ///----------------------------------------------------------------///
  JINT    iGattState;
  JINT    iGattStateStep;

  ///----------------------------------------------------------------///  
  /// Open status
  ///----------------------------------------------------------------///
  JINT    iGattStatus;

  JINT    iGattCBResp;

  ///----------------------------------------------------------------///
  /// timeout control
  ///----------------------------------------------------------------///
  JINT    iGattTimeMS;
  JINT    iGattTimeOutMS;
  JINT    iGattTimeWaitMS;

  time_t  iOpenTimeT0;
  time_t  iOpenTimeT1;
  JINT    iOpenTimeSec;


  JLONG   tVsdModeStart;
  JLONG   t0; ///< previous T
  JLONG   t1; ///< now T    

  ///----------------------------------------------------------------///
  /// Gatt Handle
  ///----------------------------------------------------------------///
  JWORD   wHandleRx;
  JWORD   wHandleTx;

  ///----------------------------------------------------------------///
  /// Gatt status of TX and RX 
  ///----------------------------------------------------------------///  
  JINT    iGattStatusRx;
  
  JBYTE   bGattRxBuf[JGATT_RX_BUF_MAX_SIZE];
  JINT    iGattRxBufLen;
  JINT    iGattRxBufIdx;

	///----------------------------------------------------------------///
  /// VSC Mode
  ///----------------------------------------------------------------///
  JBOOL    bVscModeAdded;
  JINT     iVscModeQueueHead;
  JINT     iVscModeQueueTail;  
  VscModeControlType vscModeQueue[VSC_MODE_QUEUE_SIZE];

  ///----------------------------------------------------------------///  
  ///  MTU
  ///----------------------------------------------------------------///
  JINT    iMtu;
  
  ///----------------------------------------------------------------///  
  ///  Service
  ///----------------------------------------------------------------///
  JWORD   wServiceStart;
  JWORD   wServiceEnd;
  JBOOL   bServiceFind;
  JINT    iServiceCnt;

  ///----------------------------------------------------------------///  
  ///  Characteristic
  ///----------------------------------------------------------------///
  JWORD   wCharacteristicStart;
  JWORD   wCharacteristicEnd;
  JBOOL   bCharacteristicFind;
  JINT    iCharacteristicCnt;

  ///----------------------------------------------------------------///  
  /// Notify register
  ///----------------------------------------------------------------///  
  JBOOL  bNotifyRegister;

  ///----------------------------------------------------------------///  
  ///  Write Request & response
  ///----------------------------------------------------------------///
  JBOOL   bWriteReq;
  JBOOL   bWriteRsp;

  ///----------------------------------------------------------------///  
  ///  Packet command
  ///----------------------------------------------------------------///  
  JBOOL   bGattCmdStatus;
  JINT    iGattCmdTimeoutMS;
  long    iGattCmdMS0;
  long    iGattCmdMS1;

  long    iGattStateMS0;
  long    iGattStateMS1;

  ///----------------------------------------------------------------///  
  ///  Thread leave
  ///----------------------------------------------------------------///  
  JBOOL bLeave;

} JGattCtlType;


extern EpollEventType EpollEvent;
extern JGattCtlType * JGattCtlPtr;
extern JBOOL  bDebugPrint;

extern JBOOL  EpollEventPrint(void);
extern JBOOL  EpollCreate(void);
extern JBOOL  EpollDelete(JINT fd);
extern JBOOL  EpollAdd(JINT fd, JDWORD dwEvent, EpollEventType *pEpollEventNew);
extern JBOOL  EpollWait(JINT iMS);
extern JBOOL  EpollFinal(void);
extern JBOOL  EpollInit(void);

extern void   HciParamSet(JINT id, char * strParam, char *strValue);
extern JBOOL  HciDeviceReset(void);
extern JBOOL  HciDeviceOpen(void);
extern JBOOL  HciDeviceClose(void);

extern JBOOL  HciScanStart(void);
extern JBOOL  HciScanStop(void);

extern JBOOL  JAttReadByGroupReq(JINT fd, JWORD wStart, JWORD wEnd);
extern JBOOL  JAttReadByTypeReq(JINT fd, JWORD wStart, JWORD wEnd);
extern JBOOL  JAttWriteReq(JINT fd, JWORD wHandle, JBYTE *pbWriteData, JINT iWriteLen);
extern JBOOL  JAttReadData(JINT fd);
extern JBOOL  JAttWriteData(JINT fd, JBYTE *pbWriteBuf, JINT iWriteBufLen);
extern JBOOL  JAttDisconnectHandler(JINT fd);

extern JBOOL  JGattScanResult(void);

extern JBOOL  JGattServicePrint(JINT id, JGattServiceType *pGattService);
extern JBOOL  JGattServicesPrint(void);
extern JBOOL  JGattServiceAdd(JWORD wStart, JWORD wEnd, JBYTE *pbUuid, JBYTE bUuidLen);
extern JBOOL  JGattServiceFind(JINT fd);
extern JBOOL  JGattServiceInit(void);

extern JBOOL  JGattCharacteristicPrint(void);
extern JBOOL  JGattCharacteristicPrint(JINT id, JGattCharacteristicType *pGattCharacteristic);
extern JBOOL  JGattCharacteristicAdd(JWORD wStart, JWORD wEnd, JBYTE *pbUuid, JBYTE bUuidLen, JBYTE bProperty);
extern JBOOL  JGattCharacteristicFind(JINT fd);
extern JBOOL  JGattCharacteristicInit(void);
/// notify
extern JBOOL  JGattNotifyRegister(JINT fd);

extern JBOOL  JGattAddrSet(JBYTE * pbMacAddr);
extern JBOOL  JGattClose(void);
extern JBOOL  JGattOpen(void);

extern void   JGattInit(void);

extern JBOOL  JGattControl(void);

#endif ///< for  FEATURE_JGATT
#endif ///< __JGATT_H__
