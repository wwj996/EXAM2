#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "timer.h"
#include "EXTI.h"
float speed = 0;
int main(void)
{
	  extern u8 PrintfSign2;
		extern u8 PrintfSign;
		extern u32 HighNumber;
    HAL_Init();                     //��ʼ��HAL��   
    Stm32_Clock_Init(360,25,2,8);   //����ʱ��,180Mhz
    delay_init(180);                //��ʼ����ʱ����
    LED_Init();                     //��ʼ��LED 
		EXTI_Init();
		uart_init(115200);
		TIM3_Init(2700-1,9000-1);
    while(1)
    {
			if(PrintfSign)
			{
				printf("%fr/s\n",speed);
				PrintfSign = 0;
				PrintfSign2 = 1;
			}
    }
}

//��߾���->���̽����ж��¼�->��С������ֵ


