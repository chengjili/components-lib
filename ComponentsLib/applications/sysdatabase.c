/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-07-11     cheng       the first version
 */

#include "dfs_file.h"
#include "sqlite3.h"
#include "sysdatabase.h"

#define DBG_ENABLE
#define DBG_SECTION_NAME "app.user_gui"
#define DBG_LEVEL DBG_INFO
#define DBG_COLOR
#include <rtdbg.h>


static uint8_t sql_str[PKG_SQLITE_SQL_MAX_LEN];


void create_sysdb_table(void)
{
    int fd = 0, res;
    db_set_name(SYSDB_NAME);
    fd = open(db_get_name(), O_RDONLY);
    if (fd < 0)
    {
        LOG_I("database:%s cant open,wile create it!\r\n",db_get_name());
        /* there is not the .db file.create db and table */
        sprintf(sql_str,"CREATE TABLE %s(id INTEGER PRIMARY KEY AUTOINCREMENT,name varchar(32) NOT NULL,password varchar(32) NOT NULL);",USER_TABLE_NAME);
        res = db_create_database(sql_str);
        if(res == SQLITE_OK || res == SQLITE_DONE)
        {
           LOG_I("%s has created!\r\n", USER_TABLE_NAME);
        }
        else {
            LOG_E("%s cant created!\r\n", USER_TABLE_NAME);
        }
        sprintf(sql_str,"CREATE TABLE %s(id INTEGER PRIMARY KEY AUTOINCREMENT,name varchar(32) NOT NULL,package varchar(32),type varchar(32),box INT NOT NULL,count INT NOT NULL);",CHIP_TABLE_NAME);
        res = db_create_database(sql_str);
        if(res == SQLITE_OK || res == SQLITE_DONE)
        {
           LOG_I("%s has created!\r\n", CHIP_TABLE_NAME);
        }
        else {
            LOG_E("%s cant created!\r\n", CHIP_TABLE_NAME);
        }
    }
    else
    {
        close(fd);
        if(db_table_is_exist(USER_TABLE_NAME) > 0)
        {
            LOG_I("%s has already existed!\r\n", USER_TABLE_NAME);
        }
        else {
            /* there is not the table int db.create the table */
            sprintf(sql_str,"CREATE TABLE %s(id INTEGER PRIMARY KEY AUTOINCREMENT,name varchar(32) NOT NULL,password varchar(32) NOT NULL);",USER_TABLE_NAME);
            res = db_create_database(sql_str);
            if(res == SQLITE_OK || res == SQLITE_DONE)
            {
               LOG_I("%s has created!\r\n", USER_TABLE_NAME);
            }
            else {
                LOG_E("%s cant created!\r\n", USER_TABLE_NAME);
            }
        }
        if(db_table_is_exist(CHIP_TABLE_NAME) > 0)
        {
            LOG_I("%s has already existed!\r\n", CHIP_TABLE_NAME);
        }
        else {
            /* there is not the table int db.create the table */
            sprintf(sql_str,"CREATE TABLE %s(id INTEGER PRIMARY KEY AUTOINCREMENT,name varchar(32) NOT NULL,package varchar(32),type varchar(32),box INT NOT NULL,count INT NOT NULL);",CHIP_TABLE_NAME);
            res = db_create_database(sql_str);
            if(res == SQLITE_OK || res == SQLITE_DONE)
            {
               LOG_I("%s has created!\r\n", CHIP_TABLE_NAME);
            }
            else {
                LOG_E("%s cant created!\r\n", CHIP_TABLE_NAME);
            }
        }
    }
}



static int user_insert_bind(sqlite3_stmt *stmt, int index, void *arg)
{
    int rc;
    rt_list_t *h = arg, *pos, *n;
    user_struct *s = RT_NULL;
    rt_list_for_each_safe(pos, n, h)
    {
        s = rt_list_entry(pos, user_struct, list);
        sqlite3_reset(stmt);                                                    //reset the stmt
        sqlite3_bind_text(stmt, 1, s->name, strlen(s->name), NULL);             //bind the 1st data,is a string
        sqlite3_bind_text(stmt, 2, s->password, strlen(s->password), NULL);     //bind the 2st data,is a string
        rc = sqlite3_step(stmt);                                                //execute the stmt by step
    }

    if (rc != SQLITE_DONE)
        return rc;
    return SQLITE_OK;
}

