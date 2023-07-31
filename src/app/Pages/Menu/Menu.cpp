#include "Menu.h"
#include "app/app.h"

using namespace Page; 

Menu::Menu()
{

}

Menu::~Menu()
{

}

void Menu::onCustomAttrConfig()
{

}

void Menu::onViewLoad()
{
    Model.Init();
    View.Create(root);
}

void Menu::onViewDidLoad(){
    
}

void Menu::onViewWillAppear(){
    lv_indev_set_group(lv_get_indev(LV_INDEV_TYPE_ENCODER),View.ui.group);

    // timer = lv_timer_create(onTimerUpdate,100,this);
    // lv_timer_ready(timer);

    View.SetScrollToY(root,-LV_VER_RES,LV_ANIM_OFF);
    lv_obj_fade_in(root,300,10);
}

void Menu::onViewDidAppear(){
    View.onFocus(View.ui.group);
}

void Menu::onViewWillDisappear(){
    lv_obj_fade_out(root,300,10);
}

void Menu::onViewDidDisappear(){
    // lv_timer_del(timer);
}

void Menu::onViewDidUnload(){
    View.Delete();
    Model.Deinit();
}