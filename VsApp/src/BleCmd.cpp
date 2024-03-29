/**
 * @file BleCmd.cpp
 * 		BLE Command
 * @version $Revision$
 * @author JLJuang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021, VitalSigns Technology Co., Ltd., all rights reserved.
 */
#include "Global.h"

///---------------------------------------------------------------------------------------------------------------------///
/// Packet Send function
///---------------------------------------------------------------------------------------------------------------------///
JINT SBlePacketSend(PacketType * pPacketOut, PacketAckType * pPacketIn, JINT iTimeout)
{
  JINT iErrNo = NO_ERR;
  PacketType    	PacketOut;
  PacketAckType   PacketIn;
  JINT iMS = 0;

	while(1)
	{
		if(GlobalVar.bBleCmdOn == FALSE)
		{
			break;
		}
		UtilMsSleep(2);
		iMS = iMS + 2;
		if(iMS >= iTimeout)
		{
			DBG_PRINTF("[BLE] COMMAND BUSY\r\n");
			return ERR_BLE_BUSY_TIMEOUT;
		}
	}

	GlobalVar.bBleCmdOn = TRUE;
		
	PacketCheckSumSet(pPacketOut);

  PacketInit(&PacketOut);
  PacketOut.bGroupId = (JBYTE)CMD_GROUP_ID_BLE;
  PacketOut.bCmd     = (JBYTE)CMD_BLE_PACKET_WRITE;
  PacketOut.bPCode   = (JBYTE)CMD_BLE_PACKET_WRITE;

  PacketOut.wMOSILen = pPacketOut->wMOSILen + PACKET_CMD_BDATA_SIZE + PACKET_ACK_HEADER_SIZE ;
  PacketOut.wMISOLen = pPacketOut->wMISOLen + PACKET_ACK_HEADER_SIZE;

  memcpy(&PacketOut.bCmdData[0], pPacketOut, PacketOut.wMOSILen);

  PacketCheckSumSet(&PacketOut);
  
  /// uart write cmd
  iErrNo = PacketSend(&PacketOut, &PacketIn, iTimeout);

	GlobalVar.bBleCmdOn = FALSE;
  
  if(iErrNo != NO_ERR)
  {
    return iErrNo;
  }
  if(PacketIn.bAck != CMD_ACK)
  {
    return ERR_NACK_FAIL;
  }
  /// copy data
  memcpy(pPacketIn, PacketIn.bData, PacketIn.wDataLen);
  
  return iErrNo;
}

///---------------------------------------------------------------------------------------------------------------------///
///
/// BLE : BLE Master and Slave command
///
///---------------------------------------------------------------------------------------------------------------------///

///---------------------------------------------------------------------------------------///
/// MBLE
///---------------------------------------------------------------------------------------///
JINT CmdMBleScan(void)
{
  JINT iErrNo = NO_ERR;
  PacketType    PacketOut;
  PacketAckType PacketIn; 
  JINT iLen = 0;
  JINT iTypeSize = 0;

	JINT iDeviceCnt = 0;
  JINT iTimeout = 500;

  JINT iDataCnt = 0;

  JINT i = 0;

  BleDeviceItemType *pItem = NULL;
  char msg[256];
  
  PacketInit(&PacketOut);

	PacketOut.bGroupId = CMD_GROUP_ID_BLE;
	PacketOut.bCmd     = CMD_BLE_SCAN_TABLE;
	PacketOut.bPCode   = CMD_BLE_SCAN_TABLE;
	PacketOut.wMOSILen = 0;
	PacketOut.wMISOLen = 2048;  

  iErrNo = PacketSend(&PacketOut, &PacketIn, iTimeout);
  if(PacketIn.bAck != 'A')
  {
   	GlobalVar.BleDeviceList.iCnt = 0;
  	sprintf(msg, "%s","[MBLE] Scan failed\r\n");
    DBG_PRINTF(msg);
    return ERR_COMM_ISSUE;
  }

 	iDataCnt = *(JINT *) &PacketIn.bData[0];
	
	if(iDataCnt < 0)
	{
		iDataCnt = 0;
	}
	if(iDataCnt > BLE_DEVICE_LIST_MAX_CNT)
	{
		iDataCnt = 0;
	}
	pItem =  &GlobalVar.BleDeviceList.BleDeviceItems[0];
	UtilMemcpy((JBYTE *)pItem, (JBYTE *)&PacketIn.bData[8], (iDataCnt * sizeof(BleDeviceItemType)));
 	GlobalVar.BleDeviceList.iCnt = iDataCnt;
	
  return iErrNo;
}


