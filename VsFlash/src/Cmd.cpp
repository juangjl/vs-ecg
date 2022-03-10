/**
 * @file cmd.cpp
 *
 *  Cmd
 *
 *
 * @version $Revision$
 * @author JLJuang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021, VitalSigns Technology Co., Ltd., all rights reserved.
 */
#include "Global.h"

///---------------------------------------------------------------------------------------------------------------------///
///
/// SYS: System command
///
///---------------------------------------------------------------------------------------------------------------------///
JINT CmdSysVersion(void)
{
  JINT iErrNo = NO_ERR;
  PacketType    PacketOut;
  PacketAckType PacketIn;
  JINT  iTimeout = CMD_TIMEOUT_100MS;
  char msg[256];
  
  JDWORD dwVersion;
  char strModelName[256];
    
  PacketInit(&PacketOut);   
  UtilMemset((JBYTE *)&PacketIn, 0x00, 64);

  PacketOut.bGroupId 	  = CMD_GROUP_ID_SYS;
  PacketOut.bCmd 			  = CMD_SYS_VER_GET;
  PacketOut.bPCode 		  = CMD_SYS_VER_GET;
  PacketOut.wMOSILen 	  = 0; ///< for BOOT CODE the packet shal >= 24
  PacketOut.wMISOLen 	  = 18;
  PacketOut.bCmdData[0] = CMD_SYS_VER_GET;

	PacketCheckSumSet(&PacketOut);
	  
  ///Packet command send  
  iErrNo = PacketSend(&PacketOut, &PacketIn, iTimeout);
  
  if(iErrNo != NO_ERR)
  {
    return iErrNo;
  }
  UtilDataPrint((JBYTE *)&PacketIn, PacketIn.wDataLen + PACKET_ACK_HEADER_SIZE);

  if(PacketIn.bAck != 'A')
  {
    sprintf(msg, "\t[CMD] SYS_VERSION READ ERROR\r\n");
    DBG_PRINTF(msg);
    return ERR_COMM_ISSUE;
  }
  
  /// Get Version
  dwVersion = *(JDWORD *)&PacketIn.bData[0];

  /// Get device Name
  UtilMemcpy((JBYTE *)&strModelName[0], (JBYTE *)&PacketIn.bData[4], 16);
  
  GlobalVar.iVersion = dwVersion;
  strcpy(GlobalVar.strModelName, strModelName);

	sprintf(msg, "\t Model    : %s\r\n", GlobalVar.strModelName);
  DBG_PRINTF(msg);
  /// print version
	sprintf(msg, "\t Version  : %d\r\n", GlobalVar.iVersion);
  DBG_PRINTF(msg);

	
	return iErrNo;
}

JINT CmdSysTimeSet(JTM *pJTM)
{
  JINT iErrNo = NO_ERR;
  PacketType    PacketOut;
  PacketAckType PacketIn;
  JINT iTimeout = CMD_TIMEOUT_100MS;
  char msg[256];
    
  PacketInit(&PacketOut);
  PacketAckInit(&PacketIn);
  
  ///  SET OUTPUT MODE
  PacketOut.bGroupId 	= CMD_GROUP_ID_SYS;
  PacketOut.bCmd 			= CMD_SYS_TIME_SET;
  PacketOut.bPCode 		= CMD_SYS_TIME_SET;
  PacketOut.wMOSILen 	= 16 + PACKET_CMD_BDATA_SIZE;
  PacketOut.wMISOLen 	= 0;

	///-----------------------------------------///
	/// Time Set
	///-----------------------------------------///
	*(JWORD *)&PacketOut.bCmdData[0] = (JWORD) pJTM->iYear;
	*(JBYTE *)&PacketOut.bCmdData[2] = (JBYTE) pJTM->iMonth;
	*(JBYTE *)&PacketOut.bCmdData[3] = (JBYTE) pJTM->iDay;
	*(JBYTE *)&PacketOut.bCmdData[4] = (JBYTE) pJTM->iHour;
	*(JBYTE *)&PacketOut.bCmdData[5] = (JBYTE) pJTM->iMin;
	*(JBYTE *)&PacketOut.bCmdData[6] = (JBYTE) pJTM->iSec;

  *(JINT  *)&PacketOut.bCmdData[8]  = (JINT) pJTM->t;
  *(JINT  *)&PacketOut.bCmdData[12] = pJTM->iTimeZoneSec ;

  PacketCheckSumSet(&PacketOut);

  ///Packet command send  
  iErrNo = PacketSend(&PacketOut, &PacketIn, iTimeout);
  if(PacketIn.bAck != 'A')
  {
    sprintf(msg, "\t [CMD] SYS_TIME_SET ERROR\r\n");
    DBG_PRINTF(msg);
    return ERR_COMM_ISSUE;
  }


  /// printf set time information
  sprintf(msg, "\t Time set : %04d/%02d/%02d-%02d:%02d:%02d\r\n",
                 pJTM->iYear,  pJTM->iMonth,  pJTM->iDay,
                 pJTM->iHour,  pJTM->iMin,    pJTM->iSec);
  DBG_PRINTF(msg);

	return iErrNo;
}

