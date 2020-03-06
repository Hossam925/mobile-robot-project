/*

 * tasks.c
 *
 *  Created on: Nov 1, 2019
 *      Author: Ahmed Khaled
 */

#include"../../std_types.h"  //contain data types to be more readable
#include"../../macros.h"    //contain some fundamental expression
#include"../../MCAL/GPIO_Module/GPIO_interface.h"   // contain all prototypes of the followed functions
#include"tasks.h"




/* Task called every 20 Mili-seconds to check the button state */
void LED1_ONOFF(void)
{

    GPIO_toggle_pin_value(PORTA,2);

}

/* Task called every 40 Mili-seconds to refresh the LED */
void LED2_ONOFF(void)
{

    GPIO_toggle_pin_value(PORTA,3);

}

/* Task called every 60 Mili-seconds to get the button status and toggle the led */

void LED3_ONOFF(void)
{

    GPIO_toggle_pin_value(PORTA,4);
}
void LED4_ON(void)
{

    GPIO_toggle_pin_value(PORTA,5);

}
