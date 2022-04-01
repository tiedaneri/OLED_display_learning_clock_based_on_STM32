#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f10x.h"

void SysTick_Init(void);
void Delay_ms(__IO u32 nTime);
void Delay_s(unsigned int ms);
void TimingDelay_Decrement(void);



#endif /* __SYSTICK_H */
