/**
 * @file JGattState.h
 *
 *  JGATT State Machine Control
 *
 * @version $Revision$
 * @author JL Juang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021,  VitalSigns Technology Co., LTD., all rights reserved.
 * @note
*/
#ifndef __JGATT_STATE_H__
#define __JGATT_STATE_H__

#include "Global.h"

#ifdef FEATURE_JGATT

/// state machine
extern JBOOL  JGattStateSet(JINT iState);
extern JBOOL  JGattStateMain(void);

extern JBOOL  JGattStateEnd(void);
extern JBOOL  JGattStateRun(void);

#endif ///< for  FEATURE_JGATT
#endif ///< __JGATT_STATE_H__
