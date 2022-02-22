/**
 * @file serialPort.cpp
 *
 *   serial port function for Mac and Linux
 *
 * @version $Revision$
 * @author JLJuang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021, VitalSigns Technology Co., Ltd.,, all rights reserved.
 * @note
*/


///------------------------------------------///
///  Include Area
///------------------------------------------///
#include "Global.h"

#ifndef ARCH_WIN32 ///< only mac and ubuntu

//#define SERIAL_PORT_USB0  "/dev/ttyUSB0"
#define SERIAL_PORT_USB0  "/dev/cu.SLAB_USBtoUART"

///------------------------------------------///
///  Function Area
///------------------------------------------///

DevSPType DevSP0;

JBOOL SerialPortFlush(DevSPType *pDevSP)
{
  if(pDevSP->fd == -1)
  {   
    return FALSE;
  }
  tcflush(pDevSP->fd, TCIOFLUSH);
   return TRUE;  
}

JBOOL SerialPortCloseEx(DevSPType *pDevSP)
{
	close(pDevSP->fd);
	return TRUE;
}

JBOOL SerialPortOpenEx(DevSPType *pDevSP)
{
  int fd; /// File descriptor for the port 
  
  pDevSP->fd = open(pDevSP->strName, O_RDWR | O_NOCTTY | O_NDELAY);
  if(pDevSP->fd == -1)
  {
    ///---------------------------------------------------------///    
    /// Could not open the port.
    ///---------------------------------------------------------///
    printf("[ERROR] open_port: Unable to open '%s'\r\n", pDevSP->strName);
    return FALSE;
  }
  else
  {
    fcntl(fd, F_SETFL, 0);
  }
  return TRUE;
}

JBOOL SerialPortSetup(DevSPType *pDevSP)
{  
  struct termios tty;
  
  if(pDevSP->fd == -1)
  {
    return FALSE;
  }

  if(tcgetattr(pDevSP->fd, &tty)!= 0)
  {
    printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
    return FALSE;
  }

  /// 8-bit
  tty.c_cflag |= CS8; // 8 bits per byte (most common)
  /// no parity bit
  tty.c_cflag &= ~PARENB;
  /// 1 stop bit
  tty.c_cflag &= ~CSTOPB;  // Clear stop field, only one stop bit used in communication (most common)
  
  
  /// no flow control
  tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
  
  tty.c_cflag |= CREAD | CLOCAL;

  tty.c_lflag &= ~ICANON;
  tty.c_lflag &= ~ECHO;   ///< Disable echo
  tty.c_lflag &= ~ECHOE;  ///< Disable erasure
  tty.c_lflag &= ~ECHONL; ///< Disable new-line echo

  tty.c_lflag &= ~ISIG; 

  cfsetispeed(&tty, B921600);
  cfsetospeed(&tty, B921600);
  
  tcsetattr(pDevSP->fd, TCSANOW, &tty);

  return TRUE;
}

