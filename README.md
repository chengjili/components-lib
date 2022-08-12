# ComponentsLib

#### 介绍

基于新唐N9H30硬件平台，RTThread+LVGL软件平台的便携式器件库存管理系统。LVGL嵌入式GUI挑战赛作品。

下图为设想的最终使用场景图，把系统想办法固定在器件柜旁边，方便管理和查找器件。（由于还没有开发完成，所以临时胶固示意一下）

<img title="" src="file:///C:/Users/chengjili/AppData/Roaming/marktext/images/2022-08-12-09-22-43-fd2a6ee82e08ab14773a5242b3c7b41.jpg" alt="" width="495">

#### 系统架构

如下为主要的系统框架图

<img title="" src="file:///C:/Users/chengjili/AppData/Roaming/marktext/images/2022-08-12-10-05-55-image.png" alt="" width="1448">

#### 已实现的主要功能

- 基于LVGL的UI
  
  - 用户登录界面
  
  - 用户管理界面
  
  - 器件检索界面
  
  - 器件管理界面
  
  - 系统设置界面

- 文件系统，存放图片和数据库资源文件

- 绑定DFS虚拟文件系统到LVGL的文件操作接口

- 注册JPEG软件解码器到LVGL，实现从SD卡加载图片

- SQLite数据库管理
  
  - 用户表
  
  - 器件表

- 显示屏背光的亮度调节，定时无操作自动熄屏，触碰触摸屏唤醒

- 通过终端串口命令实现的更丰富的数据库操作功能（未链接到UI）

- 通过终端串口命令实现的excel文件导入数据库功能

#### 尚未完成功能

- 更丰富合理的用户管理功能
  
  - 通过网络授权用户注册
  
  - 用户登录、操作日志

- 更丰富的器件管理功能
  
  - 通过网络远程管理

- 优化UI，使其效率更高，更优雅

- 加入中文支持

#### 开发过程与关键点记录

