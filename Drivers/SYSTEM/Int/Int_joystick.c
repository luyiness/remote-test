//
// Created by luyi on 2026/5/27.
//

#include "../include/Int_joystick.h"

uint16_t joystick_buff[4] = {0};     //DMA传过来的数据是HalfWord长度、也就是16位，2个摇杆对应4个数字量


void Int_joystick_init(void)
{
    //启动ADC
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)joystick_buff, 4);
}

//将扫描的数据存到结构体中
void Int_joystick_scan(Remote_Data *remote_data)
{
    //配置的ADC的4个通道、按照1 6 2 3的顺序采集，所以这里也是按顺序接收
    //ADC1-1, rank1   throttle  PA1
    //ADC1-6, rank2   yaw       PA6
    //ADC1-2, rank3   pitch     PA2
    //ADC1-3, rank4   roll      PA3
    remote_data->throttle = joystick_buff[0];
    remote_data->yaw = joystick_buff[1];
    remote_data->pitch = joystick_buff[2];
    remote_data->roll = joystick_buff[3];
}