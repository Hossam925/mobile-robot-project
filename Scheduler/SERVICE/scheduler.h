/*
 * scheduler.h
 *
 *  Created on: Nov 2, 2019
 *      Author: Ahmed Khaled
 */

#ifndef SERVICE_SCHEDULER_H_
#define SERVICE_SCHEDULER_H_

/****************************A scheduler has the following key components*****************************
 * 1) the scheduler data structure "the heart of the scheduler"                                      *
 * 2)An initialization functions                                                                     *
 * 3)A single interrupt service routine "ISR",used to update the scheduler at regular time           *
 * 4)A function for adding task to the scheduler                                                     *
 * 5)A dispatcher function that causes tasks to be executed when they are due to run                 *
 * 6)A function for removing  tasks from scheduler (optional),not required in all applications       *
 ****************************************************************************************************/

#include "../std_types.h"

#define NULL_PTR 0
/* Timer counting time in ms */
#define SCH_BASE_TIME 20

//#define SCH_MAX_TASKS   3

/***************  ERRORS   *************/
#define ERROR_SCH_TOO_MANY_TASKS 0




/* define APIs of scheduler */

void SCH_Start(void);

void SCH_Init_Tasks(void);                     //timer initialization
void SCH_Start_Task(void);                    //
void SCH_Dispatch_Tasks(void);
u8   SCH_Add_Task(void (*func_ptr) (void) ,const u32  period, u32 delay);          //Add task
void SCH_Update(void);
void SCH_Delete_Task(u8 index);


#endif /* SERVICE_SCHEDULER_H_ */