static int chip_insert_bind(sqlite3_stmt *stmt, int index, void *arg)
{
    int rc;
    rt_list_t *h = arg, *pos, *n;
    chip_struct *s = RT_NULL;
    rt_list_for_each_safe(pos, n, h)
    {
        s = rt_list_entry(pos, chip_struct, list);
        sqlite3_reset(stmt);                                                    //reset the stmt
        sqlite3_bind_text(stmt, 1, s->name, strlen(s->name), NULL);             //bind the 1st data,is a string
        sqlite3_bind_text(stmt, 2, s->package, strlen(s->package), NULL);       //bind the 2st data,is a string
        sqlite3_bind_text(stmt, 3, s->type, strlen(s->type), NULL);
        sqlite3_bind_int(stmt, 4, s->box);
        sqlite3_bind_int(stmt, 5, s->count);
        rc = sqlite3_step(stmt);                                                //execute the stmt by step
    }

    if (rc != SQLITE_DONE)
        return rc;
    return SQLITE_OK;
}

int database_add(rt_list_t *h, const char* table_nm)
{
    if(rt_strcmp(table_nm, USER_TABLE_NAME) == 0)
    {
        sprintf(sql_str,"insert into %s (name,password) values (?,?);",table_nm);
        return db_nonquery_operator(sql_str, user_insert_bind, h);
    }
    else if(rt_strcmp(table_nm, CHIP_TABLE_NAME) == 0)
    {
        sprintf(sql_str,"insert into %s (name,package,type,box,count) values (?,?,?,?,?);",table_nm);
        return db_nonquery_operator(sql_str, chip_insert_bind, h);
    }
}


int database_del(const char* table_nm, int id)
{
    if(id >= 0)
    {
        sprintf(sql_str,"delete from %s where id=?;",table_nm);
        return db_nonquery_by_varpara(sql_str, "%d", id);
    }
    else {  //delete all
        sprintf(sql_str,"delete from %s;",table_nm);
        return db_nonquery_by_varpara(sql_str, 0, 0);
    }
}

int database_del_by_name(const char* table_nm, const char* name)
{
    sprintf(sql_str,"delete from %s where name=?;",table_nm);
    return db_nonquery_by_varpara(sql_str, "%s", name);
}

int database_del_all(const char* table_nm)
{
    sprintf(sql_str,"delete from %s;",table_nm);
    return db_nonquery_operator(sql_str, 0, 0);
}

static int user_update_bind(sqlite3_stmt *stmt, int index, void *arg)
{
    int rc;
    user_struct *s = arg;
    sqlite3_bind_text(stmt, 1, s->name, strlen(s->name), NULL);
    sqlite3_bind_text(stmt, 2, s->password, strlen(s->password), NULL);
    sqlite3_bind_int(stmt, 3, s->id);
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
        return rc;
    return SQLITE_OK;
}
static int chip_update_bind(sqlite3_stmt *stmt, int index, void *arg)
{
    int rc;
    chip_struct *s = arg;
    sqlite3_bind_text(stmt, 1, s->name, strlen(s->name), NULL);
    sqlite3_bind_text(stmt, 2, s->package, strlen(s->package), NULL);
    sqlite3_bind_text(stmt, 3, s->type, strlen(s->type), NULL);
    sqlite3_bind_int(stmt, 4, s->box);
    sqlite3_bind_int(stmt, 5, s->count);
    sqlite3_bind_int(stmt, 6, s->id);
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
        return rc;
    return SQLITE_OK;
}
int database_update(const char* table_nm, void *s)
{
    if(rt_strcmp(table_nm, USER_TABLE_NAME) == 0)
    {
        sprintf(sql_str,"update %s set name=?,password=? where id=?;",table_nm);
        return db_nonquery_operator(sql_str, user_update_bind, s);
    }
    else if(rt_strcmp(table_nm, CHIP_TABLE_NAME) == 0)
    {
        sprintf(sql_str,"update %s set name=?,package=?,type=?,box=?,count=? where id=?;",table_nm);
        return db_nonquery_operator(sql_str, chip_update_bind, s);
    }
}

