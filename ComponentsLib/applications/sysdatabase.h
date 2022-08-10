/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-07-11     cheng       the first version
 */
#ifndef APPLICATIONS_SYSDATABASE_H_
#define APPLICATIONS_SYSDATABASE_H_

#include <rtconfig.h>
#include <rtdevice.h>
#include <rthw.h>
#include <rtthread.h>
#include <stddef.h>
#include "dbhelper.h"

#define SYSDB_NAME              "/mnt/sd0/sys.db"
#define USER_TABLE_NAME         "user_table"
#define CHIP_TABLE_NAME         "chip_table"

#define DB_STR_LEN_MAX              32


typedef struct __user_struct
{
    unsigned int id;
    char name[32];
    char password[32];
    rt_list_t list;
}user_struct;

typedef struct __chip_struct
{
    unsigned int id;
    char name[32];
    char package[32];
    char type[32];
    rt_uint32_t box;
    rt_uint32_t count;
    rt_list_t list;
}chip_struct;


void create_sysdb_table(void);
int user_get_all(rt_list_t *q);
void user_free_list(rt_list_t *h);
int user_select(rt_list_t *q, const char *str);
void chip_free_list(rt_list_t *h);
int chip_select(rt_list_t *q, const char *str);
int chip_select_nm(rt_list_t *q, const char *str);
rt_err_t user_add(const char *nm, const char *pwd);
int database_del_by_name(const char* table_nm, const char* name);

#endif /* APPLICATIONS_SYSDATABASE_H_ */
