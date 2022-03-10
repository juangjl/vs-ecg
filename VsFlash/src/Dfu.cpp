/**
 * @file Dfu.cpp
 *
 *  Dfu function
 *
 *
 * @version $Revision$
 * @author JLJuang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021, VitalSigns Technology Co., Ltd., all rights reserved.
 */
#include "Global.h"

DfuDataType DfuData;



uint16_t btl_crc16(const uint8_t newByte, uint16_t prevResult)
{
  prevResult = (prevResult >> 8) | (prevResult << 8);
  prevResult ^= newByte;
  prevResult ^= (prevResult & 0xff) >> 4;
  prevResult ^= (prevResult << 8) << 4;

  prevResult ^= ((uint8_t) ((uint8_t) ((uint8_t) (prevResult & 0xff)) << 5))
                | ((uint16_t) ((uint8_t) ((uint8_t) (prevResult & 0xff))
                               >> 3) << 8);

  return prevResult;
}

uint16_t btl_crc16Stream(const uint8_t *buffer,
                         size_t        length,
                         uint16_t      prevResult)
{
  size_t position = 0;
  for (; position < length; position++) {
    prevResult = btl_crc16(buffer[position], prevResult);
  }

  return prevResult;
}

JWORD DfuCrcUpdate(JBYTE b, JWORD wCrc)
{
  JINT i = 0;
	JWORD wData = b;

  wCrc = wCrc ^ (JWORD)(wData << 8);
  for(i = 1; i <= 8; i++)
  {
  	if((wCrc & 0x800) != 0)
  	{
  	  wCrc = (wCrc << 1) ^ 0x1021;
  	}
  	else
  	{
  	  wCrc = wCrc << 1;
  	}
  }
  return wCrc;
}

JWORD DfuChksumGet(JBYTE *pbData)
{
  JINT	i 	 = 0;
  JWORD wCrc = 0;

	for(i = 0; i < DFU_DATA_SIZE; i = i + 1)
	{
	  wCrc = DfuCrcUpdate(pbData[i], wCrc);
	}
	return wCrc;
}


JBOOL DfuDataSet(DfuDataType *pDfuData, JBYTE bPacketNo, JBYTE *pbData)
{	  
  JWORD wCrc = 0;
  JBYTE bBuffer[DFU_DATA_SIZE];
	JWORD wCrc2 = 0;

  /// for transmit format header 
  pDfuData->start    = SOH;
  pDfuData->bPID  = bPacketNo;
  pDfuData->bPIDC = ~bPacketNo;


  UtilMemcpy((JBYTE *)&pDfuData->data[0], (JBYTE *)&pbData[0], DFU_DATA_SIZE);

  /// for transmit format chacksun (CRC)
  wCrc  = DfuChksumGet(&pDfuData->data[0]);
	wCrc2 = btl_crc16Stream(&pDfuData->data[0], DFU_DATA_SIZE, 0);

  pDfuData->CRCHHighByte = (JBYTE)(wCrc2 >> 8);
  pDfuData->CRCHLowByte  = (JBYTE)(wCrc2 & 0x00FF);

  return TRUE;
}
