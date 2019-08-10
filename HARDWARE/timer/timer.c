#include "timer.h"
extern u32 HighNumber;
extern u8 PrintfSign;
extern float speed;
TIM_HandleTypeDef TIM3_Handler;

void TIM3_Init(u32 arr,u16 psc)
{
	TIM3_Handler.Instance = TIM3;
	TIM3_Handler.Init.Prescaler = psc;
	TIM3_Handler.Init.Period = arr;
	TIM3_Handler.Init.CounterMode = TIM_COUNTERMODE_UP;
	HAL_TIM_Base_Init(&TIM3_Handler);
	
	HAL_TIM_Base_Start_IT(&TIM3_Handler);
}
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM3)
	{
		__HAL_RCC_TIM3_CLK_ENABLE();
		HAL_NVIC_SetPriority(TIM3_IRQn,1,3);
		HAL_NVIC_EnableIRQ(TIM3_IRQn);
	}
}
void TIM3_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&TIM3_Handler);
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	static double time = 0;
	u32 highnumber = HighNumber;
	highnumber = highnumber/334;			//得出圈数
	time = TIM3_Handler.Init.Prescaler + 1;
	time = 90000000 / time;
	time = 1/ time;
	time *= htim->Init.Period;//进入中断的时间
	speed = highnumber/time;
	PrintfSign = 1;
}
