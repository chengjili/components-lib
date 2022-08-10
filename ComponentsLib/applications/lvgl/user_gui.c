/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-06-22     cheng       the first version
 */


#include "user_gui.h"
#include "lv_ll.h"
#include "lv_gc.h"
#include "nu_jpegcodec.h"
#include "dfs_file.h"
#include "sqlite3.h"
#include "sysdatabase.h"
#include "lv_disp.h"

#define DBG_ENABLE
#define DBG_SECTION_NAME "app.user_gui"
#define DBG_LEVEL DBG_INFO
#define DBG_COLOR
#include <rtdbg.h>

uint8_t backgound_image_name_LVGL[] =      "S:/mnt/sd0/backgound/backgound2.jpg";        //"S:/mnt/sd0/backgound1.bin";
uint8_t backgound2_image_name_LVGL[] =     "S:/mnt/sd0/backgound/backgound3.jpg";
//uint8_t user_icon_name_LVGL[] = "S:/mnt/sd0/img/user.png";
//uint8_t pwd_icon_name_LVGL[] = "S:/mnt/sd0/img/password.png";

static void ta_event_cb(lv_event_t * e);
static void user_ta_event_cb(lv_event_t * e);
static void user_roller_event_handler(lv_event_t * e);
static void login_btn_event_handler(lv_event_t * e);
static void register_btn_event_handler(lv_event_t * e);
static void logout_btn_event_handler(lv_event_t * e);

static void user_reg_ta_event_cb(lv_event_t * e);
static void reg_cancel_btn_event_handler(lv_event_t * e);
static void reg_pwd_ta_1_event_cb(lv_event_t * e);
static void reg_pwd_ta_2_event_cb(lv_event_t * e);
static void admi_pwd_ta_event_cb(lv_event_t * e);
static void reg_ok_btn_event_handler(lv_event_t * e);
static void draw_part_event_cb(lv_event_t * e);

static void chip_search_ta_event_cb(lv_event_t * e);

static void chip_tb_select_cb(lv_event_t * e);

static void chip_table_update(lv_obj_t *tb, const char *nm);

static void main_tv_change_cb(lv_event_t * e);

static void chip_delete_btn_event_cb(lv_event_t * e);

static void chip_OK_btn_event_cb(lv_event_t * e);
static void chip_cancel_btn_event_cb(lv_event_t * e);
void logout_timer_cb(struct _lv_timer_t *tm);

static lv_obj_t * kb;
static lv_obj_t *main_view_buf[3];

static uint32_t logout_tm = 0;

void test_timer_cb(struct _lv_timer_t *tm)
{
//    LV_IMG_DECLARE(backgound1);
//    LV_IMG_DECLARE(backgound2);
//    lv_obj_t *img = (lv_obj_t *)(tm->user_data);
//    if(img != RT_NULL)
//    {
//        if(lv_img_get_src(img) == backgound2_image_name_LVGL)
//        {
////            lv_img_set_src(img, &backgound1);
//            lv_img_set_src(img, backgound_image_name_LVGL);
//        }
//        else {
////            lv_img_set_src(img, &backgound2);
//            lv_img_set_src(img, backgound2_image_name_LVGL);
//        }
////        lv_label_set_text_fmt(label, "%d FSP, %d%% CPU\r\n", lvgl_fps, lvgl_cpu);
//    }
//    rt_kprintf("rand val:%d\r\n",rand()%4);

//    static rt_uint16_t i=0;
//    lv_obj_t *cont = (lv_obj_t *)(tm->user_data);
//    if(i++ % 2)
//        lv_obj_add_flag(cont, LV_OBJ_FLAG_HIDDEN);
//    else {
//        lv_obj_clear_flag(cont, LV_OBJ_FLAG_HIDDEN);
//    }
}

static int sys_current_ui = USER_LOGIN;

