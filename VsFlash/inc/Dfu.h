/**
 * @file DFU.h
 *
 *  DFU Definition
 *
 * @version $Revision$
 * @author JL Juang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021,  VitalSigns Technology CO., LTD., all rights reserved.
 * @note
*/
#ifndef __DFU_H__
#define __DFU_H__

///=====================================================================///  
///  DFU control code
///=====================================================================///
#define NUL                 (0x00)
#define SOH                 (0x01)
#define STX                 (0x02)
#define ETX                 (0x03)
#define EOT                 (0x04)
#define ENQ                 (0x05)
#define ACK                 (0x06)
#define BEL                 (0x07)
#define BS                  (0x08)
#define HT                  (0x09)
#define LF                  (0x0A)
#define VT                  (0x0B)
#define FF                  (0x0C)
#define CR                  (0x0D)
#define NAK                 (0x15)
#define ETB                 (0x17)
#define CAN                 (0x18)
#define ASCII_C             (0x43)

///=====================================================================///  
///  XMODEM_CMD
///=====================================================================///
/// Start of Header
#define XMODEM_CMD_SOH                (0x01)
/// End of Transmission
#define XMODEM_CMD_EOT                (0x04)
/// Acknowledge
#define XMODEM_CMD_ACK                (0x06)
/// Not Acknowledge
#define XMODEM_CMD_NAK                (0x15)
/// Cancel
#define XMODEM_CMD_CAN                (0x18)
/// Ctrl+C
#define XMODEM_CMD_CTRL_C             (0x03)
/// ASCII 'C'
#define XMODEM_CMD_C                  (0x43)

///=====================================================================///  
///  DFU  DATA
///=====================================================================///
#define DFU_DATA_SIZE       (128)

#pragma pack(push)
#pragma pack(1)

typedef struct DfuDataSt
{
  JBYTE start;
  JBYTE bPID;
  JBYTE bPIDC;
  JBYTE data[DFU_DATA_SIZE];
  JBYTE CRCHHighByte;
  JBYTE CRCHLowByte;
} DfuDataType;

#pragma pack(pop)

extern DfuDataType DfuData;
extern JWORD DfuChksumGet(JBYTE *pbData);
extern JBOOL DfuDataSet(DfuDataType *pDfuData, JBYTE bPacketNo, JBYTE *pbData);

#endif ///< for __CMD_H__

