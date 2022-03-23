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

extern JBOOL FuncBleOpenCheck(void);

extern JBOOL FuncVSDongleOpen(char *strPortName);
extern JBOOL FuncVSDongleClose(void);

extern JBOOL FuncVSDongleVersionGet(void);
extern JBOOL FuncVSDongleTimeSet(void);

extern JBOOL FuncMBleScan(void);
extern JBOOL FuncMBleSelect(void);

extern JBOOL FuncMBleOpen(void);
extern JBOOL FuncMBleOpenCheck(JINT iSec);

extern JBOOL FuncMBleClose(void);

extern JBOOL FuncSBleVersionGet(void);

/// VSC MODE
extern JBOOL FuncVscModeInit(void);
extern JBOOL FuncVscModeStart(void);
extern JBOOL FuncVscModeStop(void);
extern JBOOL FuncVscModeRead(JINT iSecTotal);

extern JBOOL FuncEcgFileDataGet(JINT iTimeMS, JDataSet *pDataSet);

extern JBOOL  FuncSRegRead(char *strRegName);
extern JBOOL  FuncSRegWrite(char *strRegName, JBYTE *pbData);

extern JBOOL FuncSerialPortDetect(void);

extern JBOOL FuncEcgFileDataLoad(char *pFilePath);
extern JBOOL FuncVscInfoDataLoad(char *pFilePath);

#endif ///< for __FUNC_H__
