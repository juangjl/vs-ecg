/**
 * @file JGatt.cpp
 *
 *  JGATT
 *
 * @version $Revision$
 * @author JL Juang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021,  VitalSigns Technology Co., LTD., all rights reserved.
 * @note
*/
#include "Global.h"

#ifdef FEATURE_JGATT

JGattServiceType        JGattService[JGATT_SERVICE_MAX_COUNT];
JGattCharacteristicType JGattCharacteristic[JGATT_CHARACTERISTIC_MAX_COUNT];

EpollEventType EpollEvent;

JGattCtlType    JGattCtl;
JGattCtlType *  JGattCtlPtr = &JGattCtl;

JBOOL bDebugPrint = FALSE;

///------------------------------------------------------------------------///
///
/// EPOLL
///
///------------------------------------------------------------------------///
JINT EpollFd = EPOLL_FP_INIT;

#define EPOLL_EVENT_LEN     (30)

EpollEventType EpollEvents[EPOLL_EVENT_LEN];

JBOOL EpollInit(void)
{
  EpollEventType *pEpollEvent = NULL;
  JINT i = 0;

  for(i = 0; i < EPOLL_EVENT_LEN; i = i + 1)
  {    
    pEpollEvent = &EpollEvents[EPOLL_EVENT_LEN];
    UtilMemset((JBYTE *)pEpollEvent, 0x00, sizeof(EpollEventType));
    pEpollEvent->iValid = FALSE;
  }

  EpollCreate();
  //EpollEventPrint();  

  return TRUE;
}

JBOOL EpollModify(JINT fd, JDWORD dwEvent)
{
  return TRUE;
}

JBOOL EpollAdd(JINT fd, JDWORD dwEvent, EpollEventType *pEpollEventNew)
{
  char msg[256];
	struct epoll_event ev;
	JINT iErrNo = 0;

  EpollEventType *pEpollEvent = NULL;

  ///----------------------------------------------------------------------------------------------------------///
  /// EPOLLIN    - The associated file is available for read(2) operations.
  /// EPOLLOUT   - The associated file is available for write(2) operations.
  /// EPOLLRDHUP - Stream socket peer closed connection, or shut down writing half of connection.
  /// EPOLLPRI   - There is an exceptional condition on the file descriptor.
  /// EPOLLERR   - Error condition happened on the associated file descriptor.
  /// EPOLLHUP   - Hang up happened on the associated file descriptor.
  /// EPOLLET    - Requests edge-triggered notification for the associated file descriptor.  
  /// EPOLLONESHOT (since Linux 2.6.2)  - Requests one-shot notification for the associated file descriptor.    
  /// EPOLLWAKEUP (since Linux 3.5)  - ...     
  /// EPOLLEXCLUSIVE (since Linux 4.5) - ...
  ///----------------------------------------------------------------------------------------------------------///
  
  ///------------------------------------------------------///
  /// Check the epoll  
  ///------------------------------------------------------///
	if(fd < 0)
	{	
    sprintf(msg, "\t [EPOLL][ERROR] fd < 0 \r\n");
    DBG_PRINTF(msg);
		return FALSE;
	}

  if(fd > EPOLL_EVENT_LEN)
  {
    sprintf(msg, "\t [EPOLL][ERROR] fd > %d \r\n", EPOLL_EVENT_LEN);
    DBG_PRINTF(msg);
    return FALSE;
  }

  ///------------------------------------------------------///  
  /// set fd
  ///------------------------------------------------------///
	pEpollEventNew->fd      = fd;
  pEpollEventNew->iValid  = TRUE;
  pEpollEventNew->dwEvent = dwEvent;
  
  ///------------------------------------------------------///
  /// update the Epoll event table  
  ///------------------------------------------------------///
	pEpollEvent = &EpollEvents[fd];
  UtilMemcpy((JBYTE *)pEpollEvent, (JBYTE *)pEpollEventNew, sizeof(EpollEventType));
	
  ///------------------------------------------------------///  
  /// set events  
  ///------------------------------------------------------///
  UtilMemset((JBYTE *)&ev, 0x00, sizeof(ev));
  ev.events   = dwEvent;
	ev.data.ptr = pEpollEvent;

	iErrNo = epoll_ctl(EpollFd, EPOLL_CTL_ADD, fd, &ev);
	if(iErrNo < 0)
	{				
		perror("epoll add failed");
    return FALSE;
	}

  sprintf(msg, "[EPOLL][ADD] epoll_fd= %d, event = %04x\r\n", EpollFd, dwEvent);
  DBG_PRINTF(msg);

	return TRUE;
}

JBOOL EpollDelete(JINT fd)
{
  char msg[256];
  EpollEventType *pEpollEvent = NULL;

  if(fd < 0)
	{	
    sprintf(msg, "\t [EPOLL][ERROR] fd < 0 \r\n");
    DBG_PRINTF(msg);
		return FALSE;
	}

  if(fd > EPOLL_EVENT_LEN)
  {
    sprintf(msg, "\t [EPOLL][ERROR] fd > %d \r\n", EPOLL_EVENT_LEN);
    DBG_PRINTF(msg);
    return FALSE;
  }
  epoll_ctl(EpollFd, EPOLL_CTL_DEL, fd, NULL);  

  ///------------------------------------------------------///
  /// clear the Epoll event table  
  ///------------------------------------------------------///
	pEpollEvent = &EpollEvents[fd];
  UtilMemset((JBYTE *)pEpollEvent, 0x00, sizeof(EpollEventType));

  return TRUE;
}


JBOOL EpollCreate(void)
{  
	EpollFd = epoll_create1(EPOLL_CLOEXEC);
  if(EpollFd <= 0)
  {
    return FALSE;
  }
  return TRUE;
}

JBOOL EpollFinal(void)
{
  EpollEventType *pEpollEvent = NULL;
  JINT i = 0;

  for(i = 0; i < EPOLL_EVENT_LEN; i = i + 1)
  {
    pEpollEvent = &EpollEvents[EPOLL_EVENT_LEN];
    if(pEpollEvent->fd > 0)
    {
      epoll_ctl(EpollFd, EPOLL_CTL_DEL, pEpollEvent->fd, NULL);
    }
  }
  close(EpollFd);
  EpollFd = EPOLL_FP_INIT;
  return TRUE;
}

JBOOL EpollEventPrint(void)
{
  printf("EPOLLIN (%04x)\r\n",        EPOLLIN);
  printf("EPOLLOUT(%04x)\r\n",        EPOLLOUT);
  printf("EPOLLRDHUP(%04x)\r\n",      EPOLLRDHUP);
  printf("EPOLLPRI(%04x)\r\n",        EPOLLPRI);
  printf("EPOLLERR(%04x)\r\n",        EPOLLERR);
  printf("EPOLLHUP(%04x)\r\n",        EPOLLHUP);
  printf("EPOLLET(%04x)\r\n",         EPOLLET);
  printf("EPOLLONESHOT(%04x)\r\n",    EPOLLONESHOT);
  printf("EPOLLEXCLUSIVE(%04x)\r\n",  EPOLLEXCLUSIVE);
  printf("EPOLLEXCLUSIVE(%04x)\r\n",  EPOLLEXCLUSIVE);  

  return TRUE;
}

JBOOL EpollWait(JINT iMS)
{
  JINT i = 0;
  char msg[256];

  JINT iFdNum = 0;

  EpollEventType *pEpollEvent = NULL;
  struct epoll_event events[EPOLL_EVENT_LEN];

  JINT    iReadLen = 0;
  JBYTE   bData[1024];
  JDWORD  dwEvent = 0;

  
  iFdNum = epoll_wait(EpollFd, events, EPOLL_EVENT_LEN, iMS);
  if(iFdNum > 0)
  {				
    for(i = 0; i < iFdNum; i = i + 1)
    {
      pEpollEvent = (EpollEventType *)events[i].data.ptr;

      dwEvent = events[i].events;
      if(bDebugPrint == TRUE)
      {
        sprintf(msg, "\t [EVENT][IN] fd = %d, %04x\r\n", pEpollEvent->fd, dwEvent);
        DBG_PRINTF(msg);   
      }

      if(dwEvent & EPOLLIN)
      {	        
        JAttReadData(pEpollEvent->fd);
      }
      if(dwEvent & EPOLLOUT)
      {	
        
      }
      if(dwEvent & EPOLLRDHUP)
      {	
        DBG_PRINTF("Device hang up (EPOLLRDHUP) \r\n");
        JAttDisconnectHandler(pEpollEvent->fd);
        //EpollDelete(pEpollEvent->fd);         
        return FALSE;
      }
      if(dwEvent & EPOLLPRI)
      {	
        
      }
      if(dwEvent & EPOLLHUP)
      {	
        DBG_PRINTF("Device hang up (EPOLLHUP)\r\n");
        JAttDisconnectHandler(pEpollEvent->fd);
        //EpollDelete(pEpollEvent->fd);
        return FALSE;
      }
      if(dwEvent & EPOLLET)
      {	
        
      }
      if(dwEvent & EPOLLONESHOT)
      {	
        
      }
      if(dwEvent & EPOLLWAKEUP)
      {	
        
      }
      if(dwEvent & EPOLLWAKEUP)
      {	
        
      }
    }
  }  
  else
  {
    return TRUE;
  }

  return TRUE;
}

