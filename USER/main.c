#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "timer.h"
#include "EXTI.h"
float speed = 0;
int main(void)
{
	u8 dir = 0;
		u16 MotorPwmVal = 0;
	  extern u8 PrintfSign2;
		extern u8 PrintfSign;
		extern u32 HighNumber;
    HAL_Init();                     //初始化HAL库   
    Stm32_Clock_Init(360,25,2,8);   //设置时钟,180Mhz
    delay_init(180);                //初始化延时函数
    LED_Init();                     //初始化LED 
		EXTI_Init();
		uart_init(115200);
		PWM_Init(500-1,90-1);
		TIM3_Init(2700-1,12000-1);
    while(1)
    {
			delay_us(100);
			if(PrintfSign)
			{
				printf("%fr/s\n",speed);
				PrintfSign = 0;
				PrintfSign2 = 1;
			}
			if(dir)MotorPwmVal++;
			else MotorPwmVal--;
			if(MotorPwmVal>300)dir = 0;
			if(MotorPwmVal==0)dir = 1;
			TIM4_SetCompare2(MotorPwmVal);
    }
}

//提高精度->缩短进入中断事件->减小重载数值


