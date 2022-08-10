/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2021-10-17     Meco Man      First version
 */
#include <rtthread.h>
#include <lvgl.h>
#define DBG_TAG    "LVGL"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>
#include "user_gui.h"

#ifndef LV_THREAD_STACK_SIZE
    #define LV_THREAD_STACK_SIZE 409600     //�����õ���sqlite ����Ϊ400K
#endif

#ifndef LV_THREAD_PRIO
    #define LV_THREAD_PRIO (RT_THREAD_PRIORITY_MAX*2/3)
#endif

static void lvgl_thread(void *parameter)
{
#if LV_USE_DEMO_BENCHMARK
    extern void lv_demo_benchmark(void);
    lv_demo_benchmark();
#endif
#if LV_USE_DEMO_WIDGETS
    extern void lv_demo_widgets(void);
#endif
#if LV_USE_DEMO_MUSIC || LV_USE_DEMO_RTT_MUSIC
    extern void lv_demo_music(void);
    lv_demo_music();
#endif
    rt_thread_delay(1000);
    user_gui_init();
    while (1)
    {
        lv_task_handler();
        rt_thread_mdelay(1);
    }
}

static int lvgl_demo_init(void)
{
    rt_thread_t tid;

    tid = rt_thread_create("LVGL", lvgl_thread, RT_NULL, LV_THREAD_STACK_SIZE, LV_THREAD_PRIO, 10);
    if (tid == RT_NULL)
    {
        LOG_E("Fail to create 'LVGL' thread");
    }
    rt_thread_startup(tid);

    return 0;
}
INIT_APP_EXPORT(lvgl_demo_init);
