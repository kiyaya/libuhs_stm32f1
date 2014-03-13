/*
 * bsp.c
 *
 *  Created on: 2014-3-6
 *      Author: kiya
 */

#ifndef _bsp_h_
#define _bsp_h_
#ifdef __cplusplus
 extern "C" {
#endif

 /* --- includes. --- */
#include <stdbool.h>
#include "misc.h" /* High level functions for NVIC and SysTick (add-on to CMSIS functions) */

#include "stm32f10x.h"
#include "stm3210c_eval.h"
#include "comm.h"

#ifdef USE_SDCARD
#include "rtc.h"
#include "ff_test_term.h"
//#include "misc_test_term.h"
#endif
/* External function prototypes (defined in syscalls.c) */
extern int printf(const char *fmt, ...);

/* --- Function declaration --- */
void BSP_init(void);

/* --- Delay definition --- */

uint32_t millis(void);
__inline void delay_ms(uint32_t count) {
	uint32_t end_time = millis() + count;	// + (count >> 1);
	while(end_time - millis());
}
__inline void delay_us(uint32_t count) {
	count = count * (SystemCoreClock / 1000000);
	for(; count > 0; count--);
}
#define delay delay_ms

/* --- GPIO definition --- */
#define LED1_ON		GPIO_SetBits(GPIOC, GPIO_Pin_8);
#define LED1_OFF	GPIO_ResetBits(GPIOC, GPIO_Pin_8);
#define LED2_ON		GPIO_SetBits(GPIOC, GPIO_Pin_7);
#define LED2_OFF	GPIO_ResetBits(GPIOC, GPIO_Pin_7);
#define LED3_ON		GPIO_SetBits(GPIOC, GPIO_Pin_6);
#define LED3_OFF	GPIO_ResetBits(GPIOC, GPIO_Pin_6);

void GPIO_Configuration(void);

/* --- Compiler related --- */
void __cxa_pure_virtual(void);
//#define __init      __attribute__ ((__section__ (".init.text")))


#ifdef __cplusplus
}
#endif
#endif