static int user_create(sqlite3_stmt *stmt, void *arg)
{
    user_struct *s = arg;
    int ret = sqlite3_step(stmt);
    if (ret != SQLITE_ROW)
    {
        return 0;
    }
    else
    {
        s->id = db_stmt_get_int(stmt, 0);
        db_stmt_get_text(stmt, 1, s->name);
        db_stmt_get_text(stmt, 2, s->password);
    }
    return ret;
}
static int chip_create(sqlite3_stmt *stmt, void *arg)
{
    chip_struct *s = arg;
    int ret = sqlite3_step(stmt);
    if (ret != SQLITE_ROW)
    {
        return 0;
    }
    else
    {
        s->id = db_stmt_get_int(stmt, 0);
        db_stmt_get_text(stmt, 1, s->name);
        db_stmt_get_text(stmt, 2, s->package);
        db_stmt_get_text(stmt, 3, s->type);
        s->box = db_stmt_get_int(stmt, 4);
        s->count = db_stmt_get_int(stmt, 5);
    }
    return ret;
}

int user_get_by_id(user_struct *s, int id)
{
    sprintf(sql_str,"select * from %s where id=?;",USER_TABLE_NAME);
    int res = db_query_by_varpara(sql_str, user_create, s, "%d", id);
    return res;
}

int chip_get_by_id(chip_struct *s, int id)
{
    sprintf(sql_str,"select * from %s where id=?;",CHIP_TABLE_NAME);
    int res = db_query_by_varpara(sql_str, chip_create, s, "%d", id);
    return res;
}

void user_free_list(rt_list_t *h)
{
    rt_list_t *head = h, *pos, *n;
    user_struct *p = RT_NULL;
    rt_list_for_each_safe(pos, n, head)
    {
        p = rt_list_entry(pos, user_struct, list);
        rt_free(p);
    }
    rt_free(head);
}

void chip_free_list(rt_list_t *h)
{
    rt_list_t *head = h, *pos, *n;
    chip_struct *p = RT_NULL;
    rt_list_for_each_safe(pos, n, head)
    {
        p = rt_list_entry(pos, chip_struct, list);
        rt_free(p);
    }
    rt_free(head);
}

void database_print_list(const char* table_nm, rt_list_t *q)
{
    if(rt_strcmp(table_nm, USER_TABLE_NAME) == 0)
    {
        user_struct *s = NULL;
        for (s = rt_list_entry((q)->next, user_struct, list);
             &s->list != (q);
             s = rt_list_entry(s->list.next, user_struct, list))
        {
            rt_kprintf("id:%d\tname:%s\tpassword:%s\n", s->id, s->name, s->password);
        }
    }
    else if(rt_strcmp(table_nm, CHIP_TABLE_NAME) == 0)
    {
        chip_struct *s = NULL;
        for (s = rt_list_entry((q)->next, chip_struct, list);
             &s->list != (q);
             s = rt_list_entry(s->list.next, chip_struct, list))
        {
            rt_kprintf("id:%d\tname:%s\tpackage:%s\ttype:%s\tbox:%d\tcount:%d\n", s->id, s->name, s->package, s->type, s->box, s->count);
        }
    }
}

static int user_create_queue(sqlite3_stmt *stmt, void *arg)
{
    rt_list_t *q = arg;
    user_struct *s;
    int ret, count = 0;
    ret = sqlite3_step(stmt);
    if (ret != SQLITE_ROW)
    {
        return 0;
    }
    do
    {
        s = rt_calloc(sizeof(user_struct), 1);
        if (!s)
        {
            LOG_E("No enough memory!");
            goto __create_user_fail;
        }
        s->id = db_stmt_get_int(stmt, 0);
        db_stmt_get_text(stmt, 1, s->name);
        db_stmt_get_text(stmt, 2, s->password);
        rt_list_insert_before(q, &(s->list));
        count++;
    } while ((ret = sqlite3_step(stmt)) == SQLITE_ROW);
    return count;
__create_user_fail:
    return -1;
}

static int chip_create_queue(sqlite3_stmt *stmt, void *arg)
{
    rt_list_t *q = arg;
    chip_struct *s;
    int ret, count = 0;
    ret = sqlite3_step(stmt);
    if (ret != SQLITE_ROW)
    {
        return 0;
    }
    do
    {
        s = rt_calloc(sizeof(chip_struct), 1);
        if (!s)
        {
            LOG_E("No enough memory!");
            goto __create_chip_fail;
        }
        s->id = db_stmt_get_int(stmt, 0);
        db_stmt_get_text(stmt, 1, s->name);
        db_stmt_get_text(stmt, 2, s->package);
        db_stmt_get_text(stmt, 3, s->type);
        s->box = db_stmt_get_int(stmt, 4);
        s->count = db_stmt_get_int(stmt, 5);
        rt_list_insert_before(q, &(s->list));
        count++;
    } while ((ret = sqlite3_step(stmt)) == SQLITE_ROW);
    return count;
__create_chip_fail:
    return -1;
}