///------------------------------------------------------------------------///
///
/// HCI
///
/// /sys/kernel/debug/bluetooth/hci0
/// /sys/kernel/debug/bluetooth/hci1
///------------------------------------------------------------------------///
void HciUp(int id)
{
  char cmd[256];
  sprintf(cmd, "hciconfig hci%d up", id);
	system(cmd);
}

void HciDown(int id)
{
  char cmd[256];
  sprintf(cmd, "hciconfig hci%d down", id);
	system(cmd);
}

void HciParamSet(JINT id, char * strParam, char *strValue)
{
  char cmd[256];
  ///----------------------------------------------------------------///
  ///  echo  %d > /sys/kernel/debug/bluetooth/hci%d/supervision_timeout
  ///----------------------------------------------------------------///                          
  sprintf(cmd, "echo %s > /sys/kernel/debug/bluetooth/hci%d/%s", strValue, id, strParam);
	system(cmd);
}

void HciReset(int id)
{
  HciDown(id);  
  HciUp(id);
}

JBOOL HciDeviceReset(void)
{  
  JGattCtlType *pJGattCtl = JGattCtlPtr;

  if(pJGattCtl->iDD > 0)
  {
    hci_close_dev(pJGattCtl->iDD);
  }

  pJGattCtl->iHciDevId = hci_get_route(NULL);

  if(pJGattCtl->iHciDevId != JGATT_HCI_DEV_ID_INVALID)
  {
    HciReset(pJGattCtl->iHciDevId);
  }
  pJGattCtl->iHciDevId = JGATT_HCI_DEV_ID_INVALID;
  pJGattCtl->iDD       = JGATT_SOCKET_INVALID;
  return TRUE;  
}

JBOOL HciDeviceOpen(void)
{  
  char    msg[256];
  JINT    iHciDevId = 0;
  JINT    iRet   = 0;
  struct  hci_dev_info hciDevInfo;

  JGattCtlType *pJGattCtl = JGattCtlPtr;

  pJGattCtl->iHciDevId = JGATT_HCI_DEV_ID_INVALID;  
  pJGattCtl->iDD       = JGATT_SOCKET_INVALID;

  //HciDeviceReset();
  //UtilMsSleep(1000);

  ///--------------------------------------------------------------------------------///
  /// 1. HCI  route get
  ///--------------------------------------------------------------------------------///
  iHciDevId = hci_get_route(NULL);
  if(iHciDevId < 0) 
  {
    sprintf(msg, "%s", "[JGATT] HCI ROUTE Failed\r\n");
    DBG_PRINTF(msg);
    pJGattCtl->iDD = JGATT_SOCKET_INVALID;
    return FALSE;
  }

  ///--------------------------------------------------------------------------------///
  /// 2. HCI information get
  ///--------------------------------------------------------------------------------///  
  iRet = hci_devinfo(iHciDevId, &hciDevInfo);
  if(iRet < 0)
  {
    sprintf(msg, "%s", "[JGATT] HCI INFO READ Failed\r\n");
    DBG_PRINTF(msg);    
    return FALSE;
  }

  pJGattCtl->iHciDevId  = iHciDevId;

  /// Copy MacAddr
  UtilMemcpy((JBYTE *)&pJGattCtl->bHciDevMacAddr[0], (JBYTE *)&hciDevInfo.bdaddr.b[0], BLE_MAC_ADDR_SIZE);
  
  UtilMemset((JBYTE *)&pJGattCtl->strBusName[0],        0x00, ADAPTER_INFO_SIZE);
  UtilMemset((JBYTE *)&pJGattCtl->strInterfaceName[0],  0x00, ADAPTER_INFO_SIZE);
  UtilMemset((JBYTE *)&pJGattCtl->strAdPathName[0],     0x00, ADAPTER_INFO_SIZE);

  sprintf(pJGattCtl->strBusName,       "%s",   "org.bluez");
  sprintf(pJGattCtl->strInterfaceName, "%s",   "org.bluez.Adapter1");
  sprintf(pJGattCtl->strAdPathName,    "%s%s", "/org/bluez/", hciDevInfo.name);
    
  ///--------------------------------------------------------------------------------///
  /// 3. HCI device open
  ///--------------------------------------------------------------------------------///  
  pJGattCtl->iDD = hci_open_dev(pJGattCtl->iHciDevId);
	if(pJGattCtl->iDD < 0)
  {
	  sprintf(msg, "[JGATT] device '%s' open failed \r\n", pJGattCtl->strAdPathName);
    DBG_PRINTF(msg);  
    pJGattCtl->iDD  = JGATT_SOCKET_INVALID;
    return FALSE;  
	}

  sprintf(msg, "[JGATT][HCI] device '%s' open OK (%d)\r\n", pJGattCtl->strAdPathName, pJGattCtl->iDD);
  DBG_PRINTF(msg);    

  sprintf(msg, "[JGATT][HCI] device MAC = %02X:%02X:%02X:%02X:%02X:%02X\r\n", 
            pJGattCtl->bHciDevMacAddr[5], pJGattCtl->bHciDevMacAddr[4], pJGattCtl->bHciDevMacAddr[3], 
            pJGattCtl->bHciDevMacAddr[2], pJGattCtl->bHciDevMacAddr[1], pJGattCtl->bHciDevMacAddr[0]);
  DBG_PRINTF(msg);    

  return TRUE;
}

JBOOL HciDeviceClose(void)
{ 
  JGattCtlType * pJGattCtl = JGattCtlPtr;
   
  if(pJGattCtl->iDD != JGATT_SOCKET_INVALID)
  {
    close(pJGattCtl->iDD);
  }
  
  pJGattCtl->iHciDevId = JGATT_HCI_DEV_ID_INVALID;  
  pJGattCtl->iDD         = JGATT_SOCKET_INVALID;
  pJGattCtl->iScanStatus = JGATT_SCAN_STATUS_OFF;
  
  return TRUE;
}

/*
int hci_le_set_scan_parameters(int dd, uint8_t type,
      uint16_t interval, uint16_t window,
      uint8_t own_type, uint8_t filter, int to)
{
  struct hci_request rq;
  le_set_scan_parameters_cp param_cp;
  uint8_t status;

  memset(&param_cp, 0, sizeof(param_cp));
  param_cp.type = type;
  param_cp.interval = interval;
  param_cp.window = window;
  param_cp.own_bdaddr_type = own_type;
  param_cp.filter = filter;

  memset(&rq, 0, sizeof(rq));
  rq.ogf = OGF_LE_CTL;
  rq.ocf = OCF_LE_SET_SCAN_PARAMETERS;
  rq.cparam = &param_cp;
  rq.clen = LE_SET_SCAN_PARAMETERS_CP_SIZE;
  rq.rparam = &status;
  rq.rlen = 1;

  if (hci_send_req(dd, &rq, to) < 0)
  return -1;

  if (status) {
    errno = EIO;
    return -1;
  }

  return 0;
}

int hci_le_set_scan_enable(int dd, uint8_t enable, uint8_t filter_dup, int to)
{
	struct hci_request rq;
	le_set_scan_enable_cp scan_cp;
	uint8_t status;

	memset(&scan_cp, 0, sizeof(scan_cp));
	scan_cp.enable = enable;
	scan_cp.filter_dup = filter_dup;

	memset(&rq, 0, sizeof(rq));
	rq.ogf = OGF_LE_CTL;
	rq.ocf = OCF_LE_SET_SCAN_ENABLE;
	rq.cparam = &scan_cp;
	rq.clen = LE_SET_SCAN_ENABLE_CP_SIZE;
	rq.rparam = &status;
	rq.rlen = 1;

	if (hci_send_req(dd, &rq, to) < 0)
		return -1;

	if (status) {
		errno = EIO;
		return -1;
	}

	return 0;
}
*/

JBOOL HciScanStart(void)
{
  char msg[256];

  JINT iErr = 0;

  JBYTE bOwnType      = LE_PUBLIC_ADDRESS;
	JBYTE bScanType     = 0x01;           ///< possive mode :0x00
	JBYTE bFilterType   = 0x00;
	JBYTE bFiltePolicy  = 0x00;
	JWORD wInterval     = htobs(0x0010);
	JWORD wWindow       = htobs(0x0010);
	JBYTE bFilterDup    = 0x00;
  JINT  iTimeout      = 1000;

  JGattCtlType *pJGattCtl = JGattCtlPtr;

  pJGattCtl->iScanStatus =  JGATT_SCAN_STATUS_OFF;

  if(pJGattCtl->iDD == JGATT_SOCKET_INVALID)
  {
    return FALSE;
  }
  
	iErr = hci_le_set_scan_parameters(pJGattCtl->iDD, bScanType, wInterval, wWindow,	bOwnType, bFiltePolicy, iTimeout);
	if(iErr < 0)
  {
    perror("set scan parameters error\r\n");
	  sprintf(msg, "[JGATT][HCI] scan parameter set failed (%d) \r\n", iErr);
    DBG_PRINTF(msg);
    return FALSE;
	}

	iErr = hci_le_set_scan_enable(pJGattCtl->iDD, 0x01, bFilterDup, iTimeout);
	if(iErr < 0)
  {
    sprintf(msg, "[JGATT][HCI] scan start failed DEV_ID = %d, (%d) \r\n", pJGattCtl->iHciDevId,  iErr);
    DBG_PRINTF(msg);
    return FALSE;
	}

  sprintf(msg, "%s", "[JGATT][HCI] scan start OK\r\n");
  DBG_PRINTF(msg);
  return TRUE;
}

