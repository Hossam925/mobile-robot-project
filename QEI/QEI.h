/*************************************************************************************************************************************************
**************
                                               Quadrature Encoder Interface "QEI" header file 
																							       implementation the functions's code
                                                      Hardware:  TM4C123 Tiva board
                                                          ---> author: Ahmed Khaled       
                                                          ---> release v1.0.0
*************************************************************************************************************************************************/
/**
 *  @file  <QEI.h>
 *  @brief <Header File of The Quadrature Encoder Interface(QEI) Module of the Tm4c123 controller.>
 *         <It contains The Prototypes of all function available in
 *          the library,definitions of all Macros, and Enumerations>
 *
 *************************************************************************************************************************************************/

#ifndef _QEI_H_
#define _QEI_H_


#include <stdint.h>
/********************************************************************************************************************************************
                                                          Public definitions 
																													
	 1- we have 2 QEI in tiva c   
	 2- I make some define for some bits related with QEI
	 
*/ 		

//***************************************************************************************************************************************
 
/* This Enumeration select the signal Mode for each QEI Module*/
  typedef enum
  {
      QEI_Quadrature_PHASE_SIG = 0x00000000,        QEI_CLOCK_DIR_SIG      = 0x00000004,

  }QEI_SIG_MODE;

//****************************************************************************************************************************************
	
/* This Enumeration Select the Reset state for each QEI Module*/
  typedef enum
  {
      QEI_NO_RESET_ON_INDEX  =     0x00000000,       QEI_RESET_ON_INDEX_CHANGE =  0x00000010,

  }Reset_State;

//****************************************************************************************************************************************
	
/* This Enumeration Select the signal capture mode for each QEI Module*/
	               /*not applicable with clock and diriction mode*/
  typedef enum
  {
      QEI_CAP_PhA_ONLY       =     0x00000000,       QEI_CAP_BOTH_PhA_PhB     =  0x00000008,

  }Signal_CAP_Mode;

//****************************************************************************************************************************************
	
 /* This Enumeration Selects between signal swapping or not  for each QEI Module*/
  typedef enum
  {
      QEI_NO_SIG_SWAP        =     0x00000000,       QEI_SWAP_SIGNAL      =       0x00000002,

  }SWAP_State;

//****************************************************************************************************************************************
	
/* This Enumeration Selects the Inversion state for the signal and the index for each QEI Module*/
  typedef enum
  {
      QEI_NO_INVERT          =      0x00000000,     QEI_INVERT_INDEX       =      0x00000800,
      QEI_INVERT_PhA         =      0x00000200,     QEI_INVERT_PhB         =      0x00000400,
      QEI_INVERT_A_B         =      0x00000600,     QEI_INVERT_A_B_I       =      0x00000E00,
  }Signal_invert_State;

//****************************************************************************************************************************************
	
/* This Enumeration Selects the velocity predevide value  for each QEI Module*/
  typedef enum
  {
      QEI_VEL_PRE_DIV_1      =      0x00000000,     QEI_VEL_PRE_DIV_2      =      0x00000040,
      QEI_VEL_PRE_DIV_4      =      0x00000080,     QEI_VEL_PRE_DIV_8      =      0x000000C0,
      QEI_VEL_PRE_DIV_16     =      0x00000100,     QEI_VEL_PRE_DIV_32     =      0x00000140,
      QEI_VEL_REW_DIV_64     =      0x00000180,     QEI_VEL_PRE_DIV_128    =      0x000001C0,
  }Velocity_PreDevide;
	
//****************************************************************************************************************************************
	
/* This Enumeration Selects the velocity predevide value for each QEI Module*/
  typedef enum
  {
      QEI_NO_FILTER          =      0x00000000,     QEI_FILTCNT_3          =      0x00012000,
      QEI_FILTCNT_4          =      0x00022000,     QEI_FILTCNT_5          =      0x00032000,
      QEI_FILTCNT_6          =      0x00042000,     QEI_FILTCNT_7          =      0x00052000,
      QEI_FILTCNT_8          =      0x00062000,     QEI_FILTCNT_9          =      0x00072000,
      QEI_FILTCNT_10         =      0x00082000,     QEI_FILTCNT_11         =      0x00092000,
      QEI_FILTCNT_12         =      0x000A2000,     QEI_FILTCNT_13         =      0x000B2000,
      QEI_FILTCNT_14         =      0x000C2000,     QEI_FILTCNT_15         =      0x000D2000,
      QEI_FILTCNT_16         =      0x000E2000,     QEI_FILTCNT_17         =      0x000F2000,
  }Input_Filter_State;
	
