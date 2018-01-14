【LPC824Lite】 Mac OS X下开发环境建立
=====
有幸获得爱板网试用LPC824Lite开发板的机会，1月10日拿到板子后就着手创建开发环境。由于一直在MacBook Pro用arm-none-eabi-gcc开发STM32，LPC824Lite又是基于ARM Cortex M0+的开发板，因此很自然选择恩智浦的MCUXpresso IDE。MCUXpresso IDE基于Eclipse IDE，并包含业界标准的ARM GNU工具链。它为基于Cortex-M内核的NXP MCU（LPC和Kinetis）提供了易于使用和无限制代码大小的开发环境。 MCUXpresso IDE调试连接支持Freedom、Tower、LPCXpresso和您的定制开发板，并且具有行业领先的开源和商业级的调试仿真器，包括LPC-Link2、P＆E和SEGGER。全功能调试器支持SWD和JTAG调试，并且可以直接下载到片上闪存。本节主要讲解在Mac OS X搭建MCUXpresso IDE编译环境，用LPCOpen库创建一个新项目。
## 准备工作
1. [下载最新MCUXpresso IDE](https://www.nxp.com/support/developer-resources/software-development-tools/mcuxpresso-software-and-tools/mcuxpresso-integrated-development-environment-ide:MCUXpresso-IDE?tab=Design_Tools_Tab)
2. [下载LPC824Lite SDK](http://www.ucdragon.cn/ProductsSt/250.html)
3. [下载LPCOpen](https://www.nxp.com/support/developer-resources/software-development-tools/lpc-developer-resources-/lpcopen-libraries-and-examples:LPC-OPEN-LIBRARIES)

## 安装MCUXpresso IDE
在Mac OS X下安装MCUXpresso IDE还是比较简单的，点击下载的包文件（MCUXpressoIDE_XX.x.x_XXX.pkg）一路“继续”即可安装好，MCUXpresso IDE默认安装就已汉化。LPC824Lite板载USB设备：CMSIS-DAP调试器，虚拟串口、Mbed U盘下载器，在Mac OS X下免驱，无须安装驱动。
![主窗口](install.png)

## 重构LPC824Lite SDK
从优龙科技官网下载SDK是Keil MDK-ARM环境的，MCUXpresso IDE用不上，需要重构。进入MCUXpresso IDE主界面，按左下的“Quickstart Panel”的“New project”建新项目
![](wizard0.png)
在“SDK Wizard”窗口的”Preinstalled MCUs“选LPC824,在“Available board”点LPCpresso824-MAX板“下一步”
![](wizard1.png)
在“New project...”窗口"Wizard selection page"向导选择页中，点选“LPCOpen C Static Library Project”
![](wizard2.png)
在“project creation...”项目创建页的项目名中输入“lpc_board_lpc824lite”
![](wizard3.png)
在“wizard properties page”向导属性页按“import...”
![](wizard4.png)
在“import”导入窗口预览选取LPCOpen库文件，这里是3.02版lpcopen_3_02_lpcxpresso_nxp_lpcxpresso_824.zip,按下一步，只选lpc_chip_82x和lpc_board_nxp_lpcxpresso_824。
![](wizard5.png)

![](wizard6.png)
按“完成”，选lpc_board_nxp_lpcxpresso_824,一路“下一步”即可创建一个空项目
![](wizard7.png)
将优龙科技的SDK“common／board”目录的文件复制到新项目lpc_board_lpc824lite中，同时把lpc_board_nxp_lpcxpresso_824的board_sysint.c也复制。
![](wizard8.png)

![](wizard9.png)
构建lpc_board_lpc824lite项目，board.c有几个警告，对引用没有定义的函数进行修改。
![](wizard10.png)
board.c第61行、72行
Chip_GPIO_PinSetDIR改Chip_GPIO_SetPinDIR

board.c第73行、153行
Chip_GPIO_PinSetState改Chip_GPIO_SetPinState

board.c163行
Chip_GPIO_PinGetState改Chip_GPIO_GetPinState

board.c第173行
Chip_GPIO_PinSetToggle改Chip_GPIO_SetPinToggle

再次构建项目，忽略两个警告，LPC824Lite开发板库就建好了。
![](wizard11.png)
## 创建第一个应用项目
按上面新建项目，在“Wizard selection page”选“LPCOpen- C Project”
![](blink0.png)
项目名blinky，开发板库选刚刚建立的lpc_board_lpc824lite
![](blink1.png)
按系统默认完成向导，创建blinky新项目
添加代码

`i++ ;
if((i%20000)==0)
{
  Board_LED_Toggle(0);
}`
按“Quickstart panel”的“build‘blinky’[Debug]”编译项目
连好数据线给开发板上电按“Debug'blinky'[Debug]”创建调试配置
![](blink3.png)
MCUXpresso IDE已检测到LPC824Lite板载“Mbed CMSIS-DAP”调试接口，按“OK”就可进入调试，系统自动将程序烧写到板子上并停在main函数。
![](blink4.png)
按F8恢复运行就可看见LED0闪烁。
![]()