JBOOL HciScanStop(void)
{
  char  msg[256];

  JINT  iErr       = 0;
	JBYTE bFilterDup = 0x00;
  JINT  iTimeout    = 2000;
  JINT  iRetry    = 0;

  JGattCtlType *pJGattCtl = JGattCtlPtr;

  if(pJGattCtl->iDD == JGATT_SOCKET_INVALID)
  {
    return FALSE;
  }
  while(1)
  {
    iErr = hci_le_set_scan_enable(pJGattCtl->iDD, FALSE , bFilterDup, iTimeout);
    if(iErr < 0)
    {      
      iRetry = iRetry + 1;
      if(iRetry > 20)
      {
        sprintf(msg, "[JGATT][HCI] scan stop no = (%d), retry = %d \r\n", iErr, iRetry);
        DBG_PRINTF(msg);
        return FALSE;
      }
      UtilMsSleep(100);
      continue;
    }
    else
    {
      break;
    }    
  }
  
  sprintf(msg, "%s", "[JGATT][HCI] scan stop OK\r\n");
  DBG_PRINTF(msg);

  return TRUE;
}

JBOOL JAttReadByTypeReq(JINT fd, JWORD wStart, JWORD wEnd)
{
  JGattCtlType  * pJGattCtl = JGattCtlPtr;
  JBYTE bWriteBuf[7];
  JBYTE bWriteBufLen = 7;
  JWORD wType = JATT_TYPE_UUID_CHARACTERISTIC;    

  bWriteBuf[0] = BT_ATT_OP_READ_BY_TYPE_REQ;
  bWriteBuf[1] = wStart & 0x00FF;
  bWriteBuf[2] = (wStart >> 8) & 0x00FF;
  bWriteBuf[3] = wEnd & 0x00FF;
  bWriteBuf[4] = (wEnd >> 8) & 0x00FF;
  bWriteBuf[5] = wType & 0x00FF;
  bWriteBuf[6] = (wType >> 8) & 0x00FF;  
  pJGattCtl->bCharacteristicFind = JGATT_CHARACTERISTIC_FINDING;
  JAttWriteData(fd, bWriteBuf, bWriteBufLen);

  return TRUE; 
}

JBOOL JAttReadByGroupReq(JINT fd, JWORD wStart, JWORD wEnd)
{
  JGattCtlType  * pJGattCtl = JGattCtlPtr;
  JBYTE bWriteBuf[7];
  JBYTE bWriteBufLen = 7;
  JWORD wType  = JATT_TYPE_UUID_PRIMARY_SERVICE;    

  bWriteBuf[0] = BT_ATT_OP_READ_BY_GRP_TYPE_REQ;
  bWriteBuf[1] = wStart & 0x00FF;
  bWriteBuf[2] = (wStart >> 8) & 0x00FF;
  bWriteBuf[3] = wEnd & 0x00FF;
  bWriteBuf[4] = (wEnd >> 8) & 0x00FF;
  bWriteBuf[5] = wType & 0x00FF;
  bWriteBuf[6] = (wType >> 8) & 0x00FF;  
  pJGattCtl->bServiceFind = JGATT_SERVICE_FINDING;
  JAttWriteData(fd, bWriteBuf, bWriteBufLen);

  return TRUE; 
}

JBOOL JAttWriteReq(JINT fd, JWORD wHandle, JBYTE *pbWriteData, JINT iWriteLen)
{
  JGattCtlType  * pJGattCtl = JGattCtlPtr;
  JBYTE bWriteBuf[512];
  JBYTE bWriteBufLen = iWriteLen + 3;
  
  if(bDebugPrint == TRUE)
  {
    DBG_PRINTF("\t [JATT] WRITE_REQ\r\n");
  }
  
  bWriteBuf[0] = BT_ATT_OP_WRITE_REQ;  
  bWriteBuf[1] = (JBYTE)(wHandle & 0x00FF);  
  bWriteBuf[2] = (JBYTE)((wHandle >> 8) & 0x00FF);   
  UtilMemcpy((JBYTE *)&bWriteBuf[3], (JBYTE *)&pbWriteData[0], iWriteLen);

  JAttWriteData(fd, bWriteBuf, bWriteBufLen);
  pJGattCtl->bWriteReq = TRUE;
  return TRUE; 
}

JBOOL JAttErrRsp(JINT fd, JBYTE *pbReadBuf, JINT iReadLen)
{
  JGattCtlType  * pJGattCtl = JGattCtlPtr;
  JBYTE bAttErrOpCode = 0x00;
  
  if(bDebugPrint == TRUE)
  {
    DBG_PRINTF("[JATT] ERR_RSP\r\n");
  }

  bAttErrOpCode  = pbReadBuf[1];
  if(bAttErrOpCode == BT_ATT_OP_READ_BY_TYPE_REQ)
  {            
    if(pJGattCtl->iCharacteristicCnt == 0)
    {
      pJGattCtl->bCharacteristicFind = JGATT_CHARACTERISTIC_FIND;
    }
    else
    {        
      pJGattCtl->bCharacteristicFind = JGATT_CHARACTERISTIC_FIND_OK;
      JGattCharacteristicPrint();    
    }
  }
  if(bAttErrOpCode == BT_ATT_OP_READ_BY_GRP_TYPE_REQ)
  {
    JGattServiceInit();
    JGattCharacteristicInit();
    pJGattCtl->bServiceFind = JGATT_SERVICE_FIND;  
  }
  return TRUE;    
}

JBOOL JAttMtuRsp(JINT fd, JBYTE *pbReadBuf, JINT iReadLen)
{
  JWORD wMTU = 0;
  JBOOL bRet = FALSE;
  JINT  iWriteBufLen = 0;
  JBYTE bWriteBuf[1024];

  JGattCtlType  * pJGattCtl = JGattCtlPtr;

  wMTU = pbReadBuf[1] + pbReadBuf[2] * 256;
  bWriteBuf[0] = BT_ATT_OP_MTU_RSP;
  bWriteBuf[1] = wMTU &0xFF;
  bWriteBuf[2] = (wMTU >> 8);
  iWriteBufLen = 3;
  bRet = JAttWriteData(fd, bWriteBuf, iWriteBufLen);
  pJGattCtl->bServiceFind = JGATT_SERVICE_FIND;
  return TRUE;
}

JBOOL JAttReadByTypeRsp(JINT fd, JBYTE *pbReadBuf, JINT iReadLen)
{
  JGattCtlType  * pJGattCtl = JGattCtlPtr;
  char    msg[256];
  JINT    iDataLen = pbReadBuf[1];
  JWORD   wStart = 0;
  JWORD   wEnd   = 0;
  JBYTE   bProperty = 0;  
  JBYTE   bUuid[16];
  JBYTE   bUuidLen = 0;
  JINT    i = 0;

  if(bDebugPrint == TRUE)
  {
    DBG_PRINTF("[JATT] READ_BY_TYPE_RSP\r\n");
  }

  for(i = 2 ; i < iReadLen; i = i + iDataLen)
  {
    if(iDataLen == 0x07)
    {
      bUuidLen = 2;
      wStart    = pbReadBuf[i] + pbReadBuf[i + 1]  * 256;
      bProperty = pbReadBuf[i + 2];
      wEnd      = pbReadBuf[i + 3] + pbReadBuf[i + 4]  * 256;
      UtilMemcpy(&bUuid[0], &pbReadBuf[i + 5], bUuidLen);
      JGattCharacteristicAdd(wStart, wEnd, bUuid, bUuidLen, bProperty);      
    }
    else if(iDataLen == 0x15)
    {
      bUuidLen  = 16;
      wStart    = pbReadBuf[i] + pbReadBuf[i + 1]  * 256;
      bProperty = pbReadBuf[i + 2];
      wEnd      = pbReadBuf[i + 3] + pbReadBuf[i + 4]  * 256;
      UtilMemcpy(&bUuid[0], &pbReadBuf[i + 5], bUuidLen);
      JGattCharacteristicAdd(wStart, wEnd, bUuid, bUuidLen, bProperty);      
    }
    else
    {
      sprintf(msg, "[JATT][READ_BYTE_TYPE] unknown format\r\n");
      DBG_PRINTF(msg);
    }    
  }

  pJGattCtl->wCharacteristicEnd      = wEnd;
  if(pJGattCtl->wCharacteristicEnd != 0xFFFF)
  {
    pJGattCtl->bCharacteristicFind = JGATT_CHARACTERISTIC_FIND;
  }
  else
  {
    JGattCharacteristicPrint();    
  }
  return TRUE;
}

JBOOL JAttReadByGroupRsp(JINT fd, JBYTE *pbReadBuf, JINT iReadLen)
{
  JGattCtlType  * pJGattCtl = JGattCtlPtr;
  JINT    iDataLen = pbReadBuf[1];
  JWORD   wStart = 0;
  JWORD   wEnd   = 0;
  JBYTE   bUuid[16];
  JBYTE   bUuidLen = iDataLen - 4;
  JINT i = 0;
  if(bDebugPrint == TRUE)
  {
    DBG_PRINTF("[JATT] READ_BY_GRP_RSP\r\n");
  }

  for(i = 2 ; i < iReadLen; i = i + iDataLen)
  {
    wStart = pbReadBuf[i] + pbReadBuf[i + 1]  * 256;
    wEnd = pbReadBuf[i + 2] + pbReadBuf[i + 3]  * 256;
    UtilMemcpy(&bUuid[0], &pbReadBuf[i + 4], bUuidLen);
    JGattServiceAdd(wStart, wEnd, bUuid, bUuidLen);
  }

  pJGattCtl->wServiceEnd = wEnd;
  if(pJGattCtl->wServiceEnd != 0xFFFF)
  {
    pJGattCtl->bServiceFind = JGATT_SERVICE_FIND;
  }
  else
  {
    JGattServicesPrint();    
    pJGattCtl->bServiceFind = JGATT_CHARACTERISTIC_FIND_OK;
    pJGattCtl->bCharacteristicFind = JGATT_CHARACTERISTIC_FIND;
  }
  return TRUE;
}

