
#include "hal.h"
#include <Arduino.h>
#include "config.h"

static ButtonEvent btn1_event(2000);
static ButtonEvent btn2_event(2000);
static ButtonEvent btn3_event(2000);
static ButtonEvent btn4_event(2000);

bool HAL::btn1_is_pressed(void)
{
    if (digitalRead(Btn_1)== LOW){
        return true; 
    }
    else
        return false; 
}

bool HAL::btn2_is_pressed(void)
{
    if (digitalRead(Btn_2)== LOW){
        return true; 
    }
    else
        return false; 
}

bool HAL::btn3_is_pressed(void)
{
    if (digitalRead(Btn_3)== LOW){
        return true; 
    }
    else
        return false; 
}

bool HAL::btn4_is_pressed(void)
{
    if (digitalRead(Btn_4)== LOW){
        return true; 
    }
    else
        return false; 
}


static void btn1_handler(ButtonEvent* btn, int event)
{
    if (event == ButtonEvent::EVENT_PRESSED){
        Serial.println("btn1 pushed");
    }
}


static void btn2_handler(ButtonEvent* btn, int event)
{
    if (event == ButtonEvent::EVENT_PRESSED){
        Serial.println("btn2 pushed");
    }
}


static void btn3_handler(ButtonEvent* btn, int event)
{
    if (event == ButtonEvent::EVENT_PRESSED){
        Serial.println("btn3 pushed");
    }
}


static void btn4_handler(ButtonEvent* btn, int event)
{
    if (event == ButtonEvent::EVENT_PRESSED){
        Serial.println("btn4 pushed");
    }
}

void HAL::button_update(void){
    
}

void HAL::button_init(){
    pinMode(Btn_1,INPUT_PULLUP);
    pinMode(Btn_2,INPUT_PULLUP);
    pinMode(Btn_3,INPUT_PULLUP);
    pinMode(Btn_4,INPUT_PULLUP);
    btn1_event.EventAttach(btn1_handler);
    btn2_event.EventAttach(btn2_handler);
    btn3_event.EventAttach(btn3_handler);
    btn4_event.EventAttach(btn4_handler);
}