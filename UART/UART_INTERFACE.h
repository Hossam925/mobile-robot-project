  
 
//author: KHALED
//release v1.0.0
//the main interfacing ponit of the driver
  
#ifndef    UART_INTERFACE_H
#define    UART_INTERFACE_H
	
#include <stdint.h>



  /********************************
       Public definitions
********************************/

  
/* we define buad rate to swtich any one of them when we want to use it */
	
#define buadrate           115200            // 4800 , 9600 , 57600, 115200 


/* bit for clear */
#define     UART_CTL_UARTDIS        0x00000000
#define		UART_CTL_UARTEN   	    0x00000001
/* uart offset */
#define		UART_CTL_R_OFFSET  		0x030
#define		UART_CRH_R_OFFSET   	0x02C
#define		UART_CC_R_OFFSET   		0xFC8
#define		UART_IBRD_R_OFFSET 	    0x024
#define     UART_FBRD_R_OFFSET      0x028
#define		UART_FLAG_R_OFFSET  	0x018
#define		UART_DATA_R_OFFSET      0x000





/*now we make  enum for every  def have varity */
/*Enumerations Which are used in the Configure Structure*/
typedef enum
{
	
	UART_0=0,UART_1,UART_2,UART_3,UART_4,UART_5,UART_6,UART_7
	
}UART_Number;

typedef enum
{

  BIT_5=0,BIT_6,BIT_7,BIT_8
	
}UART_WordLength;

typedef enum
{

	FIFO_DISABLED=0,FIFO_ENABLED

}UART_FIFO;



typedef enum
{

	BIT_1=0,BIT_2

}UART_StopBit;


typedef enum
{
 
	PARITY_DISABLED,PARITY_ENABLED

}UART_ParityEnable;

typedef enum
{
 
	ODD_PARITY=0,EVEN_PARITY

}UART_ParitySelect;




typedef enum
{

	NO_INTERRUPT=0,INTERRUPT

}UART_InterruptSelect;





/* Configuration Structures */

/*This structure should be configured by the Driver user to initiate the various UART modules
  With any required settings */
typedef struct configure
{
	
    UART_Number          UN;
    UART_WordLength      UWL;
    UART_ParityEnable    UPE;
    UART_InterruptSelect UIS;
    UART_ParitySelect    UPS;
    UART_StopBit         USB;
    UART_FIFO            UF;
	
}UART_ConfigureStruct;




/*Function Prototypes*/

/*This function initializes the UART module ( GPIO / UART Registers ) */
/*Inputs: Reference to the ConfigureStruct which contains all the required settings to be set*/
void UART_init(uint8_t Num);



/*This function sends only one byte of data(Word Length)*/
/*Inputs: The UART number module to be sent from
          The 8-bits word to be sen                     */
void UART_sendByte(UART_Number,uint8_t data);


/*This function receives only one byte of data(Word Length)*/
/*Inputs: The UART number module to receive on*/
/*Return: The 8-bit(one byte) data received*/
uint8_t UART_receiveByte(UART_Number);

void UART_sendString(char* arr);
void UART_Print_Number(float fNumber);

#endif
