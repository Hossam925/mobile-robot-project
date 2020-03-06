/*************************************************************************************************************************************************
                                               Serial Perphirals interface "ADC" Header file  
																							       function prototype and some defintions 
                                                      Hardware:  TM4C123 Tiva board
                                                          ---> author: Ahmed Khaled       
                                                          ---> release v1.0.0
*************************************************************************************************************************************************/

#ifndef ADC_HAL_H
#define ADC_HAL_H

#include <stdint.h>
/********************************************************************************************************************************************
                                                          Public definitions 
																													
	 1- we have 2 ADC module from ADC0 to ADC1 each module have (AIN0 to AIN11) ---->> 12channel and internal tempreture 
	 2- I make some define for some bits related with ADC 
	 
*/ 			
			
  
//*****************************************************************************
//
// The following are defines for ADC_Module NO.
//
//*****************************************************************************

#define  ADC0  0
#define  ADC1  1

//*****************************************************************************
//
// The following are defines for ADC channel NO.
//
//*****************************************************************************

#define AIN0   0
#define	AIN1   1
#define	AIN2   2
#define	AIN3   3
#define	AIN4   4
#define	AIN5   5
#define	AIN6   6
#define	AIN7   7
#define	AIN8   8
#define	AIN9   9
#define	AIN10  10
#define	AIN11  11

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCADC register.
//
//*****************************************************************************
#define Enable_ADC1       0x00000002  // ADC Module 1 Run Mode Clock
                                            // Gating Control
#define Enable_ADC0       0x00000001  // ADC Module 0 Run Mode Clock
                                            // Gating Control
																						
//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PRADC register.
//
//*****************************************************************************
 
#define ADC1_CLOCK_READY         0x00000002  // ADC Module 1 Peripheral Ready
#define ADC0_CLOCK_READY         0x00000001  // ADC Module 0 Peripheral Ready

//***************************************************************************** 
//
// The following are defines for the bit fields in the ADC_O_ACTSS register.
//
//*****************************************************************************
#define ADC_ACTSS_BUSY         0x00010000  // ADC Busy
#define ADC_Enable_SS3         0x00000008  // ADC SS3 Enable
#define ADC_Enable_SS2         0x00000004  // ADC SS2 Enable
#define ADC_Enable_SS1         0x00000002  // ADC SS1 Enable
#define ADC_Enable_SS0         0x00000001  // ADC SS0 Enable

//*****************************************************************************

