################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../packages/LVGL-v8.2.0/src/widgets/lv_arc.c \
../packages/LVGL-v8.2.0/src/widgets/lv_bar.c \
../packages/LVGL-v8.2.0/src/widgets/lv_btn.c \
../packages/LVGL-v8.2.0/src/widgets/lv_btnmatrix.c \
../packages/LVGL-v8.2.0/src/widgets/lv_canvas.c \
../packages/LVGL-v8.2.0/src/widgets/lv_checkbox.c \
../packages/LVGL-v8.2.0/src/widgets/lv_dropdown.c \
../packages/LVGL-v8.2.0/src/widgets/lv_img.c \
../packages/LVGL-v8.2.0/src/widgets/lv_label.c \
../packages/LVGL-v8.2.0/src/widgets/lv_line.c \
../packages/LVGL-v8.2.0/src/widgets/lv_objx_templ.c \
../packages/LVGL-v8.2.0/src/widgets/lv_roller.c \
../packages/LVGL-v8.2.0/src/widgets/lv_slider.c \
../packages/LVGL-v8.2.0/src/widgets/lv_switch.c \
../packages/LVGL-v8.2.0/src/widgets/lv_table.c \
../packages/LVGL-v8.2.0/src/widgets/lv_textarea.c 

OBJS += \
./packages/LVGL-v8.2.0/src/widgets/lv_arc.o \
./packages/LVGL-v8.2.0/src/widgets/lv_bar.o \
./packages/LVGL-v8.2.0/src/widgets/lv_btn.o \
./packages/LVGL-v8.2.0/src/widgets/lv_btnmatrix.o \
./packages/LVGL-v8.2.0/src/widgets/lv_canvas.o \
./packages/LVGL-v8.2.0/src/widgets/lv_checkbox.o \
./packages/LVGL-v8.2.0/src/widgets/lv_dropdown.o \
./packages/LVGL-v8.2.0/src/widgets/lv_img.o \
./packages/LVGL-v8.2.0/src/widgets/lv_label.o \
./packages/LVGL-v8.2.0/src/widgets/lv_line.o \
./packages/LVGL-v8.2.0/src/widgets/lv_objx_templ.o \
./packages/LVGL-v8.2.0/src/widgets/lv_roller.o \
./packages/LVGL-v8.2.0/src/widgets/lv_slider.o \
./packages/LVGL-v8.2.0/src/widgets/lv_switch.o \
./packages/LVGL-v8.2.0/src/widgets/lv_table.o \
./packages/LVGL-v8.2.0/src/widgets/lv_textarea.o 

C_DEPS += \
./packages/LVGL-v8.2.0/src/widgets/lv_arc.d \
./packages/LVGL-v8.2.0/src/widgets/lv_bar.d \
./packages/LVGL-v8.2.0/src/widgets/lv_btn.d \
./packages/LVGL-v8.2.0/src/widgets/lv_btnmatrix.d \
./packages/LVGL-v8.2.0/src/widgets/lv_canvas.d \
./packages/LVGL-v8.2.0/src/widgets/lv_checkbox.d \
./packages/LVGL-v8.2.0/src/widgets/lv_dropdown.d \
./packages/LVGL-v8.2.0/src/widgets/lv_img.d \
./packages/LVGL-v8.2.0/src/widgets/lv_label.d \
./packages/LVGL-v8.2.0/src/widgets/lv_line.d \
./packages/LVGL-v8.2.0/src/widgets/lv_objx_templ.d \
./packages/LVGL-v8.2.0/src/widgets/lv_roller.d \
./packages/LVGL-v8.2.0/src/widgets/lv_slider.d \
./packages/LVGL-v8.2.0/src/widgets/lv_switch.d \
./packages/LVGL-v8.2.0/src/widgets/lv_table.d \
./packages/LVGL-v8.2.0/src/widgets/lv_textarea.d 


# Each subdirectory must supply rules for building sources it contributes
packages/LVGL-v8.2.0/src/widgets/%.o: ../packages/LVGL-v8.2.0/src/widgets/%.c
	arm-none-eabi-gcc -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\legacy\dfs" -I"D:\RT-ThreadStudio\workspace\ComponentsLib" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\applications\lvgl" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\applications" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\board" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\libraries\n9h30\Driver\Include" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\libraries\n9h30\UsbHostLib\inc" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\libraries\n9h30\rtt_port" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\libraries\nu_packages\ADC_TOUCH" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\libraries\nu_packages\AudioCodec" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\libraries\nu_packages\NuUtils\inc" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\libraries\nu_packages\TPC" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\env_support\rt-thread" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\core" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\draw\nxp_pxp" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\draw\nxp_vglite" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\draw\sdl" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\draw\stm32_dma2d" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\draw\sw" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\draw" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\layouts\flex" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\layouts\grid" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\layouts" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\libs\bmp" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\libs\ffmpeg" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\libs\freetype" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\libs\fsdrv" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\libs\gif" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\libs\png" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\libs\qrcode" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\libs\rlottie" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\libs\sjpg" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\libs" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\others\gridnav" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\others\monkey" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\others\snapshot" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\others" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\themes\basic" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\themes\default" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\themes\mono" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\themes" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\widgets\animimg" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\widgets\calendar" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\widgets\chart" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\widgets\colorwheel" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\widgets\imgbtn" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\widgets\keyboard" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\widgets\led" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\widgets\list" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\widgets\menu" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\widgets\meter" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\widgets\msgbox" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\widgets\span" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\widgets\spinbox" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\widgets\spinner" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\widgets\tabview" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\widgets\tileview" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\widgets\win" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\widgets" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\font" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\gpu" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\hal" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\misc" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\widgets" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\ramdisk-latest\inc" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\sqlite-v3.19.3" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\dfs\filesystems\devfs" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\dfs\filesystems\elmfat" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\dfs\include" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\drivers\audio" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\drivers\include" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\drivers\spi\sfud\inc" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\drivers\spi" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\drivers\touch" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\drivers\usb\usbdevice" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\drivers\usb\usbhost\class" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\drivers\usb\usbhost\core" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\drivers\usb\usbhost" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\fal\inc" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\finsh" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\libc\compilers\common" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\libc\compilers\newlib" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\libc\posix\io\poll" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\libc\posix\io\stdio" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\libc\posix\ipc" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\net\lwip\lwip-2.0.3\src\include\netif" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\net\lwip\lwip-2.0.3\src\include" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\net\lwip\port" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\net\netdev\include" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\net\sal\impl" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\net\sal\include\dfs_net" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\net\sal\include\socket\sys_socket" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\net\sal\include\socket" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\net\sal\include" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\utilities\ulog" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\utilities\utest" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\include" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\libcpu\arm\arm926" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\libcpu\arm\common" -include"D:\RT-ThreadStudio\workspace\ComponentsLib\rtconfig_preinc.h" -std=gnu11 -mcpu=arm926ej-s -O2 -g -gdwarf-2 -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