void user_gui_init(void)
{
    lv_fs_posix_init();             //绑定fs接口

    lv_split_jpeg_init();           //绑定jpeg软解码器

    lv_obj_t *lv_img_t = lv_img_create(lv_scr_act());
//    lv_img_set_src(lv_img_t, &backgound2);
    lv_img_set_src(lv_img_t, backgound_image_name_LVGL);
    lv_obj_center(lv_img_t);

    lv_obj_set_style_text_font(lv_scr_act(), &lv_font_montserrat_24, 0);

//    lv_obj_t *ui_dev_list = lv_dropdown_create(lv_scr_act());
//    lv_dropdown_set_options(ui_dev_list, "test1\n""test2\n""test3");
//    lv_obj_align(ui_dev_list, LV_ALIGN_TOP_MID, 0, 20);
//    lv_dropdown_set_symbol(ui_dev_list, LV_SYMBOL_EYE_OPEN);
//    lv_obj_set_width(ui_dev_list, LV_PCT(50));
//    lv_obj_set_style_bg_opa(ui_dev_list, LV_OPA_80, 0);

    create_sysdb_table();

    lv_style_t *main_wiew_style = rt_malloc(sizeof(lv_style_t));
    lv_style_init(main_wiew_style);
    lv_style_set_bg_opa(main_wiew_style, LV_OPA_0);
    lv_style_set_border_opa(main_wiew_style, LV_OPA_0);

    main_view_buf[0] = lv_obj_create(lv_scr_act());
    lv_obj_add_style(main_view_buf[0], main_wiew_style, 0);
    lv_obj_set_size(main_view_buf[0], LV_HOR_RES, LV_VER_RES);
//    lv_obj_add_flag(main_view_buf[0], LV_OBJ_FLAG_HIDDEN);
    main_view_buf[1] = lv_obj_create(lv_scr_act());
    lv_obj_add_style(main_view_buf[1], main_wiew_style, 0);
    lv_obj_set_size(main_view_buf[1], LV_HOR_RES, LV_VER_RES);

    main_view_buf[2] = lv_obj_create(lv_scr_act());
    lv_obj_add_style(main_view_buf[2], main_wiew_style, 0);
    lv_obj_set_size(main_view_buf[2], LV_HOR_RES, LV_VER_RES);
    sys_current_ui = USER_LOGIN;

    /************************************user_login_tab****************************************/
    if(main_view_buf[0] != RT_NULL)
    {
        static lv_coord_t col_dsc[] = {50, 350, 100, LV_GRID_TEMPLATE_LAST};
        static lv_coord_t row_dsc[] = {50, 50, LV_GRID_TEMPLATE_LAST};

        lv_obj_t * cont = lv_obj_create(main_view_buf[0]);
        lv_obj_set_grid_dsc_array(cont, col_dsc, row_dsc);
        lv_obj_set_size(cont, LV_HOR_RES * 3 / 4, LV_SIZE_CONTENT);
        lv_obj_align(cont, LV_ALIGN_TOP_MID, 0, 20);
        lv_obj_set_style_bg_opa(cont, LV_OPA_20, 0);
        lv_obj_set_grid_align(cont,LV_GRID_ALIGN_CENTER ,LV_GRID_ALIGN_CENTER);
        lv_obj_set_style_pad_column(cont, 20, 0);
        lv_obj_set_style_pad_row(cont, 20, 0);
        lv_obj_clear_flag(cont, LV_OBJ_FLAG_SCROLLABLE);

        lv_obj_t *user_name_label = lv_label_create(cont);
        lv_label_set_text(user_name_label, "");
        lv_obj_set_size(user_name_label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_set_grid_cell(user_name_label,LV_GRID_ALIGN_CENTER ,0,1,LV_GRID_ALIGN_CENTER ,0,1);
        lv_obj_set_style_bg_opa(user_name_label, LV_OPA_0, 0);
        lv_obj_set_style_pad_left(user_name_label, 20, 0);
        lv_obj_t *user_icon = lv_img_create(user_name_label);
        LV_IMG_DECLARE(user_img);
        lv_img_set_src(user_icon, &user_img);
        lv_obj_center(user_icon);
        lv_obj_set_size(user_icon, 60, 60);

        lv_obj_t *user_ta = lv_textarea_create(cont);
        lv_textarea_set_text(user_ta, "");
        lv_textarea_set_one_line(user_ta, true);
        lv_obj_set_width(user_ta, lv_pct(50));
        lv_obj_set_style_bg_opa(user_ta, LV_OPA_80, 0);
        lv_textarea_set_accepted_chars(user_ta, "0123456789ABCDJEGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz#$@*_");
        lv_textarea_set_max_length(user_ta, DB_STR_LEN_MAX);
        lv_obj_set_grid_cell(user_ta,LV_GRID_ALIGN_CENTER ,1,1,LV_GRID_ALIGN_CENTER ,0,1);

        lv_obj_t *user_roller = lv_roller_create(main_view_buf[0]);
        lv_roller_set_visible_row_count(user_roller, 1);
        lv_obj_set_style_text_font(user_roller, &lv_font_montserrat_32, LV_PART_SELECTED);
        lv_obj_add_event_cb(user_roller, user_roller_event_handler, LV_EVENT_ALL, user_ta);
        lv_obj_add_flag(user_roller, LV_OBJ_FLAG_HIDDEN);

        lv_obj_add_event_cb(user_ta, user_ta_event_cb, LV_EVENT_ALL, user_roller);

        lv_obj_t *reg_user_btn = lv_btn_create(cont);
        lv_obj_t *reg_user_btn_label = lv_label_create(reg_user_btn);
        lv_label_set_text(reg_user_btn_label, "register");
        lv_obj_set_size(reg_user_btn, 130, LV_SIZE_CONTENT);
        lv_obj_set_grid_cell(reg_user_btn,LV_GRID_ALIGN_CENTER ,2,1,LV_GRID_ALIGN_CENTER ,0,1);
        lv_obj_add_event_cb(reg_user_btn, register_btn_event_handler, LV_EVENT_CLICKED, 0);

        lv_obj_t *password_label = lv_label_create(cont);
        lv_label_set_text(password_label, "");
        lv_obj_set_size(password_label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_set_grid_cell(password_label,LV_GRID_ALIGN_CENTER ,0,1,LV_GRID_ALIGN_CENTER ,1,1);
        lv_obj_set_style_bg_opa(password_label, LV_OPA_0, 0);
        lv_obj_set_style_pad_left(password_label, 20, 0);
        lv_obj_t *pwd_icon = lv_img_create(password_label);
        LV_IMG_DECLARE(password_img);
        lv_img_set_src(pwd_icon, &password_img);
        lv_obj_center(pwd_icon);
        lv_obj_set_size(pwd_icon, 60, 60);

        /*Create the password box*/
        lv_obj_t * pwd_ta = lv_textarea_create(cont);
        lv_textarea_set_text(pwd_ta, "");
        lv_textarea_set_password_mode(pwd_ta, true);
        lv_textarea_set_one_line(pwd_ta, true);
        lv_obj_set_width(pwd_ta, lv_pct(50));
        lv_obj_set_style_bg_opa(pwd_ta, LV_OPA_80, 0);
        lv_textarea_set_accepted_chars(pwd_ta, "0123456789ABCDJEGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz#@$*_");
        lv_textarea_set_max_length(pwd_ta, DB_STR_LEN_MAX);
        lv_obj_set_grid_cell(pwd_ta,LV_GRID_ALIGN_CENTER ,1,1,LV_GRID_ALIGN_CENTER ,1,1);
        lv_obj_add_event_cb(pwd_ta, ta_event_cb, LV_EVENT_ALL, 0);

        lv_obj_t *login_btn = lv_btn_create(cont);
        lv_obj_t *login_btn_label = lv_label_create(login_btn);
        lv_label_set_text(login_btn_label, "login");
        lv_obj_set_size(login_btn, 130, LV_SIZE_CONTENT);
        lv_obj_set_grid_cell(login_btn,LV_GRID_ALIGN_CENTER ,2,1,LV_GRID_ALIGN_CENTER ,1,1);
        user_login_data *lg_data = rt_malloc(sizeof(user_login_data));
        lg_data->name_ta_p = user_ta;
        lg_data->pwd_ta_p = pwd_ta;
        lv_obj_add_event_cb(login_btn, login_btn_event_handler, LV_EVENT_CLICKED, lg_data);
    }

    /************************************user_login_tab end****************************************/

    /************************************user_register_tab****************************************/
    if(main_view_buf[1] != RT_NULL)
    {
        static lv_coord_t col_dsc[] = {60, 200, 60, 200, LV_GRID_TEMPLATE_LAST};
        static lv_coord_t row_dsc[] = {50, 50, 50, LV_GRID_TEMPLATE_LAST};

        lv_obj_t * cont = lv_obj_create(main_view_buf[1]);
        lv_obj_set_grid_dsc_array(cont, col_dsc, row_dsc);
        lv_obj_set_size(cont, LV_HOR_RES * 3 / 4, LV_SIZE_CONTENT);
        lv_obj_align(cont, LV_ALIGN_TOP_MID, 0, 20);
        lv_obj_set_style_bg_opa(cont, LV_OPA_20, 0);
        lv_obj_set_grid_align(cont,LV_GRID_ALIGN_CENTER ,LV_GRID_ALIGN_CENTER);
        lv_obj_set_style_pad_column(cont, 20, 0);
        lv_obj_set_style_pad_row(cont, 20, 0);
        lv_obj_clear_flag(cont, LV_OBJ_FLAG_SCROLLABLE);

        lv_obj_t *user_name_label = lv_label_create(cont);
        lv_label_set_text(user_name_label, "user");
        lv_obj_set_size(user_name_label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_set_grid_cell(user_name_label,LV_GRID_ALIGN_CENTER ,0,1,LV_GRID_ALIGN_CENTER ,0,1);
        lv_obj_set_style_bg_opa(user_name_label, LV_OPA_0, 0);
        lv_obj_set_style_pad_left(user_name_label, 20, 0);

        lv_obj_t *user_ta = lv_textarea_create(cont);
        lv_textarea_set_text(user_ta, "");
        lv_textarea_set_one_line(user_ta, true);
        lv_obj_set_width(user_ta, 250);
        lv_obj_set_style_bg_opa(user_ta, LV_OPA_80, 0);
        lv_textarea_set_accepted_chars(user_ta, "0123456789ABCDJEGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz#$@*_");
        lv_textarea_set_max_length(user_ta, DB_STR_LEN_MAX);
        lv_obj_set_grid_cell(user_ta,LV_GRID_ALIGN_CENTER ,1,2,LV_GRID_ALIGN_CENTER ,0,1);

        lv_obj_add_event_cb(user_ta, ta_event_cb, LV_EVENT_ALL, RT_NULL);

        lv_obj_t *reg_user_cancel_btn = lv_btn_create(cont);
        lv_obj_t *reg_user_cancel_btn_label = lv_label_create(reg_user_cancel_btn);
        lv_label_set_text(reg_user_cancel_btn_label, "cancel");
        lv_obj_center(reg_user_cancel_btn_label);
        lv_obj_set_size(reg_user_cancel_btn, 180, LV_SIZE_CONTENT);
        lv_obj_set_grid_cell(reg_user_cancel_btn,LV_GRID_ALIGN_CENTER ,3,1,LV_GRID_ALIGN_CENTER ,0,1);
        lv_obj_add_event_cb(reg_user_cancel_btn, reg_cancel_btn_event_handler, LV_EVENT_CLICKED, 0);

        lv_obj_t *password_label_1 = lv_label_create(cont);
        lv_label_set_text(password_label_1, "pwd");
        lv_obj_set_size(password_label_1, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_set_grid_cell(password_label_1,LV_GRID_ALIGN_CENTER ,0,1,LV_GRID_ALIGN_CENTER ,1,1);
        lv_obj_set_style_bg_opa(password_label_1, LV_OPA_0, 0);
        lv_obj_set_style_pad_left(password_label_1, 20, 0);

        /*Create the password box*/
        lv_obj_t * pwd_ta_1 = lv_textarea_create(cont);
        lv_textarea_set_text(pwd_ta_1, "");
        lv_textarea_set_password_mode(pwd_ta_1, true);
        lv_textarea_set_one_line(pwd_ta_1, true);
        lv_obj_set_width(pwd_ta_1, 180);
        lv_obj_set_style_bg_opa(pwd_ta_1, LV_OPA_80, 0);
        lv_textarea_set_accepted_chars(pwd_ta_1, "0123456789ABCDJEGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz#@$*_");
        lv_textarea_set_max_length(pwd_ta_1, DB_STR_LEN_MAX);
        lv_obj_set_grid_cell(pwd_ta_1,LV_GRID_ALIGN_CENTER ,1,1,LV_GRID_ALIGN_CENTER ,1,1);
        lv_obj_add_event_cb(pwd_ta_1, ta_event_cb, LV_EVENT_ALL, 0);

        lv_obj_t *password_label_2 = lv_label_create(cont);
        lv_label_set_text(password_label_2, "repwd");
        lv_obj_set_size(password_label_2, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_set_grid_cell(password_label_2,LV_GRID_ALIGN_CENTER ,2,1,LV_GRID_ALIGN_CENTER ,1,1);
        lv_obj_set_style_bg_opa(password_label_2, LV_OPA_0, 0);
        lv_obj_set_style_pad_left(password_label_2, 20, 0);

        /*Create the password box*/
        lv_obj_t * pwd_ta_2 = lv_textarea_create(cont);
        lv_textarea_set_text(pwd_ta_2, "");
        lv_textarea_set_password_mode(pwd_ta_2, true);
        lv_textarea_set_one_line(pwd_ta_2, true);
        lv_obj_set_width(pwd_ta_2, 180);
        lv_obj_set_style_bg_opa(pwd_ta_2, LV_OPA_80, 0);
        lv_textarea_set_accepted_chars(pwd_ta_2, "0123456789ABCDJEGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz#@$*_");
        lv_textarea_set_max_length(pwd_ta_2, DB_STR_LEN_MAX);
        lv_obj_set_grid_cell(pwd_ta_2,LV_GRID_ALIGN_CENTER ,3,1,LV_GRID_ALIGN_CENTER ,1,1);
        lv_obj_add_event_cb(pwd_ta_2, ta_event_cb, LV_EVENT_ALL, 0);

        lv_obj_t *admi_password_label = lv_label_create(cont);
        lv_label_set_text(admi_password_label, "adpwd");
        lv_obj_set_size(admi_password_label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_set_grid_cell(admi_password_label,LV_GRID_ALIGN_CENTER ,0,1,LV_GRID_ALIGN_CENTER ,2,1);
        lv_obj_set_style_bg_opa(admi_password_label, LV_OPA_0, 0);
        lv_obj_set_style_pad_left(admi_password_label, 20, 0);

        /*Create the password box*/
        lv_obj_t * admi_pwd_ta = lv_textarea_create(cont);
        lv_textarea_set_text(admi_pwd_ta, "");
        lv_textarea_set_password_mode(admi_pwd_ta, true);
        lv_textarea_set_one_line(admi_pwd_ta, true);
        lv_obj_set_width(admi_pwd_ta, 180);
        lv_obj_set_style_bg_opa(admi_pwd_ta, LV_OPA_80, 0);
        lv_textarea_set_accepted_chars(admi_pwd_ta, "0123456789ABCDJEGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz#@$*_");
        lv_textarea_set_max_length(admi_pwd_ta, DB_STR_LEN_MAX);
        lv_obj_set_grid_cell(admi_pwd_ta,LV_GRID_ALIGN_CENTER ,1,1,LV_GRID_ALIGN_CENTER ,2,1);
        lv_obj_add_event_cb(admi_pwd_ta, ta_event_cb, LV_EVENT_ALL, 0);

        lv_obj_t *reg_user_OK_btn = lv_btn_create(cont);
        lv_obj_t *reg_user_OK_btn_label = lv_label_create(reg_user_OK_btn);
        lv_label_set_text(reg_user_OK_btn_label, "OK");
        lv_obj_center(reg_user_OK_btn_label);
        lv_obj_set_size(reg_user_OK_btn, 180, LV_SIZE_CONTENT);
        lv_obj_set_grid_cell(reg_user_OK_btn,LV_GRID_ALIGN_CENTER ,3,1,LV_GRID_ALIGN_CENTER ,2,1);
        user_register_data *reg_data = rt_malloc(sizeof(user_register_data));
        reg_data->name_ta_p = user_ta;
        reg_data->pwd_ta_p = pwd_ta_1;
        reg_data->repwd_ta_p = pwd_ta_2;
        reg_data->admipwd_ta_p = admi_pwd_ta;
        lv_obj_add_event_cb(reg_user_OK_btn, reg_ok_btn_event_handler, LV_EVENT_CLICKED, reg_data);
    }

    /************************************user_register_tab end************************************/


    /************************************chip_manage_tab****************************************/
    lv_obj_t *main_tv = lv_tileview_create(main_view_buf[2]);
    lv_obj_set_style_bg_color(main_tv, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(main_tv,LV_OPA_0,0);

    main_tv_data *mtv_data = rt_malloc(sizeof(main_tv_data));
    mtv_data->m_tv = main_tv;

    lv_obj_t * tile1 = lv_tileview_add_tile(main_tv, 0, 0, LV_DIR_BOTTOM);

    static lv_coord_t col_dsc[] = {700, LV_GRID_TEMPLATE_LAST};
    static lv_coord_t row_dsc[] = {80, 350, LV_GRID_TEMPLATE_LAST};

    lv_obj_t * cont = lv_obj_create(tile1);
    lv_obj_set_grid_dsc_array(cont, col_dsc, row_dsc);
    lv_obj_set_size(cont, LV_HOR_RES-50, LV_VER_RES-50);
    lv_obj_center(cont);
//    lv_obj_align(cont, LV_ALIGN_TOP_MID, 0, 20);
    lv_obj_set_style_bg_color(cont, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(cont, LV_OPA_20, 0);
    lv_obj_set_style_border_opa(cont, LV_OPA_0, 0);
    lv_obj_set_grid_align(cont,LV_GRID_ALIGN_CENTER ,LV_GRID_ALIGN_CENTER);
    lv_obj_set_style_pad_column(cont, 20, 0);
    lv_obj_set_style_pad_row(cont, 20, 0);
    lv_obj_clear_flag(cont, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *chip_search_ta = lv_textarea_create(cont);
    lv_textarea_set_text(chip_search_ta, "");
    lv_textarea_set_one_line(chip_search_ta, true);
    lv_obj_set_width(chip_search_ta, 500);
    lv_obj_set_style_bg_opa(chip_search_ta, LV_OPA_80, 0);
//    lv_textarea_set_accepted_chars(user_ta, "0123456789ABCDJEGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz#$@*_");
    lv_textarea_set_max_length(chip_search_ta, DB_STR_LEN_MAX);
    lv_obj_set_grid_cell(chip_search_ta,LV_GRID_ALIGN_CENTER ,0,1,LV_GRID_ALIGN_CENTER ,0,1);

    lv_obj_t * chip_table = lv_table_create(cont);

    /*Fill the first column*/
    lv_table_set_cell_value(chip_table, 0, 0, "Name");

    /*Fill the second column*/
    lv_table_set_cell_value(chip_table, 0, 1, "Type");

    lv_table_set_cell_value(chip_table, 0, 2, "Package");

    lv_table_set_cell_value(chip_table, 0, 3, "Box");

    lv_table_set_cell_value(chip_table, 0, 4, "Count");

    chip_table_update(chip_table, "");

    lv_obj_add_event_cb(chip_search_ta, chip_search_ta_event_cb, LV_EVENT_ALL, chip_table);

    /*Set a smaller height to the table. It'll make it scrollable*/
    lv_obj_set_size(chip_table, LV_HOR_RES-100,LV_VER_RES-150);
    lv_obj_center(chip_table);
    lv_obj_set_style_text_font(chip_table, &lv_font_montserrat_16, 0);
    lv_table_set_col_width(chip_table, 0, 230);
    lv_table_set_col_width(chip_table, 1, 90);
    lv_table_set_col_width(chip_table, 2, 160);
    lv_table_set_col_width(chip_table, 3, 90);
    lv_table_set_col_width(chip_table, 4, 110);
    lv_obj_set_grid_cell(chip_table,LV_GRID_ALIGN_CENTER ,0,1,LV_GRID_ALIGN_START,1,1);

    /*Add an event callback to to apply some custom drawing*/
    lv_obj_add_event_cb(chip_table, draw_part_event_cb, LV_EVENT_DRAW_PART_BEGIN, NULL);
    lv_obj_add_event_cb(chip_table, chip_tb_select_cb, LV_EVENT_LONG_PRESSED, mtv_data);


    lv_obj_t * tile3 = lv_tileview_add_tile(main_tv, 1, 0, LV_DIR_NONE);            //chip manage tile 0行1列

    static lv_coord_t tile3_col_dsc[] = {60, 200, 60, 200, LV_GRID_TEMPLATE_LAST};
    static lv_coord_t tile3_row_dsc[] = {50, 50, 50, 50, LV_GRID_TEMPLATE_LAST};

    lv_obj_t * tile3_cont = lv_obj_create(tile3);
    lv_obj_set_grid_dsc_array(tile3_cont, tile3_col_dsc, tile3_row_dsc);
    lv_obj_set_size(tile3_cont, LV_HOR_RES * 3 / 4, LV_SIZE_CONTENT);
    lv_obj_align(tile3_cont, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_bg_opa(tile3_cont, LV_OPA_20, 0);
    lv_obj_set_grid_align(tile3_cont,LV_GRID_ALIGN_CENTER ,LV_GRID_ALIGN_CENTER);
    lv_obj_set_style_pad_column(tile3_cont, 20, 0);
    lv_obj_set_style_pad_row(tile3_cont, 20, 0);
    lv_obj_clear_flag(tile3_cont, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *chip_name_label = lv_label_create(tile3_cont);
    lv_label_set_text(chip_name_label, "name");
    lv_obj_set_size(chip_name_label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_grid_cell(chip_name_label,LV_GRID_ALIGN_CENTER ,0,1,LV_GRID_ALIGN_CENTER ,0,1);
    lv_obj_set_style_bg_opa(chip_name_label, LV_OPA_0, 0);
    lv_obj_set_style_pad_left(chip_name_label, 20, 0);

    lv_obj_t *chip_nm_ta = lv_textarea_create(tile3_cont);
    lv_textarea_set_text(chip_nm_ta, "");
    lv_textarea_set_one_line(chip_nm_ta, true);
    lv_obj_set_width(chip_nm_ta, 180);
    lv_obj_set_style_bg_opa(chip_nm_ta, LV_OPA_80, 0);
    lv_textarea_set_max_length(chip_nm_ta, DB_STR_LEN_MAX);
    lv_obj_set_grid_cell(chip_nm_ta,LV_GRID_ALIGN_CENTER ,1,1,LV_GRID_ALIGN_CENTER ,0,1);
    mtv_data->chip_nm_ta = chip_nm_ta;

    lv_obj_add_event_cb(chip_nm_ta, ta_event_cb, LV_EVENT_ALL, RT_NULL);

    lv_obj_t *chip_delete_btn = lv_btn_create(tile3_cont);
    lv_obj_t *chip_delete_label = lv_label_create(chip_delete_btn);
    lv_label_set_text(chip_delete_label, "Delete");
    lv_obj_center(chip_delete_label);
    lv_obj_set_size(chip_delete_btn, 180, LV_SIZE_CONTENT);
    lv_obj_set_grid_cell(chip_delete_btn,LV_GRID_ALIGN_CENTER ,3,1,LV_GRID_ALIGN_CENTER ,0,1);
    lv_obj_add_event_cb(chip_delete_btn, chip_delete_btn_event_cb, LV_EVENT_CLICKED, mtv_data);

    lv_obj_t *chip_type_label = lv_label_create(tile3_cont);
    lv_label_set_text(chip_type_label, "type");
    lv_obj_set_size(chip_type_label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_grid_cell(chip_type_label,LV_GRID_ALIGN_CENTER ,0,1,LV_GRID_ALIGN_CENTER ,1,1);
    lv_obj_set_style_bg_opa(chip_type_label, LV_OPA_0, 0);
    lv_obj_set_style_pad_left(chip_type_label, 20, 0);

    lv_obj_t *chip_type_ta = lv_textarea_create(tile3_cont);
    lv_textarea_set_text(chip_type_ta, "");
    lv_textarea_set_one_line(chip_type_ta, true);
    lv_obj_set_width(chip_type_ta, 180);
    lv_obj_set_style_bg_opa(chip_type_ta, LV_OPA_80, 0);
    lv_textarea_set_max_length(chip_type_ta, DB_STR_LEN_MAX);
    lv_obj_set_grid_cell(chip_type_ta,LV_GRID_ALIGN_CENTER ,1,1,LV_GRID_ALIGN_CENTER ,1,1);
    mtv_data->chip_type_ta = chip_type_ta;

    lv_obj_add_event_cb(chip_type_ta, ta_event_cb, LV_EVENT_ALL, RT_NULL);

    lv_obj_t *chip_pkg_label = lv_label_create(tile3_cont);
    lv_label_set_text(chip_pkg_label, "pkg");
    lv_obj_set_size(chip_pkg_label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_grid_cell(chip_pkg_label,LV_GRID_ALIGN_CENTER ,2,1,LV_GRID_ALIGN_CENTER ,1,1);
    lv_obj_set_style_bg_opa(chip_pkg_label, LV_OPA_0, 0);
    lv_obj_set_style_pad_left(chip_pkg_label, 20, 0);

    lv_obj_t *chip_pkg_ta = lv_textarea_create(tile3_cont);
    lv_textarea_set_text(chip_pkg_ta, "");
    lv_textarea_set_one_line(chip_pkg_ta, true);
    lv_obj_set_width(chip_pkg_ta, 180);
    lv_obj_set_style_bg_opa(chip_pkg_ta, LV_OPA_80, 0);
    lv_textarea_set_max_length(chip_pkg_ta, DB_STR_LEN_MAX);
    lv_obj_set_grid_cell(chip_pkg_ta,LV_GRID_ALIGN_CENTER ,3,1,LV_GRID_ALIGN_CENTER ,1,1);
    mtv_data->chip_pkg_ta = chip_pkg_ta;

    lv_obj_add_event_cb(chip_pkg_ta, ta_event_cb, LV_EVENT_ALL, RT_NULL);

    lv_obj_t *chip_box_label = lv_label_create(tile3_cont);
    lv_label_set_text(chip_box_label, "box");
    lv_obj_set_size(chip_box_label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_grid_cell(chip_box_label,LV_GRID_ALIGN_CENTER ,0,1,LV_GRID_ALIGN_CENTER ,2,1);
    lv_obj_set_style_bg_opa(chip_box_label, LV_OPA_0, 0);
    lv_obj_set_style_pad_left(chip_box_label, 20, 0);

    lv_obj_t *chip_box_ta = lv_textarea_create(tile3_cont);
    lv_textarea_set_text(chip_box_ta, "");
    lv_textarea_set_one_line(chip_box_ta, true);
    lv_obj_set_width(chip_box_ta, 180);
    lv_obj_set_style_bg_opa(chip_box_ta, LV_OPA_80, 0);
    lv_textarea_set_max_length(chip_box_ta, DB_STR_LEN_MAX);
    lv_textarea_set_accepted_chars(chip_box_ta, "0123456789");
    lv_obj_set_grid_cell(chip_box_ta,LV_GRID_ALIGN_CENTER ,1,1,LV_GRID_ALIGN_CENTER ,2,1);
    mtv_data->chip_box_ta = chip_box_ta;

    lv_obj_add_event_cb(chip_box_ta, ta_event_cb, LV_EVENT_ALL, RT_NULL);

    lv_obj_t *chip_count_label = lv_label_create(tile3_cont);
    lv_label_set_text(chip_count_label, "count");
    lv_obj_set_size(chip_count_label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_grid_cell(chip_count_label,LV_GRID_ALIGN_CENTER ,2,1,LV_GRID_ALIGN_CENTER ,2,1);
    lv_obj_set_style_bg_opa(chip_count_label, LV_OPA_0, 0);
    lv_obj_set_style_pad_left(chip_count_label, 20, 0);

    lv_obj_t *chip_count_ta = lv_textarea_create(tile3_cont);
    lv_textarea_set_text(chip_count_ta, "");
    lv_textarea_set_one_line(chip_count_ta, true);
    lv_obj_set_width(chip_count_ta, 180);
    lv_obj_set_style_bg_opa(chip_count_ta, LV_OPA_80, 0);
    lv_textarea_set_max_length(chip_count_ta, DB_STR_LEN_MAX);
    lv_textarea_set_accepted_chars(chip_count_ta, "0123456789");
    lv_obj_set_grid_cell(chip_count_ta,LV_GRID_ALIGN_CENTER ,3,1,LV_GRID_ALIGN_CENTER ,2,1);
    mtv_data->chip_count_ta = chip_count_ta;

    lv_obj_add_event_cb(chip_count_ta, ta_event_cb, LV_EVENT_ALL, RT_NULL);

    lv_obj_t *chip_OK_btn = lv_btn_create(tile3_cont);
    lv_obj_t *chip_OK_label = lv_label_create(chip_OK_btn);
    lv_label_set_text(chip_OK_label, "OK");
    lv_obj_center(chip_OK_label);
    lv_obj_set_size(chip_OK_btn, 180, LV_SIZE_CONTENT);
    lv_obj_set_grid_cell(chip_OK_btn,LV_GRID_ALIGN_CENTER ,1,1,LV_GRID_ALIGN_CENTER ,3,1);
    lv_obj_add_event_cb(chip_OK_btn, chip_OK_btn_event_cb, LV_EVENT_CLICKED, mtv_data);

    lv_obj_t *chip_cancel_btn = lv_btn_create(tile3_cont);
    lv_obj_t *chip_cancel_label = lv_label_create(chip_cancel_btn);
    lv_label_set_text(chip_cancel_label, "Cancel");
    lv_obj_center(chip_cancel_label);
    lv_obj_set_size(chip_cancel_btn, 180, LV_SIZE_CONTENT);
    lv_obj_set_grid_cell(chip_cancel_btn,LV_GRID_ALIGN_CENTER ,3,1,LV_GRID_ALIGN_CENTER ,3,1);
    lv_obj_add_event_cb(chip_cancel_btn, chip_cancel_btn_event_cb, LV_EVENT_CLICKED, mtv_data);


    lv_obj_t * tile2 = lv_tileview_add_tile(main_tv, 0, 1, LV_DIR_TOP);
    lv_obj_t *logout_btn = lv_btn_create(tile2);
    lv_obj_t *logout_btn_label = lv_label_create(logout_btn);
    lv_label_set_text(logout_btn_label, "logout");
    lv_obj_set_size(logout_btn, 130, LV_SIZE_CONTENT);
    lv_obj_center(logout_btn);
    lv_obj_add_event_cb(logout_btn, logout_btn_event_handler, LV_EVENT_CLICKED, 0);

    /************************************chip_manage_tab end************************************/
    mtv_data->chip_table = chip_table;
    mtv_data->chip_search_tile = tile1;
    mtv_data->chip_manage_tile = tile3;
    lv_obj_add_event_cb(main_tv, main_tv_change_cb, LV_EVENT_VALUE_CHANGED, mtv_data);
    lv_obj_set_tile_id(main_tv, 0, 0, LV_ANIM_ON);

    /*Create a keyboard*/
    kb = lv_keyboard_create(lv_scr_act());
    lv_obj_set_size(kb,  LV_HOR_RES, LV_VER_RES / 2);
    lv_obj_align(kb, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);

//    lv_keyboard_set_textarea(kb, pwd_ta); /*Focus it on one of the text areas to start*/

//    lv_obj_t *ui_user_list = lv_dropdown_create(cont);
//    lv_obj_set_width(ui_user_list, LV_PCT(50));
//    lv_obj_set_style_bg_opa(ui_user_list, LV_OPA_80, 0);
//    lv_obj_set_grid_cell(ui_user_list,LV_GRID_ALIGN_CENTER ,1,1,LV_GRID_ALIGN_CENTER ,0,1);
//    lv_dropdown_clear_options(ui_user_list);
//    rt_list_t *user_list = rt_calloc(sizeof(user_struct), 1);
//    rt_list_init(user_list);
//    if(user_get_all(user_list) >= 0)
//    {
//        rt_list_t *pos, *n;
//        user_struct *u = RT_NULL;
//        int i=0;
//        rt_list_for_each_safe(pos, n, user_list)
//        {
//            u = rt_list_entry(pos, user_struct, list);
//            lv_dropdown_add_option(ui_user_list, u->name, i++);
//            rt_kprintf("%d:%s\r\n",i,u->name);
//        }
//        user_free_list(user_list);
//    }

//
//    if(sys_db)
//        rt_kprintf("sys_db:%s\r\n",sys_db);

//    lv_obj_set_style_size(lv_img_t, lv_pct(20), 0);
//    lv_obj_set_size(lv_img_t, 400, 240);
//    lv_obj_set_pos(lv_img_t, 400, 240);

//    lv_obj_t *lv_img2_t = lv_img_create(lv_scr_act());
//    lv_img_set_src(lv_img2_t, backgound2_image_name);
//    lv_obj_set_size(lv_img2_t, 400, 240);
//    lv_obj_set_pos(lv_img2_t, 400, 0);
//    lv_obj_t *label = lv_label_create(lv_scr_act());
//    lv_label_set_text_fmt(label, "%d FSP, %d%% CPU\r\n", lvgl_fps, lvgl_cpu);
//    lv_obj_set_style_text_font(label, &lv_font_montserrat_48, 0);
//    lv_obj_set_style_text_color(label, lv_color_white(), 0);
//    lv_obj_center(label);

    lv_obj_add_flag(main_view_buf[1], LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(main_view_buf[2], LV_OBJ_FLAG_HIDDEN);
    lv_timer_create(logout_timer_cb, 1000, RT_NULL);
}

static void sys_ui_change(user_gui_id id, user_gui_id old_id)
{
    sys_current_ui = id;
    lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    switch(old_id)
    {
    case USER_LOGIN:
        lv_obj_add_flag(main_view_buf[0], LV_OBJ_FLAG_HIDDEN);
        break;
    case USER_REGISTER:
        lv_obj_add_flag(main_view_buf[1], LV_OBJ_FLAG_HIDDEN);
        break;
    case CHIP_MANAGE:
        lv_obj_add_flag(main_view_buf[2], LV_OBJ_FLAG_HIDDEN);
        break;
    }
    switch(id)
    {
    case USER_LOGIN:
        lv_obj_clear_flag(main_view_buf[0], LV_OBJ_FLAG_HIDDEN);
        break;
    case USER_REGISTER:
        lv_obj_clear_flag(main_view_buf[1], LV_OBJ_FLAG_HIDDEN);
        break;
    case CHIP_MANAGE:
        lv_obj_clear_flag(main_view_buf[2], LV_OBJ_FLAG_HIDDEN);
        break;
    }
}

static void ta_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED || code == LV_EVENT_FOCUSED) {
        /*Focus on the clicked text area*/
        if(kb != NULL) lv_keyboard_set_textarea(kb, ta);
        lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
    else if(code == LV_EVENT_READY) {
        LOG_I("Ready, current text: %s", lv_textarea_get_text(ta));
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
}

static void user_ta_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    lv_obj_t * roller = lv_event_get_user_data(e);
    static char *options = RT_NULL;
    int i=0;

    if(code == LV_EVENT_CLICKED || code == LV_EVENT_FOCUSED) {
        /*Focus on the clicked text area*/
        if(kb != NULL) lv_keyboard_set_textarea(kb, ta);
        lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }

    else if(code == LV_EVENT_READY) {
        LOG_I("Ready, current text: %s", lv_textarea_get_text(ta));
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
        if(roller != RT_NULL)
            lv_obj_add_flag(roller, LV_OBJ_FLAG_HIDDEN);
        if(options != RT_NULL)
        {
            rt_free(options);
        }
    }
    if(code == LV_EVENT_VALUE_CHANGED || code == LV_EVENT_CLICKED)
    {
        if(roller != RT_NULL)
        {
            lv_obj_set_width(roller, 278);
            lv_obj_set_pos(roller,236 , 95);
            rt_list_t *user_list = rt_calloc(sizeof(user_struct), 1);
            rt_list_init(user_list);
            if(options == RT_NULL)
                options = rt_malloc(128);
            if(options != RT_NULL && user_select(user_list, lv_textarea_get_text(ta)) >= 0)
            {
                rt_list_t *pos, *n;
                user_struct *u = RT_NULL;
                rt_sprintf(options,"");
                rt_list_for_each_safe(pos, n, user_list)
                {
                    u = rt_list_entry(pos, user_struct, list);
                    if(rt_strlen(options) + rt_strlen(u->name) + 1 < 128)
                    {
                        rt_sprintf(options+rt_strlen(options), "%s\n", u->name);
                        i++;
                    }
                }
            }
            user_free_list(user_list);
            lv_roller_set_visible_row_count(roller, (i > 3 ? 3 : i));
            lv_roller_set_options(roller, options, LV_ROLLER_MODE_NORMAL);
            lv_obj_clear_flag(roller, LV_OBJ_FLAG_HIDDEN);
        }
    }
}

static void user_roller_event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    lv_obj_t *ta = lv_event_get_user_data(e);
    if(code == LV_EVENT_LONG_PRESSED)
    {
        char buf[32];
        lv_roller_get_selected_str(obj, buf, sizeof(buf));
        LOG_I("Selected value ready: %s", buf);
        lv_textarea_set_text(ta, buf);
        char *opt = lv_roller_get_options(obj);
        lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
        if(opt != RT_NULL)
        {
            rt_free(opt);
        }
    }
}

static void mbox_timer_cb(lv_timer_t *tm)
{
    if(tm != RT_NULL)
    {
        lv_obj_t *mbox = (tm->user_data);
        if(mbox != RT_NULL)
            lv_msgbox_close(mbox);
        lv_timer_del(tm);
    }
    LOG_I("mbox_timer_cb!");
}
static void login_btn_event_handler(lv_event_t * e)
{
    user_login_data * lg_d = lv_event_get_user_data(e);
    if(lg_d != RT_NULL)
    {
        char *u_name = lv_textarea_get_text(lg_d->name_ta_p);
        char *u_pwd = lv_textarea_get_text(lg_d->pwd_ta_p);
        if(strlen(u_name)==0 || strlen(u_pwd)==0)
        {
            lv_obj_t * mbox = lv_msgbox_create(NULL, "Warning", "The name or password can not be empty!", RT_NULL, 0);
            lv_obj_center(mbox);
            lv_timer_create(mbox_timer_cb, 3000, mbox);
        }
        else {
            rt_list_t *user_list = rt_calloc(sizeof(user_struct), 1);
            rt_list_init(user_list);
            if(user_select(user_list, u_name) >= 0)
            {
                rt_list_t *pos, *n;
                user_struct *u = RT_NULL;
                rt_list_for_each_safe(pos, n, user_list)
                {
                    u = rt_list_entry(pos, user_struct, list);
                    if(rt_strcmp(u->name, u_name)==0 && rt_strcmp(u->password,u_pwd)==0)
                    {
                        LOG_I("%s login!", u_name);
                        lv_textarea_set_text(lg_d->pwd_ta_p, "");
                        sys_ui_change(CHIP_MANAGE, USER_LOGIN);
                    }
                    else {
                        lv_obj_t * mbox = lv_msgbox_create(NULL, "Warning", "The name or password is error!", RT_NULL, 0);
                        lv_obj_center(mbox);
                        lv_timer_create(mbox_timer_cb, 3000, mbox);
                    }
                }
            }
            user_free_list(user_list);
        }
    }
}

static void register_btn_event_handler(lv_event_t * e)
{
    sys_ui_change(USER_REGISTER, USER_LOGIN);
    LOG_I("register btn clicked!");
}


static void logout_btn_event_handler(lv_event_t * e)
{
    sys_ui_change(USER_LOGIN, CHIP_MANAGE);
}

static void reg_cancel_btn_event_handler(lv_event_t * e)
{
    sys_ui_change(USER_LOGIN, USER_REGISTER);
}

static void set_lcd_backlight(int sta)
{
    static int old_sta = 0;
    if(old_sta != sta)
    {
        rt_device_t lcd_pwm = rt_device_find("pwm0");
        if(lcd_pwm != RT_NULL)
        {
            struct rt_pwm_configuration pwm_cfg;
            pwm_cfg.channel = 0;
            pwm_cfg.period = 1000;
            if(sta)             //点亮
            {
                pwm_cfg.pulse = 1;       //1000熄灭    1点亮
            }
            else {              //熄灭
                pwm_cfg.pulse = 1000;       //1000熄灭    1点亮
            }
            rt_device_control(lcd_pwm, PWM_CMD_SET, &pwm_cfg);
            rt_kprintf("power off lcd!\r\n");
        }
    }
    old_sta = sta;
}

void clear_logout_time(void)
{
    logout_tm = 0;
    set_lcd_backlight(1);
}

void logout_timer_cb(struct _lv_timer_t *tm)
{
    if(logout_tm < LOGOUT_WAIT_SEC)
        logout_tm++;
    else {              //logout and lcd power off
        if(sys_current_ui == CHIP_MANAGE)
            sys_ui_change(USER_LOGIN, CHIP_MANAGE);
        set_lcd_backlight(0);
    }
}


static void reg_ok_btn_event_handler(lv_event_t * e)
{
    user_register_data * reg_d = lv_event_get_user_data(e);
    char admin_pwd[DB_STR_LEN_MAX];
    int pwd_fd = open(ADMINPWD_FILE, O_RDONLY);
    if(pwd_fd>=0)
    {
        int rd_len = read(pwd_fd,admin_pwd,DB_STR_LEN_MAX);
        close(pwd_fd);
        char *admin_pwd_in = lv_textarea_get_text(reg_d->admipwd_ta_p);
        char *u_nm = lv_textarea_get_text(reg_d->name_ta_p);
        char *u_pwd = lv_textarea_get_text(reg_d->pwd_ta_p);
        char *u_repwd = lv_textarea_get_text(reg_d->repwd_ta_p);
        if(strlen(u_nm) == 0 || strlen(u_pwd) == 0 || strcmp(u_pwd,u_repwd))
        {
            lv_obj_t * mbox = lv_msgbox_create(NULL, "Warning", "Please confirm user name and password!", RT_NULL, 0);
            lv_obj_center(mbox);
            lv_timer_create(mbox_timer_cb, 3000, mbox);
        }
        else if(rt_strncmp(admin_pwd, admin_pwd_in, rd_len) == 0)
        {
            if(user_add(u_nm, u_pwd) == RT_EOK)
            {
                lv_textarea_set_text(reg_d->name_ta_p, "");
                lv_textarea_set_text(reg_d->pwd_ta_p, "");
                lv_textarea_set_text(reg_d->repwd_ta_p, "");
                lv_textarea_set_text(reg_d->admipwd_ta_p, "");
                sys_ui_change(USER_LOGIN, USER_REGISTER);
            }
            else {
                lv_obj_t * mbox = lv_msgbox_create(NULL, "Warning", "add user failed!", RT_NULL, 0);
                lv_obj_center(mbox);
                lv_timer_create(mbox_timer_cb, 3000, mbox);
            }
        }
        else {
            lv_obj_t * mbox = lv_msgbox_create(NULL, "Warning", "admin password error!", RT_NULL, 0);
            lv_obj_center(mbox);
            lv_timer_create(mbox_timer_cb, 3000, mbox);
        }
    }
    else {
        lv_obj_t * mbox = lv_msgbox_create(NULL, "Warning", "not config admin password!", RT_NULL, 0);
        lv_obj_center(mbox);
        lv_timer_create(mbox_timer_cb, 3000, mbox);
    }
}

static void draw_part_event_cb(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_target(e);
    lv_obj_draw_part_dsc_t * dsc = lv_event_get_param(e);
    lv_event_code_t code = lv_event_get_code(e);
    /*If the cells are drawn...*/
    if(dsc->part == LV_PART_ITEMS) {
        uint32_t row = dsc->id /  lv_table_get_col_cnt(obj);
        uint32_t col = dsc->id - row * lv_table_get_col_cnt(obj);

        /*Make the texts in the first cell center aligned*/
        if(row == 0) {
            if(col % 2)
            {
                dsc->label_dsc->align = LV_TEXT_ALIGN_CENTER;
                dsc->rect_dsc->bg_color = lv_color_mix(lv_palette_main(LV_PALETTE_BLUE), dsc->rect_dsc->bg_color, LV_OPA_20);
                dsc->rect_dsc->bg_opa = LV_OPA_COVER;
            }
            else {
                dsc->label_dsc->align = LV_TEXT_ALIGN_CENTER;
                dsc->rect_dsc->bg_color = lv_color_mix(lv_palette_main(LV_PALETTE_BLUE), dsc->rect_dsc->bg_color, LV_OPA_50);
                dsc->rect_dsc->bg_opa = LV_OPA_COVER;
            }
        }
        /*In the first column align the texts to the right*/
        else if(col == 0) {
            dsc->label_dsc->align = LV_TEXT_ALIGN_LEFT;
        }

        /*MAke every 2nd row grayish*/
        if((row != 0 && row % 2) == 0) {
            dsc->rect_dsc->bg_color = lv_color_mix(lv_palette_main(LV_PALETTE_GREY), dsc->rect_dsc->bg_color, LV_OPA_10);
            dsc->rect_dsc->bg_opa = LV_OPA_COVER;
        }
    }
}


static void chip_search_ta_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    lv_obj_t *tb = lv_event_get_user_data(e);
    if(code == LV_EVENT_CLICKED || code == LV_EVENT_FOCUSED) {
        /*Focus on the clicked text area*/
        if(kb != NULL) lv_keyboard_set_textarea(kb, ta);
        lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
    else if(code == LV_EVENT_READY) {
        LOG_I("Ready, current text: %s", lv_textarea_get_text(ta));
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
        lv_obj_t *tv = lv_event_get_user_data(e);
        lv_obj_set_tile_id(tv, 0, 1, LV_ANIM_ON);
    }
    if(code == LV_EVENT_CLICKED || code == LV_EVENT_VALUE_CHANGED)
    {
        chip_table_update(tb, lv_textarea_get_text(ta));
    }
}

static void chip_table_update(lv_obj_t *tb, const char *nm)
{
    if(tb != RT_NULL && nm != RT_NULL)
    {
        rt_list_t *chip_list = rt_calloc(sizeof(chip_struct), 1);
        rt_list_init(chip_list);
        int res = chip_select(chip_list, nm);
        if(res >= 0)
        {
            rt_list_t *pos, *n;
            chip_struct *u = RT_NULL;
            lv_table_set_row_cnt(tb, 1);
            rt_uint16_t row_i=1;
            rt_list_for_each_safe(pos, n, chip_list)
            {
                u = rt_list_entry(pos, chip_struct, list);
                lv_table_set_cell_value(tb, row_i, 0, u->name);
                lv_table_set_cell_value(tb, row_i, 1, u->type);
                lv_table_set_cell_value(tb, row_i, 2, u->package);
                lv_table_set_cell_value_fmt(tb, row_i, 3, "%d",u->box);
                lv_table_set_cell_value_fmt(tb, row_i, 4, "%d",u->count);
                row_i++;
            }
        }
        chip_free_list(chip_list);
    }
}

static int chip_in_table(const char *nm)
{
    int id = -1;
    if(nm != RT_NULL)
    {
        rt_list_t *chip_list = rt_calloc(sizeof(chip_struct), 1);
        rt_list_init(chip_list);
        int sqlite_res = chip_select_nm(chip_list, nm);
        if(sqlite_res == 1)
        {
            chip_struct *cp = rt_list_entry(chip_list->next, chip_struct, list);
            id = cp->id;
        }
        chip_free_list(chip_list);
    }
    return id;
}

static void main_tv_change_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * tv = lv_event_get_target(e);
    main_tv_data *mtv_data = lv_event_get_user_data(e);
    if(code == LV_EVENT_VALUE_CHANGED)
    {
        if(lv_tileview_get_tile_act(tv) == mtv_data->chip_search_tile)
        {
            chip_table_update(mtv_data->chip_table, "");
        }
    }
}

static void chip_tb_select_cb(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_target(e);
    main_tv_data *mtv_data = lv_event_get_user_data(e);
    uint16_t col;
    uint16_t row;
    lv_table_get_selected_cell(obj, &row, &col);
    if(row == 0)
    {
        if(mtv_data->chip_nm_ta != RT_NULL)
        {
            lv_textarea_set_text(mtv_data->chip_nm_ta, "");
        }
        if(mtv_data->chip_type_ta != RT_NULL)
        {
            lv_textarea_set_text(mtv_data->chip_type_ta, "");
        }
        if(mtv_data->chip_pkg_ta != RT_NULL)
        {
            lv_textarea_set_text(mtv_data->chip_pkg_ta, "");
        }
        if(mtv_data->chip_box_ta != RT_NULL)
        {
            lv_textarea_set_text(mtv_data->chip_box_ta, "");
        }
        if(mtv_data->chip_count_ta != RT_NULL)
        {
            lv_textarea_set_text(mtv_data->chip_count_ta, "");
        }
    }
    else {
        if(mtv_data->chip_nm_ta != RT_NULL)
        {
            lv_textarea_set_text(mtv_data->chip_nm_ta, lv_table_get_cell_value(obj, row, 0));
        }
        if(mtv_data->chip_type_ta != RT_NULL)
        {
            lv_textarea_set_text(mtv_data->chip_type_ta, lv_table_get_cell_value(obj, row, 1));
        }
        if(mtv_data->chip_pkg_ta != RT_NULL)
        {
            lv_textarea_set_text(mtv_data->chip_pkg_ta, lv_table_get_cell_value(obj, row, 2));
        }
        if(mtv_data->chip_box_ta != RT_NULL)
        {
            lv_textarea_set_text(mtv_data->chip_box_ta, lv_table_get_cell_value(obj, row, 3));
        }
        if(mtv_data->chip_count_ta != RT_NULL)
        {
            lv_textarea_set_text(mtv_data->chip_count_ta, lv_table_get_cell_value(obj, row, 4));
        }
    }

    if(mtv_data->m_tv != RT_NULL && mtv_data->chip_manage_tile != RT_NULL)
    {
        lv_obj_set_tile(mtv_data->m_tv, mtv_data->chip_manage_tile, LV_ANIM_ON);
    }
}
void lv_chip_manage_msgbox(const char *title, const char *msg, void *arg);
static void chip_manage_msgbox_event_cb(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_current_target(e);
    lv_obj_t *title = lv_msgbox_get_title(obj);
    main_tv_data *mtv_data = lv_event_get_user_data(e);
    char *title_str = lv_label_get_text(title);
    if(rt_strcmp("Error", title_str)==0)
    {
        lv_msgbox_close(obj);
    }
    else if(rt_strcmp("Delete", title_str)==0)
    {
        if(rt_strcmp(lv_msgbox_get_active_btn_text(obj), "Cancel") == 0)
        {
            lv_msgbox_close(obj);
        }
        else if(rt_strcmp(lv_msgbox_get_active_btn_text(obj), "OK") == 0)
        {
            char *nm = lv_textarea_get_text(mtv_data->chip_nm_ta);
            lv_msgbox_close(obj);
            if(database_del_by_name(CHIP_TABLE_NAME,nm)==RT_EOK)
            {
                lv_chip_manage_msgbox("Info","chip delete OK!",RT_NULL);
            }
            else {
                lv_chip_manage_msgbox("Info","chip delete False!",RT_NULL);
            }
        }
    }
    else if(rt_strcmp("Update", title_str)==0)
    {
        if(rt_strcmp(lv_msgbox_get_active_btn_text(obj), "Cancel") == 0)
        {
            lv_msgbox_close(obj);
        }
        else if(rt_strcmp(lv_msgbox_get_active_btn_text(obj), "OK") == 0)
        {
            chip_struct *cp = rt_calloc(sizeof(chip_struct), 1);
            if(mtv_data != RT_NULL)
            {
                cp->id = mtv_data->db_id;
                if(mtv_data->chip_nm_ta != RT_NULL)
                    rt_strcpy(cp->name, lv_textarea_get_text(mtv_data->chip_nm_ta));
                if(mtv_data->chip_type_ta != RT_NULL)
                    rt_strcpy(cp->type, lv_textarea_get_text(mtv_data->chip_type_ta));
                if(mtv_data->chip_pkg_ta != RT_NULL)
                    rt_strcpy(cp->package, lv_textarea_get_text(mtv_data->chip_pkg_ta));
                if(mtv_data->chip_box_ta != RT_NULL)
                    cp->box = atol(lv_textarea_get_text(mtv_data->chip_box_ta));
                if(mtv_data->chip_count_ta != RT_NULL)
                    cp->count = atol(lv_textarea_get_text(mtv_data->chip_count_ta));
                lv_msgbox_close(obj);
                if (database_update(CHIP_TABLE_NAME, cp) == SQLITE_OK)
                {
                    lv_chip_manage_msgbox("Info","chip update OK!",RT_NULL);
                }
                else {
                    lv_chip_manage_msgbox("Info","chip update False!",RT_NULL);
                }
            }
            rt_free(cp);
        }
    }
    else if(rt_strcmp("Add", title_str)==0)
    {
        if(rt_strcmp(lv_msgbox_get_active_btn_text(obj), "Cancel") == 0)
        {
            lv_msgbox_close(obj);
        }
        else if(rt_strcmp(lv_msgbox_get_active_btn_text(obj), "OK") == 0)
        {
            rt_list_t *h = (rt_list_t *)rt_calloc(1, sizeof(rt_list_t));
            rt_list_init(h);
            chip_struct *cp = (chip_struct *)rt_calloc(1, sizeof(chip_struct));
            if(mtv_data != RT_NULL)
            {
                if(mtv_data->chip_nm_ta != RT_NULL)
                    rt_strcpy(cp->name, lv_textarea_get_text(mtv_data->chip_nm_ta));
                if(mtv_data->chip_type_ta != RT_NULL)
                    rt_strcpy(cp->type, lv_textarea_get_text(mtv_data->chip_type_ta));
                if(mtv_data->chip_pkg_ta != RT_NULL)
                    rt_strcpy(cp->package, lv_textarea_get_text(mtv_data->chip_pkg_ta));
                if(mtv_data->chip_box_ta != RT_NULL)
                    cp->box = atol(lv_textarea_get_text(mtv_data->chip_box_ta));
                if(mtv_data->chip_count_ta != RT_NULL)
                    cp->count = atol(lv_textarea_get_text(mtv_data->chip_count_ta));
                rt_list_insert_before(h, &(cp->list));

                int res = database_add(h, CHIP_TABLE_NAME);
                lv_msgbox_close(obj);
                if (res != SQLITE_OK)
                {
                    lv_chip_manage_msgbox("Info","chip add False!",RT_NULL);
                }
                else
                {
                    lv_chip_manage_msgbox("Info","chip add OK!",RT_NULL);
                }
            }
            chip_free_list(h);
        }
    }
    else if(rt_strcmp("Info", title_str)==0)
    {
        lv_msgbox_close(obj);
    }
}

void lv_chip_manage_msgbox(const char *title, const char *msg, void *arg)
{
    static const char * btns[] ={"OK", "Cancel", ""};

    lv_obj_t * chip_manage_mbox = lv_msgbox_create(NULL, title, msg, btns, false);
    lv_obj_add_event_cb(chip_manage_mbox, chip_manage_msgbox_event_cb, LV_EVENT_VALUE_CHANGED, arg);
    lv_obj_center(chip_manage_mbox);
    lv_obj_set_style_text_font(chip_manage_mbox, &lv_font_montserrat_20, 0);
}

static void chip_delete_btn_event_cb(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_target(e);
    lv_event_code_t code = lv_event_get_code(e);
    main_tv_data *mtv_data = lv_event_get_user_data(e);
    if(code == LV_EVENT_CLICKED)
    {
        char msg_str[64];
        if(mtv_data != RT_NULL && mtv_data->chip_nm_ta != RT_NULL && rt_strlen(lv_textarea_get_text(mtv_data->chip_nm_ta))>0)
        {
            rt_sprintf(msg_str, "Are you sure to delete the chip:%s?",lv_textarea_get_text(mtv_data->chip_nm_ta));
            lv_chip_manage_msgbox("Delete",msg_str, mtv_data);
        }
        else {
            rt_sprintf(msg_str, "Please fill in the information correctly!");
            lv_chip_manage_msgbox("Error",msg_str, mtv_data);
        }
    }
}

static void chip_OK_btn_event_cb(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_target(e);
    lv_event_code_t code = lv_event_get_code(e);
    main_tv_data *mtv_data = lv_event_get_user_data(e);
    char msg_str[64];
    if(code == LV_EVENT_CLICKED && mtv_data->chip_nm_ta != RT_NULL)
    {
        int id = chip_in_table(lv_textarea_get_text(mtv_data->chip_nm_ta));
        if(id >= 0)       //update
        {
            mtv_data->db_id = id;
            rt_sprintf(msg_str, "Are you sure to update the chip:%s?",lv_textarea_get_text(mtv_data->chip_nm_ta));
            lv_chip_manage_msgbox("Update",msg_str, mtv_data);
        }
        else {                                                              //add
            rt_sprintf(msg_str, "Are you sure to add the chip:%s?",lv_textarea_get_text(mtv_data->chip_nm_ta));
            lv_chip_manage_msgbox("Add",msg_str, mtv_data);
        }
    }
}

static void chip_cancel_btn_event_cb(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_target(e);
    lv_event_code_t code = lv_event_get_code(e);
    main_tv_data *mtv_data = lv_event_get_user_data(e);
    if(code == LV_EVENT_CLICKED)
    {
        if(mtv_data->m_tv != RT_NULL && mtv_data->chip_search_tile != RT_NULL)
        {
            lv_obj_set_tile(mtv_data->m_tv, mtv_data->chip_search_tile, LV_ANIM_ON);
        }
    }
}


