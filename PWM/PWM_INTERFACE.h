 
//author: KHALED
//release v1.0.0
//the main interfacing ponit of the driver

#ifndef _INTERFACE_INTERFACE_H
#define _INTERFACE_INTERFACE_H








// OFFSETS  
#define    PWM0GENA_OFFSET                     0x060                 
#define    PWM1GENA_OFFSET                     0x0A0                     
#define    PWM2GENA_OFFSET                     0x0E0                    
#define    PWM3GENA_OFFSET                     0x120                    
#define    PWM0CTL_OFFSET                      0x040                    
#define    PWM1CTL_OFFSET                      0x080                   
#define    PWM2CTL_OFFSET                      0x0C0                     
#define    PWM3CTL_OFFSET                      0x100                  
#define    PWM0LOAD_OFFSET                     0x050                 
#define    PWM1LOAD_OFFSET                     0x090                  
#define    PWM2LOAD_OFFSET                     0x0D0                  
#define    PWM3LOAD_OFFSET                     0x110                  
#define    PWM0CMPA_OFFSET                     0x058                  
#define    PWM1CMPA_OFFSET                     0x098                  
#define    PWM2CMPA_OFFSET                     0x0D8                  
#define    PWM3CMPA_OFFSET                     0x118 



// adddress for pwm 
#define	 	PWM0_R_BASE_ADDRESSE    0x40028000
#define	 	PWM1_R_BASE_ADDRESSE    0x40029000


// CONFIGRATION




// TO  pre-divded  use bit 20
/* TO CHOSIE PRE OR NOT 
 ENABLE_PREDIVIDED          SYSCTL->RCC |=    0x00100000    // use predivided for pwm clock
 DISABLE_PREDIVED         	 SYSCTL ->RCC &= ~ 0x00100000 // not use predivded
*/ 
 // if we use it we select one from following
 // after choise enable predivided SYSCTL->RCC |= CLK2 (chose from following )
 #define clk2            0x00000000             // 8Mhz for module frequancy 
 #define clk4            0x00020000             // 4Mhz for module frequancy 	    
 #define clk8            0x00040000             // 2Mhz for module frequancy 
 #define clk16           0x00060000             // 1Mhz for module frequancy 
 #define clk64           0x000E0000             // 250khz for module frequancy 
  
 
 
 
 /* DEFENTIONS FOR DRIVER */
enum KIND 
	{
        KIND0 =0,
		KIND1,
		KIND2,
		KIND3
};


	

enum PWM_NUMBER 
{
		PWM0 = 0,
		PWM1
		
	
};








// functions 



void pwm_init_num(int8_t  pwmnumber,int8_t KIND ); // funct to inizliation
void pwm_enable(int8_t  pwmnumber, int8_t KIND   );// fucn to enable
void pwm_disbale(int8_t  pwmnumber);               //func to disable
void pwm_stop(int8_t  pwmnumber, int8_t KIND);     //func to stop
void pwm_load(int8_t  pwmnumber, int8_t KIND, int16_t load_value);  // funct to set value 
void pwm_cmp(int8_t  pwmnumber, int8_t KIND, int16_t CMP_value);   // funct to compare and duty CYCLE
void pwm_gena(int8_t  pwmnumber,int8_t KIND ); // funct to generate 





#endif
