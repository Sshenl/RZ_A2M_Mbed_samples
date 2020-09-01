# 2020年瑞萨杯信息科技前沿专题邀请赛作品源代码
## 作品名称：针对手机语音助手的超声黑客攻击与防御
## 作品简介
麦克风非线性导致的手机语音助手安全漏洞可在手机用户无法察觉的情况下被黑客使用超声波控制手机语音助手。本作品以超声攻击的数学原理为基础，对攻击信号的生成进行了一定改进，以便模拟实际场景下的超声攻击和进一步研究超声攻击的防御，同时针对这一类攻击方式设计了一种有效的防御方法。本组作品包括超声波攻击装置和基于RZ/A2M开发板的防御装置。攻击装置实现了在1.2米左右的距离唤醒语音助手，并利用语音助手控制手机；防御装置能够监听环境中的超声波攻击信号并告警，同时能将超声攻击内容转为可以被人耳听见的音频信号。

## 代码结构
### 攻击装置：
* 超声攻击信号生成：[attack_generator.m](https://github.com/Sshenl/RZ_A2M_Mbed_samples/blob/master/attack_generator.m)
### 防御装置：
* 此工程以[d-kato/RZ_A2M_Mbed_samples](https://github.com/d-kato/RZ_A2M_Mbed_samples)为模板
* 主函数：[sample_22_main.cpp](https://github.com/Sshenl/RZ_A2M_Mbed_samples/blob/master/sample_programs/sample_22_main.cpp)
* 主要库文件：
  * DDS模块驱动函数库：[mylibs/AD9850.h](https://github.com/Sshenl/RZ_A2M_Mbed_samples/blob/master/mylibs/AD9850.h)
  * 显示屏驱动函数库：[mylibs/OCM_driver.h](https://github.com/Sshenl/RZ_A2M_Mbed_samples/blob/master/mylibs/OCM_driver.h)
  * 数字滤波器函数库：[mylibs/filter.h](https://github.com/Sshenl/RZ_A2M_Mbed_samples/blob/master/mylibs/filter.h)
  * 人机交互界面有关函数库：[mylibs/LCD_disp.h](https://github.com/Sshenl/RZ_A2M_Mbed_samples/blob/master/mylibs/LCD_disp.h)
## 防御装置要求
* 硬件要求：RZ/A2M Evaluation Board Kit
* 开发环境：Mbed Studio
