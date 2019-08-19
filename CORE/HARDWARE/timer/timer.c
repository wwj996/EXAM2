#include "timer.h"
extern u32 HighNumber;
extern u8 PrintfSign2;
extern u8 PrintfSign;
extern float speed;
TIM_HandleTypeDef TIM3_Handler;
TIM_HandleTypeDef TIM5_Handler;
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
//	static double time = 0;
//	u32 highnumber = HighNumber;
//	highnumber = highnumber/334;			//得出圈数
//	time = TIM3_Handler.Init.Prescaler + 1;
//	time = 90000000 / time;
//	time = 1/ time;
//	time *= htim->Init.Period;//进入中断的时间
//	speed = highnumber/time;
  PrintfSign = 1;
}
void TIM5_PWM_Init(u16 arr,u16 psc)
{
	TIM5_Handler.Instance = TIM5;
	TIM5_Handler.Init.Period = arr;
	TIM5_Handler.Init.Prescaler = psc;
	TIM5_Handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	TIM5_Handler.Init.CounterMode = TIM_COUNTERMODE_UP;
	HAL_TIM_PWM_Init(&TIM5_Handler);
	
	TIM_OC_InitTypeDef TIM5_CH2Handler;
	TIM5_CH2Handler.OCPolarity = TIM_OCPOLARITY_LOW;
	TIM5_CH2Handler.Pulse = arr/2;
	TIM5_CH2Handler.OCMode = TIM_OCMODE_PWM1;
	HAL_TIM_PWM_ConfigChannel(&TIM5_Handler,&TIM5_CH2Handler,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&TIM5_Handler,TIM_CHANNEL_2);
}
void HAL_TIM_PWMM_MspInit(TIM_HandleTypeDef *htim)
{
	GPIO_InitTypeDef GPIO_Initure;
	__HAL_RCC_TIM5_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	GPIO_Initure.Pin = GPIO_PIN_1;
	GPIO_Initure.Pull = GPIO_PULLUP;
	GPIO_Initure.Speed = GPIO_SPEED_HIGH;
	GPIO_Initure.Mode = GPIO_MODE_AF_PP;
	GPIO_Initure.Alternate =  GPIO_AF2_TIM5;
	HAL_GPIO_Init(GPIOA,&GPIO_Initure);
}
void TIM_SetTIM5Compare2(u16 compare)
{
	TIM5->CCR2  = compare;
}
u32 TIM_GetTIM3Capture2(void)
{
	return HAL_TIM_ReadCapturedValue(&TIM5_Handler,TIM_CHANNEL_2);
}
