#ifndef __CONFIG_H__
#define __CONFIG_H__

/*SPI monitor*/

#define CONFIG_SCREEN_HOR_RES       240
#define CONFIG_SCREEN_VER_RES       240
#define CONFIG_SCREEN_BUFFER_SIZE   (CONFIG_SCREEN_HOR_RES * CONFIG_SCREEN_VER_RES /2)

#define SCLK    12
#define S_MOSI  11
#define TFT_CS  10 
#define TFT_BLK 13
#define TFT_DC  14 
#define TFT_RST 9 


/*Button*/

#define Btn_1  15 
#define Btn_2  16
#define Btn_3  17 
#define Btn_4  18

/***Encoder*****/
#define encoder_btn 5 
#define encoder_sw1 6
#define encoder_sw2 7

/*Core assignment*/
#define LVGL_RUNNING_CORE   0            
#define ESP32_RUNNING_CORE  1  

#endif