JBOOL JAttWriteRsp(JINT fd, JBYTE *pbReadBuf, JINT iReadLen)
{
  if(bDebugPrint == TRUE)
  {
    DBG_PRINTF("\t [JATT] WRITE_RSP\r\n");
  }
  JGattCtlType  * pJGattCtl = JGattCtlPtr;
  pJGattCtl->bWriteReq = FALSE;
  pJGattCtl->bWriteRsp = TRUE; 
  
  if(pJGattCtl->bNotifyRegister == JGATT_NOTIFY_REGISTER_ON)
  {
    pJGattCtl->bNotifyRegister = JGATT_NOTIFY_REGISTER_OK;
  }

  return TRUE;
}

JBOOL JAttNotifyRsp(JINT fd, JBYTE *pbReadBuf, JINT iReadLen)
{
  char msg[256];
  JGattCtlType  * pJGattCtl = JGattCtlPtr;
  PacketAckType *pPacketAck = NULL;
  JWORD wHandle     = 0;
  JINT iReadBufLen  = iReadLen - 3;
  if(bDebugPrint == TRUE)
  {
    DBG_PRINTF("\t [JATT] NOTIFY_RSP\r\n");
  }

  wHandle = pbReadBuf[1] + (pbReadBuf[2] << 8);
  if(wHandle != pJGattCtl->wHandleRx)
  {
    sprintf(msg, "\t [JATT] NOTIFY_RSP - unknown notify %04x\r\n", wHandle);
    DBG_PRINTF(msg);
    return FALSE;
  }

  if(iReadBufLen < 0)
  {
    DBG_PRINTF("\t [JATT] NOTIFY_RSP - length < 0\r\n");
    return FALSE;
  }

  if(iReadLen == 0)
  {    
    pJGattCtl->iGattStatusRx = GATT_STATUS_RX_OK;
    return TRUE;
  }

  if((iReadLen + pJGattCtl->iGattRxBufIdx) < JGATT_RX_BUF_MAX_SIZE)
  {
    UtilMemcpy((JBYTE *)&pJGattCtl->bGattRxBuf[pJGattCtl->iGattRxBufIdx], (JBYTE *)&pbReadBuf[3], iReadBufLen);
    pJGattCtl->iGattRxBufIdx = pJGattCtl->iGattRxBufIdx + iReadBufLen;
  }  

  if(pJGattCtl->iGattRxBufIdx == pJGattCtl->iGattRxBufLen)
  {
    pJGattCtl->iGattStatusRx  = GATT_STATUS_RX_OK;
    pJGattCtl->bGattCmdStatus = JGATT_CMD_STATUS_DATA_OK;
    pJGattCtl->iGattRxBufIdx  = 0;
  }
  else if(pJGattCtl->iGattRxBufIdx > pJGattCtl->iGattRxBufLen)
  {
    pJGattCtl->iGattStatusRx = GATT_STATUS_RX_OVERFLOW;
    pJGattCtl->iGattRxBufIdx = 0;
  }
  else if(pJGattCtl->iGattRxBufIdx > 0)
  {
    pJGattCtl->iGattStatusRx = GATT_STATUS_RX_READING;
  }
  ///--------------------------------------------------------------------///
  /// Packet command check
  ///--------------------------------------------------------------------///
  if(pJGattCtl->iGattRxBufIdx >= 8)
  {
    pPacketAck = (PacketAckType *)&pJGattCtl->bGattRxBuf[0];
    if((pPacketAck->bAck == 'A') && ((pPacketAck->wDataLen + PACKET_ACK_HEADER_SIZE) == pJGattCtl->iGattRxBufIdx))
    {
      pJGattCtl->iGattStatusRx  = GATT_STATUS_RX_OK;
      pJGattCtl->bGattCmdStatus = JGATT_CMD_STATUS_DATA_OK;
      pJGattCtl->iGattRxBufLen  = pPacketAck->wDataLen + PACKET_ACK_HEADER_SIZE;
      pJGattCtl->iGattRxBufIdx  = 0;
    }
  }

  return TRUE;
}

JBOOL JAttReadDataParse(JINT fd, JBYTE *pbReadBuf, JINT iReadLen)
{
  char msg[256];
  JBYTE bAttCode    = pbReadBuf[0];    
  
  if(bAttCode == BT_ATT_OP_ERROR_RSP)
  {
    JAttErrRsp(fd, pbReadBuf, iReadLen);
  }
  else if(bAttCode == BT_ATT_OP_MTU_REQ)
  {
    JAttMtuRsp(fd, pbReadBuf, iReadLen);
  }
  else if(bAttCode == BT_ATT_OP_READ_BY_TYPE_RSP)
  {
    JAttReadByTypeRsp(fd, pbReadBuf, iReadLen);
  }
  else if(bAttCode == BT_ATT_OP_READ_BY_GRP_TYPE_RSP)
  {
    JAttReadByGroupRsp(fd, pbReadBuf, iReadLen);
  }
  else if(bAttCode == BT_ATT_OP_WRITE_RSP)
  {
    JAttWriteRsp(fd, pbReadBuf, iReadLen);
  }
  else if(bAttCode == BT_ATT_OP_HANDLE_VAL_NOT)
  {
    JAttNotifyRsp(fd, pbReadBuf, iReadLen);
  }  
  else 
  {
    sprintf(msg,  "[JATT][DATA][ERROR] att_code = %02x!!!!!\r\n", bAttCode);
    DBG_PRINTF(msg);
  }

  return TRUE;
}

JBOOL JAttDisconnectHandler(JINT fd)
{
  char msg[256];
  JINT err = 0;
	socklen_t len;

	len = sizeof(err);

	if(getsockopt(fd, SOL_SOCKET, SO_ERROR, &err, &len) < 0)
	{
    sprintf(msg, "%s", "Failed to get the error\r\n");
    DBG_PRINTF(msg);
		err = 0;
    return FALSE;
	}

  sprintf(msg, "Physical link disconnected: %s \r\n",	strerror(err));
  DBG_PRINTF(msg);

  JGattStateSet(JGATT_STATE_CLOSE);

  return TRUE;
}

JBOOL JAttReadData(JINT fd)
{
  JGattCtlType *pJGattCtl = JGattCtlPtr;
  JINT  iReadLen = 0;  
  JBYTE bData[4096];
  JBYTE *pbReadBuf  = &bData[0];
  JINT  iReadBufLen = pJGattCtl->iMtu;
  if(bDebugPrint == TRUE)
  {
    DBG_PRINTF("\t [JATT][IO][READ]\r\n");
  }
  iReadLen = read(fd, pbReadBuf, iReadBufLen);

  if(iReadLen < 0)
  {
    return FALSE;
  }
  
  if(bDebugPrint == TRUE)
  {
    UtilDataPrint(pbReadBuf, iReadLen);
  }
    
  JAttReadDataParse(fd, pbReadBuf, iReadLen);

  return TRUE;
}

JBOOL JAttWriteData(JINT fd, JBYTE *pbWriteBuf, JINT iWriteBufLen)
{
  JINT iWriteLen = 0;
  char msg[256];
  if(bDebugPrint == TRUE)
  {
    DBG_PRINTF("\t [JATT][IO][WRITE]\r\n");
    UtilDataPrint(pbWriteBuf, iWriteBufLen);
  }
  
  iWriteLen = write(fd, pbWriteBuf, iWriteBufLen);
  if(iWriteLen != iWriteBufLen)
  {
    sprintf(msg, "[JATT][ERROR] Write failed (%d, %d)\r\n", iWriteLen, iWriteBufLen);
    DBG_PRINTF(msg);
  }
  return TRUE;
}

