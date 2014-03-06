/*
 * main.cpp
 *
 *  Created on: 2013-6-3
 *      Author: Hz
 */

#include "bsp.h"

void setup(void) {
	BSP_init();

	printf("\n\rWelcome to USB-Host-Dock project!\n\r");
}

int main(void)
{
	setup();

	for(;;) {

		LED1_ON;	delay_ms(500);
		LED2_ON;	delay_ms(500);
		LED3_ON;	delay_ms(500);
		delay_ms(500);
		LED1_OFF;	delay_ms(500);
		LED2_OFF;	delay_ms(500);
		LED3_OFF;	delay_ms(500);
		delay_ms(500);

		printf("\ntime:%d", millis());
	}

	return 1;
}

