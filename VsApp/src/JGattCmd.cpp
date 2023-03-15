/**
 * @file JGattCmd.cpp
 *
 *  JGATT Command
 *
 * @version $Revision$
 * @author JL Juang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021,  VitalSigns Technology Co., LTD., all rights reserved.
 * @note
*/
#include "Global.h"

#ifdef FEATURE_JGATT

PacketType      PacketOutGatt;
PacketAckType   PacketInGatt;
  
///---------------------------------------------------------------------------------------------------------------------///
/// Packet Send function
///---------------------------------------------------------------------------------------------------------------------///
JBOOL JGattPacketCmdSend(JINT iTimeout)
{
  JGattCtlType *pJGattCtl = JGattCtlPtr;
  PacketType *pPacketOut = &PacketOutGatt;

  JBYTE *pbWriteBuf = (JBYTE *)pPacketOut;
  JINT bWriteBufLen = 0;

  JWORD wHandle = pJGattCtl->wHandleTx;
  JINT fd = pJGattCtl->iSocket;
  
  PacketCheckSumSet(pPacketOut);

  bWriteBufLen = pPacketOut->wMOSILen + PACKET_ACK_HEADER_SIZE;   

  pJGattCtl->iGattRxBufIdx = 0;  
  pJGattCtl->iGattRxBufLen = pPacketOut->wMISOLen + PACKET_ACK_HEADER_SIZE;

  pJGattCtl->iGattCmdMS0        = UtilMsGet();
  pJGattCtl->bGattCmdStatus     = JGATT_CMD_STATUS_SEND;
  pJGattCtl->iGattCmdTimeoutMS  = iTimeout;

  JAttWriteReq(fd, wHandle, pbWriteBuf, bWriteBufLen);

  return TRUE;
}

///---------------------------------------------------------------------------------------------------------------------///
///
/// GATT : Packet command
///
///---------------------------------------------------------------------------------------------------------------------///

JINT CmdJGattSysVersionGet(void)
{
  JINT iErrNo = NO_ERR;

  PacketType    *pPacketOut = &PacketOutGatt;
    
  JINT 	iTimeout = 2500;
  char 	msg[256];

  ///-----------------------------------------------------------------------------------------///
  /// Packet Init
  ///-----------------------------------------------------------------------------------------///
  PacketInit(pPacketOut);
  
  ///-----------------------------------------------------------------------------------------///
  /// output packet set
  ///-----------------------------------------------------------------------------------------///
  pPacketOut->bGroupId 	= CMD_GROUP_ID_SYS;
  pPacketOut->bCmd 			= CMD_SYS_VER_GET;
  pPacketOut->bPCode 		= CMD_SYS_VER_GET;
  pPacketOut->wMOSILen 	= 0;
  pPacketOut->wMISOLen 	= 32;
  
  ///-----------------------------------------------------------------------------------------///
  /// slave packet Cmd
  ///-----------------------------------------------------------------------------------------///
	iErrNo = JGattPacketCmdSend(iTimeout);

  return iErrNo;
}

JINT CmdJGattSysTimeSet(void)
{
  JINT iErrNo = NO_ERR;

  PacketType    *pPacketOut = &PacketOutGatt;
    
  JINT 	iTimeout = 3500;
  JINT  iDevVersoin;
  char 	strDevName[256];  
  char 	msg[256];
  time_t t = time(NULL);
  JTM jtm;

  /// Set time
  JTMTimeZoneSecSet(&jtm, GlobalVar.iTimeZoneSec);
  JTMLocalTimeGet(&jtm, t);
  
  PacketInit(pPacketOut);
  
  /// output packet set
  pPacketOut->bGroupId 	= CMD_GROUP_ID_SYS;
  pPacketOut->bCmd 			= CMD_SYS_TIME_SET;
  pPacketOut->bPCode 		= CMD_SYS_TIME_SET;
  pPacketOut->wMOSILen 	= 16 + PACKET_CMD_BDATA_SIZE;
  pPacketOut->wMISOLen 	= 32;


	*(JWORD *)&pPacketOut->bCmdData[0] = (JWORD) jtm.iYear;
	*(JBYTE *)&pPacketOut->bCmdData[2] = (JBYTE) jtm.iMonth;
	*(JBYTE *)&pPacketOut->bCmdData[3] = (JBYTE) jtm.iDay;
	*(JBYTE *)&pPacketOut->bCmdData[4] = (JBYTE) jtm.iHour;	
	*(JBYTE *)&pPacketOut->bCmdData[5] = (JBYTE) jtm.iMin;		
	*(JBYTE *)&pPacketOut->bCmdData[6] = (JBYTE) jtm.iSec;			

  *(JINT  *)&pPacketOut->bCmdData[8]  = (JINT) t;
  *(JINT  *)&pPacketOut->bCmdData[12] = jtm.iTimeZoneSec ;

  ///-----------------------------------------------------------------------------------------///
  /// slave packet Cmd
  ///-----------------------------------------------------------------------------------------///
	iErrNo = JGattPacketCmdSend(iTimeout);

  return iErrNo;
}


