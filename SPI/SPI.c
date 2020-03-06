/*************************************************************************************************************************************************
                                               Serial Perphirals interface "SPI" source file 
																							       implementation the functions's code
                                                      Hardware:  TM4C123 Tiva board
                                                          ---> author: Ahmed Khaled       
                                                          ---> release v1.0.0
*************************************************************************************************************************************************/

#include <stdint.h>    // --------------------->>include file for stdandard data types 
#include "macros.h"                                        
#include "GPIO_interface.h"
#include "SPI_Private.h"
#include "tm4.h"   //-------------------------->header file to link address to register name section

/*******************************************************************************************************************
                                                functions implementations
																								
1----------------------------------->>SPI_Initialization
2----------------------------------->>MasterSlave_Init
3----------------------------------->>Data Transmit
4----------------------------------->>Data Receive

******************************************************************************************************************/



/*
 1----------------------------------->>SPI_Initialization 
Description: Initialize The SPI_Module 
*Args: 
	1- Module : SPI0 to SPI3
* Return: void
STEPS :
1)Enable The SPI Module 
2)Enable Clock for  GPIO Port Related with SPI Module 
3)Set Altrnate Function Select for each pin in SPI Module
4)Set Digital Function Bit field Encoding for each bit in GPIOPCTL
5)make Pins for SPI Dgital DEN  
       
*/


void SPI_VidInit(uint8_t module)
{
  switch(module)
		{
		case SPI0:
		{ 
			SYSCTL_RCGCSSI_R |= Enable_SPI0;  //1)Enable The SPI Module 
			GPIO_init_port(PORTA);            //2)PORTA intialization related with SPI0
			GPIO_set_pin_alt_fun(PORTA,PIN2);   //3)Set Altrnate Function Select for pin2 SSI0CLK in SPI0 Module
			GPIO_set_pin_alt_fun(PORTA,PIN3);   //3)Set Altrnate Function Select for pin3 SSI0FSS in SPI0 Module
			GPIO_set_pin_alt_fun(PORTA,PIN4);   //3)Set Altrnate Function Select for pin4 SSI0RX  in SPI0 Module
			GPIO_set_pin_alt_fun(PORTA,PIN5);   //3)Set Altrnate Function Select for pin5 SSI0TX  in SPI0 Module
			
			GPIO_PORTA_PCTL_R  |= ( PA2_SSI0CLK | PA3_SSI0FSS | PA4_SSI0RX | PA5_SSI0TX );   //4)Set Digital Function Bit field Encoding for each bit in GPIOPCTL
			GPIO_set_pin_signal_type(PORTA, PIN2, DIGITAL); //5)make Pin2 for SPI Dgital DEN
			GPIO_set_pin_signal_type(PORTA, PIN3, DIGITAL); //5)make Pin3 for SPI Dgital DEN
			GPIO_set_pin_signal_type(PORTA, PIN4, DIGITAL); //5)make Pin4 for SPI Dgital DEN
			GPIO_set_pin_signal_type(PORTA, PIN5, DIGITAL); //5)make Pin5 for SPI Dgital DEN
			
	
			
			break ;
		}
		case SPI1:
		{
			SYSCTL_RCGCSSI_R |= Enable_SPI1;
			GPIO_init_port(PORTF);
			GPIO_PORTF_LOCK_R = 0x4C4F434B;
			GPIO_PORTF_CR_R = 0x01;
			GPIO_set_pin_alt_fun(PORTF,PIN2);
			GPIO_set_pin_alt_fun(PORTF,PIN3);
			GPIO_set_pin_alt_fun(PORTF,PIN0);
			GPIO_set_pin_alt_fun(PORTF,PIN1);
			GPIO_PORTF_PCTL_R |= ( PF0_SSI1RX  | PF1_SSI1TX  | PF2_SSI1CLK | PF3_SSI1FSS );
			GPIO_set_pin_signal_type(PORTF, PIN2, DIGITAL);
			GPIO_set_pin_signal_type(PORTF, PIN3, DIGITAL);
			GPIO_set_pin_signal_type(PORTF, PIN0, DIGITAL);
			GPIO_set_pin_signal_type(PORTF, PIN1, DIGITAL);

			break ;
		}
		case SPI2:
		{
			SYSCTL_RCGCSSI_R |= Enable_SPI2;
			GPIO_init_port(PORTB);
			GPIO_set_pin_alt_fun(PORTB,PIN4);
			GPIO_set_pin_alt_fun(PORTB,PIN5);
			GPIO_set_pin_alt_fun(PORTB,PIN6);
			GPIO_set_pin_alt_fun(PORTB,PIN7);
			GPIO_PORTB_PCTL_R |= ( PB7_SSI2TX  | PB6_SSI2RX  | PB4_SSI2CLK | PB5_SSI2FSS );
			GPIO_set_pin_signal_type(PORTB, PIN4, DIGITAL);
			GPIO_set_pin_signal_type(PORTB, PIN5, DIGITAL);
			GPIO_set_pin_signal_type(PORTB, PIN6, DIGITAL);
			GPIO_set_pin_signal_type(PORTB, PIN7, DIGITAL);

			break ;
		}
		case SPI3:
		{ 
			SYSCTL_RCGCSSI_R |= Enable_SPI3;
			GPIO_init_port(PORTD);
			GPIO_set_pin_alt_fun(PORTD,PIN0);
			GPIO_set_pin_alt_fun(PORTD,PIN1);
			GPIO_set_pin_alt_fun(PORTD,PIN2);
			GPIO_set_pin_alt_fun(PORTD,PIN3);
			GPIO_PORTB_PCTL_R |= ( PD3_SSI3TX  | PD2_SSI3RX  | PD0_SSI3CLK | PD1_SSI3FSS );
			GPIO_set_pin_signal_type(PORTD, PIN0, DIGITAL);
			GPIO_set_pin_signal_type(PORTD, PIN1, DIGITAL);
			GPIO_set_pin_signal_type(PORTD, PIN2, DIGITAL);
			GPIO_set_pin_signal_type(PORTD, PIN3, DIGITAL);

			break ;
		}
	}
}

