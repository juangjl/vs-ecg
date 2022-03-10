/**
 * @file Func.h
 *
 *  Function Definition
 *
 * @version $Revision$
 * @author JL Juang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021,  VitalSigns Technology CO., LTD., all rights reserved.
 * @note
*/
#ifndef __FUNC_H__
#define __FUNC_H__

extern JBOOL FuncSerialPortOpen(char *strPortName);
extern JBOOL FuncSerialPortClose(void);

extern JBOOL FuncSysVersionGet(void);
extern JBOOL FuncSysTimeSet(void);

extern JBOOL FuncBootCodeEnter(void);
extern JBOOL FuncDfuFileRead(void);

extern JBOOL FuncDfuStart(void);
extern JBOOL FuncDfuEnd(void);
extern JBOOL FuncDfuWrite(void);


#endif ///< for __FUNC_H__