///---------------------------------------------------------------------------------------------------------------------///
///
/// JGATT : BLE Master and Slave command
///
///---------------------------------------------------------------------------------------------------------------------///
JINT CmdJGattVscModeTypeSet(void)
{
  JINT iErrNo = NO_ERR;

  PacketType    *pPacketOut = &PacketOutGatt;
    
  JINT 	  iTimeout = 3500;
  JDWORD  dwVscModeType = VSC_MODE_TYPE0;

  PacketInit(pPacketOut);
    
  /// output packet set
  pPacketOut->bGroupId 	= CMD_GROUP_ID_BLE;
  pPacketOut->bCmd 			= CMD_BLE_VSC_MODE_TYPE_SET;
  pPacketOut->bPCode 		= CMD_BLE_VSC_MODE_TYPE_SET;
  pPacketOut->wMOSILen 	= 20;
  pPacketOut->wMISOLen 	= 0;

  UtilMemcpy((JBYTE *)&pPacketOut->bCmdData[0], (JBYTE *)&dwVscModeType, 4);
  
  /// slave packet Cmd
	iErrNo = JGattPacketCmdSend(iTimeout);
  DBG_PRINTF("VSC_MODE_TYPE_SET\r\n");

  return iErrNo;
}

JINT CmdJGattVscModeStart(void)
{
  JINT iErrNo = NO_ERR;

  PacketType    *pPacketOut = &PacketOutGatt;
    
  JINT 	iTimeout = 500;

  PacketInit(pPacketOut);
  
  /// output packet set
  pPacketOut->bGroupId 	= CMD_GROUP_ID_BLE;
  pPacketOut->bCmd 			= CMD_BLE_VSC_MODE_START;
  pPacketOut->bPCode 		= CMD_BLE_VSC_MODE_START;
  pPacketOut->wMOSILen 	= 0;
  pPacketOut->wMISOLen 	= 0;
  DBG_PRINTF("VSC_MODE_START\r\n");
  ///-----------------------------------------------------------------------------------------///
  /// slave packet Cmd
  ///-----------------------------------------------------------------------------------------///
  iErrNo = JGattPacketCmdSend(iTimeout);

  return iErrNo;
}

JINT CmdJGattVscModeStop(void)
{
  JINT iErrNo = NO_ERR;
  PacketType    *pPacketOut = &PacketOutGatt;
  
  JINT iTimeout = 3500;

  PacketInit(pPacketOut);
  
  /// output packet set
  pPacketOut->bGroupId 	= CMD_GROUP_ID_BLE;
  pPacketOut->bCmd 			= CMD_BLE_VSC_MODE_STOP;
  pPacketOut->bPCode 		= CMD_BLE_VSC_MODE_STOP;
  pPacketOut->wMOSILen 	= 0;
  pPacketOut->wMISOLen 	= 0;

  ///-----------------------------------------------------------------------------------------///
  /// slave packet Cmd
  ///-----------------------------------------------------------------------------------------///
  iErrNo = JGattPacketCmdSend(iTimeout);

  return iErrNo;
}

