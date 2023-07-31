#include "StartUp.h"
#include "Arduino.h"
using namespace Page;

Startup::Startup()
{
}

Startup::~Startup()
{

}

void Startup::onCustomAttrConfig()
{
    SetCustomCacheEnable(false);
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_NONE);
}

void Startup::onViewLoad()
{   
    Serial.println("Startup page in 'onViewLoad'");
    Model.Init();
    // Model.SetEncoderEnable(false);
    View.Create(root);
    lv_timer_t* timer = lv_timer_create(onTimer, 2000, this);
    if (timer == NULL) {
        Serial.printf("\ntimer create error\n");
    }
    lv_timer_set_repeat_count(timer, 1);
}

void Startup::onViewDidLoad()
{
    Serial.println("Startup page on 'onViewDidLoad'");
    // lv_obj_fade_out(root, 300, 15000);
}

void Startup::onViewWillAppear()
{   
    Serial.println("Startup page on 'onViewWillAppear'");
    lv_anim_timeline_start(View.ui.anim_timeline);
}

void Startup::onViewDidAppear()
{
    Serial.println("Startup page on 'onViewDidAppear'");
}

void Startup::onViewWillDisappear()
{
    Serial.println("Startup page on 'onViewWillDisappear'");
}

void Startup::onViewDidDisappear()
{
    // StatusBar::Appear(true);
    Serial.println("Startup page on 'onViewDidDisappear'");
}

void Startup::onViewDidUnload()
{   

    Serial.println("Startup page on 'onViewDidUnload'");
    View.Delete();
    // Model.SetEncoderEnable(true);
    Model.DeInit();
}

void Startup::onTimer(lv_timer_t* timer)
{   

    Serial.printf("\n StartUp on timer\n");
    Startup* instance = (Startup*)timer->user_data;

    instance->Manager->Push("Pages/Menu");
}