///-----------------------------------------------------------------------------------------------///
/// Device Firmware Update (DFU) Function
///-----------------------------------------------------------------------------------------------///
JINT CmdSysBootCodeEnter(void)
{
  JINT iErrNo = NO_ERR;
  
  PacketType    PacketOut;
  PacketAckType PacketIn;
  JINT iTimeout = CMD_TIMEOUT_100MS;
  char msg[256];

  PacketInit(&PacketOut);
  PacketAckInit(&PacketIn);
  
  /// setting the packet
  PacketOut.bPCode    = CMD_SYS_BOOTLOADER_ENTER;
  PacketOut.bGroupId  = CMD_GROUP_ID_SYS;
  PacketOut.bCmd      = CMD_SYS_BOOTLOADER_ENTER;
  PacketOut.wMOSILen  = 0;
  PacketOut.wMISOLen  = 0;

	PacketCheckSumSet(&PacketOut);
	  
  ///Packet command send  
  iErrNo = PacketSend(&PacketOut, &PacketIn, iTimeout);
  if(PacketIn.bAck != 'A')
  {
    sprintf(msg, "\t [CMD]BOOT CODE ENTER ERROR\r\n");
    DBG_PRINTF(msg);
    return ERR_COMM_ISSUE;
  }

  if(iErrNo != NO_ERR)
  {    
    return iErrNo;
  }
  return iErrNo;
}


JINT CmdBootSysVersion(void)
{
  JINT iErrNo = NO_ERR;
  PacketType    PacketOut;
  PacketAckType PacketIn;
  JINT  iTimeout = CMD_TIMEOUT_100MS;
  char msg[256];
  
  JDWORD dwVersion;
  char strModelName[256];
    
  PacketInit(&PacketOut);   
  UtilMemset((JBYTE *)&PacketIn, 0x00, 64);

  PacketOut.bGroupId 	  = CMD_GROUP_ID_SYS;
  PacketOut.bCmd 			  = CMD_SYS_VER_GET;
  PacketOut.bPCode 		  = CMD_SYS_VER_GET;
  PacketOut.wMOSILen 	  = 0; ///< for BOOT CODE the packet shal >= 24
  PacketOut.wMISOLen 	  = 18;
  PacketOut.bCmdData[0] = CMD_SYS_VER_GET;

	PacketCheckSumSet(&PacketOut);
	  
  ///Packet command send  
  iErrNo = PacketSendBootCode(&PacketOut, &PacketIn, iTimeout);
  
  if(iErrNo != NO_ERR)
  {
    return iErrNo;
  }
  UtilDataPrint((JBYTE *)&PacketIn, PacketIn.wDataLen + PACKET_ACK_HEADER_SIZE);

  if(PacketIn.bAck != 'A')
  {
    sprintf(msg, "\t[CMD] SYS_VERSION READ ERROR\r\n");
    DBG_PRINTF(msg);
    return ERR_COMM_ISSUE;
  }
  
  /// Get Version
  dwVersion = *(JDWORD *)&PacketIn.bData[0];

  /// Get device Name
  UtilMemcpy((JBYTE *)&strModelName[0], (JBYTE *)&PacketIn.bData[4], 16);
  
  GlobalVar.iVersion = dwVersion;
  strcpy(GlobalVar.strModelName, strModelName);

	sprintf(msg, "\t Model    : %s\r\n", GlobalVar.strModelName);
  DBG_PRINTF(msg);
  /// print version
	sprintf(msg, "\t Version  : %d\r\n", GlobalVar.iVersion);
  DBG_PRINTF(msg);

	
	return iErrNo;
}