JINT CmdMBleOpen(JBYTE *pbMacAddr)
{
  JINT iErrNo = NO_ERR;
  PacketType    PacketOut;
  PacketAckType PacketIn;
  JINT iTimeout = 3500;
  JINT i = 0;

  PacketInit(&PacketOut);
  
	PacketOut.bGroupId = CMD_GROUP_ID_BLE;
	PacketOut.bCmd     = CMD_BLE_OPEN;
	PacketOut.bPCode   = CMD_BLE_OPEN;
	PacketOut.wMOSILen = 22;
	PacketOut.wMISOLen = 0;  

	///--------------------------------------------------------///
	/// set mac for connection
	///--------------------------------------------------------///	
	for(i = 0; i < 6 ; i = i + 1)
	{	
		PacketOut.bCmdData[i] = pbMacAddr[i];
	}
  
  iErrNo = PacketSend(&PacketOut, &PacketIn, iTimeout);
  if(PacketIn.bAck != 'A')
  {
   	GlobalVar.BleDeviceList.iCnt = 0;
  	printf("[MBLE] BLE Open failed\r\n");
    return ERR_COMM_ISSUE;
  }
  
  return iErrNo;
}

JINT CmdMBleClose(void)
{
  JINT iErrNo = NO_ERR;
  PacketType    PacketOut;
  PacketAckType PacketIn;
  JINT iTimeout = 3500;

  PacketInit(&PacketOut);
  
	PacketOut.bGroupId = CMD_GROUP_ID_BLE;
	PacketOut.bCmd     = CMD_BLE_CLOSE;
	PacketOut.bPCode   = CMD_BLE_CLOSE;
	PacketOut.wMOSILen = 0;
	PacketOut.wMISOLen = 0;  
  
  iErrNo = PacketSend(&PacketOut, &PacketIn, iTimeout);
  if(PacketIn.bAck != 'A')
  {
   	GlobalVar.BleDeviceList.iCnt = 0;
  	printf("\t\t [CMD][MBLE] BLE Close failed\r\n");
    return ERR_COMM_ISSUE;
  }
  
  return iErrNo;
}

JINT CmdMBleConnectStatus(JBOOL *pbStatus)
{
  JINT iErrNo = NO_ERR;
  PacketType    PacketOut;
  PacketAckType PacketIn;
  JINT iTimeout = CMD_TIMEOUT_100MS;
  JINT i = 0;

  PacketInit(&PacketOut);
  
	PacketOut.bGroupId = CMD_GROUP_ID_BLE;
	PacketOut.bCmd     = CMD_BLE_CONNECT_STATUS;
	PacketOut.bPCode   = CMD_BLE_CONNECT_STATUS;
	PacketOut.wMOSILen = 0;
	PacketOut.wMISOLen = 8;  

  iErrNo = PacketSend(&PacketOut, &PacketIn, iTimeout);
  if(PacketIn.bAck != 'A')
  {
   	GlobalVar.BleDeviceList.iCnt = 0;
  	printf("\t\t [CMD][MBLE] Connect Status Failed\r\n");
    return ERR_COMM_ISSUE;
  }

  *pbStatus = *(JBYTE *)&PacketIn.bData[0]; 
  
  return iErrNo;
}

