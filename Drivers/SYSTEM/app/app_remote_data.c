//
// Created by luyi on 2026/5/27.
//

#include "app_remote_data.h"

int16_t joystick_dv_bias[4] = {0};       //digital value bias 存储偏移值，可能为负数
const uint8_t COLLECT_COUNT = 50;     //共采集COLLECT_COUNT次。 注意每次采集时间是joystick task的延迟时间

//摇杆校准：就是将这些摇杆的数字量digital value修改成理想的值
static void App_Calibrate_Joystick_Data(Remote_Data *rd)
{
    //求每个摇杆的数字量的偏移的平均值
    int16_t sum[4] = {0};
    for (int i = 0; i < COLLECT_COUNT; i++)
    {
        sum[0] += rd->throttle - 0;
        sum[1] += rd->yaw - 500;
        sum[2] += rd->pitch - 500;
        sum[3] += rd->roll - 500;
        vTaskDelay(10);         //延迟每次采集时间
    }
    joystick_dv_bias[0] += sum[0] / COLLECT_COUNT;     //为什么是+=而不是= ：第一次校准没问题。第二次执行校准时，joystick_dv_bias[0]就=0了，不就把原先的校准值清除了 和没校准时一样了
    joystick_dv_bias[1] += sum[1] / COLLECT_COUNT;
    joystick_dv_bias[2] += sum[2] / COLLECT_COUNT;
    joystick_dv_bias[3] += sum[3] / COLLECT_COUNT;
}

void App_Process_Joystick_Data(Remote_Data *rd)
{
    taskENTER_CRITICAL();

    Int_joystick_scan(rd);

    //拿到的数字量digital value，范围改成0～1000， 并改极性（因为尚硅谷的这块板子摇杆pcb的3.3v接反了，比如油门拉到最小是=4095，所以要改极性）
    rd->throttle = 1000 - rd->throttle * 1000 / 4095;
    rd->yaw = 1000 - rd->yaw * 1000 / 4095;
    rd->pitch = 1000 - rd->pitch * 1000 / 4095;
    rd->roll = 1000 - rd->roll * 1000 / 4095;

    //校准；
    rd->throttle -= joystick_dv_bias[0];
    rd->yaw -= joystick_dv_bias[1];
    rd->pitch -= joystick_dv_bias[2];
    rd->roll -= joystick_dv_bias[3];

    //重新限定范围；（因为前面的校准只是减一个数，有可能成负数 是不允许的）
    rd->throttle = LIMIT(rd->throttle, 0, 1000);
    rd->yaw = LIMIT(rd->yaw, 0, 1000);
    rd->pitch = LIMIT(rd->pitch, 0, 1000);
    rd->roll = LIMIT(rd->roll, 0, 1000);

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
    case KEY_UP:            //throttle偏移+10
        joystick_dv_bias[2] -= 10;        //偏移量-10，实际的remote_data->throttle就是+10
        break;
    case KEY_DOWN:
        joystick_dv_bias[2] += 10;
        break;
    case KEY_LEFT:
        joystick_dv_bias[3] += 10;
        break;
    case KEY_RIGHT:
        joystick_dv_bias[3] -= 10;
        break;
    case KEY_LEFT_X:        //关机
        debug_printfln("key_left_x");
        remote_data->shut = 1;              //平常=0，=1表示关机
        break;
    case KEY_RIGHT_X:       //定高
        debug_printfln("key_right_x");
        remote_data->fix_height = 1;         //平常=0，=1表示切换成定高/不定高
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