/********************************************************************************************************************/

/* 2----------------------------------->>Master_Init
Description: Initialize SPI master ,POL = 0 , PHA = 0, clock = ..... ,8 bit data 
*Args: 
	1- SPI_module :SPI0 to SPI3
* Return: void
STEPS :
  1) Disable SPI before making any cofiguration change and act as master  
  2) select master or slave 
	2) use the system clock not PIOSC "percision internal osc 16 MHZ"
	3) Configure the clock prescale divisor by writing the SSICPSC
  4) configure the Serial clock rate value to genertat the bit rate  
  5) 8 bit data , SPI module 
  6) Enable SPI
*/
void SPI_VidMasterSlaveInit(uint8_t module ,uint8_t master_slave_select)
{
   switch(module)
	 {
	  case SPI0:
		{ 
			SSI0_CR1_R   &= ~(1<<0); // Disable SPI before making any cofiguration change  
			if(master_slave_select == master)
			{
				SSI0_CR1_R  |= SPI_CR1_Master ;         //act as master
			}
			else
			{
			 SSI0_CR1_R   |= SPI_CR1_Slave ;           //act as slave
			}
			SSI0_CC_R    = SPI_CC_CS_SYSPLL ; //use PIOSC "percision internal osc 16 MHZ" NOt the system clock 
			SSI0_CPSR_R |= pre_scaler; // Configure the clock prescale divisor by writing the SSICPSC "PLZ configuer it "
			SSI0_CR0_R  |= SCR ;       //configure the Serial clock rate value to genertat the bit rate "PLZ configuer it"
			SSI0_CR0_R  |= (freescale_SPI | data_bit ); //8 bit data , SPI module 
			SSI0_CR1_R   |= SPI_CR1_SSE ; //Enable SPI
      break ;
		}			
			case SPI1:
		{ 
			SSI1_CR1_R   &= ~(1<<1); //Disable SPI before making any cofiguration change  
			if(master_slave_select == master)
			{
				SSI1_CR1_R   |= SPI_CR1_Master ;         //act as master
			}
			else
			{
			 SSI1_CR1_R   |= SPI_CR1_Slave ;           //act as slave
			}
			SSI1_CC_R    = SPI_CC_CS_SYSPLL; //use the system clock not PIOSC "percision internal osc 16 MHZ"
			SSI1_CPSR_R |= pre_scaler; // Configure the clock prescale divisor by writing the SSICPSC
			SSI1_CR0_R  |= SCR ;       //configure the Serial clock rate value to genertat the bit rate
			SSI1_CR0_R  |= (freescale_SPI | data_bit ); //8 bit data , SPI module 
			SSI1_CR1_R  |= SPI_CR1_SSE ; //Enable SPI
      break ;
		}	
      case SPI2:
		{ 
      SSI2_CR1_R   &= ~(1<<2); //Disable SPI before making any cofiguration change  
			if(master_slave_select == master)
			{
				SSI2_CR1_R   |= SPI_CR1_Master ;         //act as master
			}
			else
			{
			 SSI2_CR1_R   |= SPI_CR1_Slave ;           //act as slave
			}
			SSI2_CC_R    = 0; //use the system clock not PIOSC "percision internal osc 16 MHZ"
			SSI2_CPSR_R |= pre_scaler; // Configure the clock prescale divisor by writing the SSICPSC
			SSI2_CR0_R  |= SCR ;       //configure the Serial clock rate value to genertat the bit rate
			SSI2_CR0_R  |= (freescale_SPI | data_bit ); //8 bit data , SPI module 
			SSI2_CR1_R  |= SPI_CR1_SSE ; //Enable SPI
      break ;
		}	
      case SPI3:
		{ 
			SSI3_CR1_R   &= ~(1<<3); //Disable SPI before making any cofiguration change  
			if(master_slave_select == master)
			{
				SSI3_CR1_R   |= SPI_CR1_Master ;         //act as master
			}
			else
			{
			 SSI3_CR1_R   |= SPI_CR1_Slave ;           //act as slave
			}
			SSI3_CC_R    = 0; //use the system clock not PIOSC "percision internal osc 16 MHZ"
			SSI3_CPSR_R |= pre_scaler; // Configure the clock prescale divisor by writing the SSICPSC
			SSI3_CR0_R  |= SCR ;       //configure the Serial clock rate value to genertat the bit rate
			SSI3_CR0_R  |= (freescale_SPI | data_bit ); //8 bit data , SPI module 
			SSI3_CR1_R  |= SPI_CR1_SSE ; //Enable SPI
      break ;
		}					
	 
	 }  
}
/*****************************************************************************************************************/

