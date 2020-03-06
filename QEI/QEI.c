/*************************************************************************************************************************************************
                                               Serial Perphirals interface "QEI" source file 
																							       implementation the functions's code
                                                      Hardware:  TM4C123 Tiva board
                                                          ---> author: Ahmed Khaled       
                                                          ---> release v1.0.0
************************************************************************************************************************************************************/
/**
 *  @file  <QEI.c>
 *  @brief <Implements the functions defined in the header file.>
 */
 //*********************************************************************************************************************************************************

#include <stdint.h>    // --------------------->>include file for stdandard data types 
#include "macros.h"                                        
#include "GPIO_interface.h"
#include "QEI.h"
#include "tm4.h"   //-------------------------->header file to link address to register name section

//#define clock 16000000
//#define load  16000000

/*******************************************************************************************************************
                                                functions implementations
																								
1----------------------------------->>QEI_Initialization 
2----------------------------------->>QEI_Configuration 
3----------------------------------->>QEI_Velocity_Configuration
4----------------------------------->>QEI_Input_Filter_Configuration
5----------------------------------->>QEI_Interrupts_Configuration
6----------------------------------->>QEI_Get_Position
7----------------------------------->>QEI_Get_Velocity
8----------------------------------->>QEI_Get_Direction 
9----------------------------------->>QEI_Enable

******************************************************************************************************************/

/*
 1----------------------------------->>QEI_Initialization 
Description: Initialize The QEI_Module 
*Args: 
	1- Module : QEI 0 to QEI 1
* Return: void
STEPS :
1)Enable The QEI Module 
2)Enable Clock for  GPIO Port Related with QEI Module 
3)Set Altrnate Function Select for each pin in QEI Module
4)Set Digital Function Bit field Encoding for each bit in GPIOPCTL
5)make Pins for QEI Dgital DEN  
       
*/
void QEI_VidInit(uint8_t module)
{
  switch(module)
		{
		case QEI0:
		{ 
			SYSCTL_RCGCQEI_R  = SYSCTL_RCGCQEI_R0 ;    //1)Enable The QEI Module 0
			GPIO_init_port(PORTF);              //2)PORTA intialization related with QEI 0 we can use PORTD also
			GPIO_set_pin_alt_fun(PORTF,PIN0);   //3)Set Altrnate Function Select for pin0 PFA0  in QEI Module 0
			GPIO_set_pin_alt_fun(PORTF,PIN1);   //3)Set Altrnate Function Select for pin1 PFB0  in QEI Module 0
			GPIO_set_pin_alt_fun(PORTF,PIN4);   //3)Set Altrnate Function Select for pin4 IDX0  in QEI Module 0
			
			GPIO_PORTF_PCTL_R  |= ( GPIO_PCTL_PF0_PHA0 | GPIO_PCTL_PF1_PHB0 | GPIO_PCTL_PF4_IDX0  );   //4)Set Digital Function Bit field Encoding for each bit in GPIOPCTL
			
			GPIO_set_pin_signal_type(PORTF, PIN0, DIGITAL); //5)make Pin0 for QEI 0 Dgital DEN
			GPIO_set_pin_signal_type(PORTF, PIN1, DIGITAL); //5)make Pin1 for QEI 0 Dgital DEN
			GPIO_set_pin_signal_type(PORTF, PIN4, DIGITAL); //5)make Pin4 for QEI 0 Dgital DEN
			
			break ;
		}
		case QEI1:
		{
		  SYSCTL_RCGCQEI_R  = SYSCTL_RCGCQEI_R1 ;    //1)Enable The QEI Module 1
			GPIO_init_port(PORTC);              //2)PORTA intialization related with QEI 0 we can use PORTD also
			GPIO_set_pin_alt_fun(PORTC,PIN5);   //3)Set Altrnate Function Select for pin5 PFA1  in QEI Module 1
			GPIO_set_pin_alt_fun(PORTC,PIN6);   //3)Set Altrnate Function Select for pin6 PFB1  in QEI Module 1
			GPIO_set_pin_alt_fun(PORTC,PIN4);   //3)Set Altrnate Function Select for pin4 IDX1  in QEI Module 1
			
			GPIO_PORTC_PCTL_R  |= ( GPIO_PCTL_PC5_PHA1 | GPIO_PCTL_PC6_PHB1 |  GPIO_PCTL_PC4_IDX1  );   //4)Set Digital Function Bit field Encoding for each bit in GPIOPCTL
			
			GPIO_set_pin_signal_type(PORTC, PIN5, DIGITAL); //5)make Pin5 for QEI 1 Dgital DEN
			GPIO_set_pin_signal_type(PORTC, PIN6, DIGITAL); //5)make Pin6 for QEI 1 Dgital DEN
			GPIO_set_pin_signal_type(PORTC, PIN4, DIGITAL); //5)make Pin4 for QEI 1 Dgital DEN

			break ;
		}
 }
}
/********************************************************************************************************************/
/*
 2----------------------------------->>QEI_Configuration 
Description: Configur The QEI_Module 
*Args: 
	1- Module : QEI 0 to QEI 1
* Return: void
STEPS :
1)Disable The QEI Module before configuration
2)configure the parameter from config file 
3)put the maximum position value 

*/

