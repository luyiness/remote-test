//
// Created by luyi on 2026/5/26.
//

#include "Int_key.h"


//检测6个按键是否按下
KEY_TypeDef int_key_scan(void)
{
    //检测KEY_UP按键是否按下
    if (READ_KEY_UP == GPIO_PIN_RESET)
    {
        //进入if就是按下了，进行消抖：
        vTaskDelay(10);
        if (READ_KEY_UP == GPIO_PIN_RESET)  //确认是按下了
        {
            //等待抬起按键
            while (READ_KEY_UP == GPIO_PIN_RESET)
                ;
            return KEY_UP;
        }
    }

    //检测KEY_DOWN按键是否按下
    if (READ_KEY_DOWN == GPIO_PIN_RESET)
    {
        vTaskDelay(10);
        if (READ_KEY_DOWN == GPIO_PIN_RESET)
        {
            while (READ_KEY_DOWN == GPIO_PIN_RESET)
                ;
            return KEY_DOWN;
        }
    }

    //检测KEY_LEFT按键是否按下
    if (READ_KEY_LEFT == GPIO_PIN_RESET)
    {
        vTaskDelay(10);
        if (READ_KEY_LEFT == GPIO_PIN_RESET)
        {
            while (READ_KEY_LEFT == GPIO_PIN_RESET)
                ;
            return KEY_LEFT;
        }
    }

    //检测KEY_RIGHT按键是否按下
    if (READ_KEY_RIGHT == GPIO_PIN_RESET)
    {
        vTaskDelay(10);
        if (READ_KEY_RIGHT == GPIO_PIN_RESET)
        {
            while (READ_KEY_RIGHT == GPIO_PIN_RESET)
                ;
            return KEY_RIGHT;
        }
    }

    //检测KEY_LEFT_X按键是否按下
    if (READ_KEY_LEFT_X == GPIO_PIN_RESET)
    {
        uint32_t start = xTaskGetTickCount();
        vTaskDelay(10);
        if (READ_KEY_LEFT_X == GPIO_PIN_RESET)
        {
            while (READ_KEY_LEFT_X == GPIO_PIN_RESET)
                ;
            if (xTaskGetTickCount() - start > 500)
            {
                return KEY_LEFT_X_HOLD;
            }
            return KEY_LEFT_X;
        }
    }

    //检测KEY_RIGHT_X按键是否按下
    if (READ_KEY_RIGHT_X == GPIO_PIN_RESET)
    {
        uint32_t start = xTaskGetTickCount();
        vTaskDelay(10);
        if (READ_KEY_RIGHT_X == GPIO_PIN_RESET)
        {
            while (READ_KEY_RIGHT_X == GPIO_PIN_RESET)
                ;
            if (xTaskGetTickCount() - start > 500)
            {
                return KEY_RIGHT_X_HOLD;
            }
            return KEY_RIGHT_X;
        }
    }


    return KEY_NONE;
}
