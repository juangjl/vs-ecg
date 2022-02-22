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
  JINT  iTimeout = 1000;
  char msg[256];
  JDWORD dwVersion;
    
  PacketInit(&PacketOut);
  
  ///  SET OUTPUT MODE
  PacketOut.bGroupId 	  = CMD_GROUP_ID_SYS;
  PacketOut.bCmd 			  = CMD_SYS_VER_GET;
  PacketOut.bPCode 		  = CMD_SYS_VER_GET;
  PacketOut.wMOSILen 	  = 0;
  PacketOut.wMISOLen 	  = 4;
  PacketOut.bCmdData[0] = CMD_SYS_VER_GET;

	PacketCheckSumSet(&PacketOut);
	  
  ///Packet command send  
  iErrNo = PacketSend(&PacketOut, &PacketIn, iTimeout);
  if(PacketIn.bAck != 'A')
  {
    sprintf(msg, "\t[CMD] SYS_VERSION READ ERROR\r\n");
    DBG_PRINTF(msg);
    return ERR_COMM_ISSUE;
  }
  dwVersion = *(JDWORD *)&PacketIn.bData[0];

  /// print version
	sprintf(msg, "Version  : %d\r\n", dwVersion);
  DBG_PRINTF(msg);
	
	return iErrNo;
}

JINT CmdSysTimeSet(JTM *pJTM)
{
  JINT iErrNo = NO_ERR;
  PacketType    PacketOut;
  PacketAckType PacketIn;
  JINT iTimeout = 1000;
  char msg[256];
  
  PacketInit(&PacketOut);
  
  ///  SET OUTPUT MODE
  PacketOut.bGroupId 	= CMD_GROUP_ID_SYS;
  PacketOut.bCmd 			= CMD_SYS_TIME_SET;
  PacketOut.bPCode 		= CMD_SYS_TIME_SET;
  PacketOut.wMOSILen 	= 24;
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


	PacketCheckSumSet(&PacketOut);
	  
  ///Packet command send  
  iErrNo = PacketSend(&PacketOut, &PacketIn, iTimeout);
  if(PacketIn.bAck != 'A')
  {
    sprintf(msg, "\t[CMD] SYS_TIME_SET ERROR\r\n");
    DBG_PRINTF(msg);
    return ERR_COMM_ISSUE;
  }

  /// printf set time information
  sprintf(msg, "Time set : %04d/%02d/%02d-%02d:%02d:%02d\r\n",
                 pJTM->iYear,  pJTM->iMonth,  pJTM->iDay,
                 pJTM->iHour,  pJTM->iMin,    pJTM->iSec);
  DBG_PRINTF(msg);

	return iErrNo;
}


