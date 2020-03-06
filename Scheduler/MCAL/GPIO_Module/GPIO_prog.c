
//Author: HOSSAM
//Release: v1.0.0
//implementation the functions's code
/***************************************/
//Edit by: HOSSAM
//Release: v1.1.0
//release notes:
//        1-Added a new function (Toggle pin)
//        2-changed the implementation for (get pin data)
//        3-general bug fixs 

#include "GPIO_interface.h"
#include "../../TM4C123GH6PM.h"

/*
*Description: sending clock to specified port
*Args: 
	1- PORT: port name
*Return: void
*/
void GPIO_init_port(int8_t PORT)
{
	switch(PORT){
		case PORTA: SYSCTL_RCGCGPIO_R |= (1<<PORTA); break;
		case PORTB: SYSCTL_RCGCGPIO_R |= (1<<PORTB); break;
		case PORTC: SYSCTL_RCGCGPIO_R |= (1<<PORTC); break;
		case PORTD: SYSCTL_RCGCGPIO_R |= (1<<PORTD); break;
		case PORTE: SYSCTL_RCGCGPIO_R |= (1<<PORTE); break;
		case PORTF: SYSCTL_RCGCGPIO_R |= (1<<PORTF); break;
	}
}


/*
*Description: specifying the direction of the data for all port pins
*Args: 
	1- PORT:  PORTA to PORTF
	2- DIRECTION: INPUT, OUTPUT, 0xXX 
*Return: void
*/
void GPIO_set_port_dir(int8_t PORT, int8_t DIRECTION)
{
	switch(PORT){
		case PORTA: 
			GPIO_PORTA_DIR_R = DIRECTION;
			GPIO_PORTA_DEN_R = 0xff;
			GPIO_PORTA_PUR_R = ~DIRECTION;
			break;
		case PORTB: 
			GPIO_PORTB_DIR_R = DIRECTION;
			GPIO_PORTB_DEN_R = 0xff;
			GPIO_PORTB_PUR_R = ~DIRECTION;
			break;
		case PORTC: 
			GPIO_PORTC_DIR_R = DIRECTION;
			GPIO_PORTC_DEN_R = 0xff;
			GPIO_PORTC_PUR_R = ~DIRECTION;
			break;
		case PORTD: 
			GPIO_PORTD_DIR_R = DIRECTION;
			GPIO_PORTD_DEN_R = 0xff;
			GPIO_PORTD_PUR_R = ~DIRECTION;
			break;
		case PORTE: 
			GPIO_PORTE_DIR_R = DIRECTION;
			GPIO_PORTE_DEN_R = 0xff;
			GPIO_PORTE_PUR_R = ~DIRECTION;
			break;
		case PORTF: 
			GPIO_PORTF_DIR_R = DIRECTION;
			GPIO_PORTF_DEN_R = 0xff;
			GPIO_PORTF_PUR_R = ~DIRECTION;
			break;
	}
}




/*
*Description: outputing data to a specified port
*Args: 
	1- PORT:  PORTA to PORTF
	2- DATA: uint8_t
*Return: void
*/
void GPIO_set_port_data(int8_t PORT, uint8_t DATA)
{
	switch(PORT){
		case PORTA: GPIO_PORTA_DATA_R = DATA; break;
		case PORTB: GPIO_PORTB_DATA_R = DATA; break;
		case PORTC: GPIO_PORTC_DATA_R = DATA; break;
		case PORTD: GPIO_PORTD_DATA_R = DATA; break;
		case PORTE: GPIO_PORTE_DATA_R = DATA; break;
		case PORTF: GPIO_PORTF_DATA_R = DATA; break;
	}
}


/*
*Description: readin data from a specified port
*Args: 
	1- PORT:  PORTA to PORTF
*Return: uint8_t the read data
*/
uint8_t GPIO_get_port_value(int8_t PORT)
{
	uint8_t data = 0;
	switch(PORT)
	{
		case PORTA: data = GPIO_PORTA_DATA_R; break;
		case PORTB: data = GPIO_PORTB_DATA_R; break;
		case PORTC: data = GPIO_PORTC_DATA_R; break;
		case PORTD: data = GPIO_PORTD_DATA_R; break;
		case PORTE: data = GPIO_PORTE_DATA_R; break;
		case PORTF: data = GPIO_PORTF_DATA_R; break;
	}
	
	return data;

}


void GPIO_set_pin_dir(int8_t PORT, int8_t PIN ,int8_t DIRECTION)
{
	switch(PORT)
	{
		case PORTA: 
			GPIO_PORTA_DIR_R |= (DIRECTION<<PIN);
			GPIO_PORTA_PUR_R |= (~DIRECTION<<PIN);
			GPIO_set_pin_signal_type(PORT, PIN, DIGITAL);
			break;
		case PORTB: 
			GPIO_PORTB_DIR_R |= (DIRECTION<<PIN);
			GPIO_PORTB_PUR_R |= (~DIRECTION<<PIN);
			GPIO_set_pin_signal_type(PORT, PIN, DIGITAL);
			break;
		case PORTC: 
			GPIO_PORTC_DIR_R |= (DIRECTION<<PIN);
			GPIO_PORTC_PUR_R |= (~DIRECTION<<PIN);
			GPIO_set_pin_signal_type(PORT, PIN, DIGITAL);
			break;
		case PORTD: 
			GPIO_PORTD_DIR_R |= (DIRECTION<<PIN);
			GPIO_PORTD_PUR_R |= (~DIRECTION<<PIN);
			GPIO_set_pin_signal_type(PORT, PIN, DIGITAL);
			break;
		case PORTE: 
			GPIO_PORTE_DIR_R |= (DIRECTION<<PIN);
			GPIO_PORTE_PUR_R |= (~DIRECTION<<PIN);
			GPIO_set_pin_signal_type(PORT, PIN, DIGITAL);
			break;
		case PORTF: 
			GPIO_PORTF_DIR_R |= (DIRECTION<<PIN);
			GPIO_PORTF_PUR_R |= (~DIRECTION<<PIN);
			GPIO_set_pin_signal_type(PORT, PIN, DIGITAL);
			break;
	}
}

