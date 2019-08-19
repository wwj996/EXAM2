#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "timer.h"
#include "EXTI.h"
extern u8 PrintfSign;
extern u32 HighNumber;
int main(void)
{
    HAL_Init();                     //初始化HAL库   
    Stm32_Clock_Init(360,25,2,8);   //设置时钟,180Mhz
    delay_init(180);                //初始化延时函数
    LED_Init();                     //初始化LED 
	EXTI_Init();
	uart_init(115200);
	TIM3_Init(3000-1,9000-1);
	TIM5_PWM_Init(500-1,90-1);
    while(1)
    {
		TIM_SetTIM5Compare2(TIM_GetTIM3Capture2()+1);
		if(TIM_GetTIM3Capture2() == 300) TIM_SetTIM5Compare2(0);
		if(PrintfSign)
		{
			printf("%d/s\n",HighNumber);
			PrintfSign = 0;
			HighNumber = 0;
		}
    }
		
}


