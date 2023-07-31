#ifndef __STARTUP_VIEW_H
#define __STARTUP_VIEW_H

#include "app/Pages/Page.h"

namespace Page
{
class StartupView
{
public:
    struct
    {
        lv_obj_t* cont;
        lv_obj_t* labelLogo;

        lv_anim_timeline_t* anim_timeline;
    } ui;

    void Create(lv_obj_t* root);
    void Delete();

};
}


#endif