/**
 * @file BleCmd.h
 *
 *  Ble Related Command Header
 *
 * @version $Revision$
 * @author JL Juang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021,  VitalSigns Technology Co., LTD., all rights reserved.
 * @note
*/
#ifndef __BLECMD_H__
#define __BLECMD_H__

#include "Global.h"

///-------------------------------------------------------------------------------------///
/// Functions
///-------------------------------------------------------------------------------------///

///--------------------------------------------------------------------------------///
/// BLE: 
///			MBLE --> packet send to master
///     SBLE --> packet send to slave, shall be connected first
///--------------------------------------------------------------------------------///

///--------------------------------------------------------------------------------///
///			MBLE --> packet send for master 
///--------------------------------------------------------------------------------///
extern JINT CmdMBleScan(void);
extern JINT CmdMBleOpen(JBYTE *pbMacAddr);
extern JINT CmdMBleClose(void);
extern JINT CmdMBleConnectStatus(JBOOL *pbStatus);

///--------------------------------------------------------------------------------///
///		SBLE --> packet send to slave, shall be connected first
///--------------------------------------------------------------------------------///
extern JINT CmdSBleSysVersionGet(void);
extern JINT CmdSBleSysTimeSet(void);

extern JINT CmdSBleSysSsnGet(void);
extern JINT CmdSBleSysSsnSet(char *pSSN);

extern JINT CmdSBleVscModeStart(void);
extern JINT CmdSBleVscModeStop(void);
extern JINT CmdSBleVscModeRead(void);

extern JINT CmdSBleMonitorMode(JINT *piMonitorMode);

#endif ///< for __BLECMD_H__

