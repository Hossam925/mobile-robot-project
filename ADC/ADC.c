/*************************************************************************************************************************************************
                                                 Analog to digital converter "ADC" source file 
																							       implementation the functions's code
                                                      Hardware:  TM4C123 Tiva board
                                                          ---> author: Ahmed Khaled       
                                                          ---> release v1.0.0
*************************************************************************************************************************************************/

#include <stdint.h>    // --------------------->>include file for stdandard data types 
#include "macros.h"                                        
#include "GPIO_interface.h"
#include "ADC_Private.h"
#include "tm4.h"   //-------------------------->header file to link address to register name section

/*******************************************************************************************************************
                                                functions implementations
																								
1----------------------------------->>ADC_Initialization
2----------------------------------->>Data Read

******************************************************************************************************************/

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
       
*/

void ADC_VidInit(uint8_t module, uint8_t channel,uint8_t SS_NO)
{
	switch(module)
	{
		case ADC0:
		{
	        SYSCTL_RCGCADC_R = Enable_ADC0 ;                              //1)Enable clock to ADC0 module 
		     // Wait for the ADC peripheral to be ready...
		     while (!(SYSCTL_PRADC_R & ADC0_CLOCK_READY )){}
			   //-------------------------------------------------------------------------------------------------------
					 
	       switch(channel)
				 {
					 case AIN0:
						 //configure GPIO PIN 
						 GPIO_init_port(PORTE);                                     //2)Enable clock to GPIO module 
						 GPIO_set_pin_alt_fun(PORTE,PIN3);                            //3)Enable Altrnate function 
						 GPIO_PORTE_DEN_R &=~(1<<PIN3);                            //4)Disable digital function 
						 GPIO_set_pin_signal_type(PORTE,PIN3,ANALOUGE);               //5)Enable Analog function 
						 
						 //Choose & Disable The Sample Sequencer 
			 
							ADC0_ACTSS_R &=~(1<<SS_NO);                               //6) /*disable Sample sequencer during configuration */
					  /*PLZ configure the trigger source from ADC_Private*/
							ADC0_EMUX_R = ADC_SS3_TRIGEER_PROCESSOR ;                //7)Software trigger convertion by processor(default)
						 switch(SS_NO)                                             //8)get input from your channel/channels
						 { 
							 /*PLZ configure the following if you SS0,SS1,SS2 to select channels */
							 case SS3:
							 {					 
								 ADC0_SSMUX3_R = channel ;                             //-------->> for 1 channel
																		 //9)set ADC control
								 ADC0_SSCTL3_R |= (ADC0_INT_ENABLE | ADC0_EOS  );      //take one sample at a time ,set flag at 1st sample
								 ADC0_SSCTL3_R &= ~(ADC0_TEMP_SENSOR); 	               //(optional)read from Input channels
								 ADC0_SSCTL3_R &= ~(ADC0_SAMPLE_DIFFERENTIAL); 				 //the analog signal are not differntialy sampled		 
								 break ;                                                 
							 }
								case SS2:
							 {					 
								 ADC0_SSMUX2_R = channel ;                             //-------->> for 4 channel
																		 //9)set ADC control
								 ADC0_SSCTL2_R |= (ADC0_INT_ENABLE | ADC0_EOS  );      //take one sample at a time ,set flag at 1st sample
								 ADC0_SSCTL2_R &= ~(ADC0_TEMP_SENSOR); 	               //(optional)read from Input channels
								 ADC0_SSCTL2_R &= ~(ADC0_SAMPLE_DIFFERENTIAL); 				 //the analog signal are not differntialy sampled		 
								 break ;                                                 
							 }
								case SS1:
							 {					 
								 ADC0_SSMUX1_R = channel ;                             //-------->> for 4 channel
																		 //9)set ADC control
								 ADC0_SSCTL1_R |= (ADC0_INT_ENABLE | ADC0_EOS  );      //take one sample at a time ,set flag at 1st sample
								 ADC0_SSCTL1_R &= ~(ADC0_TEMP_SENSOR); 	               //(optional)read from Input channels
								 ADC0_SSCTL1_R &= ~(ADC0_SAMPLE_DIFFERENTIAL); 				 //the analog signal are not differntialy sampled		 
								 break ;                                                 
							 }
								case SS0:
							 {					 
								 ADC0_SSMUX0_R = channel ;                             //-------->> for 8 channel
																		 //9)set ADC control
								 ADC0_SSCTL0_R |= (ADC0_INT_ENABLE | ADC0_EOS  );      //take one sample at a time ,set flag at 1st sample
								 ADC0_SSCTL0_R &= ~(ADC0_TEMP_SENSOR); 	               //(optional)read from Input channels
								 ADC0_SSCTL0_R &= ~(ADC0_SAMPLE_DIFFERENTIAL); 				 //the analog signal are not differntialy sampled		 
								 break ;                                                 
							 }
			 
	           }	 
	 		    ADC0_ACTSS_R |=(1<<SS_NO);                               //10) /*Enable Sample sequencer after configuration */
	       }
	     break;
			}
 	
		case ADC1:
		{
			/*make it later*/
			
		}
	}	
		
}	

/****************************************************************************************************************************/

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
extern uint32_t ADC_U32Read(uint8_t module)
{
	
	  volatile uint32_t Digital_val = 0;
	   ADC0_PSSI_R |=ADC_START_conversion_SSI3 ;         // start a conversion sequence 3 
    
    while((ADC0_RIS_R & 0x08) ==0 );                   // wait until ADC conversion Completes
    Digital_val = ADC0_SSFIFO3_R   ;                   //read conversion result 
    ADC0_ISC_R = 0x8 ;                                 //clear compilation flag 
    return  Digital_val ;
}
