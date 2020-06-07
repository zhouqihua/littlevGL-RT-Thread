
/**
 * @file main
 *
 */

/*********************
 *      INCLUDES
 *********************/
#define _DEFAULT_SOURCE /* needed for usleep() */
#include <stdlib.h>
#include <unistd.h>
#define SDL_MAIN_HANDLED /*To fix SDL's "undefined reference to WinMain" \
                            issue*/
#include "lvgl/lvgl.h"
#include "lv_examples/lv_examples.h"
#include "hardware/LCD/lcd.h"
#include "hardware/TOUCH/touch.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/


/**********************
 *  STATIC VARIABLES
 **********************/
lv_indev_t *kb_indev;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/



/**********************
 *   STATIC FUNCTIONS
 **********************/
bool touch_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    (void) indev_drv;      /*Unused*/
    tp_dev.scan(0);
    /*Store the collected data*/
    data->point.x = tp_dev.x[0];
    data->point.y = tp_dev.y[0];
    data->state = (tp_dev.sta >> 7) ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;

    return false;
}

void lcd_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
    lv_coord_t hres = disp_drv->rotated == 0 ? disp_drv->hor_res : disp_drv->ver_res;
    lv_coord_t vres = disp_drv->rotated == 0 ? disp_drv->ver_res : disp_drv->hor_res;

//    printf("x1:%d,y1:%d,x2:%d,y2:%d\n", area->x1, area->y1, area->x2, area->y2);

    /*Return if the area is out the screen*/
    if(area->x2 < 0 || area->y2 < 0 || area->x1 > hres - 1 || area->y1 > vres - 1) {

        lv_disp_flush_ready(disp_drv);
        return;
    }

    uint32_t y,x;
    uint32_t w = lv_area_get_width(area);
    for(y = area->y1; y <= area->y2 && y < disp_drv->ver_res; y++) {
    	LCD_SetCursor(area->x1,y);   	//设置光标位置
    	LCD_WriteRAM_Prepare();     //开始写入GRAM
    	for(x = 0; x < w; x++) {
    		LCD->LCD_RAM=color_p->full;//写入数据
    		color_p++;
    	}
    }
    /*IMPORTANT! It must be called to tell the system the flush is ready*/
    lv_disp_flush_ready(disp_drv);
}
/**
 * Initialize the Hardware Abstraction Layer (HAL) for the Littlev graphics
 * library
 */
void hal_init(void) {

  /*Create a display buffer*/
  static lv_disp_buf_t disp_buf1;
  //static lv_color_t buf1_1[LV_HOR_RES_MAX * 10];
  //static lv_color_t buf1_2[LV_HOR_RES_MAX * 10];
  static lv_color_t *buf1_1 = (lv_color_t *)0x68040000;
  //static lv_color_t *buf1_2 = (lv_color_t *)0x68100000;
  lv_disp_buf_init(&disp_buf1, buf1_1, NULL, LV_HOR_RES_MAX * 480);

  /*Create a display*/
  lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv); /*Basic initialization*/
  disp_drv.buffer = &disp_buf1;
  disp_drv.flush_cb = lcd_flush;
  lv_disp_drv_register(&disp_drv);

  /* Add the mouse as input device
   * Use the 'mouse' driver which reads the PC's mouse*/
  lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv); /*Basic initialization*/
  indev_drv.type = LV_INDEV_TYPE_POINTER;

  /*This function will be called periodically (by the library) to get the mouse position and state*/
  indev_drv.read_cb = touch_read;
  lv_indev_drv_register(&indev_drv);

}


