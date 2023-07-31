#ifndef __APP_H__
#define __APP_H__

#include "port/display.h"
#include "freertos/FreeRTOS.h"
#include  "freertos/task.h"

#define _INIT_DONE()\
do{\
    xTaskNotifyGive(handleTaskLvgl);\
}while(0)

void App_Init();
// void App_UnInit();



#endif