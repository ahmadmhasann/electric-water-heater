

/* 
 * File: scheduler.h
 * Author: Ahmed Hassan
 * Created : July 7, 2020 
 */

#ifndef SCHEDULER_H
#define	SCHEDULER_H

#include <xc.h>   
#define SCH_MAX_TASKS 4

typedef struct data {
    /*Pointer to the task (must be a 'void (void)' function)*/
    void (*taskFunction)(void);
    /*Delay (ticks) until the function will (next) be run*/
    u32 delay;
    /*Interval (ticks) between subsequent runs.*/
    u32 period;
    /*Incremented (by scheduler) when task is due to execute*/
    u32 runMe;
} sTask;

void sch_vid_dispatch_tasks(void);
u8 sch_u8_add_task(void ( * pFunction)(),
        const u32 DELAY,
        const u32 PERIOD);
void sch_vid_init(void);
void sch_vid_delete_task(u8 index);
void sch_update(void);

#endif

