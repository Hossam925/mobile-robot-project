 
//author: KHALED
//release v1.0.0
//the main PROG of the driver
#include <stdint.h>
#include "PWM_INTERFACE.h"
#include "header.h"




static uint32_t PWM_baseAddresses[] =
	{

		PWM0_R_BASE_ADDRESSE,
		PWM1_R_BASE_ADDRESSE
};
	


// FUNCTION FOR INTILIZATION PWM
void pwm_init_num(int8_t  pwmnumber ,int8_t KIND  )
{
	uint32_t read_back;
	SYSCTL_RCGCPWM_R |= ( 1<< pwmnumber ) ; // enable clock for module 0,1
	read_back = SYSCTL_RCGCPWM_R;
	  SYSCTL_RCC_R |=    0x00100000  ;     // enable pre divided
	SYSCTL_RCC_R |= clk2 ;                // clk/2   8mhz
	
	/*
	switch (pwmnumber)
	{
		case 0 :  PWM0->ENABLE|=0x00000001  ;     //Start PWM
			
		
			break;

		case 1 :   PWM1->ENABLE|=0x00000001 ; //Start PWM
 break;			
	}
		*/
	

	

}

//****************************************************************************************************//
/* FUNCTION FOR   enable pwm */
void pwm_enable(int8_t  pwmnumber ,int8_t KIND  )
{	
	uint32_t read_back;
	
	switch  (KIND)
	{
		case 0:
 
		(*((volatile uint32_t *)((PWM_baseAddresses[pwmnumber] + PWM0CTL_OFFSET)))) = 1;
		read_back = (*((volatile uint32_t *)((PWM_baseAddresses[pwmnumber] + PWM0CTL_OFFSET))));
    break   ; 
		
		case 1 :
	
				(*((volatile uint32_t *)((PWM_baseAddresses[pwmnumber] + PWM1CTL_OFFSET)))) = 1;
				read_back = (*((volatile uint32_t *)((PWM_baseAddresses[pwmnumber] + PWM1CTL_OFFSET))));
		break ;
	
		case 2 :
					(*((volatile uint32_t *)((PWM_baseAddresses[pwmnumber] + PWM2CTL_OFFSET)))) = 1;
					read_back = (*((volatile uint32_t *)((PWM_baseAddresses[pwmnumber] + PWM2CTL_OFFSET))));
	break ;
		case 3:
					(*((volatile uint32_t *)((PWM_baseAddresses[pwmnumber] + PWM3CTL_OFFSET)))) = 1;
					read_back = (*((volatile uint32_t *)((PWM_baseAddresses[pwmnumber] + PWM3CTL_OFFSET))));
		break ;
  }

		
		}

/* function for disable pwm */
void pwm_disbale(int8_t  pwmnumber)
{
switch (pwmnumber)
{
	case 0:
			  PWM0_CTL_R=0x00000000;//Disable PWM0
break ;
	case 1 :
	  	 PWM1_CTL_R=0x00000000;//Disable PWM1
break ; 
}

}

// fucntion to stop counter
void pwm_stop(int8_t  pwmnumber, int8_t KIND)
{
	uint32_t read_back;
	
	switch (KIND)
	{
		case 0:
	         	(*((volatile uint32_t *)((PWM_baseAddresses[pwmnumber] + PWM0CTL_OFFSET)))) = 0;
						read_back = (*((volatile uint32_t *)((PWM_baseAddresses[pwmnumber] + PWM0CTL_OFFSET))));
		break ;
		case 1 :
							(*((volatile uint32_t *)((PWM_baseAddresses[pwmnumber] + PWM1CTL_OFFSET)))) = 0;
							read_back = (*((volatile uint32_t *)((PWM_baseAddresses[pwmnumber] + PWM1CTL_OFFSET))));
  break ;
		case 2 :
							(*((volatile uint32_t *)((PWM_baseAddresses[pwmnumber] + PWM2CTL_OFFSET)))) = 0;
							read_back = (*((volatile uint32_t *)((PWM_baseAddresses[pwmnumber] + PWM2CTL_OFFSET))));

		break ;
		
		case 3 :
							(*((volatile uint32_t *)((PWM_baseAddresses[pwmnumber] + PWM3CTL_OFFSET)))) = 0;
							read_back = (*((volatile uint32_t *)((PWM_baseAddresses[pwmnumber] + PWM3CTL_OFFSET))));

		break ;

	}
}

