#include "StartUpView.h"


using namespace Page; 

#define COLOR_BlUE lv_color_hex(0x399cbd)
#define COLOR_ORANGE lv_color_hex(0xffa700)

void StartupView::Create(lv_obj_t *root)
{
    lv_obj_remove_style_all(root);
    lv_obj_set_size(root, LV_HOR_RES, LV_VER_RES);

    /***Include elements into page content***/
    /***Create Start page orange bar***/
    lv_obj_t *cont = lv_obj_create(root);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, 110, 40);   
    lv_obj_set_style_border_color(cont, COLOR_ORANGE, 0);
    lv_obj_set_style_border_side(cont, LV_BORDER_SIDE_BOTTOM, 0);
    lv_obj_set_style_border_width(cont, 3, 0);
    lv_obj_set_style_border_post(cont, true, 0);
    lv_obj_center(cont);
    ui.cont = cont;

    /****Create Titile****/
    lv_obj_t *label = lv_label_create(cont);
    lv_obj_set_style_text_font(label,&lv_font_montserrat_26,0);
    lv_obj_set_style_text_color(label,COLOR_BlUE,0);
    lv_label_set_text(label, "JACK");
    lv_obj_center(label);
    ui.labelLogo = label; 

    ui.anim_timeline = lv_anim_timeline_create();

    #define ANIM_DEF(start_time, obj, attr, start, end) \
    {start_time, obj, LV_ANIM_EXEC(attr), start, end, 1000, lv_anim_path_ease_in_out, true}
    //  {start_time, obj, LV_ANIM_EXEC(attr), start, end, 1000, lv_anim_path_ease_out, true}

    lv_anim_timeline_wrapper_t wrapper[] =
    {
        ANIM_DEF(0, ui.cont, width, 0, lv_obj_get_style_width(ui.cont, 0)),
        // ANIM_DEF(500, ui.labelLogo, y, lv_obj_get_style_height(ui.cont, 0), lv_obj_get_y(ui.labelLogo)), // 从下往上
        ANIM_DEF(500, ui.labelLogo, x, lv_obj_get_x(ui.labelLogo)+90, lv_obj_get_x(ui.labelLogo)), //
        
        LV_ANIM_TIMELINE_WRAPPER_END
    };

    lv_anim_timeline_add_wrapper(ui.anim_timeline, wrapper);
}

void StartupView::Delete()
{
    if(ui.anim_timeline)
    {
        lv_anim_timeline_del(ui.anim_timeline);
        ui.anim_timeline = nullptr;
    }
}