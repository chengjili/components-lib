/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-06-22     cheng       the first version
 */
#ifndef APPLICATIONS_LVGL_USER_GUI_H_
#define APPLICATIONS_LVGL_USER_GUI_H_

#include "lv_conf.h"
#include "../lvgl.h"
#include <rtconfig.h>
#include <rtdevice.h>
#include <rthw.h>
#include <rtthread.h>
#include <stddef.h>

#define ADMINPWD_FILE       "/mnt/filesystem/adminpwd.txt"

#define LOGOUT_WAIT_SEC     600

typedef struct __user_login_data
{
    lv_obj_t *name_ta_p;
    lv_obj_t *pwd_ta_p;
}user_login_data;

typedef struct __user_register_data
{
    lv_obj_t *name_ta_p;
    lv_obj_t *pwd_ta_p;
    lv_obj_t *repwd_ta_p;
    lv_obj_t *admipwd_ta_p;
}user_register_data;

typedef struct __main_tv_data
{
    lv_obj_t *m_tv;
    lv_obj_t *chip_search_tile;
    lv_obj_t *chip_manage_tile;
    lv_obj_t *chip_table;
    lv_obj_t *chip_nm_ta;
    lv_obj_t *chip_type_ta;
    lv_obj_t *chip_pkg_ta;
    lv_obj_t *chip_box_ta;
    lv_obj_t *chip_count_ta;
    int db_id;

}main_tv_data;

enum{
    USER_LOGIN = 0,
    USER_REGISTER,
    CHIP_MANAGE,
};

typedef rt_uint8_t user_gui_id;


void user_gui_init(void);

#endif /* APPLICATIONS_LVGL_USER_GUI_H_ */