/* 3----------------------------------->>Data Transmit
Description: Initialize SPI master ,POL = 0 , PHA = 0, clock = ..... ,8 bit data 
*Args: 
	1- SPI_module :SPI0 to SPI3
  2- send Data 
* Return: void
STEPS :
  1) Assert SS 0 "Active slave select"
  2) wait until FIFO not full 
	3) upload data 
	4) wait until transmit complete
  5) Deassert SS 1 " Disable slave select
*/

void SPI_VidTransmit(uint8_t module ,uint8_t data) 
{
  switch(module)
	{
		case SPI0:
		{
		 //GPIO_set_pin_data(PORTA,PIN3,0);  // Assert SS 0 "Active slave select"
		//	GPIO_PORTA_DATA_R &=~(1<<3);
		 while((SSI0_SR_R & SPI_SR_TNF ) == 0) ;//wait until FIFO not full
		 SSI0_DR_R = data ;
		 while((SSI0_SR_R & SPI_SR_BSY)!=0) ;   //wait until transmit complete
//		 GPIO_set_pin_data(PORTA,PIN3,1);  // Deassert SS 1 " Disable slave select
//		 GPIO_PORTA_DATA_R |=(1<<3);
     break ; 
		}
		case SPI1:
		{
		// GPIO_set_pin_data(PORTF,PIN3,0);  // Assert SS 0 "Active slave select"
		 while((SSI1_SR_R & SPI_SR_TNF ) == 0) ;//wait until FIFO not full
		 SSI0_DR_R = data ;
		 while(SSI1_SR_R & SPI_SR_BSY ) ;   //wait until transmit complete
		 GPIO_set_pin_data(PORTF,PIN3,1);  // Deassert SS 1 " Disable slave select
     break ; 
		}case SPI2:
		{
		 GPIO_set_pin_data(PORTB,PIN5,0);  // Assert SS 0 "Active slave select"
		 while((SSI2_SR_R & SPI_SR_TNF ) == 0) ;//wait until FIFO not full
		 SSI0_DR_R = data ;
		 while(SSI2_SR_R & SPI_SR_BSY ) ;   //wait until transmit complete
		 GPIO_set_pin_data(PORTB,PIN5,1);  // Deassert SS 1 " Disable slave select
     break ; 
		}case SPI3:
		{
		 //GPIO_set_pin_data(PORTD,PIN1,0);  // Assert SS 0 "Active slave select"
		 while((SSI3_SR_R & SPI_SR_TNF ) == 0) ;//wait until FIFO not full
		 SSI0_DR_R = data ;
		 while(SSI3_SR_R & SPI_SR_BSY ) ;   //wait until transmit complete
		 //GPIO_set_pin_data(PORTD,PIN1,1);  // Deassert SS 1 " Disable slave select
     break ; 
		}
		
	}
	
}

