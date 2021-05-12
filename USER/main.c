/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * 文件名  ：main.c
 * 描述    ：LED1以0.5hz的频率闪烁(定时器 TIM2 产生定时)。        
 * 实验平台：野火STM32开发板
 * 库版本  ：ST3.5.0
 *
 * 作者    ：wildfire team 
 * 论坛    ：http://www.amobbs.com/forum-1008-1.html
 * 淘宝    ：http://firestm32.taobao.com
**********************************************************************************/
#include "stm32f10x.h"
#include "led.h" 
#include "Time_test.h"

volatile u32 time; // ms 计时变量
void output(int i);
/*
 * 函数名：main
 * 描述  ：主函数
 * 输入  ：无
 * 输出  ：无	
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
	/* 配置系统时钟为 72M */  
	SystemInit();
	/* led 端口配置 */ 
	LED_GPIO_Config();
	/* TIM2 定时配置 */
	TIM2_NVIC_Configuration();
	/*TIM_Period--1000   TIM_Prescaler--71 -->中断周期为1ms*/
  TIM2_Configuration();
	/* TIM2 开始计时 */
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
