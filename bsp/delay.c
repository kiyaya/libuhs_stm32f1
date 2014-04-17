/*
 * delay.c
 *
 *  Created on: 2013-12-29
 *      Author: huihuiyao
 */

#include "delay.h"

static uint32_t tick_time = 0;

uint32_t millis(void) {
	return tick_time;
}

void delay_tick_calc(void) {
	tick_time++;
}
/*
__IO uint32_t TimingDelay;

void delay(__IO uint32_t nCount)
{
	while(nCount--)
	{
	}
}

void delay_ms(__IO uint32_t nTime)
{
  TimingDelay = nTime;
  while(TimingDelay != 0);
}
*/

__inline void delay_ms(uint32_t count) {
	uint32_t end_time = millis() + count;	// + (count >> 1);
	while(end_time - millis());
}
__inline void delay_us(uint32_t count) {
	count = count * (SystemCoreClock / 1000000);
	for(; count > 0; count--);
}

/**********************************END OF FILE**********************************/
