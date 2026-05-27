//
// Created by luyi on 2026/5/27.
//

#ifndef REMOTE_TEST_INT_JOYSTICK_H
#define REMOTE_TEST_INT_JOYSTICK_H

#include "adc.h"
#include "app_remote_data.h"

void Int_joystick_init(void);

void Int_joystick_scan(Remote_Data *remote_data);

#endif //REMOTE_TEST_INT_JOYSTICK_H
