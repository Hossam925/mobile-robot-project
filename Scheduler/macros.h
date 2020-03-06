/*
 *
 macros.h
 *
 *  Created on: Aug 24, 2019
 *      Author: Ahmed Khaled
 */

#ifndef MACROS_H_
#define MACROS_H_

#define get_bit(var,bitno)  ((var>>bitno) & 1 )
#define clr_bit(var,bitno)  var &=~(1<<bitno)
#define set_bit(var,bitno)  var |=(1<<bitno)
#define toggle_bit(Data,Bit) Data^= (1<<Bit)
#define assign_bit(Data,Bit,Val) (Val==1)? (set_bit(Data,Bit)):(clr_bit(Data,Bit))

#define vect(x)  __vector_##x
#define ISR(vect_no) void vect(vect_no) (void) __attribute__((signal));\
 void vect(vect_no) (void)

#endif /* MACROS_H_ */