1. 基于RT-Thread新建工程
   
   详见我之前在RT-Thread论坛发布过的测试文章：[RT-Thread-N9H30开发板开箱测试RT-Thread问答社区 - RT-Thread](https://club.rt-thread.org/ask/article/9a1b494513c87d83.html)

2. 新建自己的`user_gui`源文件和头文件。并把用户UI界面的代码接口，加入到`lv_demo.c`内的`lvgl_thread`函数内。屏蔽所有的DEMO宏。
   
   ```c
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
       user_gui_init();      //用户代码接口
       while (1)
       {
           lv_task_handler();
           rt_thread_mdelay(1);
       }
   }
   ```

3. 在`user_gui_init()`中调用`lv_fs_posix_init()`函数，绑定文件系统操作接口
   
   RT-Thread提供的开发包，已经适配好了DFS虚拟文件系统。这里只需要和LVGL的文件操作接口对接即可。

4. 在`user_gui_init()`中调用`lv_split_jpeg_init()`函数，注册JPEG软解码器到LVGL
   
   这里主要就是链接了`lv_sjpg.c`内的`decoder_info`,`decoder_open`,`decoder_close`,`decoder_read_line`函数接口到LVGL的解码器列表。在加载文件系统内的JPEG图片的时候，LVGL会自动查找匹配的解码器进行解码。另外，需要注意的是，在LVGL的文件系统接口下，文件路径前面要加上“S:”。当然，此标识符可以通过`lv_conf.h`内的`#define CONFIG_LV_FS_POSIX_LETTER   'S'`宏定义任意修改，默认的是“S”

5. 加入SQLite数据库支持
   
   首先在RT-Thread Studio中，搜索并加入SQLite软件包。
   
   <img title="" src="file:///C:/Users/chengjili/AppData/Roaming/marktext/images/2022-08-12-11-28-55-image.png" alt="" width="922">
   
   具体配置如下：
   
   ![](img\2022-08-12-11-30-54-image.png)
   
   开启example，会有例程代码加入到工程。然后就可以仿照例程代码，实现自己具体的功能了。我这里新建了`sysdatabase`的源文件和头文件，盛放数据库相关的操作代码。实现如下的`create_sysdb_table()`函数。并在`user_gui_init()`的最开始进行调用。判断是否有数据库文件，如果有，是否有对应的数据库表。如果没有则创建数据库和建立需要的数据库表。
   
   ```c
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
   ```
   
   更多数据库相关的操作代码，请查看gitee上传的源码。

6. 具体UI的实现
   
   具体UI，一共实现了5个界面。当然，其中的设置界面还没有完成。这5个界面的实现，我这里尝试了两种方法。上级分了用户登录，用户注册和系统功能三个主界面。这级用的是自己定义的三个obj，承载三个界面内容，然后通过hidden属性实现了三个界面的切换。然后在系统功能界面下，用tileview控件实现了器件检索，器件管理和系统设置三个界面。实践出真知，经过实测感觉确实还是用tilewiew控件实现界面的切换更为方便，简洁。后续可以全部用tilewiew实现。
   
   至于具体的UI实现，无非就是操作LVGL的不同控件，实现对应的功能。而不同控件的使用介绍，我前期学习LVGL的时候提交过一些学习笔记。这里不再赘述，有兴趣的可以直接看源码。

#### 功能展示与介绍

下面以图文形式对目前实现的主要功能做一个展示

- 下图是用户登录界面
  
  用户名和登录密码的label控件，用图标美化了一下。后面的按钮以及其它的几个界面都还没来得及去美化，暂时先用文字验证功能。这里的小图标是用LVGL官网的取模工具，转换成了`user_img.c`和`password_img.c`然后加入到工程内部的方式实现的。每个文件254KB，不是很大。用这种方式实现的加载图片应该是速度最快的，只不过图片文件会最终编译到可执行文件内部，占用代码存储空间。所以背景图片就没用这种方式，因为800x480的图片，转换成'.c'文件后基本要二三十兆字节大小。实在是过于庞大。如果还想多加几张背景图做切换的话，直接就把SPI Flash撑爆了。这里的背景图片，是在LVGL中注册了一个软件JPEG解码器，用JPEG解码器对文件系统内的jpg文件进行加载和解码，然后显示。右下角的刷新率和CPU占用率的显示框，暂时没有关闭，在右下角也妨碍功能，还可以实时监视一下运行情况。而且还稍微修改了一下背景透明度，让其在白背景下显示的更清楚一些。

![](img/DJI_0537.jpg)

- 点击用户名输入框后，会弹出键盘，以便输入用户名。下方还会弹出列表框，显示目前存在的用户名，以供直接选择。可以上下滑动查找，也可以输入关键字符，缩小查找范围。

![](G:\DCIM\DJI_0538.jpg)

- 如下是点击“register”按钮后，跳转到的用户管理界面。测试了一下注册新用户的功能。在‘user’输入框中输入'wer'的测试用户名。在'pwd'和'repwd'内分别输入密码和确认密码。这里故意把确认密码输入错误，然后点击‘OK’按钮，会弹出警示框，提示确认输入的用户名和密码是否正确。

![](G:\DCIM\DJI_0539.jpg)

- 如下是故意把管理员密码输入错误后的提示信息

![](G:\DCIM\DJI_0540.jpg)

- 如果全部输入正确的话，点击“OK”按钮，就会成功注册新用户。然后在用户登录界面输入正确的用户名和密码，点击“login”按钮，就可以成功登录了。登录后，会自动跳转到如下的器件检索界面。上侧为一个检索输入框。下面为一个列表框，加载数据库中的数据。如下是我提前用excel导入的测试数据。

![](G:\DCIM\DJI_0541.jpg)

- 在检索框中输入关键字，可以缩小检索范围，如下图，输入"stm"关键字后，下面的列表框就会显示包含“stm”的器件名。这里不区分大小写，而且是全名称模糊匹配，名称中间或结尾包含关键字也会被检索到。

![](G:\DCIM\DJI_0542.jpg)

- 上下滑动列表框可以浏览所有的数据。如下随便选取第一个“STM32G030K6T6”的芯片做测试，常按这一行数据列表，就会转到如下的器件管理界面。此界面可以对此器件的所有信息进行修改，或直接删除。也可长按表头，进入器件管理界面进行器件添加入库等操作。

![](G:\DCIM\DJI_0543.jpg)

- 下图为随便输入一个封装名称，点击“OK”按钮，测试修改信息的功能。会弹出信息框，要求确认操作。再次点击“OK”按钮，确认修改。

![](G:\DCIM\DJI_0544.jpg)

- 再次弹出信息框，提示已经修改成功了。点击“OK”按钮关闭即可。

![](G:\DCIM\DJI_0545.jpg)

- 如下图，是测试的删除功能。点击“Delete”按钮，同样也会弹出确认框。

![](G:\DCIM\DJI_0546.jpg)

- 确认后，提示删除成功。

![](G:\DCIM\DJI_0547.jpg)

- 返回器件检索界面后，可以看到，器件列表的第一个器件变成了“STM32F030F4P6”了。原来的“STM32G030K6T6”已经成功从数据库中删除了。

![](G:\DCIM\DJI_0548.jpg)

- 最后再看一下系统设置界面。这里目前只有一个用户退出登录的按钮。其它功能还未添加进来。在器件检索界面，向上滑动，即可滑到此界面。点击“logout”按钮，即可退出登录，返回用户登录界面。10分钟无任何操作，也会自动退出登录，返回用户登录界面，并且关闭屏幕背光。触控触摸屏任何部位，会再次唤醒屏幕。

![](G:\DCIM\DJI_0549.jpg)

大概的功能就演示到这里，其它的功能操作基本和上面的差不多。还有一些功能没来得及完善。也可以点击下面的链接，观看功能演示视频：

https://www.bilibili.com/video/BV1Ka411N7A6?spm_id_from=333.999.0.0&vd_source=143082a01c512169c40eb84df2924c9d

#### 参与贡献

1. 源码开源
   
   链接：[ComponentsLib: 基于新唐N9H30硬件平台，RTThread+LVGL软件平台的便携式器件库存管理系统。LVGL嵌入式GUI挑战赛作品。](https://gitee.com/chengjili/components-lib)

2. LVGL学习笔记的分享
   
   - [RT-Thread-N9H30开发板开箱测试RT-Thread问答社区 - RT-Thread](https://club.rt-thread.org/ask/article/9a1b494513c87d83.html)
   
   - [RT-Thread-N9H30开发板RTThread框架下的LVGL例程代码分析&mdash;&mdash;LVGL初始化RT-Thread问答社区 - RT-Thread](https://club.rt-thread.org/ask/article/bd14f02158909272.html)
   
   - [RT-Thread-N9H30开发板RTThread框架下的LVGL例程代码分析&mdash;&mdash;基础数据结构RT-Thread问答社区 - RT-Thread](https://club.rt-thread.org/ask/article/4ce9eae1c91426aa.html)
   
   - [RT-Thread-LVGL例程学习&mdash;&mdash;get_startedRT-Thread问答社区 - RT-Thread](https://club.rt-thread.org/ask/article/580366a0f1742c3f.html)
   
   - [RT-Thread-LVGL例程学习&mdash;&mdash;stylesRT-Thread问答社区 - RT-Thread](https://club.rt-thread.org/ask/article/e9cda20a6624b244.html)
   
   - [RT-Thread-LVGL例程学习&mdash;&mdash;animRT-Thread问答社区 - RT-Thread](https://club.rt-thread.org/ask/article/7a35d68521bd667d.html)
     
     由于比赛的时间关系，后续的学习没有整理学习笔记。先忙于实现具体功能了。等后面功能完善后，可以再继续整理分享一下更深入的LVGL学习与使用心得。

3. 官方问题的发现与解决
   
   1. 新唐N9H30开发板适配的触摸屏驱动容易误触发的问题：
      
      [RT-Thread-N9H30 HMI开发板触摸屏误触发问题，及解决办法RT-Thread问答社区 - RT-Thread](https://club.rt-thread.org/ask/article/ccbb3e920a9ad23c.html)
      
      也感谢官方对此方法的认可：
      
      ![](C:\Users\chengjili\AppData\Roaming\marktext\images\2022-08-12-18-02-06-image.png)
   
   2. 官方anim的`lv_example_anim_3()`例程，存在BUG，一运行就崩溃。我在对应的日志中也提出了简易的解决办法。

#### 特技

1. 使用 Readme\_XXX.md 来支持不同的语言，例如 Readme\_en.md, Readme\_zh.md
2. Gitee 官方博客 [blog.gitee.com](https://blog.gitee.com)
3. 你可以 [https://gitee.com/explore](https://gitee.com/explore) 这个地址来了解 Gitee 上的优秀开源项目
4. [GVP](https://gitee.com/gvp) 全称是 Gitee 最有价值开源项目，是综合评定出的优秀开源项目
5. Gitee 官方提供的使用手册 [https://gitee.com/help](https://gitee.com/help)
6. Gitee 封面人物是一档用来展示 Gitee 会员风采的栏目 [https://gitee.com/gitee-stars/](https://gitee.com/gitee-stars/)
