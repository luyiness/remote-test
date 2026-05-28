//
// Created by luyi on 2026/5/27.
//

#include "app_communication.h"

uint8_t tx_data_buff[TX_PLOAD_WIDTH];
uint32_t check_sum;

void app_comm_send_data(Remote_Data *rd)
{
    //1、头部加一个校验字段，用于接收方确认是正确的发送方 ；3Byte
    tx_data_buff[0] = HEAD_FRAME_0;
    tx_data_buff[1] = HEAD_FRAME_1;
    tx_data_buff[2] = HEAD_FRAME_2;

    //2、属性throttle等 用数字格式存放比字符串更省空间 ； 10Byte
    tx_data_buff[3] = rd->throttle;         //低8位在前
    tx_data_buff[4] = rd->throttle >> 8;    //高8位在后
    tx_data_buff[5] = rd->yaw;
    tx_data_buff[6] = rd->yaw >> 8;
    tx_data_buff[7] = rd->pitch;
    tx_data_buff[8] = rd->pitch >> 8;
    tx_data_buff[9] = rd->roll;
    tx_data_buff[10] = rd->roll >> 8;


    taskENTER_CRITICAL();
    tx_data_buff[11] = rd->fix_height;
    tx_data_buff[12] = rd->shut;

    //因为fix_height和shut是按键控制的，每次扫描到此按键后就赋=1。 所以这里发送完数据后、要将fix_height和shut初始化=0，不然就一直=1了
    //为什么加临界区：比如就此行发生了任务切换 按键扫描使rd->fix_height=1了，那这个1就发不出去了 下面直接清零了
    rd->fix_height=0;
    rd->shut=0;
    taskEXIT_CRITICAL();

    //3、尾部校验字段：检测数据完整性 ；4Byte
    check_sum = 0;
    for (uint8_t i = 0; i < 13; i++)
    {
        check_sum += tx_data_buff[i];
    }
    tx_data_buff[13] = check_sum;
    tx_data_buff[14] = check_sum >> 8;
    tx_data_buff[15] = check_sum >> 16;
    tx_data_buff[16] = check_sum >> 24;

    Int_SI24R1_TxPacket(tx_data_buff);
}
