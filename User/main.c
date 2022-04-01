/**
  ******************************************************************************
  * @file    main.c
  * @author  GeekSi
  * @version V1.0
  * @date    2022/3
  * @brief   STM32＋OLED显示屏学习钟
  ******************************************************************************
  * @attention
  * 0.96寸OLED：SCL--PB6,SDA--PB7,3.3V,GND
	*
  *
  ******************************************************************************
  */ 
	
#include "stm32f10x.h"
#include "OLED_I2C.h"
#include "./systick/bsp_SysTick.h"
#include "./led/bsp_led.h"  
#include "./usart/bsp_usart.h"
#include "./beep/beep.h"
#include "./key/bsp_exti.h"

/**
 * @brief   屏幕倒计时函数
 * @param   ns-n秒
 * @retval  无
*/
void timer_count(unsigned int ns)
{
	unsigned int i;
	int j;
	unsigned int time1 = ns;
	char min[4];
	char sec[4];
	// int sprintf(char *str, const char *format, ...)发送格式化输出到 str 所指向的字符串。
	for(i = time1; i>=1; i--)
	{
		while(KEY2 == 1)
		{
			OLED_ShowStr(0, 3,"countdown", 2);
			OLED_ShowStr(0, 5,"stop", 2);
			Delay_ms(1000);
			OLED_CLS();
		}

		sprintf(min, "%.2d", i/60);
		OLED_ShowStr(0, 0, (unsigned char *)min, 2);
		OLED_ShowStr(16, 0, ":", 2);
		sprintf(sec, "%.2d", i%60);
		OLED_ShowStr(24, 0, (unsigned char *)sec, 2);
		Delay_ms(995);
	}
	
	for(j=2; j>0; j--)//蜂鸣器
	{
		BEEP_ON;
		Delay_ms(100);
		BEEP_OFF;
		Delay_ms(100);
	}
}

int main(void)
{	
/*初始化LED、串口*/
	EXTI_Key_Config();
	LED_GPIO_Config();
	beep_init();
	USART_Config();
	LED_BLUE;
	
	printf("\r\n 欢迎 \r\n");		 
	printf("\r\n 这是一个STM32＋OLED显示屏学习钟程序 \r\n");
	
	SysTick_Init();   //初始化延迟函数
	I2C_Configuration();//配置CPU的硬件I2C
	OLED_Init();    //初始化OLED
	
	printf("\r\n OLED初始化成功 \r\n");
	
	OLED_CLS();
	LED_GREEN;
	
	while(1)
	{
		if(Key_Scan(KEY1_INT_GPIO_PORT, KEY1_INT_GPIO_PIN) == KEY_ON)
		{
			timer_count(3000);//屏幕倒计时函数
			OLED_CLS();
			OLED_ShowStr(0,0,"50min DONE",2);
			Delay_s(2);
			OLED_CLS();
			timer_count(600);//屏幕倒计时函数
			OLED_ShowStr(0,0,"10min DONE",2);
			Delay_s(2);
			OLED_CLS();
		}
	} 
}
/*********************************************END OF FILE**********************/
