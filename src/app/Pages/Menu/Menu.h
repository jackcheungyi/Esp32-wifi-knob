#ifndef __MENU_PRESENTER_H
#define __MENU_PRESENTER_H

#include "MenuModel.h"
#include "MenuView.h"

namespace Page
{
class Menu : public PageBase 
{
public:
    Menu();
    virtual ~Menu();

    virtual void onCustomAttrConfig();
    virtual void onViewLoad();
    virtual void onViewDidLoad();
    virtual void onViewWillAppear();
    virtual void onViewDidAppear();
    virtual void onViewWillDisappear();
    virtual void onViewDidDisappear();
    virtual void onViewDidUnload();

private: 
    MenuView View; 
    MenuModel Model;
    lv_timer_t* timer;

    void Update();
    void AttachEvent(lv_obj_t* obj, lv_event_cb_t event_cb);
    static void onTimerUpdate(lv_timer_t* timer);
};

}




#endif 