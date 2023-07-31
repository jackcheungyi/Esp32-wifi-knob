#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "lvgl.h"
#include <Arduino_GFX_Library.h>

// typedef Arduino_ST7789  SCREEN_CLASS;

// void lv_port_disp_init(Arduino_GFX* scr);
// void lv_port_indev_init();

extern TaskHandle_t handleTaskLvgl;

namespace SCREEN_LCD
{
    void display_init();
}


#endif