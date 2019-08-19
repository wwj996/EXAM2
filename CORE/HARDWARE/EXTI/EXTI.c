#include "EXTI.h"
#include "timer.h"
u8 PrintfSign = 0;
u32 HighNumber = 0;
void EXTI_Init(void)
{
	GPIO_InitTypeDef GPIO_Initure;
	GPIO_Initure.Pin = GPIO_PIN_0;
	GPIO_Initure.Pull = GPIO_PULLDOWN;
	GPIO_Initure.Speed = GPIO_SPEED_HIGH;
	GPIO_Initure.Mode = GPIO_MODE_IT_RISING;
	HAL_GPIO_Init(GPIOA,&GPIO_Initure);
	
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
	HAL_NVIC_SetPriority(EXTI0_IRQn,2,1);//�������ȼ��������ȼ�����Ǻ��˽�
}
void EXTI0_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	HighNumber++;
}
