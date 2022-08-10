################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libraries/n9h30/rtt_port/drv_adc.c \
../libraries/n9h30/rtt_port/drv_can.c \
../libraries/n9h30/rtt_port/drv_common.c \
../libraries/n9h30/rtt_port/drv_crypto.c \
../libraries/n9h30/rtt_port/drv_emac.c \
../libraries/n9h30/rtt_port/drv_etimer.c \
../libraries/n9h30/rtt_port/drv_etimer_capture.c \
../libraries/n9h30/rtt_port/drv_ge2d.c \
../libraries/n9h30/rtt_port/drv_gpio.c \
../libraries/n9h30/rtt_port/drv_i2c.c \
../libraries/n9h30/rtt_port/drv_i2s.c \
../libraries/n9h30/rtt_port/drv_jpegcodec.c \
../libraries/n9h30/rtt_port/drv_pwm.c \
../libraries/n9h30/rtt_port/drv_qspi.c \
../libraries/n9h30/rtt_port/drv_rtc.c \
../libraries/n9h30/rtt_port/drv_scuart.c \
../libraries/n9h30/rtt_port/drv_sdh.c \
../libraries/n9h30/rtt_port/drv_softi2c.c \
../libraries/n9h30/rtt_port/drv_sys.c \
../libraries/n9h30/rtt_port/drv_systick.c \
../libraries/n9h30/rtt_port/drv_timer.c \
../libraries/n9h30/rtt_port/drv_uart.c \
../libraries/n9h30/rtt_port/drv_usbd.c \
../libraries/n9h30/rtt_port/drv_usbhost.c \
../libraries/n9h30/rtt_port/drv_vpost.c \
../libraries/n9h30/rtt_port/drv_wdt.c 

OBJS += \
./libraries/n9h30/rtt_port/drv_adc.o \
./libraries/n9h30/rtt_port/drv_can.o \
./libraries/n9h30/rtt_port/drv_common.o \
./libraries/n9h30/rtt_port/drv_crypto.o \
./libraries/n9h30/rtt_port/drv_emac.o \
./libraries/n9h30/rtt_port/drv_etimer.o \
./libraries/n9h30/rtt_port/drv_etimer_capture.o \
./libraries/n9h30/rtt_port/drv_ge2d.o \
./libraries/n9h30/rtt_port/drv_gpio.o \
./libraries/n9h30/rtt_port/drv_i2c.o \
./libraries/n9h30/rtt_port/drv_i2s.o \
./libraries/n9h30/rtt_port/drv_jpegcodec.o \
./libraries/n9h30/rtt_port/drv_pwm.o \
./libraries/n9h30/rtt_port/drv_qspi.o \
./libraries/n9h30/rtt_port/drv_rtc.o \
./libraries/n9h30/rtt_port/drv_scuart.o \
./libraries/n9h30/rtt_port/drv_sdh.o \
./libraries/n9h30/rtt_port/drv_softi2c.o \
./libraries/n9h30/rtt_port/drv_sys.o \
./libraries/n9h30/rtt_port/drv_systick.o \
./libraries/n9h30/rtt_port/drv_timer.o \
./libraries/n9h30/rtt_port/drv_uart.o \
./libraries/n9h30/rtt_port/drv_usbd.o \
./libraries/n9h30/rtt_port/drv_usbhost.o \
./libraries/n9h30/rtt_port/drv_vpost.o \
./libraries/n9h30/rtt_port/drv_wdt.o 

