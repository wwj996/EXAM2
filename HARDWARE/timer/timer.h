#ifndef _TIMER_H_
#define _TIMER_H_
#include "sys.h"
void TIM3_Init(u32 arr,u16 psc);
void PWM_Init(u16 arr,u16 psc);
void TIM4_SetCompare2(u32 compare);
#endif