JBOOL JGattScanAdParse(JBYTE *pData, JINT iLen, char *strDeviceName, JINT bPrint)
{
  char msg[256];
  
  JBYTE bTotalLen = iLen;
  
  JINT i = 0;
  JINT j = 0;

  JINT iIdx = 0;
  JINT iAdvLen = 0;

  JINT  iAdDataLenTotal = 0;
  JBYTE bAdType = 0;
  JWORD wUUID16 = 0;
  JBOOL bFound = FALSE;
  JBYTE  bAdData[256];

  char strName[256];

  JBYTE  bUuid128[16];	

  ///-------------------------------------------------------------------------///
	///  AD DATA Raw data print
	///-------------------------------------------------------------------------///	
	if(bPrint == TRUE)
	{
    UtilDataPrint(pData, iLen);
  }

  ///-------------------------------------------------------------------------///
	///  AD DATA Parse
	///-------------------------------------------------------------------------///	
	msg[0] = 0;
	i = 0;
	while(1)
	{
		if(i>= bTotalLen)
		{
			break;
		}
    /// 1. ADV length
		iAdDataLenTotal  = pData[i];
    i = i + 1;
    /// length 1 is type item
    if(iAdDataLenTotal <= 1)
    {
      continue;
    }

		for(j = 0; j < iAdDataLenTotal; j = j + 1)
		{
		   /// type
      if(j == 0)
      {
        bAdType       = pData[i];
      }
      else
      {
        /// value 
  			bAdData[j-1]  = pData[i];
      }
      i = i + 1;
    }
    /// adv value data len
    iIdx     = iAdDataLenTotal - 1;
    iAdvLen  = iAdDataLenTotal - 1;
    bAdData[iIdx] = 0;    
		
		if(bPrint == TRUE)
		{
			sprintf(msg, "[BLE] AD DATA TYPE = %02X  --> SIZE = %02d\r\n", bAdType, iAdDataLenTotal);
			DBG_PRINTF(msg);
		}

		if(bAdType == AD_TYPE_16BITS_UUID)
		{
			wUUID16 = bAdData[0] + bAdData[1] * 0x100;

			if(bPrint == TRUE)
			{
				msg[0] = 0;
				sprintf((char*)&msg[strlen(msg)], "\t UUID16 = %04x\r\n", wUUID16);
				DBG_PRINTF(msg);
			}
		}	
		if((bAdType == AD_TYPE_NAME) || (bAdType == AD_TYPE_SHORTNAME))
		{     
      bFound = TRUE;

      /// define the ble name size
      UtilMemset((JBYTE *)&strName[0], 0x00, 256);
      
  	  if(iAdvLen >= AD_BLE_NAME_SIZE)
      {
        iAdvLen = AD_BLE_NAME_SIZE;
      } 
      UtilMemcpy((JBYTE *)&strName[0], (JBYTE *)&bAdData[0], iAdvLen);
      strName[iAdvLen] = 0;                 
      UtilMemcpy((JBYTE *)&strDeviceName[0], (JBYTE *)&bAdData[0], iAdvLen);
		}	
		
	  if((bAdType == AD_TYPE_128BITS_UUID) || (bAdType == AD_TYPE_128BITS_UUID_INC))
		{
      /// 128-bits = 16 bytes uuid
      UtilMemcpy((JBYTE *)&bUuid128[0], (JBYTE *)&bAdData[0], 16);
     	if(bPrint == TRUE)
		  {
        sprintf(msg, "\t UUID-128 = %02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X\r\n",
                            bUuid128[15],  bUuid128[14],  bUuid128[13],  bUuid128[12], 
                            bUuid128[11],  bUuid128[10],  bUuid128[9],   bUuid128[8], 
                            bUuid128[7],   bUuid128[6],   bUuid128[5],   bUuid128[4],         
                            bUuid128[3],   bUuid128[2],   bUuid128[1],   bUuid128[0]);
        DBG_PRINTF(msg);
      }
		}	 
    
    if(bAdType == AD_TYPE_MFA_INFO)
    {
    
    }           		
	}
  return TRUE;
}

///-----------------------------------------------------------------------------------------------///
///
///  SERVICE FUNCTION
///
///-----------------------------------------------------------------------------------------------///
JBOOL JGattServicePrint(JINT id, JGattServiceType *pGattService)
{
  JINT i = 0;
  char msg[256];
  JGattCtlType  * pJGattCtl = JGattCtlPtr;  

  sprintf(msg, "\t\t SERV: #%02d -> start : %04X, end: %04X, uuid : ", id, pGattService->wStart, pGattService->wEnd);
  for(i = 0; i < pGattService->bUuidLen; i = i + 1)
  {
    sprintf(msg + strlen(msg), "%02X", pGattService->bUuid[ pGattService->bUuidLen - i - 1]);    
  }

  sprintf(msg + strlen(msg), "%s", "\r\n");    
  DBG_PRINTF(msg);
  return TRUE;
}

JBOOL JGattServicesPrint(void)
{
  JGattCtlType  * pJGattCtl = JGattCtlPtr;  
  JGattServiceType *pGattService = NULL;
  JINT i = 0;
  pJGattCtl->bServiceFind = JGATT_SERVICE_FIND_OK;  
  for(i = 0 ; i < pJGattCtl->iServiceCnt; i = i + 1)
  {
    pGattService =  &JGattService[i];
    JGattServicePrint(i, pGattService);
  }
  return TRUE;
}

JBOOL JGattServiceAdd(JWORD wStart, JWORD wEnd, JBYTE *pbUuid, JBYTE bUuidLen)
{    
  JGattCtlType  * pJGattCtl = JGattCtlPtr;  
  JGattServiceType *pGattService = &JGattService[pJGattCtl->iServiceCnt];
  JINT id = pJGattCtl->iServiceCnt;

  if(pJGattCtl->iServiceCnt >= JGATT_SERVICE_MAX_COUNT)
  {
    return FALSE;
  }

  pGattService->wStart   = wStart;
  pGattService->wEnd     = wEnd;
  pGattService->bUuidLen = bUuidLen;
  UtilMemcpy(&pGattService->bUuid[0], pbUuid, bUuidLen);
  pJGattCtl->iServiceCnt = pJGattCtl->iServiceCnt + 1;
  return TRUE;
}

JBOOL JGattServiceFind(JINT fd)
{  
  JGattCtlType  * pJGattCtl = JGattCtlPtr;
  JWORD wStart = 0;
  JWORD wEnd   = 0xFFFF;  
  JBOOL bRet = FALSE;

  wStart = pJGattCtl->wServiceEnd + 1;

  bRet = JAttReadByGroupReq(fd, wStart, wEnd);

  return bRet;
}

JBOOL JGattServiceInit(void)
{
  JINT i = 0;
  JGattCtlType  * pJGattCtl = JGattCtlPtr;
  JGattServiceType * pGattService = &JGattService[pJGattCtl->iServiceCnt];

  pJGattCtl->iServiceCnt  = 0;
  pJGattCtl->bServiceFind = JGATT_SERVICE_FIND;
  for(i = 0 ; i < JGATT_SERVICE_MAX_COUNT; i = i + 1)
  {
    pGattService = &JGattService[i];
    pGattService->bUuidLen = 0;
  }
  return TRUE;
}

///-----------------------------------------------------------------------------------------------///
///
///  CHARACTERISTIC FUNCTION
///
///-----------------------------------------------------------------------------------------------///
JBOOL JGattCharacteristicPrint(JINT id, JGattCharacteristicType *pGattCharacteristic)
{
  JINT i = 0;
  char msg[256];
  JGattCtlType  * pJGattCtl = JGattCtlPtr;  

  sprintf(msg, "\t\t CHAR: #%02d -> start : %04X, end: %04X, handle: %04x uuid : ", id, pGattCharacteristic->wStart, pGattCharacteristic->wEnd, pGattCharacteristic->wHandle);
  for(i = 0; i < pGattCharacteristic->bUuidLen; i = i + 1)
  {
    sprintf(msg + strlen(msg), "%02X", pGattCharacteristic->bUuid[pGattCharacteristic->bUuidLen - i - 1]);    
  }

  sprintf(msg + strlen(msg), "%s", "\r\n");    
  DBG_PRINTF(msg);
  return TRUE;
}

JBOOL JGattCharacteristicPrint(void)
{
  JGattCtlType  * pJGattCtl = JGattCtlPtr;  
  JGattCharacteristicType *pGattCharacteristic = NULL;
  JINT i = 0;
  pJGattCtl->bCharacteristicFind = JGATT_SERVICE_FIND_OK;  
  for(i = 0; i < pJGattCtl->iCharacteristicCnt; i = i + 1)
  {
    pGattCharacteristic =  &JGattCharacteristic[i];
    JGattCharacteristicPrint(i, pGattCharacteristic);
  }
  return TRUE;
}

JBOOL JGattCharacteristicAdd(JWORD wStart, JWORD wEnd, JBYTE *pbUuid, JBYTE bUuidLen, JBYTE bProperty)
{    
  char msg[256];
  JGattCtlType  * pJGattCtl = JGattCtlPtr;  
  JGattCharacteristicType *pGattCharacteristic = &JGattCharacteristic[pJGattCtl->iCharacteristicCnt];
      
  ///------------------------------------------------------------------------------------------------///
  /// Characteristic add
  ///------------------------------------------------------------------------------------------------///
  if(pJGattCtl->iCharacteristicCnt >= JGATT_CHARACTERISTIC_MAX_COUNT)
  {
    return FALSE;
  }

  pGattCharacteristic->wStart   = wStart;
  pGattCharacteristic->wEnd     = wEnd;
  pGattCharacteristic->wHandle  = wStart + 1;  
  pGattCharacteristic->bUuidLen = bUuidLen;
  pGattCharacteristic->bProperty = bProperty;  
  UtilMemcpy(&pGattCharacteristic->bUuid[0], pbUuid, bUuidLen);
  pJGattCtl->iCharacteristicCnt = pJGattCtl->iCharacteristicCnt + 1;  
  
  ///------------------------------------------------------------------------------------------------///
  /// Characteristic Handle Find
  ///------------------------------------------------------------------------------------------------///
  const JBYTE bUuidService[]  = { 0x9E, 0xCA, 0xDC, 0x24, 0x0E, 0xE5, 0xA9, 0xE0, 0x93, 0xF3, 0xA3, 0xB5, 0x01, 0x00, 0x40, 0x6E }; ///< service
  const JBYTE bUuidCharacTx[] = { 0x9E, 0xCA, 0xDC, 0x24, 0x0E, 0xE5, 0xA9, 0xE0, 0x93, 0xF3, 0xA3, 0xB5, 0x02, 0x00, 0x40, 0x6E }; ///< device rx, center tx
  const JBYTE bUuidCharacRx[] = { 0x9E, 0xCA, 0xDC, 0x24, 0x0E, 0xE5, 0xA9, 0xE0, 0x93, 0xF3, 0xA3, 0xB5, 0x03, 0x00, 0x40, 0x6E }; ///< device tx, center rx

  if(UtilMemcmp((JBYTE *)&pGattCharacteristic->bUuid[0], (JBYTE *)&bUuidCharacRx[0], 16) == MEMCMP_SAME)
  {
    pJGattCtl->wHandleRx =  pGattCharacteristic->wHandle ;            
  }

 	if(UtilMemcmp((JBYTE *)&pGattCharacteristic->bUuid[0], (JBYTE *)&bUuidCharacTx[0], 16) == MEMCMP_SAME)
  {
    pJGattCtl->wHandleTx =  pGattCharacteristic->wHandle ;    
  }

  return TRUE;
}

