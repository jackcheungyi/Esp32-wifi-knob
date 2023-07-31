#ifndef __HAL_H__
#define __HAL_H__
#include "button_event.h"
#include "HAL_Def.h"
#include <Arduino.h>
#include "config.h"
#include "CommonMacro.h"


namespace HAL 
{
    void Init();
    void Update();

    void button_init();
    void button_update(void);
    bool btn1_is_pressed(void);
    bool btn2_is_pressed(void);
    bool btn3_is_pressed(void);
    bool btn4_is_pressed(void);

    void encoder_init();
    void encoder_update(void);
    bool encoder_btn_pressed(void);
    int get_encoder_counter();
    
}

#endif 