int user_get_all(rt_list_t *q)
{
    sprintf(sql_str,"select * from %s;",USER_TABLE_NAME);
    return db_query_by_varpara(sql_str, user_create_queue, q, RT_NULL);
}

int user_select(rt_list_t *q, const char *str)
{
    sprintf(sql_str,"select * from %s where name like \'%%%s%%\';",USER_TABLE_NAME, str);
    rt_kprintf("%s\r\n",sql_str);
    return db_query_by_varpara(sql_str, user_create_queue, q, RT_NULL);
}

int chip_get_all(rt_list_t *q)
{
    sprintf(sql_str,"select * from %s;",CHIP_TABLE_NAME);
    return db_query_by_varpara(sql_str, chip_create_queue, q, RT_NULL);
}

int chip_select(rt_list_t *q, const char *str)      //name的模糊查询
{
    sprintf(sql_str,"select * from %s where name like \'%%%s%%\';",CHIP_TABLE_NAME, str);
    return db_query_by_varpara(sql_str, chip_create_queue, q, RT_NULL);
}

int chip_select_nm(rt_list_t *q, const char *str)       //name的精确查询
{
    sprintf(sql_str,"select * from %s where name like \'%s\';",CHIP_TABLE_NAME, str);
    return db_query_by_varpara(sql_str, chip_create_queue, q, RT_NULL);
}

static void user_list_all(void)
{
    rt_list_t *h = rt_calloc(sizeof(user_struct), 1);
    rt_list_init(h);
    int ret = user_get_all(h);
    if (ret >= 0)
    {
        database_print_list(USER_TABLE_NAME, h);
    }
    else
    {
        rt_kprintf("Get users information failed");
    }
    user_free_list(h);
    return;
}

static void user_list_select(char *str)
{
    rt_list_t *h = rt_calloc(sizeof(user_struct), 1);
    rt_list_init(h);
    int ret = user_select(h, str);
    if (ret >= 0)
    {
        database_print_list(USER_TABLE_NAME, h);
    }
    else
    {
        rt_kprintf("Get users information failed");
    }
    user_free_list(h);
    return;
}

static void chip_list_all(void)
{
    rt_list_t *h = rt_calloc(sizeof(chip_struct), 1);
    rt_list_init(h);
    int ret = chip_get_all(h);
    if (ret >= 0)
    {
        database_print_list(CHIP_TABLE_NAME, h);
    }
    else
    {
        rt_kprintf("Get chips information failed");
    }
    chip_free_list(h);
    return;
}


rt_err_t user_add(const char *nm, const char *pwd)
{
    if(nm==RT_NULL || pwd==RT_NULL)
    {
        return RT_ERROR;
    }
    rt_list_t *h = (rt_list_t *)rt_calloc(1, sizeof(rt_list_t));
    rt_list_init(h);
    user_struct *s = (user_struct *)rt_calloc(1, sizeof(user_struct));
    if(rt_strlen(nm) > 32 || rt_strlen(pwd) > 32)
    {
        LOG_E("name or password is too long!");
        return RT_ERROR;
    }
    else {
        rt_strcpy(s->name, nm);
        rt_strcpy(s->password, pwd);
        rt_list_insert_before(h, &(s->list));

        int res = database_add(h, USER_TABLE_NAME);
        if (res != SQLITE_OK)
        {
            LOG_E("add failed!");
            return RT_ERROR;
        }
        else
        {
            LOG_I("add user:%s,password:%s\r\n", nm,pwd);
        }
    }
    user_free_list(h);
    return RT_EOK;
}

void useradd(int argv, char **argc)
{
    if(argv < 3)
    {
        rt_kprintf("cmd err! [useradd name password]\r\n");
    }
    else
    {
        rt_list_t *h = (rt_list_t *)rt_calloc(1, sizeof(rt_list_t));
        rt_list_init(h);
        user_struct *s = (user_struct *)rt_calloc(1, sizeof(user_struct));
        if(rt_strlen(argc[1]) > 32 || rt_strlen(argc[2]) > 32)
        {
            LOG_E("name or password is too long!");
        }
        else {
            rt_strcpy(s->name, argc[1]);
            rt_strcpy(s->password, argc[2]);
            rt_list_insert_before(h, &(s->list));

            int res = database_add(h, USER_TABLE_NAME);
            if (res != SQLITE_OK)
            {
                LOG_E("add failed!");
            }
            else
            {
                rt_kprintf("add user:%s,password:%s\r\n", argc[1],argc[2]);
            }
        }
        user_free_list(h);
    }
}
MSH_CMD_EXPORT(useradd, add user to the database);