JBOOL JGattCharacteristicFind(JINT fd)
{
  JGattCtlType  * pJGattCtl = JGattCtlPtr;
  JWORD wStart = 0;
  JWORD wEnd   = 0xFFFF;  

  wStart = pJGattCtl->wCharacteristicEnd + 1;

  JAttReadByTypeReq(fd, wStart, wEnd);

  return TRUE;
}

JBOOL JGattCharacteristicInit(void)
{
  JINT i = 0;
  JGattCtlType  * pJGattCtl = JGattCtlPtr;
  JGattCharacteristicType * pGattCharacteristic = NULL;

  pJGattCtl->iCharacteristicCnt  = 0;
  pJGattCtl->bCharacteristicFind = JGATT_CHARACTERISTIC_FIND;
  for(i = 0 ; i < JGATT_CHARACTERISTIC_MAX_COUNT; i = i + 1)
  {
    pGattCharacteristic = &JGattCharacteristic[i];
    pGattCharacteristic->bUuidLen = 0;
  }

  return TRUE;
}

///-----------------------------------------------------------------------------------------------///
///
///  Notify register
///
///-----------------------------------------------------------------------------------------------///
JBOOL JGattNotifyRegister(JINT fd)
{
  JGattCtlType  * pJGattCtl = JGattCtlPtr;
  JBYTE bWriteData[4];
  JINT iWriteLen = 2;
  JWORD wHandle = 0;
  if(pJGattCtl->wHandleRx == JGATT_HANDLE_INVALID)
  {
    return FALSE;
  }
  wHandle = (pJGattCtl->wHandleRx + 1);
  bWriteData[0] = 0x01;
  bWriteData[1] = 0x00;

  pJGattCtl->bNotifyRegister = JGATT_NOTIFY_REGISTER_ON;
  JAttWriteReq(fd, wHandle, bWriteData, iWriteLen);

  return TRUE;
}

JBOOL JGattMacStrGet(JBYTE *pbMacAddr, char *strMac)
{  
  sprintf(strMac, "%02X:%02X:%02X:%02X:%02X:%02X", 
            pbMacAddr[5], pbMacAddr[4], pbMacAddr[3], 
            pbMacAddr[2], pbMacAddr[1], pbMacAddr[0]);
  return TRUE;
}

JBOOL JGattAddrSet(JBYTE * pbAddr)
{
  JGattCtlType *pJGattCtl = JGattCtlPtr;

  pJGattCtl->bBleDevMacAddr[0] = pbAddr[0];
  pJGattCtl->bBleDevMacAddr[1] = pbAddr[1];
  pJGattCtl->bBleDevMacAddr[2] = pbAddr[2];
  pJGattCtl->bBleDevMacAddr[3] = pbAddr[3];
  pJGattCtl->bBleDevMacAddr[4] = pbAddr[4];
  pJGattCtl->bBleDevMacAddr[5] = pbAddr[5];

  return TRUE;
}

JBOOL JGattClose(void)
{
  JGattCtlType *pJGattCtl = JGattCtlPtr;
  
  if(pJGattCtl->iSocket != JGATT_SOCKET_INVALID)
  {        
    EpollDelete(EpollEvent.fd);
    close(pJGattCtl->iSocket);   
    pJGattCtl->iSocket = JGATT_SOCKET_INVALID;    
  }

  pJGattCtl->iSocket = JGATT_SOCKET_INVALID;
 
  return TRUE;
}

JBOOL JGattOpen(void)
{
  char    msg[256];
  JGattCtlType *pJGattCtl = JGattCtlPtr;
  JINT    iSocket  = JGATT_SOCKET_INVALID;
  
  ///------------------------------------------------------------///
  /// BT_SECURITY_SDP			0
  /// BT_SECURITY_LOW			1
  /// BT_SECURITY_MEDIUM	2
  /// BT_SECURITY_HIGH		3
  /// BT_SECURITY_FIPS		4
  ///------------------------------------------------------------///
  JINT    iSecurityLevel  = BT_SECURITY_FIPS;
	struct  sockaddr_l2 saSrc;
  struct  sockaddr_l2 saDst;
	struct  bt_security btSecurity;
  JBYTE   bDstType        = BDADDR_LE_PUBLIC;
  char    strMac[256];

  JBOOL   bRet = FALSE;
  
  pJGattCtl->wHandleRx = JGATT_HANDLE_INVALID;
  pJGattCtl->wHandleTx = JGATT_HANDLE_INVALID;

  ///------------------------------------------------------///
  /// Create bluetooth socket with L2CAP
  ///------------------------------------------------------///
	iSocket = socket(PF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_L2CAP);
	if(iSocket < 0)
  {
		sprintf(msg, "%s", "Failed to create L2CAP socket");
    DBG_PRINTF(msg);
		return FALSE;
	}

  ///------------------------------------------------------///
	/// Set source address 
  ///------------------------------------------------------///
	memset(&saSrc, 0, sizeof(saSrc));
	saSrc.l2_family       = AF_BLUETOOTH;
	saSrc.l2_cid          = htobs(ATT_CID);
	saSrc.l2_bdaddr_type  = BDADDR_LE_PUBLIC;
  UtilMemcpy((JBYTE *) &saSrc.l2_bdaddr.b[0], (JBYTE *)&pJGattCtl->bHciDevMacAddr[0], BLE_MAC_ADDR_SIZE);

	if(bind(iSocket, (struct sockaddr *)&saSrc, sizeof(saSrc)) < 0)
  {
		sprintf(msg, "%s", "Failed to bind L2CAP socket");
    DBG_PRINTF(msg);
		close(iSocket);
		return FALSE;
	}

  if(bDebugPrint == TRUE)
  {
    JGattMacStrGet((JBYTE *)&pJGattCtl->bHciDevMacAddr[0], strMac);
    sprintf(msg, "\t [JGATT][CONN] SRC : %s\r\n", strMac);
    DBG_PRINTF(msg);

    JGattMacStrGet((JBYTE *)&pJGattCtl->bBleDevMacAddr[0], strMac);
    sprintf(msg, "\t [JGATT][CONN] DST : %s\r\n", strMac);
    DBG_PRINTF(msg);
  }

  ///------------------------------------------------------///
	/// Set the security level 
  ///------------------------------------------------------///
	memset(&btSecurity, 0, sizeof(btSecurity));
	btSecurity.level = iSecurityLevel;
	if(setsockopt(iSocket, SOL_BLUETOOTH, BT_SECURITY, &btSecurity,sizeof(btSecurity)) != 0)
  {		
    sprintf(msg, "%s", "Failed to set L2CAP security level\\n");
    DBG_PRINTF(msg);
		close(iSocket);
		return FALSE;
	}

  ///------------------------------------------------------///
	/// Set up destination address
  ///------------------------------------------------------///
	memset(&saDst, 0, sizeof(saDst));
	saDst.l2_family       = AF_BLUETOOTH;
	saDst.l2_cid          = htobs(ATT_CID);
	saDst.l2_bdaddr_type  = bDstType;	
  UtilMemcpy((JBYTE *)&saDst.l2_bdaddr.b[0], (JBYTE *)&pJGattCtl->bBleDevMacAddr[0], BLE_MAC_ADDR_SIZE);

  ///------------------------------------------------------///
  /// Connect to device
  ///------------------------------------------------------///
	if(connect(iSocket, (struct sockaddr *)&saDst, sizeof(saDst)) < 0)
  {
		perror("\t\t [GATT][OPEN][ERROR] Failed to connect");
		close(iSocket);    
		return FALSE;
	}

  pJGattCtl->iSocket  = iSocket;
  
	return TRUE;
}

JBOOL JGattScanItemPrint(JINT id, JGattScanItemType *pItem)
{
  char msg[256];
  JINT i = 0;  
  char strAddr[20];
  char strRssi[8];
  char strTime[16];

  JGattMacStrGet(pItem->bAddr, strAddr);
  sprintf(strRssi, "%d", pItem->iRSSI);
  sprintf(strTime, "%0.3f", 10 - (JFLOAT)(pItem->iValidCnt * GATT_SCAN_PERIOD) / 1000.0);

  sprintf(msg, "\t #%02d: %s, %4s db, %24s,  %s sec\r\n", id, strAddr, strRssi, pItem->strName, strTime);
  DBG_PRINTF(msg);  
  return TRUE;  
}