#define SS0  0
#define SS1  1
#define SS2  2
#define SS3  3

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_EMUX register.
//
//*****************************************************************************
#define ADC_SS3_TRIGEER_CONT          0x0000F000  // SS3 Trigger Select
#define ADC_SS3_TRIGEER_PROCESSOR     0x00000000  // Processor (default)
#define ADC_SS3_TRIGEER_COMP0         0x00001000  // Analog Comparator 0
#define ADC_SS3_TRIGEER_COMP1         0x00002000  // Analog Comparator 1
#define ADC_SS3_TRIGEER_EXTERNAL      0x00004000  // External (GPIO Pins)
#define ADC_SS3_TRIGEER_TIMER         0x00005000  // Timer
#define ADC_SS3_TRIGEER_PWM0          0x00006000  // PWM generator 0
#define ADC_SS3_TRIGEER_PWM1          0x00007000  // PWM generator 1
#define ADC_SS3_TRIGEER_PWM2          0x00008000  // PWM generator 2
#define ADC_SS3_TRIGEER_PWM3          0x00009000  // PWM generator 3
#define ADC_SS3_TRIGEER_ALWAYS        0x0000F000  // Always (continuously sample)
#define ADC_EMUX_EM2_M          0x00000F00  // SS2 Trigger Select
#define ADC_EMUX_EM2_PROCESSOR  0x00000000  // Processor (default)
#define ADC_EMUX_EM2_COMP0      0x00000100  // Analog Comparator 0
#define ADC_EMUX_EM2_COMP1      0x00000200  // Analog Comparator 1
#define ADC_EMUX_EM2_EXTERNAL   0x00000400  // External (GPIO Pins)
#define ADC_EMUX_EM2_TIMER      0x00000500  // Timer
#define ADC_EMUX_EM2_PWM0       0x00000600  // PWM generator 0
#define ADC_EMUX_EM2_PWM1       0x00000700  // PWM generator 1
#define ADC_EMUX_EM2_PWM2       0x00000800  // PWM generator 2
#define ADC_EMUX_EM2_PWM3       0x00000900  // PWM generator 3
#define ADC_EMUX_EM2_ALWAYS     0x00000F00  // Always (continuously sample)
#define ADC_EMUX_EM1_M          0x000000F0  // SS1 Trigger Select
#define ADC_EMUX_EM1_PROCESSOR  0x00000000  // Processor (default)
#define ADC_EMUX_EM1_COMP0      0x00000010  // Analog Comparator 0
#define ADC_EMUX_EM1_COMP1      0x00000020  // Analog Comparator 1
#define ADC_EMUX_EM1_EXTERNAL   0x00000040  // External (GPIO Pins)
#define ADC_EMUX_EM1_TIMER      0x00000050  // Timer
#define ADC_EMUX_EM1_PWM0       0x00000060  // PWM generator 0
#define ADC_EMUX_EM1_PWM1       0x00000070  // PWM generator 1
#define ADC_EMUX_EM1_PWM2       0x00000080  // PWM generator 2
#define ADC_EMUX_EM1_PWM3       0x00000090  // PWM generator 3
#define ADC_EMUX_EM1_ALWAYS     0x000000F0  // Always (continuously sample)
#define ADC_EMUX_EM0_M          0x0000000F  // SS0 Trigger Select
#define ADC_EMUX_EM0_PROCESSOR  0x00000000  // Processor (default)
#define ADC_EMUX_EM0_COMP0      0x00000001  // Analog Comparator 0
#define ADC_EMUX_EM0_COMP1      0x00000002  // Analog Comparator 1
#define ADC_EMUX_EM0_EXTERNAL   0x00000004  // External (GPIO Pins)
#define ADC_EMUX_EM0_TIMER      0x00000005  // Timer
#define ADC_EMUX_EM0_PWM0       0x00000006  // PWM generator 0
#define ADC_EMUX_EM0_PWM1       0x00000007  // PWM generator 1
#define ADC_EMUX_EM0_PWM2       0x00000008  // PWM generator 2
#define ADC_EMUX_EM0_PWM3       0x00000009  // PWM generator 3
#define ADC_EMUX_EM0_ALWAYS     0x0000000F  // Always (continuously sample)

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSCTL3 register.
//
//*****************************************************************************
#define ADC0_TEMP_SENSOR                   0x00000008  // 1st Sample Temp Sensor Select
#define ADC0_INT_ENABLE                    0x00000004  // Sample Interrupt Enable
#define ADC0_EOS                           0x00000002  // End of Sequence [take one sample at a time]
#define ADC0_SAMPLE_DIFFERENTIAL           0x00000001  // Sample Differential Input Select


//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PPSSI register.
//
//*****************************************************************************

#define ADC_START_conversion_SSI3         0x00000008   // SSI Module 3 Present
#define ADC_START_conversion_SSI2         0x00000004   // SSI Module 2 Present
#define ADC_START_conversion_SSI1         0x00000002   // SSI Module 1 Present
#define ADC_START_conversion_SSI0         0x00000001   // SSI Module 0 Present

/**************************************************************************************************************************************************
                                                     Public functions
																										 
1----------------------------------->>init_ADC
2----------------------------------->>Read_data

*********************************************************************************************************************************/
/*
 1----------------------------------->>ADC_Initialization 
Description: Initialize The ADC_Module 
*Args: 
	1- Module          : ADC0 to ADC1
	2- channel         : AIN0 to ANI11 ------>> 12 channel
	3- sample sequncer : SS0  to SS3 
* Return: void
STEPS :
1)Enable clock to ADC module 
2)Enable clock to GPIO module 
3)Enable Altrnate function 
4)Disable digital function 
5)Enable Analog function 
6)disable Sample sequencer during configuration 
7)select Software trigger convertion by processor(default)
8)get input from your channel/channels
9)set ADC control
10)Enable Sample sequencer after configuration
       
************************************************************************************************************************************/

/*
2----------------------------------->>Read Data
Description: Initialize The ADC_Module 
*Args: 
	1- Module          : ADC0 to ADC1
* Return: uint32_t
STEPS :
1)start a conversion for sequence 0,1,2,3 
2)wait until ADC conversion Completes
3)read conversion result 
4)clear compilation flag 
5)Return Digital_value
       
*/
void ADC_VidInit(uint8_t module, uint8_t channel,uint8_t SS_NO);
extern uint32_t ADC_U32Read(uint8_t module);


#endif
