#ifndef __BEEP_H
#define __BEEP_H

#define  BEEP_ON   GPIO_SetBits(GPIOA, GPIO_Pin_8);
#define  BEEP_OFF  GPIO_ResetBits(GPIOA, GPIO_Pin_8);


void beep_init(void);



#endif
