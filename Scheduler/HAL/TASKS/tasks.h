/*
 * tasks.h
 *
 *  Created on: Nov 1, 2019
 *      Author: Ahmed Khaled
 */

#ifndef HAL_TASKS_TASKS_H_
#define HAL_TASKS_TASKS_H_

/****************************************** structure data type for each task******************************/
typedef struct
{
 void (*code) (void) ;         //function pointer
 u32  periodicity ;            //time update function
 u32  delay;
 u8   RunMe ;                //flag to run function
}task;
/**********************************************************************************************************/

#define  MAX_TASKS  3            //No of tasks in my system


void Init_Task(void);
void LED1_ONOFF(void);
void LED2_ONOFF(void);
void LED3_ONOFF(void);
void LED4_ON(void);


#endif /* HAL_TASKS_TASKS_H_ */
