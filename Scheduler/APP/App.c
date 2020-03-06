/*
 * App.c
 *
 *  Created on: Sep 9, 2019
 *      Author: Ahmed Khaled
 */


#include <stdbool.h>
#include <stdint.h>
#include"../std_types.h"  //contain data types to be more readable
#include"../macros.h"    //contain some fundamental expression
#include"../MCAL/GPIO_Module/GPIO_interface.h"   // contain all prototypes of the followed functions

#include"../HAL/TASKS/tasks.h"
#include "../SERVICE/scheduler.h"
#include "driverlib/sysctl.h"






int main (void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                       SYSCTL_XTAL_16MHZ);

    GPIO_init_port(PORTA);
    GPIO_set_port_dir(PORTA,OUTPUT);
//    GPIO_set_port_data(PORTA,0xff);
	SCH_Init_Tasks();



    SCH_Add_Task(LED1_ONOFF,0,1);
    SCH_Add_Task(LED2_ONOFF,1,3);

	SCH_Start();

}
