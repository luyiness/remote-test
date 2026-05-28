//
// Created by luyi on 2026/5/27.
//

#ifndef REMOTE_TEST_APP_COMMUNICATION_H
#define REMOTE_TEST_APP_COMMUNICATION_H

#include "com_type.h"
#include "SI24R1.h"

#define HEAD_FRAME_0 'A'
#define HEAD_FRAME_1 'B'
#define HEAD_FRAME_2 'C'

void app_comm_send_data(Remote_Data *data);

#endif //REMOTE_TEST_APP_COMMUNICATION_H
