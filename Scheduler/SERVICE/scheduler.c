/*

 * scheduler.c
 *
 *  Created on: Nov 2, 2019
 *      Author: Ahmed Khaled
 */


/****************************A scheduler has the following key components*****************************
 * 1) the scheduler data structure "the heart of the scheduler"                                                                *
 * 2)An initialization functions                                                                     *
 * 3)A single interrupt service routine "ISR",used to update the scheduler at regular time           *
 * 4)A function for adding task to the scheduler                                                     *
 * 5)A dispatcher function that causes tasks to be executed when they are due to run                 *
 * 6)A function for removing  tasks from scheduler (optional),not required in all applications       *
 ****************************************************************************************************/

/********************************************functions APIs*******************************************
 * SCH_Init()                                                                                        *
 * SCH_AddTask()                                                                                     *
 * SCH_DeleteTask()                                                                                  *
 * SCH_DispatchTasks()                                                                               *
 * SCH_Update()      for ------>>>  SCH_NewTimerTick                                                 *
 * ***************************************************************************************************/

/*******************************import headers file***************************************************/
#include "../std_types.h"
#include "../macros.h"
#include "../MCAL/SysTick_Module/SysTick_interface.h"
#include"../HAL/TASKS/tasks.h"
#include "scheduler.h"
/*****************************************************************************************************/

/******************************global variable definition*********************************************/

task TASKS_DATA[MAX_TASKS];           //each elements in array from object task   <container>

u8 BUFFER_TIME_UPDATE[MAX_TASKS];       //the period for each task <<global buffer to values of update function tick>>

u8 Error_code_g = -1;

/****************************************************************************************************/


/******************************************SCH_Init_tasks********************************************/
void SCH_Init_Tasks(void)
{

 u8 index = 0 ;

     SysTick_Start_Interrupt();

     /* select between <<SCH_NewTimerTick>> OR <<SCH_Update>> */
     SysTick_setCallBack(SCH_Update);

     for(index = 0 ; index < MAX_TASKS ; index ++)
     {
         SCH_Delete_Task(index);

     }
     SysTick_Stop();
}
/****************************************************************************************************/


/***************************************SCH_Add_Task*************************************************/

u8 SCH_Add_Task(void (*func_ptr) (void) ,const u32  period, u32 delay)
{
 	u8 index = 0 ;
	//first find a gap in the array (if there is one)
	while((TASKS_DATA[index].code != 0 ) && (index < MAX_TASKS))
	{
		index++;
	}
	if(index == MAX_TASKS){
	    Error_code_g = ERROR_SCH_TOO_MANY_TASKS;
	    return MAX_TASKS;
	}

	//if we are here ,there is a space in the task array
	    TASKS_DATA[index].code = func_ptr ;
	    TASKS_DATA[index].delay = delay;
		TASKS_DATA[index].periodicity  = period;
		TASKS_DATA[index].RunMe = 0 ;
		return index ;  //return position of task (to allow later deletion )
}

/***************************************************************************************************/





/****************************************************************************************************/

/************************************** SCH_Update***************************************************/
                            /*if my dispatch not switch case*/
void SCH_Update(void)
{
	u8 index = 0;
		for(index = 0 ; index < MAX_TASKS ; index++)
		{
			//check if there is a task at this location
		   if(TASKS_DATA[index].code)
		   {
			if(TASKS_DATA[index].delay==0)
			{
				/*the task is due to run*/
				TASKS_DATA[index].RunMe += 1; //Inc the RunMe flag
				if(TASKS_DATA[index].periodicity)
				{
				    TASKS_DATA[index].delay = TASKS_DATA[index].periodicity;
				}
			}
			else
			{
				     /*the task not ready*/
				TASKS_DATA[index].delay -= 1;
			}

		   }

		}//end for

}
/*****************************************************************************************************/

/*************************************dispatches ready task*******************************************/

void SCH_Dispatch_Tasks(void)
{
	while(1)
	{
		u8 index;
		// dispatches (runs) the next task (if one is ready)
		for(index = 0 ; index < MAX_TASKS ; index++)
		{

			/*make one shot function*/
			if(TASKS_DATA[index].RunMe > 0)
			{
                ((*TASKS_DATA[index].code))(); //run the task callback
                TASKS_DATA[index].RunMe -= 1 ; //reset / reduce RunMe flag

                /* periodic tasks will automatically Run again*/
                //delete one shot
			}
		}//end for

	   /*the scheduler enters idle mode at this point
		*SCH_GO_TO_SLEEP();    to save power*/

	}
}
/****************************************************************************************************/

void SCH_Start(void)
{
	/*
	 * Set the Call Back function call to Scheduler_New_Timer_Tick
	 * this function will be called every Timer0 Compare Interrupt(20ms)
	 */


	/* Start Timer0 in Compare Mode to generate interrupt every 20ms */
    SysTick_Start();


	/* Start the Dispatcher */
	SCH_Dispatch_Tasks();
}
/************************************************************************************************/



void SCH_Delete_Task(u8 index)
{
    TASKS_DATA[index].code = NULL_PTR ;
    TASKS_DATA[index].periodicity  = 0;
    TASKS_DATA[index].delay  = 0;
    TASKS_DATA[index].RunMe = 0 ;
}

