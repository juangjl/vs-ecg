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

JBOOL FuncVSDongleOpen(char *strPortName)
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

JBOOL FuncVSDongleClose(void)
{
	JINT iErrNo = NO_ERR;
	JBOOL bRet = TRUE;

	JBOOL bConnect = FALSE;
	GlobalVar.bSerialPortOpen = FALSE;
	SERIAL_PORT_CLOSE();
	
	return bRet;
}

JBOOL FuncVSDongleVersionGet(void)
{
	JINT iErrNo = NO_ERR;
	
	iErrNo = CmdSysVersion();
	
	if(iErrNo != NO_ERR)
	{
		return FALSE;
	}
	return TRUE;
}

JBOOL FuncVSDongleTimeSet(void)
{
	JINT iErrNo = NO_ERR;
	time_t t = time(NULL);
	JTM jtm;
		
	UtilLocalTime(&jtm, t);
	iErrNo = CmdSysTimeSet(&jtm);	
	if(iErrNo != NO_ERR)
	{
		return FALSE;
	}
	return TRUE;
}
