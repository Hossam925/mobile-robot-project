/*************************************************************************************************************************************************
                                               Serial Perphirals interface "SPI" source file 
																							       implementation the functions's code
                                                      Hardware:  TM4C123 Tiva board
                                                          ---> author: Ahmed Khaled       
                                                          ---> release v1.0.0
*************************************************************************************************************************************************/


#ifndef SPI_HAL_H
#define SPI_HAL_H

#include <stdint.h>
/********************************************************************************************************************************************
                                                          Public definitions 
																													
	 1- we have 4 SPI channel from SPI0 to SPI1  
	 2- I make some define for some bits related with SPI 
	 
*/ 			
			
  
//*****************************************************************************
//
// The following are defines for SPI_Module NO.
//
//*****************************************************************************

#define  SPI0  0
#define  SPI1  1
#define  SPI2  2
#define  SPI3  3

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGCSSI register.
//
//*****************************************************************************

#define Enable_SPI3       0x00000008  // SSI Module 3 Sleep Mode Clock
                                            // Gating Control
#define Enable_SPI2       0x00000004  // SSI Module 2 Sleep Mode Clock
                                            // Gating Control
#define Enable_SPI1       0x00000002  // SSI Module 1 Sleep Mode Clock
                                            // Gating Control
#define Enable_SPI0       0x00000001  // SSI Module 0 Sleep Mode Clock

//*****************************************************************************
//
// The following are defines for Digital function (GPIOPCTL PMCx Bit Field Encoding) Port A 
//
//*****************************************************************************                                            

#define PA5_SSI0TX    0x00200000  // SSI0TX  on PA5
#define PA4_SSI0RX    0x00020000  // SSI0RX  on PA4
#define PA3_SSI0FSS   0x00002000  // SSI0FSS on PA3
#define PA2_SSI0CLK   0x00000200  // SSI0CLK on PA2

//*****************************************************************************
//
// The following are defines for Digital function (GPIOPCTL PMCx Bit Field Encoding) Port B 
//
//*****************************************************************************                                            

#define PB7_SSI2TX    0x20000000  // SSI2TX  on PB7
#define PB6_SSI2RX    0x02000000  // SSI2RX  on PB6
#define PB5_SSI2FSS   0x00200000  // SSI2FSS on PB5
#define PB4_SSI2CLK   0x00020000  // SSI2CLK on PB4

//*****************************************************************************
//
// The following are defines for Digital function (GPIOPCTL PMCx Bit Field Encoding) Port D
//
//*****************************************************************************                                            

#define PD3_SSI3TX    0x00001000  // SSI3TX  on PD3
#define PD2_SSI3RX    0x00000100  // SSI3RX  on PD2
#define PD1_SSI3FSS   0x00000010  // SSI3FSS on PD1
#define PD0_SSI3CLK   0x00000001  // SSI3CLK on PD0

//*****************************************************************************
//
// The following are defines for Digital function (GPIOPCTL PMCx Bit Field Encoding) Port F
//
//*****************************************************************************  

#define PF3_SSI1FSS   0x00002000  // SSI1FSS on PF3
#define PF2_SSI1CLK   0x00000200  // SSI1CLK on PF2
#define PF1_SSI1TX    0x00000020  // SSI1TX  on PF1
#define PF0_SSI1RX    0x00000002  // SSI1RX  on PF0

//*****************************************************************************
//
// The following are defines for the bit fields in the SSI_O_CR1 register.
//
//*****************************************************************************

#define SPI_CR1_EOT                 0x00000010  // End of Transmission
#define SPI_CR1_Slave               0x00000004  // SSI Slave Select
#define SPI_CR1_Master              0x00000000  // SSI Master Select
#define SPI_CR1_SSE                 0x00000002  // SSI Synchronous Serial Port
#define SPI_CR1_LBM                 0x00000001  // SSI Loopback Mode
#define master                           1
#define slave                            0

//*****************************************************************************
//
// The following are defines for the bit fields in the SSI_O_CR0 register.
//
//
//*****************************************************************************
#define pre_scaler     8               //for 1,2 nibble from 2 to 254
#define SCR            0x0100             //for 3,4 nibble from 0 to 255
#define data_bit       0x0007             //first nibble
#define freescale_SPI  0x0000             //second nibble with SPO = 0 , SPH = 0 

//*****************************************************************************
//
// The following are defines for the bit fields in the SSI_O_SR register.
//
//*****************************************************************************
#define SPI_SR_BSY              0x00000010  // SSI Busy Bit
#define SPI_SR_RFF              0x00000008  // SSI Receive FIFO Full
#define SPI_SR_RNE              0x00000004  // SSI Receive FIFO Not Empty
#define SPI_SR_TNF              0x00000002  // SSI Transmit FIFO Not Full
#define SPI_SR_TFE              0x00000001  // SSI Transmit FIFO Empty

//*****************************************************************************
//
// The following are defines for the bit fields in the SSI_O_CC register (clock configuration and select)
//
//*****************************************************************************
#define SPI_CC_CS_M             0x0000000F  // SSI Baud Clock Source
#define SPI_CC_CS_SYSPLL        0x00000000  // System clock (based on clock
                                            // source and divisor factor)
#define SPI_CC_CS_PIOSC         0x00000005  // PIOSC

//*****************************************************************************
/**************************************************************************************************************************************************
                                                     Public functions
																										 
*/
void SPI_VidInit(uint8_t module);
void SPI_VidMasterSlaveInit(uint8_t module ,uint8_t master_slave_select);
void SPI_VidTransmit(uint8_t module ,uint8_t data); 
uint8_t SPI_U8Receive(uint8_t module);
uint8_t SPI_uint8_tTrancieve(uint8_t module,uint8_t data);


#endif




