/**
 * @file Task.h
 *
 *  Task function
 *
 * @version $Revision$
 * @author JLJuang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021, VitalSigns Technology Co., Ltd., all rights reserved.
 * @note
*/
#ifndef __TASK_H__
#define __TASK_H__ 

extern void 	TaskRoundInit(void);

extern void   TaskSerialPort(void);

extern void   TaskBleSReg(void);

extern void   TaskBleControl(void);

extern void   TaskBleState(void);

extern void   TaskBleVscMode(void);

extern void 	TaskRoundEnd(void);

extern void   MainLoopStart(void);
extern void   SubLoopStart(void);

extern void   MainLoop(void);
extern void   SubLoop(void);

#endif ///<  __TASK_H__