JBOOL JGattScanItemsPrint(void)
{
  JGattCtlType *pJGattCtl = JGattCtlPtr;
  JINT i = 0;
  JGattScanItemType *pItem = NULL;
  
  for(i = 0 ; i < pJGattCtl->iScanItemCnt; i = i + 1)
  {
    pItem = &pJGattCtl->ScanItems[i];    
    JGattScanItemPrint(i, pItem);
  }
  
  return TRUE;
}

JBOOL JGattScanItemValidCheck(void)
{
  JGattCtlType *pJGattCtl = JGattCtlPtr;

  JINT i = 0;
  JINT j = 0;
  JGattScanItemType *pItem = NULL;
  JGattScanItemType *pItem0 = NULL;
  JGattScanItemType *pItem1 = NULL;
  while(1)
  {
    if(pJGattCtl->iScanItemCnt <= 0)
    {
      pJGattCtl->iScanItemCnt  = 0;
      break; 
    }
    if(i >= pJGattCtl->iScanItemCnt)
    {
      break;
    }
    pItem = &pJGattCtl->ScanItems[i];    
    pItem->iValidCnt =  pItem->iValidCnt - 1;
    if(pItem->iValidCnt < 0)
    {
      pItem0 =  pItem;       
      for(j = i + 1; j < pJGattCtl->iScanItemCnt; j = j + 1)
      {
         pItem1 = &pJGattCtl->ScanItems[j];     
         UtilMemcpy((JBYTE *)pItem0, (JBYTE *)pItem1, (JINT)sizeof(JGattScanItemType));
         pItem0 = pItem1;
      }
      pJGattCtl->iScanItemCnt = pJGattCtl->iScanItemCnt - 1;
      continue;      
    }
    i = i + 1;
  }
  return TRUE;
}

JBOOL JGattScanItemSort(void)
{
  JGattCtlType *pJGattCtl = JGattCtlPtr;

  JINT i = 0;
  JINT j = 0;

  JGattScanItemType itemTmp;
  JGattScanItemType *pItemTmp = &itemTmp;
  JGattScanItemType *pItem0 = NULL;
  JGattScanItemType *pItem1 = NULL;  
  
  for(i = 0 ; i < pJGattCtl->iScanItemCnt; i = i + 1)
  {    
    for(j = i + 1 ; j < pJGattCtl->iScanItemCnt; j = j + 1)
    {
      pItem0 = &pJGattCtl->ScanItems[i];
      pItem1 = &pJGattCtl->ScanItems[j];  
      if(pItem1->iRSSI > pItem0->iRSSI)
      {
        /// swap items
        UtilMemcpy((JBYTE *)pItemTmp, (JBYTE *)pItem0,    (JINT)sizeof(JGattScanItemType));
        UtilMemcpy((JBYTE *)pItem0,   (JBYTE *)pItem1,    (JINT)sizeof(JGattScanItemType));
        UtilMemcpy((JBYTE *)pItem1,   (JBYTE *)pItemTmp,  (JINT)sizeof(JGattScanItemType));
      }
    }
  }

  return TRUE;
}

JBOOL JGattScanItemAdd(JGattScanItemType *pItemNew)
{
  char msg[256];
  JGattCtlType *pJGattCtl = JGattCtlPtr;

  JINT  i      = 0;
  JBOOL bFound = FALSE;
  JGattScanItemType *pItem  = NULL;
  JGattScanItemType *pItem0 = NULL;

  ///---------------------------------------------------------------///
  /// Check item existed
  ///---------------------------------------------------------------///
  for(i = 0 ; i < pJGattCtl->iScanItemCnt; i = i + 1)
  {
    pItem = &pJGattCtl->ScanItems[i];
    if(UtilMemcmp((JBYTE *)&pItemNew->bAddr[0], (JBYTE *)&pItem->bAddr[0], BLE_MAC_ADDR_SIZE) == MEMCMP_DIFF)
    {
      continue;
    }
    bFound           = TRUE;
    pItem->iRSSI     = pItemNew->iRSSI;
    pItem->iValidCnt = GATT_SCAN_VALID_COUNT;
    
    return TRUE;
  }

  if(i >= JGATT_SCAN_ITEM_CNT)
  {
    return FALSE;
  }
  
  ///---------------------------------------------------------------///
  /// Add new item
  ///---------------------------------------------------------------///
  pItem0 =  &pJGattCtl->ScanItems[pJGattCtl->iScanItemCnt];
  UtilMemcpy((JBYTE *)pItem0, (JBYTE *)pItemNew, (JINT)sizeof(JGattScanItemType));
  pJGattCtl->iScanItemCnt = pJGattCtl->iScanItemCnt + 1;

  ///---------------------------------------------------------------///
  /// Sort item
  ///---------------------------------------------------------------///
  JGattScanItemSort();  
  return TRUE;
}

JBOOL JGattScanResult(void)
{
  char  msg[256];
  JGattCtlType *pJGattCtl = JGattCtlPtr;

  JBYTE   buf[HCI_MAX_EVENT_SIZE];
  JBYTE * ptr;
	struct hci_filter nf;
  struct hci_filter of;	
	socklen_t olen;
	JINT    iLen = 0;
  JINT    dd = pJGattCtl->iDD;

  evt_le_meta_event   * meta;
  le_advertising_info * info;
  char    strAddr[18];
  char    strDeviceName[256];

  JBYTE   bRssi = 0;
  JWORD   wRssi = 0;
  JINT    iRssi = 0;

  JDWORD  dwCnt = 0;

  JGattScanItemType item;
  JGattScanItemType *pItem = &item;

  /// timeout
  JINT iResult  = 0; ///< return values
  fd_set set;  
  struct timeval timeout;


  pJGattCtl->iScanTimeT0  = time(NULL);
 
  sprintf(msg, "%s", "[JGATT][SCAN] Scan result start\r\n");
  DBG_PRINTF(msg);

  if(pJGattCtl->iDD == JGATT_SOCKET_INVALID)
  {
    sprintf(msg, "%s", "[JGATT][SCAN] invalid id\r\n");
    DBG_PRINTF(msg);
    return FALSE;
  }
  
	olen = sizeof(of);
	if(getsockopt(dd, SOL_HCI, HCI_FILTER, &of, &olen) < 0)
  {		
    sprintf(msg, "%s", "[JGATT][HCI] Could not get socket options\r\n");
    DBG_PRINTF(msg);
		return  FALSE;
	}

	hci_filter_clear(&nf);

	hci_filter_set_ptype(HCI_EVENT_PKT,     &nf);
	hci_filter_set_event(EVT_LE_META_EVENT, &nf);

	if(setsockopt(dd, SOL_HCI, HCI_FILTER, &nf, sizeof(nf)) < 0)
  {		
    sprintf(msg, "%s", "[JGATT][HCI] Could not set socket options\r\n");
    DBG_PRINTF(msg);
		return FALSE;
	}

  timeout.tv_sec  = 0;
  timeout.tv_usec = 200000;

  FD_ZERO(&set);    ///< clear the set 
  FD_SET(dd, &set); ///< add our file descriptor to the set

	while(1)
  {
    pJGattCtl->iScanTimeT1  = time(NULL);
    pJGattCtl->iScanTimeSec =  pJGattCtl->iScanTimeT1   -  pJGattCtl->iScanTimeT0;
    UtilMsSleep(GATT_SCAN_PERIOD);        
    if(pJGattCtl->iGattState != JGATT_STATE_SCAN_RESULT)
    {
      sprintf(msg, "[JGATT][SCAN][LEAVE] state = %d \r\n", pJGattCtl->iGattState);
      DBG_PRINTF(msg);  
      break;
    }

    if(pJGattCtl->iScanStatus != JGATT_SCAN_STATUS_ON)
    {
      sprintf(msg, "[JGATT][SCAN][LEAVE] Scan on = %d \r\n", pJGattCtl->iScanStatus);
      DBG_PRINTF(msg);  
      break;
    }

    if(pJGattCtl->iScanTimeSec  > 5)
    {
      break;
    }
    
    dwCnt = dwCnt + 1;
    if((dwCnt % (1000 / GATT_SCAN_PERIOD)) == 0)
    {
      DBG_PRINTF("------- GATT SCAN PRINT --------\r\n");
      JGattScanItemValidCheck();
      JGattScanItemsPrint();
      pJGattCtl->bScanUIUpdate = TRUE;
      dwCnt = 0;
    }

    //iResult = select(dd + 1000, &set, NULL, NULL, &timeout);
    iResult = select(dd + 1000, &set, NULL, NULL, &timeout);
    if(iResult == -1)
    {      
      printf("scan error\r\n"); 
      continue;
    }
    else if(iResult == 0)
    {
      //printf("scan timeout\r\n"); ///< a timeout occured 
      continue;
    }
    else
    {      
      iLen = read(dd, buf, sizeof(buf)); ///< there is a file to read
      //printf("scan read - size = %d\r\n", iLen); ///< a timeout occured 
    }
      
		if(iLen < 0)
    {           
      sprintf(msg,  "[JGATT] len = %d (Len < 0)\r\n", iLen);
      DBG_PRINTF(msg);	
      continue;		
		}
    
		ptr  = buf +  (1 + HCI_EVENT_HDR_SIZE);		
		meta = (evt_le_meta_event * )ptr;
		if(meta->subevent != 0x02)
    {
      sprintf(msg,  "[JGATT] subevent  = %02x\r\n", meta->subevent);
      DBG_PRINTF(msg);	
			break;
    }
    UtilMemset((JBYTE *)&strDeviceName[0], 0x00, 256);

		/// Ignoring multiple reports
		info = (le_advertising_info *) (meta->data + 1);

    ba2str(&info->bdaddr, strAddr);

	  /// Get RSSI
    bRssi = buf[iLen - 1];   
    if((bRssi & 0x80) != 0)
    { 
      wRssi = 0xFF00 | bRssi;
      iRssi = (JINT)(*(JSHORT *) &wRssi);
    }
    else
    {
      iRssi = bRssi;
    } 
    if(iRssi > 0)
    {
      iRssi = -1;
    }

    /// AD Data Parse
    JGattScanAdParse(info->data, info->length, strDeviceName, FALSE);        
    if(strlen(strDeviceName) > 0)
    {           
      ///--------------------------------------------------------------------------------////
      /// Item set
      ///--------------------------------------------------------------------------------///
      UtilMemset((JBYTE *)pItem, 0x00, (JINT)sizeof(JGattScanItemType));
      UtilMemcpy((JBYTE *)&pItem->bAddr[0],(JBYTE *) &info->bdaddr, BLE_MAC_ADDR_SIZE);            
      pItem->iRSSI     = iRssi;
      pItem->iValidCnt = GATT_SCAN_VALID_COUNT;
      strcpy(pItem->strName, strDeviceName);

      JGattScanItemAdd(pItem);    
    }
	}
	setsockopt(dd, SOL_HCI, HCI_FILTER, &of, sizeof(of));
  
  sprintf(msg, "%s", "[JGATT][SCAN] Scan result end\r\n");
  DBG_PRINTF(msg);

  JGattStateSet(JGATT_STATE_SCAN_STOP);
  
  pJGattCtl->iScanStatus = JGATT_SCAN_STATUS_OFF;
  return TRUE;  
}

