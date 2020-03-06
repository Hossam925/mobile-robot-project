/*
 * UART_private.c
 *
 *  Created on: Oct 11, 2019
 *      Author: homo9
 */
#include "UART_INTERFACE.h"
#include "UART_cfg.h"


UART_ConfigureStruct U0 = {
    UART0_Number,
    UART0_WordLength,
    UART0_ParityEnable,
    UART0_InterruptSelect,
    UART0_ParitySelect,
    UART0_StopBit,
    UART0_FIFO
};


UART_ConfigureStruct U1 = {
    UART1_Number,
    UART1_WordLength,
    UART1_ParityEnable,
    UART1_InterruptSelect,
    UART1_ParitySelect,
    UART1_StopBit,
    UART1_FIFO
};



UART_ConfigureStruct U2 = {
    UART2_Number,
    UART2_WordLength,
    UART2_ParityEnable,
    UART2_InterruptSelect,
    UART2_ParitySelect,
    UART2_StopBit,
    UART2_FIFO
};




UART_ConfigureStruct U3 = {
    UART3_Number,
    UART3_WordLength,
    UART3_ParityEnable,
    UART3_InterruptSelect,
    UART3_ParitySelect,
    UART3_StopBit,
    UART3_FIFO
};



UART_ConfigureStruct U4 = {
    UART4_Number,
    UART4_WordLength,
    UART4_ParityEnable,
    UART4_InterruptSelect,
    UART4_ParitySelect,
    UART4_StopBit,
    UART4_FIFO
};



UART_ConfigureStruct U5 = {
    UART5_Number,
    UART5_WordLength,
    UART5_ParityEnable,
    UART5_InterruptSelect,
    UART5_ParitySelect,
    UART5_StopBit,
    UART5_FIFO
};



UART_ConfigureStruct U6 = {
    UART6_Number,
    UART6_WordLength,
    UART6_ParityEnable,
    UART6_InterruptSelect,
    UART6_ParitySelect,
    UART6_StopBit,
    UART6_FIFO
};




UART_ConfigureStruct U7 = {
    UART7_Number,
    UART7_WordLength,
    UART7_ParityEnable,
    UART7_InterruptSelect,
    UART7_ParitySelect,
    UART7_StopBit,
    UART7_FIFO
};


const UART_ConfigureStruct* U_Array[8] = {
    &U0,
    &U1,
    &U2,
    &U3,
    &U4,
    &U5,
    &U6,
    &U7
};
