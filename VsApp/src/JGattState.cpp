/**
 * @file JGattState.cpp
 *
 *  JGATT State Machine control
 *
 * @version $Revision$
 * @author JL Juang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021,  VitalSigns Technology Co., LTD., all rights reserved.
 * @note
*/
#include "Global.h"

#ifdef FEATURE_JGATT

void * ThreadGattScanResult(void *arg)
{
  JGattScanResult();  
  pthread_exit(NULL);	
  return NULL;	
}

JBOOL JGattStateInit(void)
{
  JGattCtlType *pJGattCtl = JGattCtlPtr;

  pJGattCtl->iGattTimeMS     = 0;
  pJGattCtl->iGattTimeOutMS  = 10000;

  return TRUE;
}

JBOOL JGattStateOpenInit(void)
{
  JGattCtlType *pJGattCtl = JGattCtlPtr;
  char  strAddr[256];
  JINT  iAddr[6];
  JBYTE bAddr[6];

  pJGattCtl->iOpenTimeT0  = time(NULL); 
  pJGattCtl->iOpenTimeT1  = time(NULL); 
  pJGattCtl->iOpenTimeSec = 0;

  DBG_PRINTF("[JGATT] JGATT_STATE_INIT\r\n");
  pJGattCtl->iGattTimeMS     = 0;
  pJGattCtl->iGattTimeOutMS  = 10000;
  pJGattCtl->iGattTimeWaitMS = 0;
  pJGattCtl->bGattCmdStatus  = JGATT_CMD_STATUS_IDLE;

  HciDeviceClose();

  /// Get the mac
  ConfigStrGet((char *)CONFIG_ITEM_GATT_DEVICE_MAC, &strAddr[0]);

  /// Fetch the mac addr from string
  sscanf(strAddr, "%02X:%02X:%02X:%02X:%02X:%02X",
          (unsigned int *)&iAddr[5], (unsigned int *)&iAddr[4], (unsigned int *)&iAddr[3],
          (unsigned int *)&iAddr[2], (unsigned int *)&iAddr[1], (unsigned int *)&iAddr[0]);

  bAddr[0] = (JBYTE)iAddr[0];
  bAddr[1] = (JBYTE)iAddr[1];
  bAddr[2] = (JBYTE)iAddr[2];
  bAddr[3] = (JBYTE)iAddr[3];
  bAddr[4] = (JBYTE)iAddr[4];
  bAddr[5] = (JBYTE)iAddr[5];

  JGattAddrSet(bAddr);				
  JGattStateSet(JGATT_STATE_OPEN);		

  return TRUE;
}

JBOOL JGattStateOpen(void)
{      
  JGattCtlType *pJGattCtl = JGattCtlPtr;
  char  msg[256];
  JBOOL bRet = FALSE;
  JINT iHciDevId = 0;
  
  pJGattCtl->iOpenTimeT1  = time(NULL); 
  pJGattCtl->iOpenTimeSec = pJGattCtl->iOpenTimeT1 -  pJGattCtl->iOpenTimeT0;
	

  iHciDevId = hci_get_route(NULL);
  HciParamSet(iHciDevId, (char *)"supervision_timeout", (char *)"250");
  HciParamSet(iHciDevId, (char *)"conn_max_interval",   (char *)"40");
  HciParamSet(iHciDevId, (char *)"conn_min_interval",   (char *)"10");

  
	bRet = JGattOpen();
  if(bRet == TRUE)
  {    
    sprintf(msg, "[JGATT] Device open ok \r\n\r\n");
    DBG_PRINTF(msg);  

    JGattServiceInit();
    JGattCharacteristicInit();      
    
    /// Add event
    EpollAdd(pJGattCtl->iSocket, EPOLLIN, &EpollEvent);

    pJGattCtl->bServiceFind = JGATT_SERVICE_FIND;
    JGattStateSet(JGATT_STATE_SERVICE_FIND);	      
  } 
  else
  {      
    sprintf(msg, "[JGATT][STATE][OPEN] gatt open failed \r\n\r\n");
    DBG_PRINTF(msg);  
    UtilMsSleep(500);
  }  
  return bRet;
}

JBOOL JGattStateServiceFind(void)
{     
  JGattCtlType *pJGattCtl = JGattCtlPtr;
  JBOOL bRet = TRUE;
  
  pJGattCtl->iOpenTimeT1  = time(NULL); 
  pJGattCtl->iOpenTimeSec = pJGattCtl->iOpenTimeT1 -  pJGattCtl->iOpenTimeT0;

  if(pJGattCtl->bServiceFind == JGATT_SERVICE_FIND_OK)
  {
    JGattStateSet(JGATT_STATE_CHARACTERISTIC_FIND);	      
  }    
  ///------------------------------------------------------------------------------///
  /// SERVICE
  ///------------------------------------------------------------------------------///
  if(pJGattCtl->bServiceFind == JGATT_SERVICE_FIND)
  {
    DBG_PRINTF("[JGATT][STATE] SERVICE FIND\r\n");
    JGattServiceFind(pJGattCtl->iSocket);    
  }
  return bRet;
}