void userdelet(int argv, char **argc)
{
    if(argv == 1)
    {
        rt_kprintf("cmd err! [userdelet id]\r\n");
    }
    else {
        rt_uint32_t id = atol(argc[1]);
        if (database_del(USER_TABLE_NAME,id) == SQLITE_OK)
        {
            rt_kprintf("Del user success with id:%d\n", id);
        }
        else
        {
            rt_kprintf("Del user failed with id:%d\n", id);
        }
    }
}
MSH_CMD_EXPORT(userdelet, delet user from the database);

void userupdate(int argv, char **argc)
{
    if(argv < 4)
    {
        rt_kprintf("cmd err! [userupdate id name password]\r\n");
    }
    else {
        user_struct *s = rt_calloc(sizeof(user_struct), 1);
        s->id = atol(argc[1]);
        if(strlen(argc[2]) > 32 || strlen(argc[3]) > 32)
        {
            LOG_E("name or password is too long!");
        }
        else {
            rt_strcpy(s->name, argc[2]);
            rt_strcpy(s->password, argc[3]);
            if (database_update(USER_TABLE_NAME, s) == SQLITE_OK)
            {
                rt_kprintf("update user success!\n");
            }
            else
            {
                rt_kprintf("update user failed!\n");
            }
        }
        rt_free(s);
    }
}
MSH_CMD_EXPORT(userupdate, update user of the database);

void userlist(int argv, char **argc)
{
    user_list_all();
}
MSH_CMD_EXPORT(userlist, list all user of the database);

void userselect(int argv, char **argc)
{
    if(argv == 1)
        user_list_all();
    else {
        user_list_select(argc[1]);
    }
}
MSH_CMD_EXPORT(userselect, list select user of the database);

void chipadd(int argv, char **argc)
{
    if(argv < 6)
    {
        rt_kprintf("cmd err! [chipadd name package type boxid count]\r\n");
    }
    else
    {
        rt_list_t *h = (rt_list_t *)rt_calloc(1, sizeof(rt_list_t));
        rt_list_init(h);
        chip_struct *s = (chip_struct *)rt_calloc(1, sizeof(chip_struct));
        if(rt_strlen(argc[1]) > 32 || rt_strlen(argc[2]) > 32 || rt_strlen(argc[3]) > 32)
        {
            LOG_E("name package or type is too long!");
        }
        else {
            rt_strcpy(s->name, argc[1]);
            rt_strcpy(s->package, argc[2]);
            rt_strcpy(s->type, argc[3]);
            s->box = atol(argc[4]);
            s->count = atol(argc[5]);
            rt_list_insert_before(h, &(s->list));

            int res = database_add(h, CHIP_TABLE_NAME);
            if (res != SQLITE_OK)
            {
                LOG_E("add failed!");
            }
            else
            {
                rt_kprintf("add chip:%s,package:%s,type:%s,boxid:%s,count:%s\r\n", argc[1],argc[2],argc[3],argc[4],argc[5]);
            }
        }
        chip_free_list(h);
    }
}
MSH_CMD_EXPORT(chipadd, add chip to the database);

void chipdelet(int argv, char **argc)
{
    if(argv == 1)
    {
        rt_kprintf("cmd err! [chipdelet id] id:-1 is all delete\r\n");
    }
    else {
        rt_int32_t id = atol(argc[1]);
        if(id == -1)
        {
            if (database_del(CHIP_TABLE_NAME,id) == SQLITE_OK)
            {
                rt_kprintf("Del chip success with id:%d\n", id);
            }
            else
            {
                rt_kprintf("Del chip failed with id:%d\n", id);
            }
        }
        else {
            if (database_del(CHIP_TABLE_NAME,id) == SQLITE_OK)
            {
                rt_kprintf("Delete all chip success\n");
            }
            else
            {
                rt_kprintf("Delete all chip failed\n");
            }
        }
    }
}
MSH_CMD_EXPORT(chipdelet, delet chip from the database);