JINT CmdMBleStatus(JDWORD *pdwStatus)
{
  JINT iErrNo = NO_ERR;
  PacketType    PacketOut;
  PacketAckType PacketIn;
  JINT iTimeout = CMD_TIMEOUT_100MS;	///< MS
  JINT i = 0;

  PacketInit(&PacketOut);
  
	PacketOut.bGroupId = CMD_GROUP_ID_BLE;
	PacketOut.bCmd     = CMD_BLE_STATUS;
	PacketOut.bPCode   = CMD_BLE_STATUS;
	PacketOut.wMOSILen = 0;
	PacketOut.wMISOLen = 4;  

  iErrNo = PacketSend(&PacketOut, &PacketIn, iTimeout);
  if(PacketIn.bAck != 'A')
  {
   	GlobalVar.BleDeviceList.iCnt = 0;
  	printf("\t\t [CMD][MBLE] Status Failed\r\n");
    return ERR_COMM_ISSUE;
  }
  *pdwStatus = *(JDWORD *)&PacketIn.bData[0];
  return iErrNo;
}

///---------------------------------------------------------------------------------------///
/// SBLE
///---------------------------------------------------------------------------------------///
JINT CmdMBleState(JINT *piState)
{
  JINT iErrNo = NO_ERR;
  PacketType    PacketOut;
  PacketAckType PacketIn;
  JINT iTimeout = CMD_TIMEOUT_100MS;
  JINT i = 0;

  PacketInit(&PacketOut);
  
	PacketOut.bGroupId = CMD_GROUP_ID_BLE;
	PacketOut.bCmd     = CMD_BLE_STATE;
	PacketOut.bPCode   = CMD_BLE_STATE;
	PacketOut.wMOSILen = 0;
	PacketOut.wMISOLen = 4;  

  iErrNo = PacketSend(&PacketOut, &PacketIn, iTimeout);
  if(PacketIn.bAck != 'A')
  {
   	GlobalVar.BleDeviceList.iCnt = 0;
  	printf("t\t [CMD][MBLE] State Failed\r\n");
    return ERR_COMM_ISSUE;
  }

  *piState = *(JDWORD *)&PacketIn.bData[0];

  printf("\t\t [CMD][MBLE] State  = %d\r\n", *piState);
  
  return iErrNo;
}


JINT CmdSBleSysVersionGet(char *pModelName, JINT *piVersion)
{
  JINT iErrNo = NO_ERR;

  PacketType    PacketOut;
  PacketAckType PacketIn;
  
  JINT 	iTimeout = 3500;
  char 	msg[256];

  PacketInit(&PacketOut);
  
  /// output packet set
  PacketOut.bGroupId 	= CMD_GROUP_ID_SYS;
  PacketOut.bCmd 			= CMD_SYS_VER_GET;
  PacketOut.bPCode 		= CMD_SYS_VER_GET;
  PacketOut.wMOSILen 	= 0;
  PacketOut.wMISOLen 	= 32;
  
  /// slave packet Cmd
	iErrNo = SBlePacketSend(&PacketOut, &PacketIn, iTimeout);

	if(PacketIn.bAck != 'A')
  {
    sprintf(msg, "[ERROR] Version  NACK\r\n");
    DBG_PRINTF(msg);
    iErrNo = ERR_WRONG_ARG_FORMAT;
  }

 	///-----------------------------------///
  /// COPY DATA
  ///-----------------------------------///		
  UtilMemcpy((JBYTE *)piVersion,       (JBYTE *)&PacketIn.bData[0], sizeof(JINT));
  UtilMemcpy((JBYTE *)&pModelName[0], (JBYTE *)&PacketIn.bData[4], 28);
  pModelName[28] = 0;
 
  return iErrNo;
}

