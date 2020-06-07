#include "touch.h" 
#include "hardware/LCD/lcd.h"
//#include "delay.h"
#include "stdlib.h"
#include "math.h"
//#include "24cxx.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//������������֧��ADS7843/7846/UH7843/7846/XPT2046/TSC2046/OTT2001A�ȣ� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/7
//�汾��V1.2
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									   
//********************************************************************************
//�޸�˵��
//V1.1 20140721
//����MDK��-O2�Ż�ʱ,�����������޷���ȡ��bug.��TP_Write_Byte�������һ����ʱ,�������.
//V1.2 20141130 
//���ݴ���������FT5206��֧��
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

//��������ʼ��  		    
//����ֵ:0,û�н���У׼
//       1,���й�У׼
u8 TP_Init(void)
{
	if(lcddev.id==0X5510)		//���ݴ�����
	{
		if(GT9147_Init()==0)	//��GT9147
		{ 
			tp_dev.scan=GT9147_Scan;	//ɨ�躯��ָ��GT9147������ɨ��
		}else
		{
			//OTT2001A_Init();
			//tp_dev.scan=OTT2001A_Scan;	//ɨ�躯��ָ��OTT2001A������ɨ��
		}
		tp_dev.touchtype|=0X80;	//������ 
		tp_dev.touchtype|=lcddev.dir&0X01;//������������ 
		return 0;
	}/*else if(lcddev.id==0X1963)
	{
		FT5206_Init();
		tp_dev.scan=FT5206_Scan;		//ɨ�躯��ָ��GT9147������ɨ��		
		tp_dev.touchtype|=0X80;			//������ 
		tp_dev.touchtype|=lcddev.dir&0X01;//������������ 
		return 0;
	}*/
	/*else
	{
		__HAL_RCC_GPIOB_CLK_ENABLE();			//����GPIOBʱ��
		__HAL_RCC_GPIOC_CLK_ENABLE();			//����GPIOCʱ��
		__HAL_RCC_GPIOF_CLK_ENABLE();			//����GPIOFʱ��
		
		//GPIOB1,2��ʼ������
		GPIO_Initure.Pin=GPIO_PIN_1|GPIO_PIN_2;	//PB1/PB2 ����Ϊ��������
		GPIO_Initure.Mode=GPIO_MODE_INPUT;  	//����ģʽ
		GPIO_Initure.Pull=GPIO_PULLUP;          //����
		GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
		HAL_GPIO_Init(GPIOB,&GPIO_Initure);     //��ʼ��
        
		//PB0
		GPIO_Initure.Pin=GPIO_PIN_0; 			//PB0����Ϊ�������
		GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
		HAL_GPIO_Init(GPIOB,&GPIO_Initure);     //��ʼ��
        
		//PC13
		GPIO_Initure.Pin=GPIO_PIN_13;          	//PC13����Ϊ�������
		HAL_GPIO_Init(GPIOC,&GPIO_Initure);     //��ʼ��
        
		//PF11
		GPIO_Initure.Pin=GPIO_PIN_11;          	//PF11�����������
		HAL_GPIO_Init(GPIOF,&GPIO_Initure);     //��ʼ��			
   
		TP_Read_XY(&tp_dev.x[0],&tp_dev.y[0]);//��һ�ζ�ȡ��ʼ��	 
		AT24CXX_Init();		//��ʼ��24CXX
		if(TP_Get_Adjdata())return 0;//�Ѿ�У׼
		else			   //δУ׼?
		{ 										    
			LCD_Clear(WHITE);//����
			TP_Adjust();  	//��ĻУ׼ 
			TP_Save_Adjdata();	 
		}			*/
		//TP_Get_Adjdata();
	//}
	return 1;
}