JBOOL SerialPortSetupPrint(DevSPType *pDevSP)
{
  struct termios tty;

  if(pDevSP->fd == -1)
  {
    return FALSE;
  }

  if(tcgetattr(pDevSP->fd, &tty)!= 0)
  {
    printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
    return FALSE;
  }

  printf("\r\n");
  printf("-----------------------------------------\r\n");
  printf("\t CFLAG  = %08X\r\n",  (JDWORD)tty.c_cflag);
  printf("\t LFLAG  = %08X\r\n",  (JDWORD)tty.c_lflag);  
  printf("\t ISPEED = %08X\r\n",  (JDWORD)tty.c_ispeed);    
  printf("\t OSPEED = %08X\r\n",  (JDWORD)tty.c_ospeed);      
  printf("-----------------------------------------\r\n"

  return TRUE;
}

JBOOL SerialPortBlockSet(DevSPType *pDevSP, JBOOL bBlock)
{
  if(pDevSP->fd == -1)
  {   
    return FALSE;
  }

  if(bBlock == FALSE)
  {
    /// non-Blocking
    fcntl(pDevSP->fd, F_SETFL, FNDELAY);
  }
  else
  {
    /// Blocking
    fcntl(pDevSP->fd, F_SETFL, 0);
  }
  return FALSE;
}

JBOOL SerialPortClose(DevSPType *pDevSP)
{
  if(pDevSP->fd == -1)
  {   
    return FALSE;
  }
  
  close(pDevSP->fd);
  pDevSP->fd = -1;
  return TRUE;  
}

JBOOL SerialPortWrite(DevSPType *pDevSP, JBYTE *pbWriteData,  JINT iWriteLen)
{
  JINT iCnt = 0;
  char msg[256];

  if(pDevSP->fd == -1)
  {   
    return FALSE;
  }
  
  iCnt = write(pDevSP->fd, pbWriteData, iWriteLen);
  
  if(iCnt != iWriteLen)
  {  
	  sprintf(msg, "[SERIAL][ERROR][WRITE]  %d bytes FAILED, Write Cnt = %d, FD = %d\n", iWriteLen, iCnt, pDevSP->fd);    
   	DBG_PRINTF(msg);
    return FALSE;
  }
  
  return TRUE;
}

JBOOL SerialPortRead(DevSPType *pDevSP, JBYTE *pbReadData, JINT iReadLen, JINT iTimeout)
{  
  JINT  iRdLen   = 0;
  JINT  iRdTotal = 0;  
  JBOOL bTimeout = FALSE;
	JINT iTimeoutCnt  = 0;
  JBYTE bData[4096];

  if(pDevSP->fd == -1)
  {   
    return FALSE;
  }
  
  while(1)
  {
    iRdLen = read(pDevSP->fd, (void *) &bData[0], sizeof(bData));
    if(iRdLen > 0)
    {
      UtilMemcpy((JBYTE *)&pbReadData[iRdTotal], (JBYTE *)&bData[0], iRdLen);
      iRdTotal = iRdTotal + iRdLen;      
    }
    else
    {
   		UtilMsSleep(1);
   		iTimeoutCnt = iTimeoutCnt + 1;
    }
    if(iTimeoutCnt >= iTimeout)
  	{
  		bTimeout = TRUE;
  		break;
  	}
    if(iRdTotal >= iReadLen)
    {
      break;
    }
  } 
  if(iTimeoutCnt == TRUE)
	{
		printf("[SERIAL][ERROR] port read time out");
		return FALSE;
	}
  return TRUE;        
}


JBOOL SerialPort0Write(JBYTE *pbWriteData,  JINT iWriteLen)
{
  JINT bRet = 0;
  DevSPType *pDevSP = &DevSP0;
   
	bRet = SerialPortWrite(pDevSP, pbWriteData,  iWriteLen);;
  return bRet;
}

JBOOL SerialPort0Read(JBYTE *pbReadData,  JINT iReadLen, JINT iTimeout)
{
  JINT bRet = 0;
  DevSPType *pDevSP = &DevSP0;
   
	bRet = SerialPortRead(pDevSP, pbReadData, iReadLen, iTimeout);
  return bRet;
}

JBOOL SerialPortTransfer(DevSPType *pDevSP, JBYTE *pbWriteData, JBYTE * pbReadData,  JINT iWriteLen, JINT iReadLen, JINT iTimeout)
{ 
	JBOOL bRet = TRUE;

	if(pDevSP->fd == -1)
  {   
    return FALSE;
  }
  
	bRet = SerialPortWrite(pDevSP, pbWriteData,  iWriteLen);
	if(bRet == FALSE)
	{
		return bRet;
	}
	if(iReadLen <= 0)
	{
		return bRet;
	}
	
	bRet = SerialPortRead(pDevSP, pbReadData,  iReadLen, iTimeout);
	if(bRet == FALSE)
	{
		return bRet;
	}
	return TRUE;		
}

JBOOL SerialPort0Transfer(JBYTE *pbWriteData, JBYTE *pbReadData, JINT iWriteLen, JINT iReadLen, JINT iTimeout)
{
  JINT bRet = 0;
  DevSPType *pDevSP = &DevSP0;

  if(pDevSP->fd == -1)
  {   
    return FALSE;
  }
     
	bRet = SerialPortTransfer(pDevSP, pbWriteData, pbReadData,  iWriteLen, iReadLen, iTimeout);
  return bRet;
}

void SerialPortNameSet(char *strPortName)
{
  DevSPType *pDevSP = &DevSP0;
  strcpy((char *)&pDevSP->strName[0], strPortName);
}

void SerialPortClose(void)
{
	DevSPType *pDevSP = &DevSP0;
  ///----------------------------------------------------------///
  /// Serial port open
  ///----------------------------------------------------------///
  SerialPortClose(pDevSP);
}
  
JBOOL SerialPortOpen(void)
{
  char msg[256];
	DevSPType *pDevSP = &DevSP0;
	JBOOL bRet = TRUE;
  ///----------------------------------------------------------///
  /// Serial port open
  ///----------------------------------------------------------///
  bRet = SerialPortOpenEx(pDevSP);
  if(bRet == FALSE)
	{
		sprintf(msg, "Serial port %s open --> failed\r\n", pDevSP->strName);
		DBG_PRINTF(msg);  
		return FALSE;
	}
  SerialPortBlockSet(pDevSP,  FALSE);  
  SerialPortFlush(pDevSP);
  SerialPortSetup(pDevSP);  
  SerialPortSetupPrint(pDevSP);
  return TRUE;
}

JBOOL SerialPortInit()
{
  DevSPType *pDevSP = &DevSP0;
  strcpy((char *)&pDevSP->strName[0], SERIAL_PORT_USB0);
  return TRUE;
}

#endif /// <for ARCH_WIN32