JINT CmdSBleSysTimeSet(void)
{
  JINT iErrNo = NO_ERR;

  PacketType    PacketOut;
  PacketAckType PacketIn;
  
  JINT 	iTimeout = 3500;
  JINT  iDevVersoin;
  char 	strDevName[256];  
  char 	msg[256];
  time_t t = time(NULL);
  JTM jtm;

  /// Set time
  JTMTimeZoneSecSet(&jtm, GlobalVar.iTimeZoneSec);
  JTMLocalTimeGet(&jtm, t);
  
  PacketInit(&PacketOut);
  
  /// output packet set
  PacketOut.bGroupId 	= CMD_GROUP_ID_SYS;
  PacketOut.bCmd 			= CMD_SYS_TIME_SET;
  PacketOut.bPCode 		= CMD_SYS_TIME_SET;
  PacketOut.wMOSILen 	= 16 + PACKET_CMD_BDATA_SIZE;
  PacketOut.wMISOLen 	= 32;


	*(JWORD *)&PacketOut.bCmdData[0] = (JWORD) jtm.iYear;
	*(JBYTE *)&PacketOut.bCmdData[2] = (JBYTE) jtm.iMonth;
	*(JBYTE *)&PacketOut.bCmdData[3] = (JBYTE) jtm.iDay;
	*(JBYTE *)&PacketOut.bCmdData[4] = (JBYTE) jtm.iHour;	
	*(JBYTE *)&PacketOut.bCmdData[5] = (JBYTE) jtm.iMin;		
	*(JBYTE *)&PacketOut.bCmdData[6] = (JBYTE) jtm.iSec;			

  *(JINT  *)&PacketOut.bCmdData[8]  = (JINT) t;
  *(JINT  *)&PacketOut.bCmdData[12] = jtm.iTimeZoneSec ;

  
  /// slave packet Cmd
	iErrNo = SBlePacketSend(&PacketOut, &PacketIn, iTimeout);

	if(PacketIn.bAck != 'A')
  {
    printf("[ERROR] SYS TIME SET\r\n");
    iErrNo = ERR_WRONG_ARG_FORMAT;
  }  
  return iErrNo;
}

JINT CmdSBleSysSsnSet(char *pSSN)
{
  JINT iErrNo = NO_ERR;

  PacketType    PacketOut;
  PacketAckType PacketIn;
  
  JINT 	iTimeout = CMD_TIMEOUT_200MS;
  JINT  iDevVersoin;
  char 	strDevName[256];  
  char 	msg[256];

  PacketInit(&PacketOut);
  
  /// output packet set
  PacketOut.bGroupId 	= CMD_GROUP_ID_SYS;
  PacketOut.bCmd 			= CMD_SYS_SSN_SET;
  PacketOut.bPCode 		= CMD_SYS_SSN_SET;
  PacketOut.wMOSILen 	= 32;
  PacketOut.wMISOLen 	= 0;
  
  UtilMemcpy((JBYTE *)&PacketOut.bData[0], (JBYTE *)&pSSN[0],  SSN_SIZE);

  /// slave packet Cmd
	iErrNo = SBlePacketSend(&PacketOut, &PacketIn, iTimeout);

	if(PacketIn.bAck != 'A')
  {
    printf("[ERROR] Version  NACK\r\n");
    iErrNo = ERR_WRONG_ARG_FORMAT;
  }

 	///-----------------------------------///
  /// COPY DATA
  ///-----------------------------------///		  

 	sprintf(msg, "\t [CMD][BLE] SET SSN ='%s'\r\n", (char *)&pSSN[0]);
  DBG_PRINTF(msg);
  
  return iErrNo;
}

JINT CmdSBleSysSsnGet(char *pStrSsn)
{
  JINT iErrNo = NO_ERR;

  PacketType    PacketOut;
  PacketAckType PacketIn;
  
  JINT 	iTimeout = CMD_TIMEOUT_200MS;
  JINT  iDevVersoin;
  char 	strDevName[256];  
  char 	msg[256];

  PacketInit(&PacketOut);
  
  /// output packet set
  PacketOut.bGroupId 	= CMD_GROUP_ID_SYS;
  PacketOut.bCmd 			= CMD_SYS_SSN_GET;
  PacketOut.bPCode 		= CMD_SYS_SSN_GET;
  PacketOut.wMOSILen 	= 0;
  PacketOut.wMISOLen 	= 32;
  
  /// slave packet Cmd
	iErrNo = SBlePacketSend(&PacketOut, &PacketIn, iTimeout);

	if(PacketIn.bAck != 'A')
  {
    printf("[ERROR] Version  NACK\r\n");
    iErrNo = ERR_WRONG_ARG_FORMAT;
  }

 	///-----------------------------------///
  /// COPY DATA
  ///-----------------------------------///		
  UtilMemcpy((JBYTE *)&pStrSsn[0], (JBYTE *)&PacketIn.bData[0], 32);


 	sprintf(msg, "\t[CMD][BLE] GET SSN='%s'\r\n", (char *)&pStrSsn[0]);
  DBG_PRINTF(msg);
  
  return iErrNo;
}

