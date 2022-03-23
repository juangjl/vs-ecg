/**
 * @file Timer.h
 *
 *  Timer control library
 *
 * @version $Revision$
 * @author JLJuang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021, VitalSigns Technology Co., Ltd., all rights reserved.
 * @note
*/
#ifndef __TIMER_H__
#define __TIMER_H__ 

#define TIMER_FREQ        (100)
#define TIMER_PERIOD_MS   (1000 / TIMER_FREQ)
#define TASK_PERIOD_MS    (50)

extern void TimerTick(void);
extern void TimerEventSet(void);
extern void TimerEventClear(void);

extern void TimerStart(void);

#endif ///<  __TIMER_H__

