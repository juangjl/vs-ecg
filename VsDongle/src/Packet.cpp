/**
 * @file Packet.cpp
 *
 *  Packet Control
 *
 * @version $Revision$
 * @author JLJuang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021, VitalSigns Technology Co., Ltd., all rights reserved.
 * @note
*/
#include "Global.h"

int PcodeIdx = 0;

void  PacketPrint(PacketType *pPacket)
{
	JBYTE *pbData 	 = (JBYTE *)pPacket;
	JINT 	 iTotalCnt = PACKET_CMD_HEADER_SIZE + pPacket->wMOSILen;	
	
	if(iTotalCnt > 256)
	{
		iTotalCnt = 256;
	}
	UtilDataPrint(pbData, iTotalCnt);			
}

void  PacketAckPrint(PacketAckType *pPacket)
{
	JBYTE *pbData 	 = (JBYTE *)pPacket;
	JINT 	 iTotalCnt = PACKET_CMD_HEADER_SIZE + pPacket->wDataLen;	
	
	if(iTotalCnt > 256)
	{
		iTotalCnt = 256;
	}
	UtilDataPrint(pbData, iTotalCnt);			
}

///-------------------------------------------------------------------///
/// Packet Control
///-------------------------------------------------------------------///
JVOID PacketInit(PacketType *pPacket)
{
	JINT i;
	JBYTE *pbData = (JBYTE *)pPacket;
	for(i = 0 ; i < sizeof(PacketType) ; i = i + 1)
	{
		pbData[i] = 0;
	}
  pPacket->bPCode = PcodeIdx;
  PcodeIdx++;
  
}

void PacketAckChkSumSet(PacketAckType *pPacketAck, JWORD wMISO)
{
	JINT 	i;

	JBYTE bCheckSum = 0x00;
	JBYTE *pbData   = (JBYTE *)pPacketAck;
	JWORD wWrtLen   = wMISO + PACKET_CMD_HEADER_SIZE;
	pPacketAck->bChkSum = 0;

	for(i = 0 ; i < wWrtLen; i++)
	{			
		if(i == 3)
		{
			continue;
		}
		bCheckSum = bCheckSum + pbData[i];
	}
	
	pPacketAck->bChkSum = bCheckSum;	
}

JBYTE PacketCheckSumGet(PacketType *pPacket)
{
	JINT 		i;
	JBYTE  	bCheckSum = 0x00;
	JBYTE * pbData = (JBYTE *)pPacket;
	for(i = 0 ; i < pPacket->wMOSILen + PACKET_CMD_HEADER_SIZE; i = i + 1)
	{
		bCheckSum += pbData[i];
	}
	return bCheckSum;
}

JVOID PacketCheckSumSet(PacketType *pPacket)
{	
	JBYTE bCheckSum = 0;
	pPacket->bCheckSum = 0;
	bCheckSum = PacketCheckSumGet(pPacket);
	pPacket->bCheckSum =  bCheckSum;	
}

JINT PacketSend(PacketType * pPacketOut, PacketAckType * pPacketIn, int iTimeout)
{
  JINT errNo = NO_ERR;
	static JWORD wSend = 0;
	JBOOL bRet = FALSE;
  JINT 	iWriteLen = 0;
  JINT 	iReadLen = 0;
  
	PacketCheckSumSet(pPacketOut);

  iWriteLen = pPacketOut->wMOSILen + PACKET_ACK_HEADER_SIZE;
  iReadLen  = pPacketOut->wMISOLen + PACKET_ACK_HEADER_SIZE;
	bRet 		  = SERIAL_PORT_TRANSFER((JBYTE *)pPacketOut, (JBYTE *)pPacketIn,  iWriteLen, iReadLen, iTimeout);
  if(bRet == FALSE)
	{
    return ERR_MASTER_CONN_FAIL;
	}					    
  return errNo;
}