JINT CmdSBleVscModeTypeSet(void)
{
  JINT iErrNo = NO_ERR;

  PacketType    PacketOut;
  PacketAckType PacketIn;
  
  JINT 	  iTimeout = 3500;
  JDWORD  dwVscModeType = VSC_MODE_TYPE0;

  PacketInit(&PacketOut);
  
  /// output packet set
  PacketOut.bGroupId 	= CMD_GROUP_ID_BLE;
  PacketOut.bCmd 			= CMD_BLE_VSC_MODE_TYPE_SET;
  PacketOut.bPCode 		= CMD_BLE_VSC_MODE_TYPE_SET;
  PacketOut.wMOSILen 	= 20;
  PacketOut.wMISOLen 	= 0;

  UtilMemcpy((JBYTE *)&PacketOut.bCmdData[0], (JBYTE *)&dwVscModeType, 4);
  
  /// slave packet Cmd
	iErrNo = SBlePacketSend(&PacketOut, &PacketIn, iTimeout);

	if(PacketIn.bAck != 'A')
  {
    printf("[ERROR] VSC_MODE_MODE_SET NACK\r\n");
    iErrNo = ERR_WRONG_ARG_FORMAT;
  }
	
  return iErrNo;
}

JINT CmdSBleVscModeTypeGet(void)
{
  
  JINT iErrNo = NO_ERR;
	char strName[32];
	SRegType *pSReg = &GlobalVar.SReg;

  // get the vsc mode type
	UtilMemset((JBYTE *)&pSReg->strName[0], 0x00, SREG_NAME_SIZE);
	strcpy(pSReg->strName, SREG_VSC_MODE_TYPE);

  iErrNo = CmdSBleSRegRead(pSReg);
	if(iErrNo != NO_ERR)
	{					
		return  iErrNo;
	}	

  UtilMemcpy((JBYTE *)&VscModeCtl.dwVscModeType ,  (JBYTE *) &pSReg->bData[0], SREG_DATA_MEAS_VSC_MODE_TYPE_SIZE);       
  if(VscModeCtl.dwVscModeType == VSC_MODE_TYPE0)
	{
  	VscModeCtl.iChannelCount = VSC_MODE_CAHNNEL_COUNT;
	}
	else
	{
  	VscModeCtl.iChannelCount = 1;
	}
  return iErrNo;
}

JINT CmdSBleVscModeStart(void)
{
  JINT iErrNo = NO_ERR;

  PacketType    PacketOut;
  PacketAckType PacketIn;
  
  JINT 	iTimeout = 3500;

  PacketInit(&PacketOut);
  
  /// output packet set
  PacketOut.bGroupId 	= CMD_GROUP_ID_BLE;
  PacketOut.bCmd 			= CMD_BLE_VSC_MODE_START;
  PacketOut.bPCode 		= CMD_BLE_VSC_MODE_START;
  PacketOut.wMOSILen 	= 0;
  PacketOut.wMISOLen 	= 0;
  
  /// slave packet Cmd
	iErrNo = SBlePacketSend(&PacketOut, &PacketIn, iTimeout);

	if(PacketIn.bAck != 'A')
  {
    printf("[ERROR] VSC_MODE_START NACK\r\n");
    iErrNo = ERR_WRONG_ARG_FORMAT;
  }
	
  return iErrNo;
}

