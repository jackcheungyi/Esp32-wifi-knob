#include "MenuView.h"

using namespace Page; 

#define ITEM_HEIGHT_MIN 100
#define ITEM_PAD ((LV_VER_RES - ITEM_HEIGHT_MIN)/2)
#define COLOR_DARK_GRAY lv_color_hex(0x5a5a5a)
#define COLOR_ORANGE lv_color_hex(0xffa700)
#define COLOR_BlUE lv_color_hex(0x399cbd)


void MenuView::Create(lv_obj_t* root){
    lv_obj_remove_style_all(root);
    lv_obj_set_size(root,LV_HOR_RES,LV_VER_RES);
    lv_obj_set_style_bg_color(root,COLOR_DARK_GRAY,0);
    lv_obj_set_style_bg_opa(root, LV_OPA_COVER, 0);
	lv_obj_set_style_pad_ver(root, ITEM_PAD, 0);

    lv_obj_set_flex_flow(root,LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(root,LV_FLEX_ALIGN_START,LV_FLEX_ALIGN_START,LV_FLEX_ALIGN_CENTER);

    Style_Init();

    Item_Create(&ui.air,root,"Air-Con","airconditioner",
                "Air-Conditioner\n" "Control\n""Your\n""Air-Con\n");

    Item_Create(&ui.setting,root,"Settings","settings",
                "Change\n" "Your\n""network\n""Settings\n");
    
    Item_Create(&ui.system,root,"System Info","cpu",
                "System\n" "Build\n""Information\n");

    Group_Init();
}; 


void MenuView::Delete(){
    lv_group_del(ui.group);
    Style_Reset();
}

void MenuView::SetScrollToY(lv_obj_t* obj, lv_coord_t y, lv_anim_enable_t en)
{
	lv_coord_t scroll_y = lv_obj_get_scroll_y(obj);
	lv_coord_t diff = -y + scroll_y;

	lv_obj_scroll_by(obj, 0, diff, en);
}

void MenuView::onFocus(lv_group_t* f_icon){
    lv_obj_t* icon = lv_group_get_focused(f_icon);
    lv_obj_t* cont = lv_obj_get_parent(icon);
    lv_coord_t y = lv_obj_get_y(cont);
    lv_obj_scroll_to_y(lv_obj_get_parent(cont), y, LV_ANIM_ON);
}

void MenuView::Group_Init(){
    ui.group = lv_group_create();
    lv_group_set_focus_cb(ui.group,onFocus);
    lv_group_add_obj(ui.group,ui.air.icon);
    lv_group_add_obj(ui.group,ui.setting.icon);
    lv_group_add_obj(ui.group,ui.system.icon);

}

void MenuView::Style_Init(){
    lv_style_init(&style.icon);
    lv_style_set_width(&style.icon,220);
    lv_style_set_bg_color(&style.icon,COLOR_DARK_GRAY);
    lv_style_set_bg_opa(&style.icon,255);
    lv_style_set_text_font(&style.icon,&lv_font_montserrat_18);
    lv_style_set_text_color(&style.icon,lv_color_white());

    lv_style_init(&style.focus);
    lv_style_set_width(&style.focus,70);
    lv_style_set_border_side(&style.focus,LV_BORDER_SIDE_RIGHT);
    lv_style_set_border_width(&style.focus , 2);
    lv_style_set_border_color(&style.focus,COLOR_ORANGE);

    static const lv_style_prop_t style_prop[] =
	{
		LV_STYLE_WIDTH,
		LV_STYLE_PROP_INV
	};

    static lv_style_transition_dsc_t trans;
    lv_style_transition_dsc_init(&trans,style_prop,lv_anim_path_overshoot,400,0,nullptr);
    lv_style_set_transition(&style.focus, &trans);
	lv_style_set_transition(&style.icon, &trans);

    lv_style_init(&style.info);
    lv_style_set_text_font(&style.info, &lv_font_montserrat_14);
    lv_style_set_text_color(&style.info,COLOR_BlUE);

    lv_style_init(&style.data);
    lv_style_set_text_font(&style.data, &lv_font_montserrat_14);
    lv_style_set_text_color(&style.data,lv_color_white());

}

void MenuView::Style_Reset()
{
	lv_style_reset(&style.icon);
	lv_style_reset(&style.info);
	lv_style_reset(&style.data);
	lv_style_reset(&style.focus);
}

void MenuView::Item_Create(item_t* item, lv_obj_t* obj,const char* name, const char* img_src, const char* infos){
    lv_obj_t* cont = lv_obj_create(obj);
    lv_obj_remove_style_all(cont);
    lv_obj_set_width(cont,220);

    lv_obj_clear_flag(cont,LV_OBJ_FLAG_SCROLLABLE);
    item->cont = cont; 

    /**icon**/
    lv_obj_t* icon = lv_obj_create(cont); 
    lv_obj_remove_style_all(icon);
    lv_obj_clear_flag(icon,LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_style(icon,&style.icon,0);
    lv_obj_add_style(icon,&style.focus,LV_STATE_FOCUSED);
    lv_obj_set_style_align(icon, LV_ALIGN_LEFT_MID, 0);

    lv_obj_set_flex_flow(icon, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(icon,LV_FLEX_ALIGN_SPACE_AROUND,LV_FLEX_ALIGN_CENTER,LV_FLEX_ALIGN_CENTER);

    lv_obj_t* img = lv_img_create(icon);
	lv_img_set_src(img, Resource.GetImage(img_src));

    lv_obj_t* label_name = lv_img_create(icon);
    lv_label_set_text(label_name, name);
	item->icon = icon;

    /**infos**/
    lv_obj_t* label = lv_label_create(cont);
    lv_label_set_text(label,infos);
    lv_obj_add_style(label, &style.info, 0);
	lv_obj_align(label, LV_ALIGN_LEFT_MID, 75, 0);
	item->labelInfo = label;

    lv_obj_move_foreground(icon);

    // /* datas */
	// label = lv_label_create(cont);
	// lv_label_set_text(label, "");
	// lv_obj_add_style(label, &style.data, 0);
	// lv_obj_align(label, LV_ALIGN_CENTER, 60, 0);
	// item->labelData = label;

    lv_obj_update_layout(item->labelInfo);
    lv_coord_t height = lv_obj_get_height(item->labelInfo);
    height = LV_MAX(height, ITEM_HEIGHT_MIN);
	lv_obj_set_height(cont, height);
	lv_obj_set_height(icon, height);

}

void MenuView::setSystem_info(char* firmVer,char* authorname,char* lvglVer, char* bootTime, char* buildTime){

}