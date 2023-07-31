#include <lvgl.h>
#include "config.h"
#include "port/display.h"


#define DISP_BUF_SIZE   CONFIG_SCREEN_BUFFER_SIZE

static uint32_t screenWidth;
static uint32_t screenHeight;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t *disp_draw_buf;
static lv_disp_drv_t disp_drv;

static void disp_flush_cb(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p){
    int32_t w = (area->x2 - area->x1 + 1);
    int32_t h = (area->y2 - area->y1 + 1);
    Arduino_GFX* screen = (Arduino_GFX*) disp->user_data;
    screen->draw16bitBeRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);

    lv_disp_flush_ready(disp);
}

void my_print(lv_log_level_t level, const char* file, uint32_t line, const char* fun, const char* dsc)
{

    Serial.printf("%s@%d %s->%s\r\n", file, line, fun);
    Serial.flush();
    
}

void myPrintCallback(lv_log_level_t level, const char *format, va_list args) {
  char log_buffer[256];  // Adjust the buffer size as needed
  vsnprintf(log_buffer, sizeof(log_buffer), format, args);
  Serial.println(log_buffer);
}



void lv_port_disp_init(Arduino_GFX* scr) {

    lv_disp_draw_buf_t draw_buf; 
    
    lv_disp_drv_t disp_drv;
    
    // lv_log_register_print_cb(
    //     reinterpret_cast<lv_log_print_g_cb_t>(my_print)); /* register print function for debugging */

    screenWidth = scr->width();
    Serial.printf("Screen Width : %d\n", screenWidth);
    screenHeight = scr->height();
    Serial.printf("Screen height: %d\n", screenHeight);
    lv_color_t *buf1;
    lv_color_t *buf2;
    // buf1 = (lv_color_t *)heap_caps_malloc(CONFIG_SCREEN_HOR_RES * 100 * sizeof(lv_color_t), MALLOC_CAP_SPIRAM);
    // assert(buf1);
    // buf2 = (lv_color_t *)heap_caps_malloc(CONFIG_SCREEN_HOR_RES * 100 * sizeof(lv_color_t), MALLOC_CAP_SPIRAM);
    // assert(buf2);
    disp_draw_buf = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * screenWidth * 40, MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
    // disp_draw_buf = (lv_color_t *)malloc(sizeof(lv_color_t) * screenWidth * 10);
    // if (!disp_draw_buf) {
    //     LV_LOG_WARN("LVGL disp_draw_buf allocate failed!");
    // }
    if (!disp_draw_buf)
    {
        Serial.println("LVGL disp_draw_buf allocate failed!");
    }
    else {
        lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, DISP_BUF_SIZE);
        lv_disp_drv_init(&disp_drv);
        disp_drv.hor_res = screenWidth;
        disp_drv.ver_res = screenHeight;
        disp_drv.flush_cb = disp_flush_cb;
        disp_drv.draw_buf = &draw_buf;
        disp_drv.user_data = scr;
        lv_disp_drv_register(&disp_drv);
    }
    
    // lv_disp_draw_buf_init(&draw_buf, disp_draw_buf_1, disp_draw_buf_2, DISP_BUF_SIZE);
    // lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, DISP_BUF_SIZE);

    /* Initialize the display */
    
    
    
    
    /* Initialize the (dummy) input device driver */
    // ui_init();
    // lv_img_set_pivot(ui_Image2, 16, 120); /*Rotate around the top left corner*/
    // lv_meter_set_indicator_value(meter, line_indic, 50);
}