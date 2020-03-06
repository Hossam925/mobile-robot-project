
//author: HOSSAM
//release v1.0.0
//the main interfacing ponit of the driver
/***************************************/
//Edit by: HOSSAM
//Release: v1.1.0
//release notes:
//        1-Added a new function (Toggle pin)
//        2-changed the implementation for (get pin data)
//        3-general bug fixs 

#include <stdint.h>

#ifndef _GPIO_INTERFACE_H
#define _GPIO_INTERFACE_H
/********************************
       Public definitions
********************************/
enum PORTS{
		PORTA = 0,
	  PORTB,
		PORTC,
		PORTD,
		PORTE,
		PORTF
	
};

enum PINS{
	PIN0 = 0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7
};

enum DIRECTION{
	INPUT = 0x00,
	OUTPUT = 0xFF
};

enum PIN_DIRECTION{
	PIN_INPUT = 0,
	PIN_OUTPUT 
};

enum SIGNAL_TYPE{
		DIGITAL = 0,
		ANALOUGE
};

/********************************
       Public functions
********************************/


/*
*Description: sending clock to specified port
*Args: 
	1- PORT: PORTA to PORTF
*Return: void
*/
void GPIO_init_port(int8_t PORT);



/*
*Description: specifing the diriction of the data for all port pins
*Args: 
	1- PORT:  PORTA to PORTF
	2- DIRECTION: INPUT, OUTPUT, 0xXX 
*Returt: void
*/
void GPIO_set_port_dir(int8_t PORT, int8_t DIRECTION);





/*
*Description: outputing data to a specified port
*Args: 
	1- PORT:  PORTA to PORTF
	2- DATA: uint8_t
*Return: void
*/
void GPIO_set_port_data(int8_t PORT, uint8_t DATA);




/*
*Description: reading data from a specified port
*Args: 
	1- PORT:  PORTA to PORTF
*Return: uint8_t the read data
*/
uint8_t GPIO_get_port_value(int8_t PORT);





/*
*Description: specifing the diriction of the data for a specific pin
*Args: 
	1- PORT:  PORTA to PORTF
	2- PIN: 0-7
	3- DIRECTION: PIN_INPUT, PIN_OUTPUT 
*Returt: void
*/
void GPIO_set_pin_dir(int8_t PORT, int8_t PIN ,int8_t DIRECTION);




/*
*Description: setting the value for a specific pin
*Args: 
	1- PORT:  PORTA to PORTF
	2- PIN: 0-7
	3- DATA: unit8_t
*Return: void
*/
void GPIO_set_pin_data(int8_t PORT, int8_t PIN, uint8_t DATA);




/*
*Description: reading the value of a specific pin
*Args: 
	1- PORT:  PORTA to PORTF
	2- PIN: 0-7
*Return: the value
*/
uint8_t GPIO_get_pin_value(int8_t PORT, int8_t PIN);



/*
*Description: specifing the pin signal type
*Args: 
	1- PORT:  PORTA to PORTF
	2- PIN: 0-7
	3- SIGNAL_TYPE: ANALOUGE or DIGITAL
*Return: the value
*/
void GPIO_set_pin_signal_type(int8_t PORT, int8_t PIN, int8_t SIGNAL_TYPE);



void GPIO_set_pin_alt_fun(int8_t PORT, int8_t PIN);

void GPIO_toggle_pin_value(int8_t PORT, int8_t PIN);

#endif
