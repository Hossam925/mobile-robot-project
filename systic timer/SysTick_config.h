 
// Author : Muhammed Abdulnaser
// This is a System Tick timer (SysTick timer) driver For Tiva c TM4C123GH6PM .
// Version 1.0.0
// SysTick Works in that library on 16 MHZ clock .

/*Equation : if i used as example 16 MHZ then the time = 1/Freq. =(1/16MHZ)=62.5 ns
          then if i want 1 sec ---> 1 sec/62.5 ns =16,000,000 count (put it in ticks) */

#define clear 0 
#define enable 1
#define disable 0

 uint32_t Ticks = 64000;                // means systick tim to be reloaded is sec
 uint8_t clock_source = 1 ;                // means cpu clock if external clock write 0
 uint8_t SysControlEnableNoInterrupt = 4;
 uint8_t SysControlEnableWithInterrupt = 6;