JBOOL JGattStateCharacteristicFind(void)
{  
  JGattCtlType *pJGattCtl = JGattCtlPtr;
  JBOOL bRet = TRUE;

  pJGattCtl->iOpenTimeT1  = time(NULL); 
  pJGattCtl->iOpenTimeSec = pJGattCtl->iOpenTimeT1 -  pJGattCtl->iOpenTimeT0;
  
  if(pJGattCtl->bCharacteristicFind == JGATT_CHARACTERISTIC_FIND_OK)
  {
    JGattStateSet(JGATT_STATE_NOTIFY_REGISTER);	      
  }
  if(pJGattCtl->bCharacteristicFind == JGATT_CHARACTERISTIC_FIND)
  {
    JGattCharacteristicFind(pJGattCtl->iSocket);        
  }
  
  return bRet;
}

JBOOL JGattStateNotifyRegister(void)
{  
  JGattCtlType *pJGattCtl = JGattCtlPtr;
  JBOOL bRet = TRUE;
  char msg[256];

  if(pJGattCtl->bNotifyRegister == JGATT_NOTIFY_REGISTER_INIT)
  {
    bRet =JGattNotifyRegister(pJGattCtl->iSocket);
  }
  if(pJGattCtl->bNotifyRegister == JGATT_NOTIFY_REGISTER_OK)
  {
    sprintf(msg, "\t [JGATT] RX = %04x\r\n", pJGattCtl->wHandleRx);
    DBG_PRINTF(msg);
    sprintf(msg, "\t [JGATT] TX = %04x\r\n", pJGattCtl->wHandleTx);
    DBG_PRINTF(msg);      
    pJGattCtl->iGattStateStep = 0;
    UtilMsSleep(20);
    JGattStateSet(JGATT_STATE_OPEN_OK);	 
  }
  return bRet;
}

JBOOL JGattStateOpenReady(void)
{  
  JGattCtlType *pJGattCtl = JGattCtlPtr;
  JBOOL bRet  = TRUE;
  long iMSNow = UtilMsGet();  
  
  if(pJGattCtl->iGattStateStep == 0)
  {
    pJGattCtl->iOpenTimeT0  = time(NULL); 
    if(pJGattCtl->bGattCmdStatus == JGATT_CMD_STATUS_IDLE)
    {        
      CmdJGattSysTimeSet();
      pJGattCtl->iGattStateStep = 1;     
    }
  }
  else if(pJGattCtl->iGattStateStep == 1)
  {
    if(pJGattCtl->bGattCmdStatus == JGATT_CMD_STATUS_IDLE)
    {        
      CmdJGattVscModeTypeSet();   
       pJGattCtl->iGattStateStep = 2;        
    }
  }
  else if(pJGattCtl->iGattStateStep == 2)
  {
    if(pJGattCtl->bGattCmdStatus == JGATT_CMD_STATUS_IDLE)
    {     
      if((iMSNow - pJGattCtl->iGattCmdMS0) > 1000)
      {   
        CmdJGattSysVersionGet();
        pJGattCtl->iOpenTimeT1  = time(NULL); 
        pJGattCtl->iOpenTimeSec = pJGattCtl->iOpenTimeT1 -  pJGattCtl->iOpenTimeT0;    
      }
    }
  }    

  return bRet;
}

JBOOL JGattStateClose(void)
{  
  JGattCtlType *pJGattCtl = JGattCtlPtr;

  DBG_PRINTF("[JGATT] JGATT_STATE_CLOSED\r\n");
  JGattClose();
  JGattStateSet(JGATT_STATE_INIT);	    

  return TRUE;
}

