/**
 * @file comPort.cpp
 *
 *   comport function for Windows
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

#ifdef ARCH_WIN32

#define COM_PORT_BUFFER_MAX  (10000)
typedef struct DevCPSt
{
	///--------------------------------------------------------///
	/// Com port setup
	///--------------------------------------------------------///
  HANDLE		hComm;				///< handler of com
	JINT 			iComPort; 		///< comport number
  JINT 			iBaudRate;		///< baudrate
	char 	    strName[32];
	///--------------------------------------------------------///
	/// Read / Write thread handle
	///--------------------------------------------------------///
  HANDLE 		hHandleRead;	///< handle for read  thread	
	HANDLE 		hHandleWrite;	///< handle for write thread

	///--------------------------------------------------------///
	/// Read / Write control
	///--------------------------------------------------------///
  JBYTE 		bReadStart;
  JBYTE 		bWriteStart;  
  JINT 			iReadLen;
  JINT 			iWriteLen;
  JDWORD 		dwTimeout;
  
	///--------------------------------------------------------///
	///  Data bffer
	///--------------------------------------------------------///  
	JBYTE 		pbReadBuf[COM_PORT_BUFFER_MAX];
	JBYTE 		pbWriteBuf[COM_PORT_BUFFER_MAX];	
} DevCPType;

DevCPType DevCP0;

#define COMPORT_THREAD_EXIT_CODE_EVENT_OK							(0)
#define COMPORT_THREAD_EXIT_CODE_EVENT_READ_FAILED		(10)
#define COMPORT_THREAD_EXIT_CODE_EVENT_WRITE_FAILED		(20)


JUINT ComPortReadThread(void* pObject)
{	
	DevCPType *pDevCP = (DevCPType *) pObject;
	
	static OVERLAPPED olRead;
	DWORD 	dwRead = 0;
  DWORD 	dwErr = 0;
	JDWORD 	dwExitCode = COMPORT_THREAD_EXIT_CODE_EVENT_OK;  

	///-------------------------------------------------------///
	/// create read event
	///-------------------------------------------------------///	
	memset(&olRead, 0, sizeof(OVERLAPPED));
	olRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if(olRead.hEvent == NULL)
  {
		dwExitCode = COMPORT_THREAD_EXIT_CODE_EVENT_READ_FAILED;
		return dwExitCode;
	}
	
  while(1)
  {
    if(pDevCP->bReadStart == TRUE)
    {
      if(ReadFile(pDevCP->hComm, pDevCP->pbReadBuf, pDevCP->iReadLen, &dwRead, &olRead))
      {
        dwExitCode = COMPORT_THREAD_EXIT_CODE_EVENT_OK;
        dwErr = 0;
      }
      else
      {
        if(WaitForSingleObject(olRead.hEvent, pDevCP->dwTimeout) == WAIT_OBJECT_0)
        {
          dwExitCode = GetOverlappedResult(pDevCP->hComm, &olRead, &dwRead, FALSE) ? 0 : 2;
          dwErr = 0;
        }
        else
        {
          dwErr = GetLastError();
          printf("GetLastError:%d,Size:%d,Read:%d, olRead:%d\r\n", dwErr, pDevCP->iReadLen, dwRead, olRead);
          dwExitCode = COMPORT_THREAD_EXIT_CODE_EVENT_READ_FAILED;
          PurgeComm(pDevCP->hComm, PURGE_RXABORT | PURGE_RXCLEAR);
        }
      }
      pDevCP->bReadStart = FALSE;
    }
    else
    {
      Sleep(1);
    }
  }

 	///-------------------------------------------------------///
	/// close read event
	///-------------------------------------------------------///	
  CloseHandle(olRead.hEvent);
 	
	return dwExitCode;
}


UINT ComPortWriteThread(void* pObject)
{
	DevCPType *pDevCP = (DevCPType *) pObject;
	
  static OVERLAPPED olWrite;
  DWORD dwWrite		= 0;
  DWORD dwErr 		= 0;
  DWORD dwErr2  	= 0;
  UINT dwExitCode  = COMPORT_THREAD_EXIT_CODE_EVENT_OK;
  
  // create read event
  memset(&olWrite,0,sizeof(OVERLAPPED));
  olWrite.hEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
  if(olWrite.hEvent==NULL)
  {
    dwExitCode = 1;  
	  return dwExitCode;
  }  
	if(pDevCP->iWriteLen > COM_PORT_BUFFER_MAX)
	{
		dwExitCode = COMPORT_THREAD_EXIT_CODE_EVENT_WRITE_FAILED;
		return dwExitCode;
	}
  if(WriteFile(pDevCP->hComm, pDevCP->pbWriteBuf, pDevCP->iWriteLen, &dwWrite, &olWrite))
  {
    dwExitCode = COMPORT_THREAD_EXIT_CODE_EVENT_OK;
  }  
  else 
  {
    dwErr = GetLastError();
    if(WaitForSingleObject(olWrite.hEvent, pDevCP->dwTimeout)==WAIT_OBJECT_0)
    {
      dwExitCode = GetOverlappedResult(pDevCP->hComm,&olWrite,&dwWrite,FALSE)? 0:2;
    }    
    else
    {
      dwErr2 = GetLastError();
      dwExitCode = COMPORT_THREAD_EXIT_CODE_EVENT_WRITE_FAILED;
      PurgeComm(pDevCP->hComm, (PURGE_TXABORT | PURGE_TXCLEAR));
    }
  }
  CloseHandle(olWrite.hEvent);
  return dwExitCode;
}

JBOOL ComPortWrite(DevCPType *pDevCP, JBYTE *pbWriteData,  JINT iWriteLen)
{
	JUINT 	dwID = 0;
	JDWORD dwExitCode = 0;
	
 	if(pDevCP->hComm == INVALID_HANDLE_VALUE)
  {
	  printf("[COM][WRITE][ERROR] COM port is not open\r\n");
    return FALSE;
  }
 	
	PurgeComm(pDevCP->hComm, (PURGE_TXABORT | PURGE_RXABORT));
	PurgeComm(pDevCP->hComm, (PURGE_TXCLEAR | PURGE_RXCLEAR));

	if(iWriteLen >= COM_PORT_BUFFER_MAX)
	{
		iWriteLen = COM_PORT_BUFFER_MAX;
		printf("[WARNING] COM port size  > %d\r\n", iWriteLen);
	}
	
	pDevCP->iWriteLen = iWriteLen;
	UtilMemcpy((JBYTE *)&pDevCP->pbWriteBuf[0], &pbWriteData[0], iWriteLen);
	
	pDevCP->hHandleWrite = (HANDLE)_beginthreadex( NULL, 0, &ComPortWriteThread, pDevCP, 0, &dwID);
	WaitForSingleObject(pDevCP->hHandleWrite, INFINITE);	
	GetExitCodeThread(pDevCP->hHandleWrite, &dwExitCode);

	if(dwExitCode != COMPORT_THREAD_EXIT_CODE_EVENT_OK)
	{
		return FALSE;
	}

  return TRUE;  	
}

JBOOL ComPortRead(DevCPType *pDevCP, JBYTE *pbReadData, JINT iReadLen, JINT iTimeout)
{  
	JBOOL bTimeout = FALSE;
	JINT iTimeoutCnt = 0;
	pDevCP->iReadLen = iReadLen;
	pDevCP->bReadStart = TRUE;

	while(1)
	{
		if(pDevCP->bReadStart == FALSE)
		{
			break;
		}
		Sleep(1);
		iTimeoutCnt = iTimeoutCnt + 1;
		if(iTimeoutCnt >= iTimeout)
		{
			bTimeout = TRUE;
			break;
		}
	}
	
	if(bTimeout == TRUE)
	{
		printf("[COM] [ERROR] failed to read data!!!\r\n");
		return FALSE;
	}
	UtilMemcpy((JBYTE *)&pbReadData[0], (JBYTE *)&pDevCP->pbReadBuf[0], iReadLen);
		
  return TRUE;        
}

JBOOL ComPortTransferEx(DevCPType *pDevCP, JBYTE *pbWriteData, JBYTE * pbReadData,  JINT iWriteLen, JINT iReadLen, JINT iTimeout)
{ 
	JBOOL bRet = TRUE;
	
	bRet = ComPortWrite(pDevCP, pbWriteData,  iWriteLen);
	if(bRet == FALSE)
	{
		return bRet;
	}
	
	if(iReadLen <= 0)
	{
		return bRet;
	}
	
	bRet = ComPortRead(pDevCP, pbReadData,  iReadLen, iTimeout);
	if(bRet == FALSE)
	{
		return bRet;
	}
	return TRUE;		
}

JBOOL ComPortTransfer(JBYTE *pbWriteData, JBYTE *pbReadData, JINT iWriteLen, JINT iReadLen, JINT iTimeout)
{
  JINT bRet = 0;
  DevCPType *pDevCP = &DevCP0;
   
	bRet = ComPortTransferEx(pDevCP, pbWriteData, pbReadData,  iWriteLen, iReadLen, iTimeout);
  return bRet;
  
  return bRet;
}

void ComPortSet(JINT iComPort)
{
	DevCPType *pDevCP = &DevCP0;
	char strName[256];

	///---------------------------------------------------------------------///
	/// Comport name set
	///---------------------------------------------------------------------///
  if(iComPort >= EXT_COM_NUM)
  {
    sprintf(strName,"\\\\.\\COM%d", iComPort);
  }
  else
  {
    sprintf(strName,"COM%d", iComPort);
  }
  
	strcpy(pDevCP->strName, strName);
}

void ComPortNameSet(char * strName)
{
	DevCPType *pDevCP = &DevCP0;
	char strCom[256];
	JINT iPort = 0;
	strcpy(strCom, strName);
	
	if(strlen(strCom) < 4)
	{
		printf("COM PORT NAME SET ERROR\r\n");
		return;
	}
	sscanf(&strCom[3], "%d", &iPort);
	ComPortSet(iPort);
  
}

void ComPortCloseEx(DevCPType *pDevCP)
{
	CloseHandle(pDevCP->hComm );
	pDevCP->hComm  = NULL;
}

JBOOL ComPortOpenEx(DevCPType *pDevCP)
{
  JINT 	iComNum 	= pDevCP->iComPort; 
	JINT 	iBaudRate = pDevCP->iBaudRate; 
	
	char 		comport[32];
  HANDLE 	hComm 	= INVALID_HANDLE_VALUE;
  DWORD 	dwErr  	= 0;

  DCB 		dcb;
  COMMTIMEOUTS cto;

  char msg[256];

  JUINT dwID = 0;

	///---------------------------------------------------------------------///
	/// Comport name set
	///---------------------------------------------------------------------///
	strcpy(comport, pDevCP->strName);

	printf("[COM] COM = '%s', Baudrate = %d\r\n", comport, iBaudRate);

  hComm = CreateFile(comport,
                     GENERIC_READ | GENERIC_WRITE,
                     0,    						/// comm devices must be opened w/exclusive-access
                     NULL, 						/// no security attributes
                     OPEN_EXISTING, 	/// comm devices must use OPEN_EXISTING
                     FILE_FLAG_OVERLAPPED,    /// not overlapped I/O
                     NULL  						/// hTemplate must be NULL for comm devices
                     );

  if(hComm == INVALID_HANDLE_VALUE) 
  {
    // Handle the error.
    printf ("CreateFile failed with error %d.\n", GetLastError());
    return FALSE;
  }

  // Fill in the DCB: baud=57,600 bps, 8 data bits, no parity, and 1 stop bit.
	memset(&dcb,0,sizeof(DCB));
	dcb.DCBlength 	= sizeof(DCB);
	dcb.fBinary 		= TRUE;
	dcb.fDtrControl = DTR_CONTROL_ENABLE;
	dcb.fRtsControl = RTS_CONTROL_ENABLE;

  dcb.BaudRate 		= iBaudRate;     ///< baud rate set
  dcb.ByteSize 		= 8;             ///< data size, xmit, and rcv
  dcb.Parity   		= NOPARITY;      ///< no parity bit
  dcb.StopBits 		= ONESTOPBIT;    ///< one stop bit

  if(!SetCommState(hComm, &dcb)) 
  {
		printf("\nSetCommState fail\r\n");
  	CloseHandle(hComm);
    return FALSE;
  }
  
  /// setting timeout
  cto.ReadIntervalTimeout        	= 0;
  cto.ReadTotalTimeoutMultiplier 	= 0;
  cto.ReadTotalTimeoutConstant   	= 3000;
  cto.WriteTotalTimeoutMultiplier = 0;
  cto.WriteTotalTimeoutConstant   = 3000;
  if(!SetCommTimeouts(hComm, &cto))
  {
  	printf("\n SetCommTimeouts fail\r\n");
  	CloseHandle(hComm);
  	return FALSE;

  }
  if(!EscapeCommFunction(hComm, RESETDEV))
  {
		printf("\nEscapeCommFunction fail\r\n");
  	CloseHandle(hComm);
    return FALSE;
  }

	if(!ClearCommError(hComm, &dwErr, NULL))
  {
		printf("\nClearCommError fail\r\n");
  	CloseHandle(hComm);
    return FALSE;
  }
	
  Sleep(300);

	PurgeComm(hComm, (PURGE_TXABORT | PURGE_RXABORT));
	PurgeComm(hComm, (PURGE_TXCLEAR | PURGE_RXCLEAR));

	//SetCommTimeouts(m_hComm, &CommTimeouts);
	pDevCP->hComm  = hComm;

  /// read thread
	pDevCP->hHandleRead = (HANDLE)_beginthreadex( NULL, 0, &ComPortReadThread, pDevCP, 0, &dwID);

  //ComDeviceTypeGet();
	sprintf(msg, "\t[COM] COM%d, baud rate = %d, open OK\r\n", pDevCP->iComPort, pDevCP->iBaudRate);
  DBG_PRINTF(msg);

  
  return TRUE;
}

void ComPortClose(void)
{
	DevCPType *pDevCP = &DevCP0;
	ComPortCloseEx(pDevCP);	
}

JBOOL ComPortOpen(void)
{
	DevCPType *pDevCP = &DevCP0;
	JBOOL bRet = FALSE;
	bRet = ComPortOpenEx(pDevCP);
	return bRet;
}

JBOOL ComPortInit(void)
{
	DevCPType *pDevCP = &DevCP0;
	
	pDevCP->iComPort  	= 8;
	pDevCP->iBaudRate 	= 921600;	
	pDevCP->hComm 			= INVALID_HANDLE_VALUE;

	pDevCP->bReadStart  = FALSE;
	pDevCP->bWriteStart = FALSE;		
	pDevCP->dwTimeout   = 1000;		
	
	return TRUE;
}

#endif /// <for ARCH_WIN32