//*****************************************************************************************************************************************
	
/* This Enumeration has the interrupt state codes for each QEI Module*/
  typedef enum
  {
      QEI_NO_Interrupts      =      0x00000000,     QEI_Error_INT_ENABLE   =      0x00000008,
      QEI_DIR_CH_INT_ENABLE  =      0x00000004,     QEI_T_EXP_INT_ENABLE   =      0x00000002,
      QEI_INDEX_INT_ENABLE   =      0x00000600,
  }Interrupt_State;
	
//**********************************************************************************************************************************************************
//
// The following are defines for QEI_Module NO.
//
//*****************************************************************************

#define  QEI0  0
#define  QEI1  1		

//*********************************************************************************************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGCQEI register.
//
//*****************************************************************************

/*

#define SYSCTL_RCGCQEI_R1       0x00000002  // QEI Module 1 Run Mode Clock
                                            // Gating Control
#define SYSCTL_RCGCQEI_R0       0x00000001  // QEI Module 0 Run Mode Clock
                                            // Gating Control
*/
//**********************************************************************************************************************************************************
//
// The following are defines for Digital function (GPIOPCTL PMCx Bit Field Encoding) Port F OR port D for QEI 0 
// and port C for QEI 1
//
//*****************************************************************************    

/*

#define GPIO_PCTL_PF0_PHA0      0x00000006  // PHA0 on PF0
#define GPIO_PCTL_PF1_PHB0      0x00000060  // PHB0 on PF1
#define GPIO_PCTL_PF4_IDX0      0x00060000  // IDX0 on PF4

#define GPIO_PCTL_PD6_PHA0      0x06000000  // PHA0 on PD6
#define GPIO_PCTL_PD7_PHB0      0x60000000  // PHB0 on PD7
#define GPIO_PCTL_PD3_IDX0      0x00006000  // IDX0 on PD3

#define GPIO_PCTL_PC5_PHA1      0x00600000  // PHA1 on PC5
#define GPIO_PCTL_PC6_PHB1      0x06000000  // PHB1 on PC6
#define GPIO_PCTL_PC4_IDX1      0x00060000  // IDX1 on PC4

*/
//**********************************************************************************************************************************************************
// The following are defines for the bit fields in the QEI_O_CTL register.
//
//*****************************************************************************

/*
#define QEI_CTL_FILTCNT_M       0x000F0000  // Input Filter Prescale Count
#define QEI_CTL_FILTEN          0x00002000  // Enable Input Filter
#define QEI_CTL_STALLEN         0x00001000  // Stall QEI
#define QEI_CTL_INVI            0x00000800  // Invert Index Pulse
#define QEI_CTL_INVB            0x00000400  // Invert PhB
#define QEI_CTL_INVA            0x00000200  // Invert PhA
#define QEI_CTL_VELDIV_M        0x000001C0  // Predivide Velocity
#define QEI_CTL_VELDIV_1        0x00000000  // QEI clock /1
#define QEI_CTL_VELDIV_2        0x00000040  // QEI clock /2
#define QEI_CTL_VELDIV_4        0x00000080  // QEI clock /4
#define QEI_CTL_VELDIV_8        0x000000C0  // QEI clock /8
#define QEI_CTL_VELDIV_16       0x00000100  // QEI clock /16
#define QEI_CTL_VELDIV_32       0x00000140  // QEI clock /32
#define QEI_CTL_VELDIV_64       0x00000180  // QEI clock /64
#define QEI_CTL_VELDIV_128      0x000001C0  // QEI clock /128
#define QEI_CTL_VELEN           0x00000020  // Capture Velocity
#define QEI_CTL_RESMODE         0x00000010  // Reset Mode
#define QEI_CTL_CAPMODE         0x00000008  // Capture Mode
#define QEI_CTL_SIGMODE         0x00000004  // Signal Mode
#define QEI_CTL_SWAP            0x00000002  // Swap Signals
#define QEI_CTL_ENABLE          0x00000001  // Enable QEI
#define QEI_CTL_FILTCNT_S       16

*/

