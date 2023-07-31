#include "ResourcePool.h"

ResourcePool Resource;

extern "C"{
#define IMPORT_IMG(name)\
do{\
    LV_IMG_DECLARE(name)\
    Resource.Image_.AddResource(#name,(void*)&name);\
}while(0)

    static void Resource_Init()
    {
        /*IMPORT Iamges*/
        IMPORT_IMG(settings);
        IMPORT_IMG(airconditioner);
        IMPORT_IMG(cpu);
    }

}



void ResourcePool::Init()
{
    lv_obj_remove_style_all(lv_scr_act());
    lv_disp_set_bg_color(lv_disp_get_default(), lv_color_black());

    Font_.SetDefault((void*)&lv_font_montserrat_14);

    Resource_Init();
}