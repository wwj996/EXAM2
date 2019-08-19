#ifndef _TIMER_H_
#define _TIMER_H_
#include "sys.h"
void TIM3_Init(u32 arr,u16 psc);
void TIM5_PWM_Init(u16 arr,u16 psc);
void TIM_SetTIM5Compare2(u16 compare);
u32 TIM_GetTIM3Capture2(void);
#endif
