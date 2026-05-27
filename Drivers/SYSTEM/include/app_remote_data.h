//
// Created by luyi on 2026/5/27.
//

#ifndef REMOTE_TEST_APP_REMOTE_DATA_H
#define REMOTE_TEST_APP_REMOTE_DATA_H
#include <stdint.h>
#include "Int_key.h"
#include "Com_debug.h"

//遥控数据：yaw,pitch,roll等
typedef struct
{
    int16_t throttle;      //参数值有正负; throttle 油门
    int16_t yaw;
    int16_t pitch;
    int16_t roll;
    uint8_t fix_height; //定高
    uint8_t shut;       //关机
}Remote_Data;

void App_Process_Remote_Data(Remote_Data *remote_data);

#endif //REMOTE_TEST_APP_REMOTE_DATA_H