//**********************************************************************************************************************************************************
//
// The following are defines for the bit fields in the QEI_O_STAT register.
//
//*****************************************************************************

/*

#define QEI_STAT_DIRECTION      0x00000002  // Direction of Rotation
#define QEI_STAT_ERROR          0x00000001  // Error Detected

*/

//**********************************************************************************************************************************************************
//
// The following are defines for the bit fields in the QEI_O_POS register.
//
//*****************************************************************************

/*
#define QEI_POS_M               0xFFFFFFFF  // Current Position Integrator
                                            // Value
#define QEI_POS_S               0

*/

//************************************************************************************************************************************************************
//
// The following are defines for the bit fields in the QEI_O_MAXPOS register.
//
//*****************************************************************************

/*
#define QEI_MAXPOS_M            0xFFFFFFFF  // Maximum Position Integrator
                                            // Value
#define QEI_MAXPOS_S            0

*/

//**********************************************************************************************************************************************************
//
// The following are defines for the bit fields in the QEI_O_LOAD register.
//
//*****************************************************************************

/*

#define QEI_LOAD_M              0xFFFFFFFF  // Velocity Timer Load Value
#define QEI_LOAD_S              0

*/

//***********************************************************************************************************************************************************
//
// The following are defines for the bit fields in the QEI_O_TIME register.
//
//*****************************************************************************

/*
#define QEI_TIME_M              0xFFFFFFFF  // Velocity Timer Current Value
#define QEI_TIME_S              0

*/
//**********************************************************************************************************************************************************
//
// The following are defines for the bit fields in the QEI_O_COUNT register.
//
//*****************************************************************************

/*

#define QEI_COUNT_M             0xFFFFFFFF  // Velocity Pulse Count
#define QEI_COUNT_S             0

*/
//****************************************************************************************************************************************
// The following are defines for the bit fields in the QEI_O_SPEED register.
//
//*****************************************************************************

/*
#define QEI_SPEED_M             0xFFFFFFFF  // Velocity
#define QEI_SPEED_S             0

*/

//*****************************************************************************************************************************************
//
// The following are defines for the bit fields in the QEI_O_INTEN register.
//
//*****************************************************************************

/*
#define QEI_INTEN_ERROR         0x00000008  // Phase Error Interrupt Enable
#define QEI_INTEN_DIR           0x00000004  // Direction Change Interrupt
                                            // Enable
#define QEI_INTEN_TIMER         0x00000002  // Timer Expires Interrupt Enable
#define QEI_INTEN_INDEX         0x00000001  // Index Pulse Detected Interrupt
                                            // Enable

*/
//****************************************************************************************************************************************
//
// The following are defines for the bit fields in the QEI_O_RIS register.
//
//*****************************************************************************

/*
#define QEI_RIS_ERROR           0x00000008  // Phase Error Detected
#define QEI_RIS_DIR             0x00000004  // Direction Change Detected
#define QEI_RIS_TIMER           0x00000002  // Velocity Timer Expired
#define QEI_RIS_INDEX           0x00000001  // Index Pulse Asserted

*/

//*****************************************************************************************************************************************
//
// The following are defines for the bit fields in the QEI_O_ISC register.
//
//*****************************************************************************

/*
#define QEI_ISC_ERROR           0x00000008  // Phase Error Interrupt
#define QEI_ISC_DIR             0x00000004  // Direction Change Interrupt
#define QEI_ISC_TIMER           0x00000002  // Velocity Timer Expired Interrupt
#define QEI_ISC_INDEX           0x00000001  // Index Pulse Interrupt

*/
//*****************************************************************************	***********************************************************
/***************************************************************Public functions******************************************************************************/
    
  /**   1----------------------------------->>QEI_Initialization 
   *
   *  @brief <void QEI_VidInit(uint8_t module)>
   *  <This function will be used to Initiate the QEI Module in The Tm4c123gh6pm by enabling module clock and PORT clock.>
   *   Enable The QEI Module 
   *   Enable Clock for  GPIO Port Related with QEI Module 
   *   Set Altrnate Function Select for each pin in QEI Module
	 *   Set Digital Function Bit field Encoding for each bit in GPIOPCTL
   *   make Pins for QEI Dgital DEN  
	 *
   *  @return <This Function Returns Void.>
   *
   */
      void QEI_VidInit(uint8_t module);
