/*
 * gpio.h
 *
 *  Created on: 2013-12-29
 *      Author: huihuiyao
 */

#ifndef __GPIO_H
#define __GPIO_H

#include <stm32f10x.h>

#define LED1_ON		GPIO_SetBits(GPIOC, GPIO_Pin_8);
#define LED1_OFF	GPIO_ResetBits(GPIOC, GPIO_Pin_8);
#define LED2_ON		GPIO_SetBits(GPIOC, GPIO_Pin_7);
#define LED2_OFF	GPIO_ResetBits(GPIOC, GPIO_Pin_7);
#define LED3_ON		GPIO_SetBits(GPIOC, GPIO_Pin_6);
#define LED3_OFF	GPIO_ResetBits(GPIOC, GPIO_Pin_6);

typedef enum
{
  LED1 = 0,
  LED2 = 1,
  LED3 = 2,
  LED4 = 3
} Led_TypeDef;


/** @addtogroup STM322xG_EVAL_LOW_LEVEL_LED
  * @{
  */
#define LEDn                             4

#define LED1_PIN                         GPIO_Pin_8
#define LED1_GPIO_PORT                   GPIOC
#define LED1_GPIO_CLK                    RCC_APB2Periph_GPIOC

#define LED2_PIN                         GPIO_Pin_7
#define LED2_GPIO_PORT                   GPIOC
#define LED2_GPIO_CLK                    RCC_APB2Periph_GPIOC

#define LED3_PIN                         GPIO_Pin_6
#define LED3_GPIO_PORT                   GPIOC
#define LED3_GPIO_CLK                    RCC_APB2Periph_GPIOC

#define LED4_PIN                         GPIO_Pin_4
#define LED4_GPIO_PORT                   GPIOD
#define LED4_GPIO_CLK                    RCC_APB2Periph_GPIOD


/**
  * @}
  */
void GPIO_Configuration(void);
void STM_EVAL_LEDInit(Led_TypeDef Led);
void STM_EVAL_LEDOn(Led_TypeDef Led);
void STM_EVAL_LEDOff(Led_TypeDef Led);
void STM_EVAL_LEDToggle(Led_TypeDef Led);

#endif

/**********************************END OF FILE**********************************/
