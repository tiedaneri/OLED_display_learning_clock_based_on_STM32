/**
  ******************************************************************************
  * @file    main.c
  * @author  GeekSi
  * @version V1.0
  * @date    2022/3
  * @brief   STM32��OLED��ʾ��ѧϰ��
  ******************************************************************************
  * @attention
  * 0.96��OLED��SCL--PB6,SDA--PB7,3.3V,GND
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
 * @brief   ��Ļ����ʱ����
 * @param   ns-n��
 * @retval  ��
*/
void timer_count(unsigned int ns)
{
	unsigned int i;
	int j;
	unsigned int time1 = ns;
	char min[4];
	char sec[4];
	// int sprintf(char *str, const char *format, ...)���͸�ʽ������� str ��ָ����ַ�����
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
	
	for(j=2; j>0; j--)//������
	{
		BEEP_ON;
		Delay_ms(100);
		BEEP_OFF;
		Delay_ms(100);
	}
}

int main(void)
{	
/*��ʼ��LED������*/
	EXTI_Key_Config();
	LED_GPIO_Config();
	beep_init();
	USART_Config();
	LED_BLUE;
	
	printf("\r\n ��ӭ \r\n");		 
	printf("\r\n ����һ��STM32��OLED��ʾ��ѧϰ�ӳ��� \r\n");
	
	SysTick_Init();   //��ʼ���ӳٺ���
	I2C_Configuration();//����CPU��Ӳ��I2C
	OLED_Init();    //��ʼ��OLED
	
	printf("\r\n OLED��ʼ���ɹ� \r\n");
	
	OLED_CLS();
	LED_GREEN;
	
	while(1)
	{
		if(Key_Scan(KEY1_INT_GPIO_PORT, KEY1_INT_GPIO_PIN) == KEY_ON)
		{
			timer_count(3000);//��Ļ����ʱ����
			OLED_CLS();
			OLED_ShowStr(0,0,"50min DONE",2);
			Delay_s(2);
			OLED_CLS();
			timer_count(600);//��Ļ����ʱ����
			OLED_ShowStr(0,0,"10min DONE",2);
			Delay_s(2);
			OLED_CLS();
		}
	} 
}
/*********************************************END OF FILE**********************/