void QEI_Configuration(uint8_t module, QEI_SIG_MODE Signal_Mode, Signal_CAP_Mode Capture_Mode,Reset_State Reset_Mode,
                           SWAP_State Swap_State,Signal_invert_State INV_state, uint32_t MAX_Postion)
{
	switch(module)
	{
		case QEI0:
		{ 
    /*1)Disable the Desired QEI Module 0 before configuration.*/
    clr_bit(QEI0_CTL_R,0) ;
		/*2)configure the parameter from config file */
    QEI0_CTL_R |= Signal_Mode |Capture_Mode |Reset_Mode |Swap_State |INV_state;
		/*3)put the maximum position value */
    QEI0_MAXPOS_R |= MAX_Postion-1;
		break ;
		}
		case QEI1:
		{ 
    /*Disable the Desired QEI Module 1 before configuration.*/
    clr_bit(QEI1_CTL_R,0) ;
		/*2)configure the parameter from config file */
    QEI1_CTL_R |= Signal_Mode |Capture_Mode |Reset_Mode |Swap_State |INV_state;
		/*3)put the maximum position value */	
    QEI1_MAXPOS_R |= MAX_Postion-1;
		break ;
		}
		
  }
}

/********************************************************************************************************************/
/*
 3----------------------------------->>QEI_Velocity_Configuration
Description: Configur The QEI_Module 
*Args: 
	1- Module : QEI 0 to QEI 1
* Return: void
STEPS :
1)select The Pre_Devision from config file 
2)put velocity load value
3)ENABLE the velocity Capture for the QEI module 

*/


void QEI_Velocity_Configuration(uint8_t module, Velocity_PreDevide Pre_Devision, uint32_t Vel_LOAD_Value)
{
   switch(module)
	{
		case QEI0:
	 {
	  QEI0_CTL_R  |= Pre_Devision;      /*1)select The Pre_Devision from config file */
    QEI0_LOAD_R |= Vel_LOAD_Value-1;  /*2)put velocity load value*/
    QEI0_CTL_R  |= QEI_CTL_VELEN;      /*3)ENABLE the velocity Capture for the QEI 0*/
		 break ;
	 }
	 
	 		case QEI1:
	 {
	  QEI1_CTL_R  |= Pre_Devision;      /*1)select The Pre_Devision from config file */
    QEI1_LOAD_R |= Vel_LOAD_Value-1;  /*2)put velocity load value*/
    QEI1_CTL_R  |= QEI_CTL_VELEN;     /*3)ENABLE the velocity Capture for the QEI 1*/
		 break ;
	 }
	 
  }
}

