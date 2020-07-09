/*
 * File:   main.c
 * Author: Hassan
 *
 * Created on July 4, 2020
 */
#define _XTAL_FREQ 8000000 
#include <xc.h>
#include<pic16f877a.h>

#include "config.h"
#include "types.h"
#include "macros.h"
#include "dio.h"
#include "ssd.h"
#include "scheduler.h"
#include "timer.h"
#include "i2c.h"
#include "eeprom_external.h"
#include "counter.h"
#include "display.h"

int main(void) {
    i2c_vid_master_init();
    display_init();
    sch_vid_init();
    sch_u8_add_task(counter_vid_update, 20, 20);
    sch_u8_add_task(display_vid_update, 0, 20);
    sch_u8_add_task(ssd_vid_update, 5, 5);

    while (1) {
        sch_vid_dispatch_tasks();
    }


}
