//
// Created by luyi on 2026/5/18.
//

#include "include/freertos_task.h"

TaskHandle_t printf_task_handle;
TaskHandle_t power_task_handle;
TaskHandle_t communicate_task_handle;
TaskHandle_t key_task_handle;
TaskHandle_t joystick_task_handle;

Remote_Data remote_data  = {0};

void printf_task(void *pvParameters)
{
    uint32_t tick = xTaskGetTickCount();        //获取OS的时间
    while (1)
    {
        // debug_printfln("Hello World");
        lcd_show_string(15, 110, 200, 24, 24, "printf_task ...", BLUE);
        vTaskDelayUntil(&tick, printf_task_period);
    }
}

void power_task(void *pvParameters)
{
    //定时启动一次IP5305T，防止自动关机
    uint32_t tick = xTaskGetTickCount();
    while (1)
    {
        int_ip5305t_start();
        vTaskDelayUntil(&tick, power_task_period);
    }
}

void communicate_task(void *pvParameters)
{
    Int_SI24R1_Init();
    uint32_t tick = xTaskGetTickCount();

    uint8_t tx_buff[32] = {0};      //发送数据的数组
    //测试：
    tx_buff[0] = 'h';
    tx_buff[1] = 'e';
    tx_buff[2] = 'l';
    tx_buff[3] = 'l';
    tx_buff[4] = 'o';

    while (1)
    {
        uint8_t result =  Int_SI24R1_TxPacket(tx_buff);
        if (result == 0)
        {
            debug_printfln("success");
        }
        vTaskDelayUntil(&tick, communicate_task_period);
    }
}

void key_task(void *pvParameters)
{
    uint32_t tick = xTaskGetTickCount();
    while (1)
    {
        App_Process_Key_Data(&remote_data);
        vTaskDelayUntil(&tick, key_task_period);
    }
}

void joystick_task(void *pvParameters)
{
    Int_joystick_init();
    uint32_t tick = xTaskGetTickCount();
    while (1)
    {
        App_Process_Joystick_Data(&remote_data);
        vTaskDelayUntil(&tick, joystick_task_period);
    }
}

void Freertos_start(void)
{
    xTaskCreate(printf_task, "printf_task", printf_task_stacksize, NULL,
        printf_task_priority, &printf_task_handle);

    //power
    xTaskCreate(power_task, "power_task", power_task_stacksize, NULL,
        power_task_priority, &power_task_handle);

    //communicate
    xTaskCreate(communicate_task, "communicate_task", communicate_task_stacksize, NULL,
        communicate_task_priority, &communicate_task_handle);

    //key
    xTaskCreate(key_task, "key_task", key_task_stacksize, NULL,
        key_task_priority, &key_task_handle);

    //joystick
    xTaskCreate(joystick_task, "joystick_task", joystick_task_stacksize, NULL,
        joystick_task_priority, &joystick_task_handle);

    vTaskStartScheduler();
}