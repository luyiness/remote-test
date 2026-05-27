//
// Created by luyi on 2026/5/27.
//

#include "app_remote_data.h"

void App_Process_Remote_Data(Remote_Data *remote_data)
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
        break;
    default:
        debug_printfln("unknown key");
        break;
    }
}