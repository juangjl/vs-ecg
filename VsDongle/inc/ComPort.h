/**
 * @file comPort.h
 *
 *  com port function for windows
 *
 * @version $Revision$
 * @author JLJuang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021, VitalSigns Technology Co., Ltd., all rights reserved.
 * @note
*/
#ifndef _COMPORT_H__
#define _COMPORT_H__ 

#ifdef ARCH_WIN32

#define EXT_COM_NUM                            (10)

extern JBOOL ComPortTransfer(JBYTE *pbWriteData, JBYTE *pbReadData, JINT iWriteLen, JINT iReadLen, JINT iTimeout);
extern void  ComPortSet(char * strName);
extern void  ComPortNameSet(char * strName);
extern void  ComPortClose(void);
extern JBOOL ComPortOpen(void);
extern JBOOL ComPortInit(void);


#endif /// <for ARCH_WIN32
#endif ///<  _COMPORT_H__