void JGattInit(void)
{
  JGattCtlType *pJGattCtl = JGattCtlPtr;

  //pJGattCtl->iOpeningTimeT0 = time(NULL);

  UtilMemset((JBYTE *)pJGattCtl, 0x00, sizeof(JGattCtlType));

  JGattClose();
  pJGattCtl->iSocket    = JGATT_SOCKET_INVALID;
  pJGattCtl->att        = NULL;  
  pJGattCtl->iGattState = JGATT_STATE_INIT;
  pJGattCtl->iHciDevId  = JGATT_HCI_DEV_ID_INVALID;

  pJGattCtl->bVscModeAdded  = FALSE;
  
  /// mtu
  pJGattCtl->iMtu = 250;

  /// Service
  pJGattCtl->wServiceStart  = 0;
  pJGattCtl->wServiceEnd    = 0;
  pJGattCtl->bServiceFind   = JGATT_SERVICE_FIND_INIT;
  pJGattCtl->iServiceCnt    = 0;

  /// Characteristic
  pJGattCtl->wCharacteristicStart  = 0;
  pJGattCtl->wCharacteristicEnd    = 0;
  pJGattCtl->bCharacteristicFind   = JGATT_CHARACTERISTIC_FIND_INIT;
  pJGattCtl->iCharacteristicCnt    = 0;  

  /// Notify Register
  pJGattCtl->bNotifyRegister  = JGATT_NOTIFY_REGISTER_INIT;

  /// Command status
  pJGattCtl->bGattCmdStatus  = JGATT_CMD_STATUS_IDLE;
}

void JGattFinal(void)
{

}

JBOOL JGattControl(void)
{
  char  msg[256];
  JBOOL bRet = FALSE;
  JINT  iAddr[6];
  JBYTE bAddr[6];
  char  strAddr[256];
  JINT  iDevId = 0;

  JGattCtlType  * pJGattCtl = JGattCtlPtr;

	///---------------------------------------------------------------------------///
	/// Gatt Scan Start
	///---------------------------------------------------------------------------///
	if(GlobalVar.dwSysCtl8 & SYS_CTL8_JGATT_SCAN_START)
	{    
    DBG_PRINTF("[JGATT] JGATT_CTL_SCAN_START\r\n");   

    pJGattCtl->iScanStatus = JGATT_SCAN_STATUS_STOP;

    ///------------------------------------------------------///
    /// Previous started
    ///------------------------------------------------------///
    if(GlobalVar.pid0 != 0)
    {
      //kill(GlobalVar.pid0, SIGSEGV);
      JGattStateEnd();
      GlobalVar.pid0 = 0;      
    }
    
   	///------------------------------------------------------///
    /// start
    ///------------------------------------------------------///
    pJGattCtl->iGattState  = JGATT_STATE_SCAN_START;
    GlobalVar.pid0 = fork();
    if(GlobalVar.pid0 == 0)
    {      
      DBG_PRINTF("Child process\r\n");
      JGattCtlPtr = (JGattCtlType *)shmat(GlobalVar.iShmId , NULL, 0);          
      JGattStateRun();    
      exit(0);
    }    
		GlobalVar.dwSysCtl8 &= ~SYS_CTL8_JGATT_SCAN_START;
	}

  ///---------------------------------------------------------------------------///
	/// Gatt Scan Stop
	///---------------------------------------------------------------------------///
	if(GlobalVar.dwSysCtl8 & SYS_CTL8_JGATT_SCAN_STOP)
	{ 
    JGattStateSet(JGATT_STATE_SCAN_STOP);
    
    DBG_PRINTF("[JGATT] JGATT_CTL_SCAN_STOP\r\n");   
    GlobalVar.dwSysCtl8 &= ~SYS_CTL8_JGATT_SCAN_STOP;    		
	}

  ///---------------------------------------------------------------------------///
	/// Gatt Open
	///---------------------------------------------------------------------------///
	if(GlobalVar.dwSysCtl8 & SYS_CTL8_JGATT_OPEN)
	{     
    DBG_PRINTF("[JGATT] JGATT_CTL_OPEN\r\n");
    ///------------------------------------------------------///
    /// Previous started
    ///------------------------------------------------------///
    if(GlobalVar.pid0 != 0)
    {            
      JGattStateEnd();
      GlobalVar.pid0 = 0;      	
    }

   	///------------------------------------------------------///
    /// start
    ///------------------------------------------------------///
    pJGattCtl->iGattState  = JGATT_STATE_OPEN_INIT;
    GlobalVar.pid0 = fork();
    if(GlobalVar.pid0 == 0)
    {            
      JGattCtlPtr = (JGattCtlType *)shmat(GlobalVar.iShmId , NULL, 0);     
      JGattStateRun();     
      exit(0); 
    }    
    GlobalVar.dwSysCtl8 &= ~SYS_CTL8_JGATT_OPEN;
	}

  ///---------------------------------------------------------------------------///
	/// Gatt Close
	///---------------------------------------------------------------------------///
	if(GlobalVar.dwSysCtl8 & SYS_CTL8_JGATT_CLOSE)
	{        
    JGattStateSet(JGATT_STATE_CLOSE);
    UtilMsSleep(50);
    DBG_PRINTF("[JGATT] JGATT_CTL_CLOSE\r\n");
    if(GlobalVar.pid0 != 0)
    {      
      JGattStateEnd();
      GlobalVar.pid0 = 0;      
    }
    
    pJGattCtl->iGattState  = JGATT_STATE_INIT;   
		GlobalVar.dwSysCtl8 &= ~SYS_CTL8_JGATT_CLOSE;
	}

  ///---------------------------------------------------------------------------///
	/// Gatt VSC_MODE START
	///---------------------------------------------------------------------------///
	if(GlobalVar.dwSysCtl8 & SYS_CTL8_JGATT_VSC_MODE_START)
	{     
    DBG_PRINTF("[JGATT] JGATT_CTL_VSC_MODE_START\r\n");
    if(pJGattCtl->iGattState  == JGATT_STATE_OPEN_OK)
    {
      JGattStateSet(JGATT_STATE_VSC_MODE_INIT);
    }    
    else
    {
      DBG_PRINTF("[JGATT] JGATT_CTL_VSC_MODE_START - ERROR\r\n");
    }

    GlobalVar.dwSysCtl8 &= ~SYS_CTL8_JGATT_VSC_MODE_START;
	}

  ///---------------------------------------------------------------------------///
	/// Gatt VSC_MODE STOP
	///---------------------------------------------------------------------------///
	if(GlobalVar.dwSysCtl8 & SYS_CTL8_JGATT_VSC_MODE_STOP)
	{     
    DBG_PRINTF("[JGATT] JGATT_CTL_VSC_MODE_STOP\r\n");

    if(pJGattCtl->iGattState  == JGATT_STATE_VSC_MODE_READ)
    {
      JGattStateSet(JGATT_STATE_VSC_MODE_STOP);
      //EcgStop();
    }    
    else
    {
      DBG_PRINTF("[JGATT] JGATT_CTL_VSC_MODE_STOP - ERROR\r\n");
    }    

    GlobalVar.dwSysCtl8 &= ~SYS_CTL8_JGATT_VSC_MODE_STOP;
	}

  return TRUE;
}
#endif ///< for  ARCH_UBUNTU
