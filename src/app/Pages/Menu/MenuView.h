#ifndef __MENU_VIEW_H
#define __MENU_VIEW_H

#include "app/Pages/Page.h"

namespace Page
{
    class MenuView
    {
        public:
            void Create(lv_obj_t* root);
            void Delete();

            typedef struct{
                lv_obj_t* cont;
                lv_obj_t* icon; 
                lv_obj_t* labelInfo;
                lv_obj_t* labelData;
            }item_t; 

            typedef struct{
                item_t air; 
                item_t setting;
                item_t system; 
                lv_group_t* group; 
            }ui_t; 

            ui_t ui;
            void SetScrollToY(lv_obj_t* obj, lv_coord_t y, lv_anim_enable_t en);
            static void onFocus(lv_group_t* e);
            void setSystem_info(char* firmVer,char* authorname,char* lvglVer, char* bootTime, char* buildTime);

            private:

                struct{
                    lv_style_t icon;
                    lv_style_t focus;
                    lv_style_t info;
                    lv_style_t data;
                }style; 

                void Group_Init();
                void Style_Init();
                void Style_Reset();
                void Item_Create(item_t* item, lv_obj_t* obj,const char* name, const char* img_src, const char* infos);

    };
} // namespace  









#endif 