void chipupdate(int argv, char **argc)
{
    if(argv < 7)
    {
        rt_kprintf("cmd err! [chipupdate id name package type boxid count]\r\n");
    }
    else {
        chip_struct *s = rt_calloc(sizeof(chip_struct), 1);
        s->id = atol(argc[1]);
        if(strlen(argc[2]) > 32 || strlen(argc[3]) > 32 || strlen(argc[4]) > 32)
        {
            LOG_E("name or package is too long!");
        }
        else {
            rt_strcpy(s->name, argc[2]);
            rt_strcpy(s->package, argc[3]);
            rt_strcpy(s->type, argc[4]);
            s->box = atol(argc[5]);
            s->count = atol(argc[6]);
            if (database_update(CHIP_TABLE_NAME, s) == SQLITE_OK)
            {
                rt_kprintf("update chip success!\n");
            }
            else
            {
                rt_kprintf("update chip failed!\n");
            }
        }
        rt_free(s);
    }
}
MSH_CMD_EXPORT(chipupdate, update chip of the database);

void chiplist(int argv, char **argc)
{
    chip_list_all();
}
MSH_CMD_EXPORT(chiplist, list all chip of the database);


void import_chipadd(char *nm, char *type, char *pkg, int box, int count)
{
    if(nm != RT_NULL && type != RT_NULL && pkg != RT_NULL)
    {
        rt_list_t *h = (rt_list_t *)rt_calloc(1, sizeof(rt_list_t));
        rt_list_init(h);
        chip_struct *s = (chip_struct *)rt_calloc(1, sizeof(chip_struct));
        if(rt_strlen(nm) > 32 || rt_strlen(type) > 32 || rt_strlen(pkg) > 32)
        {
            LOG_E("name package or type is too long!");
        }
        else {
            rt_strcpy(s->name, nm);
            rt_strcpy(s->package, pkg);
            rt_strcpy(s->type, type);
            s->box = box;
            s->count = count;
            rt_list_insert_before(h, &(s->list));

            int res = database_add(h, CHIP_TABLE_NAME);
            if (res != SQLITE_OK)
            {
                LOG_E("add failed!");
            }
            else
            {
                rt_kprintf("add chip:%s,package:%s,type:%s,boxid:%d,count:%d\r\n", nm,pkg,type,box,count);
            }
        }
        chip_free_list(h);
    }
}
void import_chips(int argv, char **argc)
{
    char rd_bf[128], *ch_p=0, *chrp_buf[10];
    rt_int16_t rd_bf_i=0, chrp_buf_i=0;
    rt_int32_t rd_line=0;
    if(argv == 2)
    {
        int fil = open(argc[1],O_RDONLY);
        if(fil >=0)
        {
            while(read(fil, rd_bf+rd_bf_i, 1) == 1)
            {
                rd_bf_i++;
                if(rd_bf[rd_bf_i-1] == '\n' || rd_bf_i==128)
                {
                    if(rd_bf_i!=128)
                    {
                        rd_bf[rd_bf_i-1] = '\0';
                        ch_p = rd_bf;
                        chrp_buf_i = 0;
                        while(ch_p > 0)
                        {
                            ch_p = strchr(ch_p, '\t');
                            if(ch_p > 0)
                            {
                                *ch_p = '\0';
                                ch_p++;
                                chrp_buf[chrp_buf_i++] = ch_p;
                                if(chrp_buf_i == 10)
                                    break;
                            }
                            else {
                                break;
                            }
                        }
                        if(chrp_buf_i == 4)
                        {
                            if(rd_line == 0)
                            {
                                if(strncmp(rd_bf,"type",4)||strncmp(chrp_buf[0],"name",4)||strncmp(chrp_buf[1],"pakage",6)
                                        || strncmp(chrp_buf[2],"box",3) || strncmp(chrp_buf[3],"count",5))
                                {
                                    rt_kprintf("table head failed!\r\n");
                                    break;
                                }
                            }
                            else {
                                import_chipadd(chrp_buf[0], rd_bf, chrp_buf[1], atol(chrp_buf[2]), atol(chrp_buf[3]));
                            }
                        }
                        rd_line++;
                    }
                    rd_bf_i = 0;
                }
            }
            close(fil);
        }
        else {
            rt_kprintf("open %s failed!\r\n", argc[1]);
        }
    }
    else {
        rt_kprintf("import_chips filename\r\n");
    }
}
MSH_CMD_EXPORT(import_chips, import chips from file);