JBOOL JGattStateScanStart(void)
{  
  JGattCtlType *pJGattCtl = JGattCtlPtr;
  JBOOL bRet  = TRUE;
  JINT iErr   = 0;

  DBG_PRINTF("[JGATT] JGATT_STATE_SCAN_START\r\n");
  
  if(pJGattCtl->iScanStatus == JGATT_SCAN_STATUS_ON)
  {
    DBG_PRINTF("[JGATT] Device open error - 1\r\n");
    return FALSE;
  }        

  if(HciDeviceOpen() == FALSE)
  {
    DBG_PRINTF("[JGATT] Device open error - 2\r\n");
    return FALSE;
  }
   
  if(HciScanStart() == FALSE)
  {
    DBG_PRINTF("[JGATT] Device open error - 3\r\n");
    return FALSE;
  }

	///--------------------------------------------------------------------------------///
	/// Seperate APP and Function 
	///--------------------------------------------------------------------------------///
	iErr = pthread_create(&pJGattCtl->tidScan, NULL, &ThreadGattScanResult, NULL);	
	if(iErr != 0)
	{
		printf("can't create thread :[%s]\r\n", strerror(iErr));
    return FALSE;
	}
	else
	{		
		pthread_detach(pJGattCtl->tidScan);		
	}

	///--------------------------------------------------------------------------------///
  ///
  ///--------------------------------------------------------------------------------///
  JGattStateSet(JGATT_STATE_SCAN_RESULT);	

  pJGattCtl->iScanStatus = JGATT_SCAN_STATUS_ON;

  return bRet;    
}

JBOOL JGattStateScanStop(void)
{  
  JGattCtlType *pJGattCtl = JGattCtlPtr;
  JBOOL bRet  = TRUE;
  
  bRet = HciScanStop();
  bRet = HciDeviceClose();   

  pJGattCtl->iScanStatus = JGATT_SCAN_STATUS_STOP;
  JGattStateSet(JGATT_STATE_INIT);	
  return bRet;
}

JBOOL JGattStateScanResult(void)
{  
  JGattCtlType *pJGattCtl = JGattCtlPtr;
  JBOOL bRet  = TRUE;
  
  if(pJGattCtl->iScanStatus != JGATT_SCAN_STATUS_ON)
  {
    JGattStateSet(JGATT_STATE_SCAN_START);	
    return FALSE;
  }
  return bRet;
}

JBOOL JGattStateScanClose(void)
{
  JBOOL bRet = TRUE;
  bRet = HciScanStop();
  bRet = HciDeviceClose();    
  JGattStateSet(JGATT_STATE_INIT);	    
  return bRet;
}

JBOOL JGattStateVscModeInit(void)
{
  JBOOL bRet = TRUE;
  JGattCtlType *pJGattCtl = JGattCtlPtr;

  VscModeCtl.wId = 0;

  pJGattCtl->bVscModeAdded = FALSE;
  pJGattCtl->iVscModeQueueHead = 0;
  pJGattCtl->iVscModeQueueTail = 0; 

  FuncJGattVscModeStart();

  JGattStateSet(JGATT_STATE_VSC_MODE_START);   

  return bRet;
}

JBOOL JGattStateVscModeStart(void)
{
  JBOOL bRet = TRUE;
  JGattCtlType *pJGattCtl = JGattCtlPtr;

  pJGattCtl->iGattTimeMS  = 0;        
  CmdJGattVscModeStart();

  pJGattCtl->tVsdModeStart = UtilMsGet();
  pJGattCtl->t0            = UtilMsGet();
    
  return bRet;
}

JBOOL JGattStateVscModeStop(void)
{
  JBOOL bRet = TRUE;
  JGattCtlType *pJGattCtl = JGattCtlPtr;
  CmdJGattVscModeStop();  
  return bRet;
}

JBOOL JGattStateVscModeRead(void)
{
  JBOOL bRet = TRUE;
  JGattCtlType *pJGattCtl = JGattCtlPtr;
  JINT iErrNo = NO_ERR;
  long iMSNow = 0; 
  iMSNow = UtilMsGet();
  if(pJGattCtl->bGattCmdStatus == JGATT_CMD_STATUS_IDLE)
  {     
    if((iMSNow - pJGattCtl->iGattCmdMS0) > 50)
    {   
      iErrNo = CmdJGattVscModeRead();    	
    }
  }
  return bRet;
}

