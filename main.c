/*
 * File:   main.c
 * Author: Ahmed Hassan
 *
 * Created on July 4, 2020
 */
#define _XTAL_FREQ 8000000 
#include <xc.h>
#include<pic16f877a.h>
#include "config.h"
#include "types.h"
#include "macros.h"
#include "ssd.h"
#include "scheduler.h"
#include "counter.h"
#include "display.h"
#include "switch.h"
int main(void) {
    
    display_vid_init();
    sch_vid_init();
    
    sch_u8_add_task(switch_vid_update, 20, 100);
    sch_u8_add_task(counter_vid_update, 20, 20);
    sch_u8_add_task(display_vid_update, 0, 20);
    sch_u8_add_task(ssd_vid_update, 20, 5);
    sch_u8_add_task(display_vid_blink_heating_led, 1000, 1000);

    while (1) {
        sch_vid_dispatch_tasks();
    }
    
}





