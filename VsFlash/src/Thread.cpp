/**
 * @file Thread.cpp
 *
 *  Thread function
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

void * ThreadDFUWrite(void *arg)
{
	char msg[256];
  JBOOL bRet = FALSE;
  if( GlobalVar.bDFUWriteOn == TRUE)
  {
    pthread_exit(NULL);
	  return NULL;
  }

  GlobalVar.bDFUWriteOn = TRUE;

  bRet = FuncDfuWrite();		
  if(bRet == FALSE)
  {
    sprintf(GlobalVar.strFlashMsg, "%s", "[ERROR] Failed to write DFU\r\n");
    GlobalVar.iState = JSTATE_ERROR;
  }
  UtilMsSleep(100);
  GlobalVar.iState = JSTATE_DFU_END;		

	pthread_exit(NULL);
	return NULL;
}

