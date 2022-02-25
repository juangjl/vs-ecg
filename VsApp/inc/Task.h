/**
 * @file Task.h
 *
 *  task function
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

extern void   TaskVsDongleOpen(void);

extern void   TaskVSH101Open(void);

extern void   TaskVSH101Read(void);

extern void   TaskVSH101Close(void);

extern void   TaskVsDongleClose(void);

extern void 	TaskRoundEnd(void);

#endif ///<  __TASK_H__
