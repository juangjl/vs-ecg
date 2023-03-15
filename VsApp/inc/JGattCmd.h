/**
 * @file JGattCmd.h
 *
 *  JGATT Command
 *
 * @version $Revision$
 * @author JL Juang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021,  VitalSigns Technology Co., LTD., all rights reserved.
 * @note
*/
#ifndef __JGATT_CMD_H__
#define __JGATT_CMD_H__

#ifdef FEATURE_JGATT
//#if 1
#include "Global.h"

extern JBOOL  JGattPacketCmdSend(JINT iTimeout);
extern JBOOL  JGattPacketCmdDispatch(void);

extern JINT   CmdJGattSysVersionGet(void);
extern JINT   CmdJGattSysTimeSet(void);
extern JINT   CmdJGattVscModeTypeSet(void);
extern JINT   CmdJGattVscModeStart(void);
extern JINT   CmdJGattVscModeStop(void);
extern JINT   CmdJGattVscModeRead(void);

#endif ///< for  FEATURE_JGATT
#endif ///< __JGATT_CMD_H__