//*********************************************************************************************************************************************************
  
	/**   2----------------------------------->>QEI_Configuration 
    *
    *  @brief <  QEI_Configuration(uint8_t module, uint32_t Signal_Mode, uint32_t Capture_Mode,uint32_t Reset_State,
    *                      uint32_t Swap_State,uint32_t INV_state, uint32_t MAX_Postion)>
		*
    *  <This function will be used to Configure The QEI Module in The Tm4c123gh6pm  Controller.>
    *  Disable The QEI Module before configuration
    *  configure the parameter from config file 
    *  put the maximum position value 
		*
    *  @return <This Function Returns Void.>
    *
    */
    void QEI_Configuration(uint8_t module, QEI_SIG_MODE Signal_Mode, Signal_CAP_Mode Capture_Mode,Reset_State Reset_Mode,
                          SWAP_State Swap_State,Signal_invert_State INV_state, uint32_t MAX_Postion);

//********************************************************************************************************************************************************

     /**  3----------------------------------->>QEI_Velocity_Configuration
      *  @brief <void QEI_Velocity_Configuration(uint8_t module, uint32_t Pre_Devision, uint32_t Vel_LOAD_Value)>
		  *
      *  <This function will be used to configure using the QEI Module for Velocity Capture .>
      *
      *  @select The Pre_Devision from config file 
      *  @put velocity load value
      *  @ENABLE the velocity Capture for the QEI module 
      *
      *  @return <This Function Returns Void.>
      *
      */
         void QEI_Velocity_Configuration(uint8_t module, Velocity_PreDevide Pre_Devision, uint32_t Vel_LOAD_Value);
		
//*********************************************************************************************************************************************************		
    
		/**  4----------------------------------->>QEI_Input_Filter_Configuration
      *
      *  @brief < void QEI_Input_Filter_Configuration(uint8_t module, uint32_t Filter_Select)> 
      *  <This function will be used to configure using input filter or not for the QEI Module and selects the desired filter.>
      *
      *  @select The filter from config file  
      *
      *  @return <This Function Returns Void.>
      *
      */
            void QEI_Input_Filter_Configuration(uint8_t module, Input_Filter_State Filter_Select);
						
//*********************************************************************************************************************************************************

      /**   5----------------------------------->>QEI_Interrupts_Configuration
       *
       *  @brief <void QEI_Interrupts_Configuration(uint8_t module, uint32_t Int_state)>
       *  <This function will be used to configure using Generating interrupts or not for the QEI Module.>
       *
       *  @select The Int_state  from config file
       *
       *  @return <This Function Returns Void.>
       *
       */
            void QEI_Interrupts_Configuration(uint8_t module, Interrupt_State Int_state);

//*********************************************************************************************************************************************************

       /**   6----------------------------------->>QEI_Get_Position 
        *
        *  @brief < uint32_t QEI_Get_Position(uint8_t module)>
        *  <This function will be used to Get the position from a desired QEI Module.>
        *
        *  @read postion value from position register
        */
            uint32_t QEI_Get_Position(uint8_t module);
						
//*********************************************************************************************************************************************************

        /**  7----------------------------------->>QEI_Get_Velocity
         *
         *  @brief <uint32_t QEI_Get_Velocity(uint8_t module)>
         *  <This function will be used to Get the velocity from a desired QEI Module.>
         *
         *  @read speed value from speed register
         *
         *  @return uint32               <The Velocity of the QEI >
         *
         */
             float QEI_Get_Velocity(uint8_t module);
						 
//*********************************************************************************************************************************************************

         /**  8----------------------------------->>QEI_Get_Direction
          *
          *  @brief <uint32_t QEI_Get_Direction(uint8_t module)>
          *  <This function will be used to Get the Direction of rootation from a desired QEI Module.>
          *
          *  @cheack the value of diriction bit in QUI status register 
          *
          *  @return Sint32               <The Direction of rotation of the QEI >
          *
          */
             uint32_t QEI_Get_Direction(uint8_t module);
						 
//*********************************************************************************************************************************************************						 
void QIE_VidEnable(uint8_t module);

#endif 