/********************************************************************************************************************/
/*
 4----------------------------------->>QEI_Input_Filter_Configuration
Description: Configur The QEI_Module 
*Args: 
	1- Module : QEI 0 to QEI 1
* Return: void
STEPS :
1)select The filter from config file  

*/

void QEI_Input_Filter_Configuration(uint8_t module, Input_Filter_State Filter_Select)
{
    switch(module)
	{
		case QEI0:
	 {
	   QEI0_CTL_R |= Filter_Select;  /*1)select The filter from config file */
		 break ;
	 }
	 case QEI1:
	 {
	   QEI1_CTL_R |= Filter_Select; /*1)select The filter from config file  */
		 break ;
	 }
 }
}

/********************************************************************************************************************/
/*
 5----------------------------------->>QEI_Interrupts_Configuration
Description: Configur The QEI_Module 
*Args: 
	1- Module : QEI 0 to QEI 1
* Return: void
STEPS :
1)select The Int_state  from config file

*/ 
void QEI_Interrupts_Configuration(uint8_t module, Interrupt_State Int_state)
{
	 switch(module)
	{
	 case QEI0:
	 {
     QEI0_INTEN_R |= Int_state; /*1)select The Int_state  from config file*/
	   break ; 
	 }
	 case QEI1:
	 {
     QEI1_INTEN_R |= Int_state; /*1)select The Int_state  from config file*/
	   break ; 
	 }
  }
}

/********************************************************************************************************************/
/*
 6----------------------------------->>QEI_Get_Position
Description: Configur The QEI_Module 
*Args: 
	1- Module : QEI 0 to QEI 1
* Return: void
STEPS :

1)read postion value from position register

*/ 
uint32_t QEI_Get_Position(uint8_t module)
{
   switch(module)
	 {
		 case QEI0 :
		 {
       return QEI0_POS_R ;  /*1)read postion value from position register*/
			 break ;
		 }
		 case QEI1 :
		 {
       return QEI1_POS_R ;  /*1)read postion value from position register*/
			 break ;
		 }
	 }
}

/********************************************************************************************************************/
/*
 7----------------------------------->>QEI_Get_Velocity
Description: Configur The QEI_Module 
*Args: 
	1- Module : QEI 0 to QEI 1
* Return: void
STEPS :
1)read speed value from speed register

*/ 
float QEI_Get_Velocity(uint8_t module)
{

    switch(module)
	 {
		 case QEI0 :
		 {
       return QEI0_SPEED_R   ; /*1)read speed value from speed register*/
			 break ;
		 }
		 case QEI1 :
		 {
       uint32_t x =  QEI1_SPEED_R   ; /*1)read speed value from speed register*/
			 float y = 960.0 * x  ;
			 float z = 753.2 ;
			 float rpm = (y/z);
			 return rpm ; 
			 break ;
		 }
	 }
}

/********************************************************************************************************************/
/*
 8----------------------------------->>QEI_Get_Direction
Description: Configur The QEI_Module 
*Args: 
	1- Module : QEI 0 to QEI 1
* Return: void
STEPS :
1)cheack the value of diriction bit in QUI status register 

*/ 
uint32_t QEI_Get_Direction(uint8_t module)
{
	switch(module)
	 {
		case QEI0 :
		{
			if(get_bit(QEI0_STAT_R,1) == 1 )        /*1)cheack the value of diriction bit in QUI status register */
			{
					return -1;
			}
			else
			{
					return 1;
			}
		break ; 
		}
	
	 case QEI1 :
	 {
			if(get_bit(QEI1_STAT_R,1) == 1 )        /*1)cheack the value of diriction bit in QUI status register */
			{
					return -1;
			}
			else
			{
					return 1;
			}
		break ; 
	 }
  }
}
//***********************************************************************************************************************************************************
void QIE_VidEnable(uint8_t module)
{
 switch(module)
 {
	 case QEI0 : 
	 {
	  set_bit(QEI0_CTL_R,0);
	  break ;
	 }
	  case QEI1 : 
	 {
	  set_bit(QEI1_CTL_R,0);
	  break ;
	 }
 
 }



}
	