JINT CmdJGattVscModeRead(void)
{
  JGattCtlType *pJGattCtl = JGattCtlPtr;
	char 	msg[256];
  JINT iErrNo = NO_ERR;
  JWORD wId   = 0;
  JWORD wLen  = 0;
   
  PacketType    *pPacketOut = &PacketOutGatt;
    
  VscModeControlType * pVscMode = NULL;
  JINT 	iTimeout = 10000; ///< 10 seconds
  
	static JINT iErrCnt = 0;

  PacketInit(pPacketOut);
  
  /// output packet set
  pPacketOut->bGroupId 	= CMD_GROUP_ID_BLE;
  pPacketOut->bCmd 			= CMD_BLE_VSC_MODE_READ;
  pPacketOut->bPCode 		= CMD_BLE_VSC_MODE_READ;
  pPacketOut->wMOSILen 	= 2;
  pPacketOut->wMISOLen 	= 968;
  
  *(JWORD *)&pPacketOut->bData[0] = VscModeCtl.wId;

  ///-----------------------------------------------------------------------------------------///
  /// slave packet Cmd
  ///-----------------------------------------------------------------------------------------///
  iErrNo = JGattPacketCmdSend(iTimeout);

  return iErrNo;
}

JINT ActJGattSysVersionGet(void)
{  
  JGattCtlType *pJGattCtl = JGattCtlPtr;
  char msg[256];
  JINT iVersion;
  char strModelName[256];
  JINT iErrNo = NO_ERR;
  PacketAckType    *pPacketIn = &PacketInGatt;  
    
  if(pPacketIn->bAck != 'A')
  {
    sprintf(msg, "[ERROR] Version  NACK\r\n");
    DBG_PRINTF(msg);
    iErrNo = ERR_WRONG_ARG_FORMAT;
    return iErrNo;
  }

  ///-----------------------------------------------------------------------------------------///
  /// COPY DATA
  ///-----------------------------------------------------------------------------------------///		
  UtilMemcpy((JBYTE *)&iVersion,        (JBYTE *)&pPacketIn->bData[0], sizeof(JINT));
  UtilMemcpy((JBYTE *)&strModelName[0], (JBYTE *)&pPacketIn->bData[4], 28);
  strModelName[28] = 0;

  sprintf(msg, "\t\t Model Name    = %s\r\n", strModelName);
	DBG_PRINTF(msg);
	sprintf(msg, "\t\t Model Version = %d\r\n", iVersion);
	DBG_PRINTF(msg);

	return iErrNo;	
}

JINT ActJGattVscModeTypeSet(void)
{
  JINT iErrNo = NO_ERR;
  PacketAckType    *pPacketIn = &PacketInGatt;
  
	if(pPacketIn->bAck != 'A')
  {
    printf("[ERROR] VSC_MODE_TYPE_SET NACK\r\n");
    iErrNo = ERR_WRONG_ARG_FORMAT;
     return iErrNo;
  }  
	return iErrNo;
}

JINT ActJGattVscModeStart(void)
{
  JINT iErrNo = NO_ERR;
  PacketAckType    *pPacketIn = &PacketInGatt;
  
	if(pPacketIn->bAck != 'A')
  {
    printf("[ERROR] VSC_MODE_START NACK\r\n");
    iErrNo = ERR_WRONG_ARG_FORMAT;
     return iErrNo;
  }

  JGattStateSet(JGATT_STATE_VSC_MODE_READ);  
	return iErrNo;
}

JINT ActJGattVscModeStop(void)
{
  JINT iErrNo = NO_ERR;  
  PacketAckType    *pPacketIn = &PacketInGatt;

	if(pPacketIn->bAck != 'A')
  {
    printf("[ERROR] VSC_MODE_STOP NACK\r\n");
    iErrNo = ERR_WRONG_ARG_FORMAT;
    return iErrNo;
  }

  JGattStateSet(JGATT_STATE_OPEN_OK);  
  return iErrNo;
}