JINT CmdDfuStart(void)
{
  JINT iErrNo = NO_ERR;
  PacketType    PacketOut;
  PacketAckType PacketIn;

  JINT  baudrate = 921600;

  JINT  iTimeout = CMD_TIMEOUT_100MS;

  /// execute command
  PacketInit(&PacketOut);

  ///  SET OUTPUT MODE
  PacketOut.bPCode   = CMD_UPGRADE_START;
  PacketOut.bGroupId = CMD_GROUP_ID_SYS;
  PacketOut.bCmd     = CMD_UPGRADE_START;
  PacketOut.wMOSILen = 1;
  PacketOut.wMISOLen = 0;
  
  PacketOut.bCmdData[0] = '1';

  iErrNo = PacketSendBootCode(&PacketOut, &PacketIn, iTimeout);
  if(iErrNo != NO_ERR)
  {
	  return iErrNo;
  }  

  return iErrNo;
}

JINT CmdDfuWrite(JBYTE *pbData)
{
  JINT iErrNo = NO_ERR;

  PacketType    PacketOut;
  PacketAckType PacketIn;

  /// execute command
  PacketInit(&PacketOut);
  PacketAckInit(&PacketIn);


  /// SET OUTPUT MODE
  PacketOut.bGroupId = CMD_GROUP_ID_SYS;
  PacketOut.bCmd     = CMD_UPGRADE_FILE_DATA;
  PacketOut.wMOSILen = sizeof(DfuDataType);
  PacketOut.wMISOLen = 1;

  memset(&PacketIn, 0, sizeof(PacketAckType));

  UtilMemcpy((JBYTE *)&PacketOut.bCmdData[0], (JBYTE *)&pbData[0], sizeof(DfuDataType));

  iErrNo = PacketSendBootCode(&PacketOut, &PacketIn, CMD_TIMEOUT_50MS);
  
  if(iErrNo != NO_ERR)
  {
    DBG_PRINTF("\t [CMD] [DFU] Write failed - 1\r\n");
	  return iErrNo;
  }
  
  if((PacketIn.bAck != 'A') || (PacketIn.bData[0] != XMODEM_CMD_ACK))
  {
    UtilDataPrint((JBYTE *)&PacketIn, 9);
    DBG_PRINTF("\t [CMD] [DFU] Write failed - 2\r\n");
    iErrNo = ERR_DFU_WRITE_FAIL;
    return iErrNo;
  }
  return iErrNo;  
}

JINT CmdDfuEnd(void)
{
  JINT iErrNo = NO_ERR;

  PacketType    PacketOut;
  PacketAckType PacketIn;

  JINT  iTimeout = CMD_TIMEOUT_100MS;

  /// execute command
  PacketInit(&PacketOut);

  ///  SET OUTPUT MODE
  PacketOut.bGroupId = CMD_GROUP_ID_SYS;
  PacketOut.bCmd = CMD_UPGRADE_END;
  PacketOut.wMOSILen = 1;
  PacketOut.wMISOLen = 0;
  PacketOut.bCmdData[0] = EOT;

  iErrNo = PacketSendBootCode(&PacketOut, &PacketIn, iTimeout);
  
  if(iErrNo != NO_ERR)
  {
	  return iErrNo;
  }

  ///-----------------------------------///
  /// COPY DATA
  ///-----------------------------------///		  

  return iErrNo;  
}
