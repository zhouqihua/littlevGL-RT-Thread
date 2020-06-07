/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     SummerGift   first version
 * 2018-11-19     flybreak     add stm32f407-atk-explorer bsp
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <lvgl/lvgl.h>
#include <lv_examples/lv_examples.h>
#include "hardware/LCD/lcd.h"
#include "hardware/TOUCH/touch.h"
/* defined the LED0 pin: PF9 */
#define LED0_PIN    GET_PIN(F, 9)
extern void hal_init(void);

uint8_t *sram = (uint8_t *)0x68000000;
int main(void)
{
//	SRAM_Init();
//	rt_kprintf("sram init successful\r\n");
	LCD_Init();
	//LCD_Fill(0, 0, 800, 480, 0xff);
	rt_kprintf("lcd init successful\r\n");
	TP_Init();
	rt_kprintf("touch init successful\r\n");
    //__IO int count = 1;
    /*Initialize LVGL*/
    lv_init();

    /*Initialize the HAL (display, input devices, tick) for LVGL*/
    hal_init();

    lv_demo_widgets();
    //lv_demo_printer();
    //rt_kprintf("lvgl init successful\r\n");
    while (1)
    {
    	lv_task_handler();
        rt_thread_mdelay(5);
    }

    return RT_EOK;
}

void write_sram(void) {
	int i;
	for (i = 0; i < 20; ++i) {
		sram[i] = i;
	}
}
MSH_CMD_EXPORT(write_sram, write sram);

void read_sram(void) {
	int i;
	for (i = 1; i < 20; ++i) {
		rt_kprintf("0x%x\r\n", sram[i]&0xff);
	}
}
MSH_CMD_EXPORT(read_sram, read sram);
