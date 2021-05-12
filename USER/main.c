/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * �ļ���  ��main.c
 * ����    ��LED1��0.5hz��Ƶ����˸(��ʱ�� TIM2 ������ʱ)��        
 * ʵ��ƽ̨��Ұ��STM32������
 * ��汾  ��ST3.5.0
 *
 * ����    ��wildfire team 
 * ��̳    ��http://www.amobbs.com/forum-1008-1.html
 * �Ա�    ��http://firestm32.taobao.com
**********************************************************************************/
#include "stm32f10x.h"
#include "led.h" 
#include "Time_test.h"

volatile u32 time; // ms ��ʱ����
void output(int i);
/*
 * ��������main
 * ����  ��������
 * ����  ����
 * ���  ����	
 */
u8 seg_tab[15]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
void solve(int i)
{
	GPIOA1(!((seg_tab[i])&0x01));
	GPIOA2(!((seg_tab[i]>>1)&0x01));
	GPIOA3(!((seg_tab[i]>>2)&0x01));
	GPIOA4(!((seg_tab[i]>>3)&0x01));
	GPIOA5(!((seg_tab[i]>>4)&0x01));
	GPIOA6(!((seg_tab[i]>>5)&0x01));
	GPIOA7(!((seg_tab[i]>>6)&0x01));
	GPIOA8(!((seg_tab[i]>>7)&0x01));
}
int main(void)
{
	/* ����ϵͳʱ��Ϊ 72M */  
	SystemInit();
	/* led �˿����� */ 
	LED_GPIO_Config();
	/* TIM2 ��ʱ���� */
	TIM2_NVIC_Configuration();
	/*TIM_Period--1000   TIM_Prescaler--71 -->�ж�����Ϊ1ms*/
  TIM2_Configuration();
	/* TIM2 ��ʼ��ʱ */
	GPIOE1(0);
	GPIO_WriteBit(GPIOC, GPIO_Pin_3, (BitAction)1); 
	GPIO_WriteBit(GPIOC, GPIO_Pin_4, (BitAction)1); 
	GPIO_WriteBit(GPIOC, GPIO_Pin_5, (BitAction)1); 
  while(1)
  {
		GPIO_WriteBit(GPIOC, GPIO_Pin_3, (BitAction)0); 
		output(5);
		GPIO_WriteBit(GPIOC, GPIO_Pin_3, (BitAction)1); 
		GPIO_WriteBit(GPIOC, GPIO_Pin_5, (BitAction)0); 
		output(3);
		GPIO_WriteBit(GPIOC, GPIO_Pin_5, (BitAction)1);     
		GPIO_WriteBit(GPIOC, GPIO_Pin_4, (BitAction)0);
		output(2);
		GPIO_WriteBit(GPIOC, GPIO_Pin_4, (BitAction)1);       		
  }
}
void output(int i)
{
	int num=0;
	START_TIME;
	solve(i);
	while(time/1000!=i+1)
	if((time%1000==0&&time/1000!=num))
	{
		num++;
		solve(i-num);
	}
	STOP_TIME;
}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