JINT CmdSBleVscModeStop(void)
{
  JINT iErrNo = NO_ERR;
  PacketType    PacketOut;
  PacketAckType PacketIn;
  JINT iTimeout = 3500;

  PacketInit(&PacketOut);
  
  /// output packet set
  PacketOut.bGroupId 	= CMD_GROUP_ID_BLE;
  PacketOut.bCmd 			= CMD_BLE_VSC_MODE_STOP;
  PacketOut.bPCode 		= CMD_BLE_VSC_MODE_STOP;
  PacketOut.wMOSILen 	= 0;
  PacketOut.wMISOLen 	= 0;
  
  /// slave packet Cmd
	iErrNo = SBlePacketSend(&PacketOut, &PacketIn, iTimeout);

	if(PacketIn.bAck != 'A')
  {
    printf("[ERROR] VSC_MODE_STOP NACK\r\n");
    iErrNo = ERR_WRONG_ARG_FORMAT;
  }
  return iErrNo;
}

JINT CmdSBleVscModeRead(void)
{
	char 	msg[256];
  JINT iErrNo = NO_ERR;
  JWORD wId = 0;
  JWORD wLen = 968;
   
  PacketType    PacketOut;
  PacketAckType PacketIn;
  
  VscModeControlType * pVscMode = NULL;
  JINT 	iTimeout = CMD_TIMEOUT_300MS;
  
	static JINT iErrCnt = 0;

  PacketInit(&PacketOut);
  
  pVscMode = &VscModeCtl;

  if(pVscMode->dwVscModeType == VSC_MODE_TYPE1)
  {
    wLen = 568;
  }
  
  /// output packet set
  PacketOut.bGroupId 	= CMD_GROUP_ID_BLE;
  PacketOut.bCmd 			= CMD_BLE_VSC_MODE_READ;
  PacketOut.bPCode 		= CMD_BLE_VSC_MODE_READ;
  PacketOut.wMOSILen 	= 8;
  PacketOut.wMISOLen 	= wLen;
  
  *(JWORD *)&PacketOut.bData[0] = VscModeCtl.wId;

  *(JDWORD *)&PacketOut.bData[4] = pVscMode->dwVscModeType;

  /// slave packet Cmd
	iErrNo = SBlePacketSend(&PacketOut, &PacketIn, iTimeout);
	if(PacketIn.bAck != 'A')
  {
    printf("[ERROR] VSC_MODE_READ NACK\r\n");
    iErrNo = ERR_WRONG_ARG_FORMAT;
    iErrCnt = iErrCnt + 1;
    return iErrNo;
  }
	
	if(PacketIn.wDataIdx  == VSC_MODE_IDX_INVALID)
	{		
		return iErrNo;
	}

	if(VscModeCtl.wId != PacketIn.wDataIdx)
	{
		sprintf(msg, "\t\t [BLE][WARNING] BLE_VSC_MODE_READ ID = %d\r\n", PacketIn.wDataIdx);
		DBG_PRINTF(msg);				
		return iErrNo;
	}	

	iErrCnt = 0;
	wId  = PacketIn.wDataIdx;
	wLen = PacketIn.wDataLen;
	
  if(pVscMode->dwVscModeType == VSC_MODE_TYPE1)
  {

  	VscModeType1Decode(wId, wLen, (JBYTE *)&PacketIn.bData[0]);
  }
  else
  {
  	VscModeDecode(wId, wLen, (JBYTE *)&PacketIn.bData[0]);
  }

  /// copy to main
  pVscMode = &GlobalVar.vscModeQueue[GlobalVar.iVscModeQueueTail];
  UtilMemcpy((JBYTE *)pVscMode, (JBYTE *)&VscModeCtl, sizeof(VscModeControlType));

  GlobalVar.iVscModeQueueTail = (GlobalVar.iVscModeQueueTail + 1) % VSC_MODE_ARR_LEN;
  GlobalVar.bVscModeAdded = TRUE;
	
	VscModeCtl.wId = (VscModeCtl.wId + 1) % VSC_MODE_IDX_MAX;		
  return iErrNo;
}

