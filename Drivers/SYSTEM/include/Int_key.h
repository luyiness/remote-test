//
// Created by luyi on 2026/5/26.
//

#ifndef REMOTE_TEST_INT_KEY_H
#define REMOTE_TEST_INT_KEY_H

#include "gpio.h"
#include "FreeRTOS.h"
#include "task.h"

typedef enum
{
    KEY_NONE,
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_LEFT_X,
    KEY_RIGHT_X,
}KEY_TypeDef;

#define READ_KEY_LEFT (HAL_GPIO_ReadPin(KEY_LEFT_GPIO_Port, KEY_LEFT_Pin))
#define READ_KEY_RIGHT (HAL_GPIO_ReadPin(KEY_RIGHT_GPIO_Port, KEY_RIGHT_Pin))
#define READ_KEY_UP (HAL_GPIO_ReadPin(KEY_UP_GPIO_Port, KEY_UP_Pin))
#define READ_KEY_DOWN (HAL_GPIO_ReadPin(KEY_DOWN_GPIO_Port, KEY_DOWN_Pin))
#define READ_KEY_LEFT_X (HAL_GPIO_ReadPin(KEY_LEFT_X_GPIO_Port, KEY_LEFT_X_Pin))
#define READ_KEY_RIGHT_X (HAL_GPIO_ReadPin(KEY_RIGHT_X_GPIO_Port, KEY_RIGHT_X_Pin))

KEY_TypeDef int_key_scan(void);

#endif //REMOTE_TEST_INT_KEY_H
