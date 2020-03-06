
// Author : Muhammed Abdulnaser
// This is a System Tick timer (SysTick timer) driver For Tiva c TM4C123GH6PM .
// Version 1.0.0
// SysTick Works in that library on 16 MHZ clock .

/************************************************************
*****************        Types    **************************
************************************************************/
typedef void(*Sys_ptr)(void);


/************************************************************
***************** Public Functions **************************
************************************************************/

void SysTick_Start_No_Interrupt (void);

void SysTick_Start_Interrupt(void);

void SysTick_Stop(void);

void SysTick_Start(void);

int SysTickFlags_Counter (void);

void SysTick_ClearCounter (void);

void SysTick_setCallBack(void(*Sys_ptr)(void));
