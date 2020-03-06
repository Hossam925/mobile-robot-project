#include "delay.h"

void delayMs(uint16_t n)
{
		int i, j;
		for(i=0;i<n;i++)
		for (j=0;j <3180;j++)
		{}
}

void delayUs(uint16_t n)
{
		int i, j;
		for(i=0;i<n;i++)
		for (j=0;j <3;j++)
		{}
}

int Myabs(int value)
{
			if(value < 0){value *= -1;}
			return value;
}
