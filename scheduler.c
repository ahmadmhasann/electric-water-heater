

/* 
 * File: scheduler.c
 * Author: Ahmed Hassan
 * Created : July 7, 2020 
 */

#define _XTAL_FREQ 8000000 
#include <xc.h>
#include "types.h"
#include "macros.h"
#include "dio.h"
#include "scheduler.h"
#include "timer.h"

sTask sch_tasks[SCH_MAX_TASKS];

void sch_vid_init(void) {
    u8 i;
    for (i = 0; i < SCH_MAX_TASKS; i++) {
        sch_vid_delete_task(i);
    }
    timer_vid_set_isr_0(sch_update);
    timer_vid_init_0(8, 1);

}

void sch_update(void) {
    u8 index;
    for (index = 0; index < SCH_MAX_TASKS; index++) {
        /*Check if there is a task at this location*/
        if (sch_tasks[index].taskFunction) {
            if (sch_tasks[index].delay == 0) {
                // The task is due to run
                sch_tasks[index].runMe += 1; // Inc. the 'RunMe' flag
                if (sch_tasks[index].period) {
                    /*Schedule periodic tasks to run again*/
                    sch_tasks[index].delay = sch_tasks[index].period;
                }
            } else {
                /*Not yet ready to run: just decrement the delay*/
                sch_tasks[index].delay -= 1;
            }
        }
    }
}

u8 sch_u8_add_task(void ( * taskFunction)(),
        const u32 delay,
        const u32 period) {
    u8 index = 0;
    
    /*First find a gap in the array (if there is one)*/
    while ((sch_tasks[index].taskFunction != 0) && (index < SCH_MAX_TASKS)) {
        index++;
    }
    
    /*Have we reached the end of the list?*/
    if (index == SCH_MAX_TASKS) {
        /*Task list is full*/
        return SCH_MAX_TASKS;
    }
    
    /*If we're here, there is a space in the task array*/
    sch_tasks[index].taskFunction = taskFunction;
    sch_tasks[index].delay = delay;
    sch_tasks[index].period = period;
    sch_tasks[index].runMe = 0;
    return index; // return position of task (to allow later deletion)
}

void sch_vid_dispatch_tasks(void) {
    u8 index;
    // Dispatches the next task (if one is ready)
    for (index = 0; index < SCH_MAX_TASKS; index++) {
        if (sch_tasks[index].runMe > 0) {
            (*sch_tasks[index].taskFunction)(); /*Run the task*/
            sch_tasks[index].runMe -= 1;
            /*Periodic tasks will automatically run again*/
            /*if this is a 'one shot' task, remove it from the array*/
            if (sch_tasks[index].period == 0) {
                sch_vid_delete_task(index);
            }
        }
    }
}

void sch_vid_delete_task(u8 index) {
    if (index < SCH_MAX_TASKS) {
        sch_tasks[index].taskFunction = 0x0000;
        sch_tasks[index].delay = 0;
        sch_tasks[index].period = 0;
        sch_tasks[index].runMe = 0;
    }
}
