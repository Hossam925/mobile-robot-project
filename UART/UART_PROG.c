
//Author: khaled
//Release: v1.0.0
//implementation the functions's code



#include "GPIO_interface.h"
#include "TM4.h"
#include "UART_INTERFACE.h"
#include "UART_cfg.h"


extern UART_ConfigureStruct* U_Array[8];

/* delay n milliseconds (16 MHz CPU clock) */


static uint32_t USART_baseAddresses[] =
	{

		UART0_BASE,
		UART1_BASE,
		UART2_BASE,
		UART3_BASE,
		UART4_BASE,
		UART5_BASE,
		UART6_BASE,
		UART7_BASE

};


void UART_init(uint8_t Num)
{
    const UART_ConfigureStruct * configure_pointer = U_Array[Num];
	uint8_t uart_num, word_wdth, prt_sel, f_en, stp, prt_en;

	word_wdth = configure_pointer->UWL;
	word_wdth = (word_wdth << 5);

	prt_sel = configure_pointer->UPS;
	prt_sel = (prt_sel << 2);

	f_en = configure_pointer->UF;
	f_en = (f_en << 4);

	stp = configure_pointer->USB;
	stp = (stp << 3);

	prt_en = configure_pointer->UPE;
	prt_en = (prt_en << 1);


	//determine the the UART Number to know which TX and RX we will use
	uart_num = configure_pointer->UN;

    //enable system clk
    SYSCTL_RCGCUART_R |= (1<<uart_num ) ;
		int i, j;
		for(i=0;i<3;i++);
		for (j=0;j <3180;j++)
		{}
	//disable the UART to set it
	CUSTOM_REG(USART_baseAddresses[uart_num] , UART_CTL_R_OFFSET) = UART_CTL_UARTDIS;

	//adjust the Baud Rate
	
	
	// BUAD RATE DIVSOR LET IT = 9600 AND CRYSTAL 16MHZ
  // BRD =	160000000 / (16*buadrate)=104.166666666666666666666666666666666
	// UARTBRD = INTEGER(0.16666667* 64 * 0.5 ) = 11
	
	 switch (buadrate)
	 {
		 case 4800 :
	CUSTOM_REG(USART_baseAddresses[uart_num] , UART_IBRD_R_OFFSET) = 208;
	CUSTOM_REG(USART_baseAddresses[uart_num] , UART_FBRD_R_OFFSET) = 21;
		 
		 break ;
		 case 9600 :
	CUSTOM_REG(USART_baseAddresses[uart_num] , UART_IBRD_R_OFFSET) = 104;
	CUSTOM_REG(USART_baseAddresses[uart_num] , UART_FBRD_R_OFFSET) = 11;
		 
		 break ;	 
		 	 case 57600 :
	CUSTOM_REG(USART_baseAddresses[uart_num] , UART_IBRD_R_OFFSET) = 17;
	CUSTOM_REG(USART_baseAddresses[uart_num] , UART_FBRD_R_OFFSET) = 23;
		 
		 break ;
			 	 case 115200 :
	CUSTOM_REG(USART_baseAddresses[uart_num] , UART_IBRD_R_OFFSET) = 8;
	CUSTOM_REG(USART_baseAddresses[uart_num] , UART_FBRD_R_OFFSET) = 44;
		 
		 break ;
			 }

	//adjust the UARTLCRH
	CUSTOM_REG(USART_baseAddresses[uart_num] , UART_CRH_R_OFFSET) |= word_wdth;
	CUSTOM_REG(USART_baseAddresses[uart_num] , UART_CRH_R_OFFSET) |= prt_sel;
	CUSTOM_REG(USART_baseAddresses[uart_num] , UART_CRH_R_OFFSET) |= stp;
	CUSTOM_REG(USART_baseAddresses[uart_num] , UART_CRH_R_OFFSET) |= prt_en;

	//adjuct UARTCC to internal clock
	CUSTOM_REG(USART_baseAddresses[uart_num] , UART_CC_R_OFFSET) = 0;
	
	//enable the UART to set it
	CUSTOM_REG(USART_baseAddresses[uart_num] , UART_CTL_R_OFFSET) |= 0x301;
}


//recieve byte function
uint8_t UART_receiveByte(UART_Number uNumber){
			
	//checking for the RXFE (bit 4) int the FLAG REGISTER....if bit = 0 then not empty and 
	//we will start reading
 	while((CUSTOM_REG(USART_baseAddresses[uNumber],UART_FLAG_R_OFFSET)& 0x00000010) != 0);
				
		return CUSTOM_REG(USART_baseAddresses[uNumber],UART_DATA_R_OFFSET);
}




/* Send Byte From UART */

void UART_sendByte(UART_Number uNumber, const uint8_t jOneChar)
{
		
	// 0x00000020 --> TXFF :: Transmitter Full Bit number 5

	
	//	while (!(*((volatile uint32_t *)((USART_baseAddresses[ uNumber] + UART_FLAG_R_OFFSET)))) & 0x00000020);
	

//	(*((volatile uint32_t *)((USART_baseAddresses[uNumber] + UART_DATA_R_OFFSET)))) = jOneChar;
	while ((CUSTOM_REG(USART_baseAddresses[uNumber] , UART_FLAG_R_OFFSET) & 0x00000020) !=0 ){};
    while((UART0_FR_R & 0x80) == 0);

	CUSTOM_REG(USART_baseAddresses[uNumber] , UART_DATA_R_OFFSET) = jOneChar;
}




void UART_sendString(char* arr)
{
		uint8_t i = 0;
	while(arr[i] != '\0')
	{
		UART_sendByte(UART_0,arr[i]);
		i++;
	}
	

}

void UART_Print_Number(float fNumber)
{
	int32_t Number = fNumber;
	uint8_t start=2;
	uint16_t Digits[10]={0};
	uint16_t Dnum=9,temp=0;
	uint16_t last;



	if(Number<0)
	{
		UART_sendByte(UART_0,'-');
		Number *=-1;
		fNumber *=-1;
	}

	last = (fNumber*100) - (Number*100);

	if(Number>=10000){start=1;}

	do
	{
		temp=Number%10;
		Number=Number/10;
		--Dnum;
		Digits[Dnum]=temp + '0';
	}while(Number!=0);




	for(uint8_t counter=start;counter<=9;counter++)
	{
		if(Digits[counter]==0)
		{
			continue;
		}

		UART_sendByte(UART_0,Digits[counter]);
	}


	if(last !=0)
	{	UART_sendByte(UART_0,'.');
		UART_Print_Number(last);
	}

}