/*****************************************************************************************************************/

/* 4----------------------------------->>Data Receive 
Description: Initialize SPI master ,POL = 0 , PHA = 0, clock = ..... ,8 bit data 
*Args: 
	1- SPI_module :SPI0 to SPI3
* Return: void
STEPS :
  1) wait until reception complete
  2) return SSI0_DR_R "receive data"
	
*/

uint8_t SPI_U8Receive(uint8_t module)
{  
	 uint8_t data ;
	 switch(module)
	 {
		 case SPI0:
		{
	  while((SSI0_SR_R & SPI_SR_RNE) == 0){} ; //wait until Receive FIFO Not empty
     data = SSI0_DR_R ;
	  break ;
	  }
		 case SPI1:
		{
	  while((SSI1_SR_R & SPI_SR_RNE ) == 0){} ; //wait until Receive FIFO not full
    data = SSI1_DR_R ;
	  break ;
   }
		 case SPI2:
		{
	  while((SSI2_SR_R & SPI_SR_RNE ) == 0){} ; //wait until Receive FIFO not full
    data = SSI2_DR_R ;
	  break ;
		}
		 case SPI3:
		{
	  while((SSI3_SR_R & SPI_SR_RNE ) == 0){} ; //wait until Receive FIFO not full
    data = SSI3_DR_R ;
	  break ;
		}
	}
	 return data ;
}


uint8_t SPI_uint8_tTrancieve(uint8_t module,uint8_t data)
{
	 switch(module)
	{
		case SPI0:
		{
		 //GPIO_set_pin_data(PORTA,PIN3,0);  // Assert SS 0 "Active slave select"
		//	GPIO_PORTA_DATA_R &=~(1<<3);
		 while((SSI0_SR_R & SPI_SR_TNF ) == 0) ;//wait until FIFO not full
		 SSI0_DR_R = data ;
		 while((SSI0_SR_R & SPI_SR_BSY)!=0) ;   //wait until transmit complete
//		 GPIO_set_pin_data(PORTA,PIN3,1);  // Deassert SS 1 " Disable slave select
//		 GPIO_PORTA_DATA_R |=(1<<3);
			data = SSI0_DR_R ;
     break ; 
		}
		case SPI1:
		{
		// GPIO_set_pin_data(PORTF,PIN3,0);  // Assert SS 0 "Active slave select"
		 while((SSI1_SR_R & SPI_SR_TNF ) == 0) ;//wait until FIFO not full
		 SSI0_DR_R = data ;
		 while(SSI1_SR_R & SPI_SR_BSY ) ;   //wait until transmit complete
		 GPIO_set_pin_data(PORTF,PIN3,1);  // Deassert SS 1 " Disable slave select
			data = SSI1_DR_R ;
     break ; 
		}case SPI2:
		{
		 GPIO_set_pin_data(PORTB,PIN5,0);  // Assert SS 0 "Active slave select"
		 while((SSI2_SR_R & SPI_SR_TNF ) == 0) ;//wait until FIFO not full
		 SSI0_DR_R = data ;
		 while(SSI2_SR_R & SPI_SR_BSY ) ;   //wait until transmit complete
		 GPIO_set_pin_data(PORTB,PIN5,1);  // Deassert SS 1 " Disable slave select
			data = SSI2_DR_R ;
     break ; 
		}case SPI3:
		{
		 GPIO_set_pin_data(PORTD,PIN1,0);  // Assert SS 0 "Active slave select"
		 while((SSI3_SR_R & SPI_SR_TNF ) == 0) ;//wait until FIFO not full
		 SSI0_DR_R = data ;
		 while(SSI3_SR_R & SPI_SR_BSY ) ;   //wait until transmit complete
		 GPIO_set_pin_data(PORTD,PIN1,1);  // Deassert SS 1 " Disable slave select
			data = SSI3_DR_R ;
     break ; 
		}
		
	}
	return data;
}

