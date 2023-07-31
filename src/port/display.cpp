#include "display.h"
#include "config.h"
#include "Arduino.h"
// #include "hal/hal.h"
#include "freertos/FreeRTOS.h"
#include  "freertos/task.h"
#include "lvgl_porting/lv_port_indev.h"

TaskHandle_t handleTaskLvgl;

Arduino_DataBus *bus  = new Arduino_ESP32SPI(TFT_DC,TFT_CS,SCLK,S_MOSI);
Arduino_GFX *screen = new Arduino_ST7789(bus,TFT_RST,0,true,240,240,0,0);

static uint32_t screenWidth;
static uint32_t screenHeight;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t *disp_draw_buf;
static lv_disp_drv_t disp_drv;



void TaskLvglUpdate(void* parameter)
{   
    Serial.println("Task handler called");
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    vTaskDelay(100/portTICK_RATE_MS);
    while(1)
    {
        lv_task_handler();
        // Serial.println("lvgl task handler running.....");
        vTaskDelay(5/portTICK_RATE_MS);
    }
}

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

#if (LV_COLOR_16_SWAP != 0)
  screen->draw16bitBeRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#else
  screen->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#endif

  lv_disp_flush_ready(disp);
}




void SCREEN_LCD::display_init(void)
{   

    Serial.println("Display init ....");
    if (!screen->begin())
    {
        Serial.println("gfx->begin() failed!");
    }
    screen->fillScreen(BLACK);
    #ifdef TFT_BLK
        pinMode(TFT_BLK, OUTPUT);
        digitalWrite(TFT_BLK, HIGH);
    #endif

// #ifdef TFT_BLK
//     pinMode(TFT_BLK, OUTPUT);
//     digitalWrite(TFT_BLK, HIGH);
// #endif
    
    lv_init();
    // Serial.println("Init lvgl passed and initializing lv disp....");
    // lv_port_disp_init(screen);
    // Serial.println("lv disp passed");
    // lv_port_indev_init();//pending to write input device 


      screenWidth = screen->width();
    screenHeight = screen->height();
    disp_draw_buf = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * screenWidth * 40, MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
    if (!disp_draw_buf)
    {
        Serial.println("LVGL disp_draw_buf allocate failed!");
    }
    else{
        lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, screenWidth * 100);
        lv_disp_drv_init(&disp_drv);
        disp_drv.hor_res = screenWidth;
        disp_drv.ver_res = screenHeight;
        disp_drv.flush_cb = my_disp_flush;
        disp_drv.draw_buf = &draw_buf;
        lv_disp_drv_register(&disp_drv);

        lv_port_indev_init();

        // lv_obj_t *label = lv_label_create(lv_scr_act());
        // lv_label_set_text(label, "Hello World! (V" GFX_STR(LVGL_VERSION_MAJOR) "." GFX_STR(LVGL_VERSION_MINOR) "." GFX_STR(LVGL_VERSION_PATCH) ")");
        // lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

        Serial.println("Setup done");
    }




    // lv_obj_t *label = lv_label_create(lv_scr_act());
    // lv_label_set_text(label, "Hello Arduino! (V" GFX_STR(LVGL_VERSION_MAJOR) "." GFX_STR(LVGL_VERSION_MINOR) "." GFX_STR(LVGL_VERSION_PATCH) ")");
    // lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

    Serial.println("Setup done");
    xTaskCreatePinnedToCore(
        TaskLvglUpdate,
        "LvglThread",
        10000,
        NULL,
        // configMAX_PRIORITIES - 1,
        1,
        &handleTaskLvgl,
        LVGL_RUNNING_CORE);
}