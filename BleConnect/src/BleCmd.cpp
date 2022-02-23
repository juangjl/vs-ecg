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
JINT CmdSBleSysVersionGet(void)
{
  JINT iErrNo = NO_ERR;

  PacketType    PacketOut;
  PacketAckType PacketIn;
  
  JINT 	iTimeout = CMD_TIMEOUT_500MS;
  JINT  iDeviceVersion;
  char 	strDeviceName[256];  
  char 	msg[256];
  JINT iRetry = 0;

  PacketInit(&PacketOut);
  
  /// output packet set
  PacketOut.bGroupId 	= CMD_GROUP_ID_SYS;
  PacketOut.bCmd 			= CMD_SYS_VER_GET;
  PacketOut.bPCode 		= CMD_SYS_VER_GET;
  PacketOut.wMOSILen 	= 0;
  PacketOut.wMISOLen 	= 32;
  
  while(1)
  {
    /// slave packet Cmd
    iErrNo = SBlePacketSend(&PacketOut, &PacketIn, iTimeout);

    if(PacketIn.bAck != 'A')
    {      
      printf("\t [ERROR] Version  NACK, retry = %d, iErrNo = %d\r\n", iRetry, iErrNo);
      iErrNo = ERR_WRONG_ARG_FORMAT;
      iRetry = iRetry + 1;
      UtilMsSleep(30);
    }
    else
    {
      break;
    }
    if(iRetry == 3)
    {      
      sprintf(msg, "%s", "[ERROR] Version get command failed\r\n");
      DBG_PRINTF(msg);
      return iErrNo;
    }
  }

 	///-----------------------------------///
  /// COPY DATA
  ///-----------------------------------///		
  UtilMemcpy((JBYTE *)&iDeviceVersion,   (JBYTE *)&PacketIn.bData[0], sizeof(JINT));
  UtilMemcpy((JBYTE *)&strDeviceName[0], (JBYTE *)&PacketIn.bData[4], 28);
  strDeviceName[28] = 0;

 	sprintf(msg, "\t Model Name = %s, version = %d\r\n", strDeviceName, iDeviceVersion);
  DBG_PRINTF(msg);
  
  return iErrNo;
}

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