C_DEPS += \
./libraries/n9h30/rtt_port/drv_adc.d \
./libraries/n9h30/rtt_port/drv_can.d \
./libraries/n9h30/rtt_port/drv_common.d \
./libraries/n9h30/rtt_port/drv_crypto.d \
./libraries/n9h30/rtt_port/drv_emac.d \
./libraries/n9h30/rtt_port/drv_etimer.d \
./libraries/n9h30/rtt_port/drv_etimer_capture.d \
./libraries/n9h30/rtt_port/drv_ge2d.d \
./libraries/n9h30/rtt_port/drv_gpio.d \
./libraries/n9h30/rtt_port/drv_i2c.d \
./libraries/n9h30/rtt_port/drv_i2s.d \
./libraries/n9h30/rtt_port/drv_jpegcodec.d \
./libraries/n9h30/rtt_port/drv_pwm.d \
./libraries/n9h30/rtt_port/drv_qspi.d \
./libraries/n9h30/rtt_port/drv_rtc.d \
./libraries/n9h30/rtt_port/drv_scuart.d \
./libraries/n9h30/rtt_port/drv_sdh.d \
./libraries/n9h30/rtt_port/drv_softi2c.d \
./libraries/n9h30/rtt_port/drv_sys.d \
./libraries/n9h30/rtt_port/drv_systick.d \
./libraries/n9h30/rtt_port/drv_timer.d \
./libraries/n9h30/rtt_port/drv_uart.d \
./libraries/n9h30/rtt_port/drv_usbd.d \
./libraries/n9h30/rtt_port/drv_usbhost.d \
./libraries/n9h30/rtt_port/drv_vpost.d \
./libraries/n9h30/rtt_port/drv_wdt.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/n9h30/rtt_port/%.o: ../libraries/n9h30/rtt_port/%.c
	arm-none-eabi-gcc -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\legacy\dfs" -I"D:\RT-ThreadStudio\workspace\ComponentsLib" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\applications\lvgl" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\applications" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\board" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\libraries\n9h30\Driver\Include" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\libraries\n9h30\UsbHostLib\inc" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\libraries\n9h30\rtt_port" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\libraries\nu_packages\ADC_TOUCH" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\libraries\nu_packages\AudioCodec" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\libraries\nu_packages\NuUtils\inc" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\libraries\nu_packages\TPC" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\env_support\rt-thread" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\core" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\draw\nxp_pxp" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\draw\nxp_vglite" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\draw\sdl" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\draw\stm32_dma2d" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\draw\sw" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\draw" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\layouts\flex" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\layouts\grid" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\layouts" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\libs\bmp" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\libs\ffmpeg" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\libs\freetype" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\libs\fsdrv" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\libs\gif" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\libs\png" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\libs\qrcode" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\libs\rlottie" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\libs\sjpg" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\libs" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\others\gridnav" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\others\monkey" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\others\snapshot" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\others" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\themes\basic" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\themes\default" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\themes\mono" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\themes" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\widgets\animimg" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\widgets\calendar" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\widgets\chart" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\widgets\colorwheel" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\widgets\imgbtn" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\widgets\keyboard" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\widgets\led" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\widgets\list" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\widgets\menu" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\widgets\meter" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\widgets\msgbox" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\widgets\span" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\widgets\spinbox" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\widgets\spinner" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\widgets\tabview" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\widgets\tileview" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\widgets\win" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra\widgets" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\extra" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\font" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\gpu" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\hal" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\misc" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src\widgets" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\LVGL-v8.2.0\src" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\ramdisk-latest\inc" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\packages\sqlite-v3.19.3" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\dfs\filesystems\devfs" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\dfs\filesystems\elmfat" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\dfs\include" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\drivers\audio" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\drivers\include" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\drivers\spi\sfud\inc" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\drivers\spi" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\drivers\touch" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\drivers\usb\usbdevice" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\drivers\usb\usbhost\class" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\drivers\usb\usbhost\core" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\drivers\usb\usbhost" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\fal\inc" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\finsh" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\libc\compilers\common" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\libc\compilers\newlib" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\libc\posix\io\poll" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\libc\posix\io\stdio" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\libc\posix\ipc" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\net\lwip\lwip-2.0.3\src\include\netif" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\net\lwip\lwip-2.0.3\src\include" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\net\lwip\port" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\net\netdev\include" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\net\sal\impl" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\net\sal\include\dfs_net" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\net\sal\include\socket\sys_socket" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\net\sal\include\socket" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\net\sal\include" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\utilities\ulog" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\components\utilities\utest" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\include" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\libcpu\arm\arm926" -I"D:\RT-ThreadStudio\workspace\ComponentsLib\rt-thread\libcpu\arm\common" -include"D:\RT-ThreadStudio\workspace\ComponentsLib\rtconfig_preinc.h" -std=gnu11 -mcpu=arm926ej-s -O2 -g -gdwarf-2 -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