JINT ActJGattVscModeRead(void)
{
  JGattCtlType *pJGattCtl = JGattCtlPtr;  
  PacketAckType    *pPacketIn = &PacketInGatt;
  JINT iErrNo  = NO_ERR;  
  JINT iErrCnt = 0;
  char msg[256];
  JWORD wId   = 0;
  JWORD wLen  = 0;    
  VscModeControlType * pVscMode = NULL;
      
	if(pPacketIn->bAck != 'A')
  {
    printf("[ERROR] VSC_MODE_READ NACK\r\n");
    iErrNo  = ERR_NACK_FAIL;
    iErrCnt = iErrCnt + 1;
    if(iErrCnt == 5)
    {
    	//GlobalVar.dwSysCtl6 |= SYS_CTL6_MBLE_CLOSE;
    }
    return iErrNo;
  }
	
  /// Check if index = 8000 ( 0x1F40)
	if(pPacketIn->wDataIdx  == VSC_MODE_IDX_INVALID)
	{    
    //sprintf(msg, "\t\t [JGATT][WARNING] INVALID_ID BLE_VSC_MODE_READ ID = %d\r\n", pPacketIn->wDataIdx);
		//DBG_PRINTF(msg);		
    iErrNo = ERR_VSC_MODE_IDX_INVALID;
		return iErrNo;
	}
  
	if(VscModeCtl.wId != pPacketIn->wDataIdx)
	{
    iErrNo = ERR_VSC_MODE_IDX_DIFF;
		sprintf(msg, "\t\t [JGATT][WARNING] DIFF_ID BLE_VSC_MODE_READ ID = %d\r\n", pPacketIn->wDataIdx);
		DBG_PRINTF(msg);		
		return iErrNo;
	}	
  
	iErrCnt = 0;
	wId  = pPacketIn->wDataIdx;
	wLen = pPacketIn->wDataLen;
	
  VscModeDecode(wId, wLen, (JBYTE *)&pPacketIn->bData[0]);
  
   /// copy to main
  pVscMode = &pJGattCtl->vscModeQueue[pJGattCtl->iVscModeQueueTail];
  UtilMemcpy((JBYTE *)pVscMode, (JBYTE *)&VscModeCtl, sizeof(VscModeControlType));
  
  pJGattCtl->iVscModeQueueTail = (pJGattCtl->iVscModeQueueTail + 1) % VSC_MODE_QUEUE_SIZE;
  if(pJGattCtl->bVscModeAdded == TRUE)
  {
    DBG_PRINTF("[JGATT][ERROR] VSC Mode ADD = TRUE, data overflow\r\n");
  }
  else
  {
    pJGattCtl->bVscModeAdded = TRUE;
  }

	VscModeCtl.wId = (VscModeCtl.wId + 1) % VSC_MODE_IDX_MAX;		
  
  return iErrNo;
}

JBOOL JGattPacketCmdDispatch(void)
{  
  char msg[256];
  JGattCtlType  * pJGattCtl  = JGattCtlPtr;
  PacketAckType * pPacketIn  = &PacketInGatt;    
  JINT iErrNo = NO_ERR;
  JINT iPacketAckLen = 0;
  iPacketAckLen = pJGattCtl->bGattRxBuf[6] + pJGattCtl->bGattRxBuf[7] * 256;
  
  if(iPacketAckLen >  sizeof(PacketAckType))
  {
    sprintf(msg, "[JGATT][ERROR]PacketAck size overflow %d, %d\r\n",iPacketAckLen, (JINT)sizeof(PacketAckType));
    DBG_PRINTF(msg);
    UtilDataPrint( pJGattCtl->bGattRxBuf, 16);
    iPacketAckLen = sizeof(PacketAckType);
  }
  UtilMemcpy((JBYTE *)pPacketIn, (JBYTE *)&pJGattCtl->bGattRxBuf[0], pJGattCtl->iGattRxBufLen);

  if(pPacketIn->bPCode == CMD_SYS_VER_GET)
  {
    iErrNo = ActJGattSysVersionGet();    
  }
  if(pPacketIn->bPCode == CMD_BLE_VSC_MODE_TYPE_SET)
  {
    iErrNo = ActJGattVscModeTypeSet();    
  }
  if(pPacketIn->bPCode == CMD_BLE_VSC_MODE_START)
  {
    iErrNo = ActJGattVscModeStart();    
  }
  if(pPacketIn->bPCode == CMD_BLE_VSC_MODE_STOP)
  {
    iErrNo = ActJGattVscModeStop();    
  }
  if(pPacketIn->bPCode == CMD_BLE_VSC_MODE_READ)
  {
    iErrNo = ActJGattVscModeRead();
  }
  UtilMemset(&pJGattCtl->bGattRxBuf[0], 0x00, pJGattCtl->iGattRxBufLen);
  pJGattCtl->iGattRxBufLen = 0;

  return TRUE;
}
#endif ///< for  ARCH_UBUNTU
