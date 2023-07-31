#include "hal.h"
#include <Arduino.h>
#include "config.h"

static int laststate_s1 ;
static int currentState_s1; 
static int counter = 0 ; 
static ButtonEvent btn_event(2000);


static void btn_handler(ButtonEvent* btn, int event){
    if (event == ButtonEvent::EVENT_PRESSED){
        Serial.println("encoder button pushed");
    }
}

bool HAL::encoder_btn_pressed(void){

    if (digitalRead(encoder_btn) == LOW){
        return true; 
    }
    return false; 
}


void HAL::encoder_init(){
    pinMode(encoder_btn,INPUT_PULLUP);
    pinMode(encoder_sw1,INPUT);
    pinMode(encoder_sw2,INPUT);
    laststate_s1 = digitalRead(encoder_sw1);
    btn_event.EventAttach(btn_handler);
}


void HAL::encoder_update(void){

    // Serial.println("encoder updating");
    currentState_s1 = digitalRead(encoder_sw1);
    // Serial.println(currentState_s1);
    if (currentState_s1 != laststate_s1 && currentState_s1 ==1){
        if (digitalRead(encoder_sw2)!=currentState_s1){
            counter--;
            Serial.printf("Current counter : %d\n", counter);
        } 
        else{
            counter++;
            Serial.printf("Current counter : %d\n", counter);
        }
    }

    laststate_s1 = currentState_s1; 
}

int HAL::get_encoder_counter(){
    return counter;
}