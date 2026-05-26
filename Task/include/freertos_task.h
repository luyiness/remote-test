//
// Created by luyi on 2026/5/18.
//

#ifndef QUAD_TEST_TASK_H
#define QUAD_TEST_TASK_H

#include "Com_debug.h"

#include "FreeRTOS.h"
#include "task.h"
#include "ip5305t.h"
#include "util.h"
#include "SI24R1.h"
#include "Int_key.h"

//printf task
void printf_task(void *pvParameters);
#define printf_task_priority 2
#define printf_task_stacksize 128
#define printf_task_period 1000     //delay time

//power task
void power_task(void *pvParameters);
#define power_task_priority 3
#define power_task_stacksize 128
#define power_task_period 10000      //可设<24s，这里设为10s

//communication task
void communicate_task(void *pvParameters);
#define communicate_task_priority 4
#define communicate_task_stacksize 128
#define communicate_task_period 6

//key task
void key_task(void *pvParameters);
#define key_task_priority 4
#define key_task_stacksize 128
#define key_task_period 10

void Freertos_start(void);


#endif //QUAD_TEST_TASK_H
