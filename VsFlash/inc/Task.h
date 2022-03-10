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

extern void   TaskApp(void);

extern void   TaskSerialPort(void);

extern void   TaskControl(void);

extern void   TaskState(void);

extern void 	TaskRoundEnd(void);

#endif ///<  __TASK_H__
