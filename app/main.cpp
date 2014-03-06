/*
 * main.cpp
 *
 *  Created on: 2014-3-6
 *      Author: kiya
 */

#include "bsp.h"

#ifdef USE_UHS20
#include "Usb.h"
#include "usbhub.h"

USB_OTG_CORE_HANDLE USB_OTG_Core_dev;
USB Usb(&USB_OTG_Core_dev);
USBHub Hub(&Usb);
#endif

void setup(void) {
	BSP_init();
	printf("\n\rWelcome to USB-Host-Dock project!\n\r");

#ifdef USE_UHS20
	if (Usb.Init() != -1)
		printf("\nUsb is initialized.\n");
#endif
}

int main(void)
{
	setup();

	for(;;) {
#ifdef USE_UHS20
		Usb.Task(&USB_OTG_Core_dev);
#else
		LED1_ON;	delay_ms(500);
		LED2_ON;	delay_ms(500);
		LED3_ON;	delay_ms(500);
		delay_ms(500);
		LED1_OFF;	delay_ms(500);
		LED2_OFF;	delay_ms(500);
		LED3_OFF;	delay_ms(500);
		delay_ms(500);

		printf("\ntime:%d", millis());
#endif
	}

	return 1;
}

