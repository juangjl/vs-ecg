/**
 * @file serial.h
 *
 *  serial function
 *
 * @version $Revision$
 * @author JLJuang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021, VitalSigns Technology Co., Ltd., all rights reserved.
 * @note
*/
#ifndef __SERIALPORT_H__
#define __SERIALPORT_H__ 

typedef struct DevSPSt
{
  int  fd; /// File descriptor for the port 
  char strName[32];
}  DevSPType;


#ifndef B921600
///-------------------------------------------///
/// MAC-OS don't have  no B921600
///-------------------------------------------///
#define  B921600   921600
#endif ///< for B921600

///--------------------------------------------------------------------///
/// Variable
///--------------------------------------------------------------------///
extern DevSPType DevSP0;


///--------------------------------------------------------------------///
/// Function
///--------------------------------------------------------------------///
extern JBOOL SerialPort0Write(JBYTE *pbWriteData,  JINT iWriteLen);
extern JBOOL SerialPort0Read(JBYTE *pbReadData,  JINT iReadLen, JINT iTimeout);
extern JBOOL SerialPort0Transfer(JBYTE *pbWriteData, JBYTE *pbReadData, JINT iWriteLen, JINT iReadLen, JINT iTimeout);
extern void  SerialPortNameSet(char *strPortName);
extern JBOOL SerialPortOpen(void);
extern void  SerialPortClose(void);
extern JBOOL SerialPortInit();

#ifdef ARCH_WIN32
#define SERIAL_PORT_NAME_SET    ComPortNameSet
#define SERIAL_PORT_CLOSE				ComPortClose
#define SERIAL_PORT_OPEN				ComPortOpen
#define SERIAL_PORT_TRANSFER		ComPortTransfer
#define SERIAL_PORT_INIT				ComPortInit
#else ///< for ARCH_WIN32
#define SERIAL_PORT_NAME_SET    SerialPortNameSet
#define SERIAL_PORT_CLOSE				SerialPortClose
#define SERIAL_PORT_OPEN				SerialPortOpen
#define SERIAL_PORT_TRANSFER		SerialPort0Transfer
#define SERIAL_PORT_INIT				SerialPortInit
#endif ///< for ARCH_WIN32

#endif ///<  __SERIALPORT_H__

