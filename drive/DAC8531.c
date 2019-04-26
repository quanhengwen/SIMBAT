/******************** (C) COPYRIGHT 2015 AVER ********************
 * 文件名  ：DAC8531.C
 * 作者    ：李振
 * 描述    ：库函数版
 * 内容    ：外置16BIT DAC
 * 硬件连接：
 * 修改日期：2015-8-18
*********************************************************************/
#include "my_register.h"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
/********************************************************************/
#define DAC_SYNC_LOW   GPIO_ResetBits(GPIOE, GPIO_Pin_2);
#define DAC_SYNC_HIGH  GPIO_SetBits(GPIOE, GPIO_Pin_2);   
      
#define DAC_SCK_LOW   GPIO_ResetBits(GPIOE, GPIO_Pin_3);
#define DAC_SCK_HIGH  GPIO_SetBits(GPIOE, GPIO_Pin_3); 

#define DAC_SDA_LOW   GPIO_ResetBits(GPIOE, GPIO_Pin_4);
#define DAC_SDA_HIGH  GPIO_SetBits(GPIOE, GPIO_Pin_4); 
/**********************************************************************************************************
*	函 数 名: DAC8531_GPIOCoing
*	功能说明: 引脚初始化
*	形    参：
*	返 回 值: 无
**********************************************************************************************************/
void DAC8531_GPIOCoing(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;//
	GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;//
	GPIO_Init(GPIOE, &GPIO_InitStructure);//
}
/**********************************************************************************************************
*	函 数 名: DAC8531_GPIOCoing
*	功能说明: 引脚初始化
*	形    参：
*	返 回 值: 无
**********************************************************************************************************/
void DAC8531_Send(vu16 date)
{
	vu8 cont;
	DAC_SYNC_LOW;//SYNC置低
	DAC_SCK_HIGH;//SCK置高
	NOP;
	NOP;
	NOP;
	NOP;
	DAC_SYNC_HIGH;//SYNC置高
	NOP;
	DAC_SCK_HIGH;//SCK置高
	DAC_SYNC_LOW;//SYNC置低
	for(cont = 0; cont < 24; cont++)
	{
		if(cont>7)
		{
			if(date & 0x8000)		// 先传高位
			{
				DAC_SDA_HIGH;
			}
			else
			{
				DAC_SDA_LOW;
			}
			date=date<<1;
		}
		else//前8位中最前6位为无效位，后2位为工作模式设定，此处为00设置为正常工作模式。
		{
			DAC_SDA_LOW;
		}
		DAC_SCK_LOW;//SCK置低
		NOP;
		NOP;
		NOP;
		DAC_SCK_HIGH;//SCK置高
	}
	DAC_SYNC_HIGH;//SYNC置高
	DAC_SCK_HIGH;//SCK置高
}
	
	
		