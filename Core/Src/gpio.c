/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitTypeDef gpio_init_struct;
    LED0_GPIO_CLK_ENABLE();                                 /* LED0时钟使能 */
    LED1_GPIO_CLK_ENABLE();                                 /* LED1时钟使能 */

    gpio_init_struct.Pin = LED0_GPIO_PIN;                   /* LED0引脚 */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* 推挽输出 */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* 高速 */
    HAL_GPIO_Init(LED0_GPIO_PORT, &gpio_init_struct);       /* 初始化LED0引脚 */

    gpio_init_struct.Pin = LED1_GPIO_PIN;                   /* LED1引脚 */
    HAL_GPIO_Init(LED1_GPIO_PORT, &gpio_init_struct);       /* 初始化LED1引脚 */


    LED0(1);                                                /* 关闭 LED0 */
    LED1(1);                                                /* 关闭 LED1 */

    //PB2： 5305T定时唤醒
    gpio_init_struct.Pin = POWER_KEY_Pin;
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(POWER_KEY_GPIO_Port, &gpio_init_struct);
    HAL_GPIO_WritePin(POWER_KEY_GPIO_Port, POWER_KEY_Pin, GPIO_PIN_SET);    //初始化=1

    //SI24R1：PA8——EN使能，PA4——NSS片选
    gpio_init_struct.Pin = SI24R1_CE_Pin;
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_LOW;
    HAL_GPIO_Init(SI24R1_CE_GPIO_Port, &gpio_init_struct);
    HAL_GPIO_WritePin(SI24R1_CE_GPIO_Port, SI24R1_CE_Pin, GPIO_PIN_RESET);    //EN初始=0

    gpio_init_struct.Pin = SI24R1_NSS_Pin;
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(SI24R1_NSS_GPIO_Port, &gpio_init_struct);
    HAL_GPIO_WritePin(SI24R1_NSS_GPIO_Port, SI24R1_NSS_Pin, GPIO_PIN_SET);  //NSS初始=1 不片选

    //remote 按键
    /*Configure GPIO pins : KEY_LEFT_X_Pin KEY_RIGHT_X_Pin KEY_DOWN_Pin */
    gpio_init_struct.Pin = KEY_LEFT_X_Pin|KEY_RIGHT_X_Pin|KEY_DOWN_Pin;
    gpio_init_struct.Mode = GPIO_MODE_INPUT;
    gpio_init_struct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOB, &gpio_init_struct);

    /*Configure GPIO pins : KEY_UP_Pin KEY_RIGHT_Pin KEY_LEFT_Pin */
    gpio_init_struct.Pin = KEY_UP_Pin|KEY_RIGHT_Pin|KEY_LEFT_Pin;
    gpio_init_struct.Mode = GPIO_MODE_INPUT;
    gpio_init_struct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &gpio_init_struct);
}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