JINT CmdSBleMonitorMode(JINT *piMonitorMode)
{
  JINT iErrNo = NO_ERR;
  PacketType    PacketOut;
  PacketAckType PacketIn;
  JINT 	iTimeout = 3500;

  PacketInit(&PacketOut);
  
  /// output packet set
  PacketOut.bGroupId 	= CMD_GROUP_ID_BLE;
  PacketOut.bCmd 			= CMD_BLE_MONITOR_MODE;
  PacketOut.bPCode 		= CMD_BLE_MONITOR_MODE;
  PacketOut.wMOSILen 	= 0;
  PacketOut.wMISOLen 	= 4;
  
  /// slave packet Cmd
	iErrNo = SBlePacketSend(&PacketOut, &PacketIn, iTimeout);

	if(PacketIn.bAck != 'A')
  {
    printf("[ERROR]MEAS Stop NACK\r\n");
    iErrNo = ERR_WRONG_ARG_FORMAT;
  }
	UtilMemcpy((JBYTE *)piMonitorMode, (JBYTE *)&PacketIn.bData[0], 4);	
	printf("[BLE] MONITOR_MODE = %d\r\n", *piMonitorMode);
	
  return iErrNo;
}

JINT CmdSBleSRegRead(SRegType *pSReg)
{
  JINT iErrNo = NO_ERR;
  PacketType    PacketOut;
  PacketAckType PacketIn;
  JINT 	iTimeout = 500;

  PacketInit(&PacketOut);
  
  /// output packet set
  PacketOut.bGroupId 	= CMD_GROUP_ID_SREG;
  PacketOut.bCmd 			= CMD_SREG_READ;
  PacketOut.bPCode 		= CMD_SREG_READ;
  PacketOut.wMOSILen 	= SREG_NAME_SIZE;
  PacketOut.wMISOLen 	= SREG_SIZE;

  /// SReg Data Clear
  UtilMemset((JBYTE *) &pSReg->bData[0], 0x00, SREG_DATA_SIZE);
	
  /// SReg Name Set
  UtilMemcpy((JBYTE *) &PacketOut.bData[0],(JBYTE *)pSReg, SREG_NAME_SIZE);


  DBG_PRINTF("SREG-READ:START\r\n");  
  /// Slave packet Cmd Send
	iErrNo = SBlePacketSend(&PacketOut, &PacketIn, iTimeout);

  DBG_PRINTF("SREG-READ:END\r\n");  

	if(PacketIn.bAck != 'A')
  {
    printf("[ERROR] SREG READ NACK\r\n");
    iErrNo = ERR_WRONG_ARG_FORMAT;
  }  
  /// SReg Data Set
  UtilMemcpy((JBYTE *) &pSReg->bData[0],(JBYTE *)&PacketIn.bData[0], SREG_DATA_SIZE);
	
  return iErrNo;
}

JINT CmdSBleSRegWrite(SRegType *pSReg)
{
  JINT iErrNo = NO_ERR;
  PacketType    PacketOut;
  PacketAckType PacketIn;
  JINT 	iTimeout = 500;

  PacketInit(&PacketOut);
  
  /// output packet set
  PacketOut.bGroupId 	= CMD_GROUP_ID_SREG;
  PacketOut.bCmd 			= CMD_SREG_WRITE;
  PacketOut.bPCode 		= CMD_SREG_WRITE;
  PacketOut.wMOSILen 	= SREG_SIZE;
  PacketOut.wMISOLen 	= 0;

  /// SReg Name and Data Set
  UtilMemcpy((JBYTE *) &PacketOut.bData[0], (JBYTE *)pSReg, SREG_SIZE);
      
  /// slave packet Cmd
	iErrNo = SBlePacketSend(&PacketOut, &PacketIn, iTimeout);

	if(PacketIn.bAck != 'A')
  {
    printf("[ERROR] SREG WRITE NACK\r\n");
    iErrNo = ERR_WRONG_ARG_FORMAT;
  }
  return iErrNo;
}


