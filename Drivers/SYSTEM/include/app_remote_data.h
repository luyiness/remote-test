//
// Created by luyi on 2026/5/27.
//

#ifndef REMOTE_TEST_APP_REMOTE_DATA_H
#define REMOTE_TEST_APP_REMOTE_DATA_H
#include "com_type.h"
#include "Int_key.h"
#include "Com_debug.h"
#include "Int_joystick.h"

void App_Process_Key_Data(Remote_Data *remote_data);

void App_Process_Joystick_Data(Remote_Data *rd);

#define LIMIT(x,min,max) (x < min ? min : (x > max ? max : x))

#endif //REMOTE_TEST_APP_REMOTE_DATA_H
