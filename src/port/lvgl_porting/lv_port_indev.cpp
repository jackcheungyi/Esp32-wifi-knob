#include "lvgl.h"
#include "hal/hal.h"

static void button_init(void);
static void button_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
static int8_t button_get_pressed_id(void);
static bool button_is_pressed(uint8_t id);

static void encoder_init(void);
static void encoder_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
static void encoder_handler(void);

static lv_indev_t * indev_button;
static lv_indev_t * indev_encoder; 
static lv_indev_drv_t indev_drv_btn;
static lv_indev_drv_t indev_drv_enc;    

void lv_port_indev_init(void)
{   
    Serial.println("lvgl input device init");
    
    // button_init(); 
    // lv_indev_drv_init(&indev_drv_btn);
    // indev_drv_btn.type = LV_INDEV_TYPE_BUTTON; 
    // indev_drv_btn.read_cb = button_read;
    // // indev_button = lv_indev_drv_register(&indev_drv_btn);
    // lv_indev_drv_register(&indev_drv_btn);

    // static const lv_point_t btn_points[2] = {
    //         {10, 10},   /*Button 0 -> x:10; y:10*/
    //         {40, 100}  /*Button 1 -> x:20; y:10*/
    //         // {30, 10},  
    //         // {40, 10},
    // };

    // lv_indev_set_button_points(indev_button, btn_points);


    encoder_init();
    lv_indev_drv_init(&indev_drv_enc); 
    indev_drv_enc.type = LV_INDEV_TYPE_ENCODER;
    indev_drv_enc.read_cb = encoder_read; 
    lv_indev_drv_register(&indev_drv_enc);
    // indev_encoder = lv_indev_drv_register(&indev_drv_enc);
    
}

static void button_init(void)
{
    /*Your code comes here*/
    Serial.println("Button init.....");
}

static void button_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    static uint8_t last_btn = 0;
    /*Get the pressed button's ID*/
    int8_t btn_act = button_get_pressed_id();

    if(btn_act >= 0) {
        data->state = LV_INDEV_STATE_PR;
        last_btn = btn_act;
    } else {
        data->state = LV_INDEV_STATE_REL;
    }

    /*Save the last pressed button's ID*/
    data->btn_id = last_btn;
}

/*Get ID  (0, 1, 2 ..) of the pressed button*/
static int8_t button_get_pressed_id(void)
{
    uint8_t i;

    /*Check to buttons see which is being pressed (assume there are 2 buttons)*/
    for(i = 0; i < 3; i++) {
        /*Return the pressed button's ID*/
        if(button_is_pressed(i)) {
            return i;
        }
    }

    /*No button pressed*/
    return -1;
}



static bool button_is_pressed(uint8_t id)
{
    switch(id){
        case 0 : 
            return HAL::btn1_is_pressed();
           break;
        case 1 :
            return HAL::btn2_is_pressed();
            break;
        case 2 : 
            return HAL::btn3_is_pressed();
            break;
        case 3 : 
            return HAL::btn1_is_pressed();
            break;
        
        default:
            return false;
    }
}

static void encoder_init(void)
{
    /******Your code here********/
    Serial.println("Encoder init........");
}


static void encoder_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data){

    // Serial.println("Encoder callback function called");
    static int prev_counter = 0 ;
    static int cur_counter = 0 ; 

    cur_counter = HAL::get_encoder_counter();

    if ((cur_counter - prev_counter)>=2){
        data->enc_diff++; 
        prev_counter = HAL::get_encoder_counter();
        Serial.println("encoder ++ in lv_indev file");
    }
    else if ((cur_counter - prev_counter)<=-2) {
        data->enc_diff--;
        prev_counter = HAL::get_encoder_counter();
        Serial.println("encoder -- in lv_indev file");
    }


    if (HAL::encoder_btn_pressed()){
        Serial.println("Encoder button is pressed");
    }
    data->state = HAL::encoder_btn_pressed()?LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
}