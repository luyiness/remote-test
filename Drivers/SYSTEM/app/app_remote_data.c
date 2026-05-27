//
// Created by luyi on 2026/5/27.
//

#include "app_remote_data.h"

int16_t joystick_digitalValue_bias[4] = {0};       //存储偏移值，可能为负数
uint8_t COLLECT_COUNT = 50;     //共采集COLLECT_COUNT次。 注意每次采集时间是joystick task的延迟时间

//摇杆校准：就是将这些摇杆的数字量digital value修改成理想的值
static void App_Calibrate_Joystick_Data(Remote_Data *remote_data)
{
    //求每个摇杆的数字量的偏移的平均值
    int16_t sum[4] = {0};
    for (int i = 0; i < COLLECT_COUNT; i++)
    {
        sum[0] += remote_data->throttle - 0;
        sum[1] += remote_data->yaw - 500;
        sum[2] += remote_data->pitch - 500;
        sum[3] += remote_data->roll - 500;
        vTaskDelay(10);         //延迟每次采集时间
    }
    joystick_digitalValue_bias[0] = sum[0] / COLLECT_COUNT;
    joystick_digitalValue_bias[1] = sum[1] / COLLECT_COUNT;
    joystick_digitalValue_bias[2] = sum[2] / COLLECT_COUNT;
    joystick_digitalValue_bias[3] = sum[3] / COLLECT_COUNT;
}

void App_Process_Joystick_Data(Remote_Data *remote_data)
{
    taskENTER_CRITICAL();

    Int_joystick_scan(remote_data);

    //拿到的数字量digital value，范围改成0～1000， 并改极性（因为尚硅谷的这块板子摇杆pcb的3.3v接反了，比如油门拉到最小是=4095，所以要改极性）
    remote_data->throttle = 1000 - remote_data->throttle * 1000 / 4095;
    remote_data->yaw = 1000 - remote_data->yaw * 1000 / 4095;
    remote_data->pitch = 1000 - remote_data->pitch * 1000 / 4095;
    remote_data->roll = 1000 - remote_data->roll * 1000 / 4095;

    //校准；   （这里和老师的代码不一样，具体看onenote笔记）
    int16_t throttle = remote_data->throttle - joystick_digitalValue_bias[0];
    int16_t yaw = remote_data->yaw - joystick_digitalValue_bias[1];
    int16_t pitch = remote_data->pitch - joystick_digitalValue_bias[2];
    int16_t roll = remote_data->roll - joystick_digitalValue_bias[3];

    //重新限定范围；（因为前面的校准只是减一个数，有可能成负数 是不允许的）
    throttle = LIMIT(throttle, 0, 1000);
    yaw = LIMIT(yaw, 0, 1000);
    pitch = LIMIT(pitch, 0, 1000);
    roll = LIMIT(roll, 0, 1000);

    taskEXIT_CRITICAL();

    // debug_printf("remote_data->pitch: %d", remote_data->pitch);
    // debug_printf("remote_data->throttle: %d", remote_data->throttle);
    // debug_printf("remote_data->fix_height: %d", remote_data->fix_height);
    //....
}

void App_Process_Key_Data(Remote_Data *remote_data)
{
    KEY_TypeDef key = int_key_scan();
    switch (key)
    {
    case KEY_UP:
        debug_printfln("key_up");
        remote_data->pitch += 10;
        break;
    case KEY_DOWN:
        debug_printfln("key_down");
        break;
    case KEY_LEFT:
        debug_printfln("key_left");
        break;
    case KEY_RIGHT:
        debug_printfln("key_right");
        break;
    case KEY_LEFT_X:        //关机
        debug_printfln("key_left_x");
        remote_data->shut = 1;
        break;
    case KEY_RIGHT_X:       //定高
        debug_printfln("key_right_x");
        remote_data->fix_height = 1;
        break;
    case KEY_LEFT_X_HOLD:
        debug_printfln("key_left_x_hold");
        break;
    case KEY_RIGHT_X_HOLD:    //校准joystick
        debug_printfln("key_right_x_hold");
        App_Calibrate_Joystick_Data(remote_data);
        break;
    default:
        debug_printfln("unknown key");
        break;
    }
}