void GPIO_set_pin_data(int8_t PORT, int8_t PIN, uint8_t DATA)
{
	if(DATA == 1){
		switch(PORT){
			case PORTA: GPIO_PORTA_DATA_R |= (1<<PIN); break;
			case PORTB: GPIO_PORTB_DATA_R |= (1<<PIN); break;
			case PORTC: GPIO_PORTC_DATA_R |= (1<<PIN); break;
			case PORTD: GPIO_PORTD_DATA_R |= (1<<PIN); break;
			case PORTE: GPIO_PORTE_DATA_R |= (1<<PIN); break;
			case PORTF: GPIO_PORTF_DATA_R |= (1<<PIN); break;
		}
	}
	else{
		switch(PORT){
			case PORTA: GPIO_PORTA_DATA_R &= ~(1<<PIN); break;
			case PORTB: GPIO_PORTB_DATA_R &= ~(1<<PIN); break;
			case PORTC: GPIO_PORTC_DATA_R &= ~(1<<PIN); break;
			case PORTD: GPIO_PORTD_DATA_R &= ~(1<<PIN); break;
			case PORTE: GPIO_PORTE_DATA_R &= ~(1<<PIN); break;
			case PORTF: GPIO_PORTF_DATA_R &= ~(1<<PIN); break;
		}
	}
}

uint8_t GPIO_get_pin_value(int8_t PORT, int8_t PIN)
{
	uint8_t data = 0;
	switch(PORT)
	{
		case PORTA: data = (GPIO_PORTA_DATA_R >> PIN) & 0x01; break;
		case PORTB: data = (GPIO_PORTB_DATA_R >> PIN) & 0x01; break;
		case PORTC: data = (GPIO_PORTC_DATA_R >> PIN) & 0x01; break;
		case PORTD: data = (GPIO_PORTD_DATA_R >> PIN) & 0x01; break;
		case PORTE: data = (GPIO_PORTE_DATA_R >> PIN) & 0x01; break;
		case PORTF: data = (GPIO_PORTF_DATA_R >> PIN) & 0x01; break;
	}
	
	return data;
}

void GPIO_set_pin_signal_type(int8_t PORT, int8_t PIN, int8_t SIGNAL_TYPE)
{
	switch(SIGNAL_TYPE)
	{
		case(ANALOUGE):
			switch(PORT){
				case PORTA: GPIO_PORTA_AMSEL_R |= (1<<PIN); break;
				case PORTB: GPIO_PORTB_AMSEL_R |= (1<<PIN); break;
				case PORTC: GPIO_PORTC_AMSEL_R |= (1<<PIN); break;
				case PORTD: GPIO_PORTD_AMSEL_R |= (1<<PIN); break;
				case PORTE: GPIO_PORTE_AMSEL_R |= (1<<PIN); break;
				case PORTF: GPIO_PORTF_AMSEL_R |= (1<<PIN); break;
			}
			
			case(DIGITAL):
				switch(PORT){
					case PORTA: GPIO_PORTA_DEN_R |= (1<<PIN); break;
					case PORTB: GPIO_PORTB_DEN_R |= (1<<PIN); break;
					case PORTC: GPIO_PORTC_DEN_R |= (1<<PIN); break;
					case PORTD: GPIO_PORTD_DEN_R |= (1<<PIN); break;
					case PORTE: GPIO_PORTE_DEN_R |= (1<<PIN); break;
					case PORTF: GPIO_PORTF_DEN_R |= (1<<PIN); break;
				}
				
	}
}


void GPIO_set_pin_alt_fun(int8_t PORT, int8_t PIN)
{
	switch(PORT){
			case PORTA: GPIO_PORTA_AFSEL_R |= (1<<PIN); break;
			case PORTB: GPIO_PORTB_AFSEL_R |= (1<<PIN); break;
			case PORTC: GPIO_PORTC_AFSEL_R |= (1<<PIN); break;
			case PORTD: GPIO_PORTD_AFSEL_R |= (1<<PIN); break;
			case PORTE: GPIO_PORTE_AFSEL_R |= (1<<PIN); break;
			case PORTF: GPIO_PORTF_AFSEL_R |= (1<<PIN); break;
		}
}



void GPIO_toggle_pin_value(int8_t PORT, int8_t PIN)
{
	switch(PORT){
		case PORTA: GPIO_PORTA_DATA_R ^= (1<<PIN); break;
		case PORTB: GPIO_PORTB_DATA_R ^= (1<<PIN); break;
		case PORTC: GPIO_PORTC_DATA_R ^= (1<<PIN); break;
		case PORTD: GPIO_PORTD_DATA_R ^= (1<<PIN); break;
		case PORTE: GPIO_PORTE_DATA_R ^= (1<<PIN); break;
		case PORTF: GPIO_PORTF_DATA_R ^= (1<<PIN); break;
	}
}
