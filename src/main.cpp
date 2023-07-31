#include <Arduino.h>
#include "hal/hal.h"
#include "port/display.h"
#include <esp_heap_caps.h>
#include "app/app.h"
// put function declarations here:

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.printf("Default free size: %d\n",heap_caps_get_free_size(MALLOC_CAP_DEFAULT));
  Serial.printf("PSRAM free size: %d\n",heap_caps_get_free_size(MALLOC_CAP_SPIRAM));
  HAL::Init();
  SCREEN_LCD::display_init();
  App_Init();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  HAL::Update();
  // lv_task_handler();
  
    /* Periodically call the lv_task handler.
     * It could be done in a timer interrupt or an OS task too.*/
  // delay(5000);
  // lv_timer_handler();
  delay(5);
  
}

