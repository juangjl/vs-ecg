/**
 * @file Cmd.h
 *
 *  Command Definition
 *
 * @version $Revision$
 * @author JL Juang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021,  VitalSigns Technology CO., LTD., all rights reserved.
 * @note
*/
#ifndef __CMD_H__
#define __CMD_H__

#define CMD_TIMEOUT_50MS						(50)
#define CMD_TIMEOUT_100MS						(100)
#define CMD_TIMEOUT_200MS						(200)
#define CMD_TIMEOUT_300MS						(300)
#define CMD_TIMEOUT_500MS						(500)

///--------------------------------------------------------------------------------///
/// SYS: System function
///--------------------------------------------------------------------------------///
extern JINT CmdSysVersion(void);
extern JINT CmdSysTimeSet(JTM *pJTM);

extern JINT CmdSysBootCodeEnter(void);

extern JINT CmdBootSysVersion(void);
extern JINT CmdDfuStart(void);
extern JINT CmdDfuWrite(JBYTE *pbData);
extern JINT CmdDfuEnd(void);

#endif ///< for __CMD_H__