// function to set load 
void pwm_load(int8_t  pwmnumber, int8_t KIND , int16_t load_value)
{
switch (KIND)
  {
		uint32_t read_back;
	case 0 :
									(*((volatile uint32_t *)((PWM_baseAddresses[pwmnumber] + PWM0LOAD_OFFSET)))) =load_value ;
									read_back = (*((volatile uint32_t *)((PWM_baseAddresses[pwmnumber] + PWM0LOAD_OFFSET))));
	break ;
		case 1 :
									(*((volatile uint32_t *)((PWM_baseAddresses[pwmnumber] + PWM1LOAD_OFFSET)))) =load_value ;
									read_back = (*((volatile uint32_t *)((PWM_baseAddresses[pwmnumber] + PWM1LOAD_OFFSET))));
	break ;
		case 2 :
									(*((volatile uint32_t *)((PWM_baseAddresses[pwmnumber] + PWM2LOAD_OFFSET)))) =load_value ;
									read_back = (*((volatile uint32_t *)((PWM_baseAddresses[pwmnumber] + PWM2LOAD_OFFSET))));
	break ;
		case 3 :
									(*((volatile uint32_t *)((PWM_baseAddresses[pwmnumber] + PWM3LOAD_OFFSET)))) =load_value ;
									read_back = (*((volatile uint32_t *)((PWM_baseAddresses[pwmnumber] + PWM3LOAD_OFFSET))));
	break ;
	}
}	
// FUCNTION TO SET COMAPARE VALUE AND DUTY CYCLE 
void pwm_cmp(int8_t  pwmnumber, int8_t KIND, int16_t CMP_value)
{
	switch (KIND)
	{
		uint32_t read_back;
		
		case 0 :
									(*((volatile uint32_t *)((PWM_baseAddresses[pwmnumber] + PWM0CMPA_OFFSET)))) =CMP_value ;
									read_back = (*((volatile uint32_t *)((PWM_baseAddresses[pwmnumber] + PWM0CMPA_OFFSET))));
	break ;
		case 1 :
									(*((volatile uint32_t *)((PWM_baseAddresses[pwmnumber] + PWM1CMPA_OFFSET)))) =CMP_value ;
									read_back = (*((volatile uint32_t *)((PWM_baseAddresses[pwmnumber] + PWM1CMPA_OFFSET))));
	break ;
		case 2 :
									(*((volatile uint32_t *)((PWM_baseAddresses[pwmnumber] +  PWM2CMPA_OFFSET)))) =CMP_value ;
									read_back = (*((volatile uint32_t *)((PWM_baseAddresses[pwmnumber] + PWM2CMPA_OFFSET))));
	break ;
		case 3 :
									(*((volatile uint32_t *)((PWM_baseAddresses[pwmnumber] + PWM3CMPA_OFFSET)))) =CMP_value ;
									read_back = (*((volatile uint32_t *)((PWM_baseAddresses[pwmnumber] + PWM3CMPA_OFFSET))));
	break ;
	}
}
/* func to gena */
	void  pwm_gena(int8_t  pwmnumber,int8_t KIND) 
	{
		uint32_t read_back;
	switch (KIND)
	       {
		case 0 :
			
    (*((volatile uint32_t *)((PWM_baseAddresses[pwmnumber] + PWM0GENA_OFFSET)))) = 140; // drive low for ACTCMPAD and drive high for ACTLOAD
		read_back = (*((volatile uint32_t *)((PWM_baseAddresses[pwmnumber] + PWM0GENA_OFFSET))));	
		break ;
		
		case 1 :
		    (*((volatile uint32_t *)((PWM_baseAddresses[pwmnumber] + PWM1GENA_OFFSET)))) = 140;
		read_back = (*((volatile uint32_t *)((PWM_baseAddresses[pwmnumber] + PWM1GENA_OFFSET))));
break ;
		
		case 2 : 
    (*((volatile uint32_t *)((PWM_baseAddresses[pwmnumber] + PWM2GENA_OFFSET)))) = 140;
		read_back = (*((volatile uint32_t *)((PWM_baseAddresses[pwmnumber] + PWM2GENA_OFFSET))));
break ;
		
		case 3 :
    (*((volatile uint32_t *)((PWM_baseAddresses[pwmnumber] + PWM3GENA_OFFSET)))) = 140;
		read_back = (*((volatile uint32_t *)((PWM_baseAddresses[pwmnumber] + PWM3GENA_OFFSET))));
break ;			
				

      }
	
}

