
// Author : Muhammed Abdulnaser
// This is a System Tick timer (SysTick timer) driver For Tiva c TM4C123GH6PM .
// Version 1.0.0
// SysTick Works in that library on 16 MHZ clock . 
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "driverlib/interrupt.h"
#include "../../TM4C123GH6PM.h"
#include "SysTick_interface.h"
#include "SysTick_config.h"




uint32_t Counter ;
Sys_ptr Handler_ptr;
	
// Description: Systick Timer Initialization With no interrupt
// Input  : NO inputs (NOTE: you shall calculate the time you need by the eq. in config and put it in variable called ticks )
// Output : No outputs

void SysTick_Start_No_Interrupt(void)
{
	// Disable the systick this action is deadly needed as first action for Initialization.
	NVIC_ST_CTRL_R = disable ;
	
	// Set the Reload value you need in Ticks (24 bit Not 32)
	NVIC_ST_RELOAD_R = Ticks-1;
  
  // Reset and clear the systick counter register.
	NVIC_ST_CURRENT_R = clear ;
	
	// Select the clock source , processor clock = 1 , external clock =0
	NVIC_ST_CTRL_R = enable ;
	
	// Enables systick Interrupt, Enable = 1 ,Disable = 0;
	NVIC_ST_CTRL_R = disable ;
	
	// Enabling the Systick it self 
	NVIC_ST_CTRL_R = SysControlEnableNoInterrupt ;
	
}

// Description: Systick Timer stop and clearing the contol and current value REGs
// Input  : NO inputs
// Output : No outputs


void SysTick_Stop  (void)
{
	 // Reset and clear the systick counter register.
	//SysTick_CURRENT_R = clear ;

	  // Disable the systick .
	NVIC_ST_CTRL_R &= ~(1<<disable) ;

}


void SysTick_Start(void)
{

     // Disable the systick .
    NVIC_ST_CTRL_R |= enable ;

}



// Description: Systick Timer Initialization eith interrupt
// Input  : NO inputs (NOTE: you shall calculate the time you need by the eq. in config and put it in variable called ticks )
// Output : No outputs
// If you use this function you must use 'void SysTick_Handler(void)' in the main funct. 

void SysTick_Start_Interrupt(void)
{


	// Disable the systick this action is deadly needed as first action for Initialization.
	NVIC_ST_CTRL_R = disable ;
	
	// Set the Reload value you need in Ticks (24 bit Not 32)
	NVIC_ST_RELOAD_R = Ticks-1;
  
  // Reset and clear the systick counter register.
	NVIC_ST_CURRENT_R = clear ;
	
	// Select the clock source , processor clock = 1 , external clock =0
	//SysTick_CTRL_R = enable ;
	
	// Enables systick Interrupt, enable = 1 ,disable = 0;
	//SysTick_CTRL_R = enable ;
	
	// Enabling the Systick it self 
	NVIC_ST_CTRL_R = SysControlEnableWithInterrupt ;
	
	// Enabling the global interrupt
	IntMasterEnable();
}

// Description: Systick Timer flags conter
// Input  : NO inputs
// Output : Counts of how many times the flag is set
// NOTE   : the variable you use in the main function must be 32 bit

int SysTickFlags_Counter (void)
{
	return Counter;
}

// Description: Systick Timer flag counter clear 
// Input  : NO inputs
// Output : No outputs

void SysTick_ClearCounter (void)
{
	Counter =0 ;
}




void SysTick_setCallBack(void(*Sys_ptr)(void))
{
    Handler_ptr = Sys_ptr;

}




void SysTick_Handler(void)
{
	

    Handler_ptr();
	Counter++;

}
