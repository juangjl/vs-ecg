/**
 * @file Func.cpp
 *
 *  Function 
 *
 * @version $Revision$
 * @author JLJuang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021, VitalSigns Technology Co., Ltd., all rights reserved.
 */
#include "Global.h"

JBOOL FuncSerialPortOpen(char *strPortName)
{
	JBOOL bSerialOpen = FALSE;

	SERIAL_PORT_NAME_SET(strPortName);
	bSerialOpen = SERIAL_PORT_OPEN();
	if(bSerialOpen == TRUE)
	{
		GlobalVar.bSerialPortOpen = TRUE;		
	}
	else
	{
		GlobalVar.bSerialPortOpen = FALSE;
		return FALSE;
	}
	return TRUE;
}

JBOOL FuncSerialPortClose(void)
{
	JINT iErrNo = NO_ERR;
	JBOOL bRet = TRUE;

	JBOOL bConnect = FALSE;
	GlobalVar.bSerialPortOpen = FALSE;
	SERIAL_PORT_CLOSE();
	
	return bRet;
}

JBOOL FuncSerialFlush(void)
{
	SERIAL_PORT_FLUSH(64);
	return TRUE;
}


JBOOL FuncSysVersionGet(void)
{
	JINT iErrNo = NO_ERR;
	
	iErrNo = CmdSysVersion();
	
	if(iErrNo != NO_ERR)
	{
		return FALSE;
	}
	return TRUE;
}

JBOOL FuncSysTimeSet(void)
{
	JINT iErrNo = NO_ERR;
	time_t t = time(NULL);
	JTM jtm;
			
  JTMTimeZoneSecSet(&jtm, GlobalVar.iTimeZoneSec);
	JTMLocalTimeGet(&jtm, t);
	
	iErrNo = CmdSysTimeSet(&jtm);	

	if(iErrNo != NO_ERR)
	{
		return FALSE;
	}
	return TRUE;
}


///-----------------------------------------------------------------------------------------------///
/// DFU Function
///-----------------------------------------------------------------------------------------------///
JBOOL FuncBootCodeEnter(void)
{
	JINT iErrNo = NO_ERR;	
	
	/// Boot code enter
	iErrNo = CmdSysBootCodeEnter();
	if(iErrNo != NO_ERR)
	{
		return FALSE;
	}

	return TRUE;
}

JBOOL FuncDfuFileRead(void)
{
	char msg[256];
	char strFileName[256];
	JINT iFileSize		 = 0;
	JINT iFileSizeRead = 0;

	FILE *fp = NULL;

	ConfigStrGet((char *)CONFIG_ITEM_FILE_NAME, (char *) &strFileName[0]);

	///---------------------------------------------------------///
	/// File Check
	///---------------------------------------------------------///	
	if(UtilFileExisted(strFileName) == FALSE)
	{
		DBG_PRINTF("[ERROR] FILE not existed\r\n");
		return FALSE;
	}
	iFileSize = UtilFileSizeGet((char *)&strFileName[0]);

	///---------------------------------------------------------///
	/// File Open
	///---------------------------------------------------------///	
	fp = fopen(strFileName, "rb");
	if(fp == NULL)
	{
		DBG_PRINTF("[ERROR] failed to open the file\r\n");
		return FALSE;
	}

	///---------------------------------------------------------///
	/// File Read
	///---------------------------------------------------------///	
	if(GlobalVar.pFileData != NULL)
	{
		free(GlobalVar.pFileData);
		GlobalVar.pFileData = NULL;
	}
	GlobalVar.pFileData = (JBYTE *)malloc(iFileSize * (sizeof(JBYTE)));
	iFileSizeRead = fread((void *)&GlobalVar.pFileData[0] , 1, iFileSize, fp);	
	fclose(fp);

	///---------------------------------------------------------///
	/// check the read size
	///---------------------------------------------------------///
	if(iFileSizeRead != iFileSize)
	{
		free(GlobalVar.pFileData);
		GlobalVar.pFileData = NULL;
		DBG_PRINTF("[ERROR] failed to read the file\r\n");
		return FALSE;
	}
	GlobalVar.iFileSize = iFileSize;
	///---------------------------------------------------------///
	/// print information
	///---------------------------------------------------------///
	sprintf(msg ,"\t FILE_NAME = %s\r\n", strFileName);
	DBG_PRINTF(msg);
	sprintf(msg ,"\t FILE_SIZE = %d bytes\r\n", iFileSize);
	DBG_PRINTF(msg);

	return TRUE;
}

JBOOL FuncDfuStart(void)
{
	JINT iErrNo = NO_ERR;
	iErrNo = CmdDfuStart();
	if(iErrNo != NO_ERR)
	{
		return FALSE;
	}
	return TRUE;
}

JBOOL FuncDfuEnd(void)
{
	JINT iErrNo = NO_ERR;
	iErrNo = CmdDfuEnd();
	if(iErrNo != NO_ERR)
	{
		return FALSE;
	}
	return TRUE;
}

JBOOL FuncDfuWrite(void)
{
	JINT 	idx  = 0;
	JINT 	iLen = 0;
	JBYTE bData[DFU_DATA_SIZE];
	JBYTE bPacketNo = 1;
	JBOOL bRet = FALSE;
	JBYTE *pbBuffer 	= GlobalVar.pFileData;
	JINT 	iTotalSize 	= GlobalVar.iFileSize;
	JINT 	iProgress    = -1;
	JINT 	iProgressPre = -1;

	JINT iErrNo = NO_ERR;
	
	char 	msg[256];

	DfuDataType *pDfuData = &DfuData;
	while(1)
	{
		if((iTotalSize - idx) <= 0)
		{
			GlobalVar.fProgress = 100;
			break;
		}

		if(GlobalVar.bFlashStart == FALSE)
		{
			DBG_PRINTF("[ERROR] Flash write is end\r\n");
			CmdDfuEnd();
			SERIAL_PORT_FLUSH(64);
			return FALSE;
		}

		///----------------------------------------------------------------------------------------///
		/// DFU Data set
		///----------------------------------------------------------------------------------------///
		UtilMemcpy((JBYTE *)&bData[0], (JBYTE *)&pbBuffer[idx], DFU_DATA_SIZE);

		bRet = DfuDataSet(pDfuData, bPacketNo, &bData[0]);
		if(bRet == FALSE)
		{
			DBG_PRINTF("[ERROR] Data Set Failed\r\n");
			return FALSE;
		}

		///----------------------------------------------------------------------------------------///
		/// DFU Data write
		///----------------------------------------------------------------------------------------///
		iErrNo = CmdDfuWrite((JBYTE*)pDfuData);
		if(iErrNo != NO_ERR)
		{
			DBG_PRINTF("[ERROR] Data Write Failed\r\n");
			CmdDfuEnd();
			return FALSE;
		}

		bPacketNo = bPacketNo + 1;

		idx  = idx + DFU_DATA_SIZE;		
		iLen = iLen + DFU_DATA_SIZE;
		GlobalVar.fProgress = (JFLOAT) (iLen * 100) / iTotalSize;

		iProgress = GlobalVar.fProgress;

		if(iProgress != iProgressPre)
		{
			//sprintf(msg, "idx = 0x%06X,  PROGRESS = %-3d%%\r\n",  idx, iProgress);
			//DBG_PRINTF(msg);			
			iProgressPre = iProgress;
		}
	}

	return TRUE;
}