JBOOL JGattStateMain(void)
{  
  char  msg[256];
  JBOOL bRet = FALSE;

  char  strModelName[256];
  JINT  iVersion = 0;
  JINT  iErrNo = NO_ERR;
  
  JGattCtlType *pJGattCtl = JGattCtlPtr;
  long iMSNow = 0; 
  
  pJGattCtl->t1 = UtilMsGet();
  bRet = EpollWait(5);   
  
  ///----------------------------------------------------------------------------------------///
  /// Command  
  ///----------------------------------------------------------------------------------------///
  if(pJGattCtl->bGattCmdStatus != JGATT_CMD_STATUS_IDLE)
  {
    if(pJGattCtl->bGattCmdStatus == JGATT_CMD_STATUS_DATA_OK)
    {
      if(bDebugPrint == TRUE)
      {
        sprintf(msg, "[JGATT][CMD] DISPATCH\r\n");
        DBG_PRINTF(msg);
      }
      JGattPacketCmdDispatch();
      pJGattCtl->bGattCmdStatus = JGATT_CMD_STATUS_IDLE;
    }
    else
    {
      pJGattCtl->iGattCmdMS1 = UtilMsGet();
      if((pJGattCtl->iGattCmdMS1 - pJGattCtl->iGattCmdMS0) > pJGattCtl->iGattCmdTimeoutMS)
      {
        sprintf(msg, "[JGATT][CMD] timeout!!!!!\r\n");
        DBG_PRINTF(msg);
        pJGattCtl->bGattCmdStatus = JGATT_CMD_STATUS_IDLE;
      }      
    }  
    return TRUE;
  }

  ///----------------------------------------------------------------------------------------///  
  /// State machine  
  ///----------------------------------------------------------------------------------------///
  iMSNow = UtilMsGet();  

  if(pJGattCtl->iGattState == JGATT_STATE_INIT)
  {
    bRet = JGattStateInit();
    return bRet;
  }
  else if(pJGattCtl->iGattState == JGATT_STATE_OPEN_INIT)
  {
    JGattInit();
    bRet = JGattStateOpenInit();			
    return bRet;
  }
  else if(pJGattCtl->iGattState == JGATT_STATE_OPEN)
  {    
    bRet = JGattStateOpen();      
    return bRet;		
  }
  else if(pJGattCtl->iGattState == JGATT_STATE_SERVICE_FIND)
  {  
    bRet = JGattStateServiceFind();
    return bRet;
  }
  else if(pJGattCtl->iGattState == JGATT_STATE_CHARACTERISTIC_FIND)
  {       
    bRet = JGattStateCharacteristicFind();
    return bRet;
  }
  else if(pJGattCtl->iGattState == JGATT_STATE_NOTIFY_REGISTER)
  {   
    bRet = JGattStateNotifyRegister();    
    return TRUE;
  }
  else if(pJGattCtl->iGattState == JGATT_STATE_OPEN_OK)
  {     
    bRet =  JGattStateOpenReady();
    return TRUE;
  }
  else if(pJGattCtl->iGattState == JGATT_STATE_CLOSE)
  {
    bRet = JGattStateClose();
    return bRet;
  }
  else if(pJGattCtl->iGattState == JGATT_STATE_SCAN_START)
  {    
    bRet = JGattStateScanStart();
    return bRet;
  }
  else if(pJGattCtl->iGattState == JGATT_STATE_SCAN_RESULT)
  {   
    bRet = JGattStateScanResult();
    return bRet;
  }
  else if(pJGattCtl->iGattState == JGATT_STATE_SCAN_STOP)
  {
    bRet = JGattStateScanStop();    
    return bRet;
  }
  else if(pJGattCtl->iGattState == JGATT_STATE_VSC_MODE_INIT)
  {
    bRet = JGattStateVscModeInit();
    return bRet;
  }
  else if(pJGattCtl->iGattState == JGATT_STATE_VSC_MODE_START)
  {
    bRet = JGattStateVscModeStart();
    return bRet;
  }
  else if(pJGattCtl->iGattState == JGATT_STATE_VSC_MODE_STOP)
  {
    bRet = JGattStateVscModeStop();
    return bRet;
  }
  else if(pJGattCtl->iGattState == JGATT_STATE_VSC_MODE_READ)
  {      
    bRet = JGattStateVscModeRead();                
    return TRUE;
  }

  return TRUE;
}

JBOOL JGattStateSet(JINT iState)
{
  JGattCtlType *pJGattCtl = JGattCtlPtr;
  pJGattCtl->iGattState   = iState;
  return TRUE;
}

JBOOL JGattStateEnd(void)
{
  JINT i = 0;
  JGattCtlType  * pJGattCtl = JGattCtlPtr;
  pJGattCtl->bLeave = TRUE;

  while(1)
  {
    if(pJGattCtl->bLeave == FALSE)
    {
      break;
    }
    UtilMsSleep(100);
    i = i + 1;
    if(i > 10)
    {
      break;
    }
  }
  return TRUE;
}

JBOOL JGattStateRun(void)
{
  char msg[256];
  JGattCtlType  * pJGattCtl = JGattCtlPtr;
  ///------------------------------------------------------------------------------///
  /// GATT Open
  ///------------------------------------------------------------------------------///    
  EpollInit();
  while(1)
  {        
    JGattStateMain();    
    if(pJGattCtl->bLeave == TRUE)
    {
      break;
    }
  }

  JGattClose();
  EpollFinal();
  sprintf(msg, "GATT-STATE-RUN END \r\n");
  DBG_PRINTF(msg);

  pJGattCtl->iGattState = JGATT_STATE_INIT;
  pJGattCtl->bLeave = FALSE;
  exit(0);  
  return TRUE;
}


#endif ///< for  FEATURE_JGATT
