#include "touch.h" 
#include "hardware/LCD/lcd.h"
//#include "delay.h"
#include "stdlib.h"
#include "math.h"
//#include "24cxx.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//触摸屏驱动（支持ADS7843/7846/UH7843/7846/XPT2046/TSC2046/OTT2001A等） 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/7
//版本：V1.2
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									   
//********************************************************************************
//修改说明
//V1.1 20140721
//修正MDK在-O2优化时,触摸屏数据无法读取的bug.在TP_Write_Byte函数添加一个延时,解决问题.
//V1.2 20141130 
//电容触摸屏增加FT5206的支持
//////////////////////////////////////////////////////////////////////////////////

_m_tp_dev tp_dev=
{
	GT9147_Init,
	GT9147_Scan,
	NULL,
	0,
	0, 
	0,
	0,
	0,
	0,	  	 		
	0,
	0,	  	 		
};

//触摸屏初始化  		    
//返回值:0,没有进行校准
//       1,进行过校准
u8 TP_Init(void)
{
	if(lcddev.id==0X5510)		//电容触摸屏
	{
		if(GT9147_Init()==0)	//是GT9147
		{ 
			tp_dev.scan=GT9147_Scan;	//扫描函数指向GT9147触摸屏扫描
		}else
		{
			//OTT2001A_Init();
			//tp_dev.scan=OTT2001A_Scan;	//扫描函数指向OTT2001A触摸屏扫描
		}
		tp_dev.touchtype|=0X80;	//电容屏 
		tp_dev.touchtype|=lcddev.dir&0X01;//横屏还是竖屏 
		return 0;
	}/*else if(lcddev.id==0X1963)
	{
		FT5206_Init();
		tp_dev.scan=FT5206_Scan;		//扫描函数指向GT9147触摸屏扫描		
		tp_dev.touchtype|=0X80;			//电容屏 
		tp_dev.touchtype|=lcddev.dir&0X01;//横屏还是竖屏 
		return 0;
	}*/
	/*else
	{
		__HAL_RCC_GPIOB_CLK_ENABLE();			//开启GPIOB时钟
		__HAL_RCC_GPIOC_CLK_ENABLE();			//开启GPIOC时钟
		__HAL_RCC_GPIOF_CLK_ENABLE();			//开启GPIOF时钟
		
		//GPIOB1,2初始化设置
		GPIO_Initure.Pin=GPIO_PIN_1|GPIO_PIN_2;	//PB1/PB2 设置为上拉输入
		GPIO_Initure.Mode=GPIO_MODE_INPUT;  	//输入模式
		GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
		GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
		HAL_GPIO_Init(GPIOB,&GPIO_Initure);     //初始化
        
		//PB0
		GPIO_Initure.Pin=GPIO_PIN_0; 			//PB0设置为推挽输出
		GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
		HAL_GPIO_Init(GPIOB,&GPIO_Initure);     //初始化
        
		//PC13
		GPIO_Initure.Pin=GPIO_PIN_13;          	//PC13设置为推挽输出
		HAL_GPIO_Init(GPIOC,&GPIO_Initure);     //初始化
        
		//PF11
		GPIO_Initure.Pin=GPIO_PIN_11;          	//PF11设置推挽输出
		HAL_GPIO_Init(GPIOF,&GPIO_Initure);     //初始化			
   
		TP_Read_XY(&tp_dev.x[0],&tp_dev.y[0]);//第一次读取初始化	 
		AT24CXX_Init();		//初始化24CXX
		if(TP_Get_Adjdata())return 0;//已经校准
		else			   //未校准?
		{ 										    
			LCD_Clear(WHITE);//清屏
			TP_Adjust();  	//屏幕校准 
			TP_Save_Adjdata();	 
		}			*/
		//TP_Get_Adjdata();
	//}
	return 1;
}
