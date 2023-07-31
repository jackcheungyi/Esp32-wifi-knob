#include "hal.h" 


void HAL::Init()
{
    Serial.println("HAL INIT....");
    button_init();
    encoder_init();
}


void HAL::Update()
{
    __IntervalExecute(HAL::button_update(), 10);
    __IntervalExecute(HAL::encoder_update(),10);
}