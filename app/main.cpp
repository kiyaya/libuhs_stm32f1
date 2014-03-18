/*
 * main.cpp
 *
 *  Created on: 2014-3-6
 *      Author: kiya
 */

#include "bsp.h"
#include "ff_test_term.h"

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
#ifdef USE_SDCARD
	typedef enum { APPSTATE_FF_TERM, APPSTATE_TESTMENU } AppState;
	AppState appState = APPSTATE_FF_TERM;
#endif
	setup();

	for(;;) {
#ifdef USE_UHS20
		Usb.Task(&USB_OTG_Core_dev);
#endif

#if 0	// @huihuiyao, un-mask if flash led.
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

#ifdef USE_SDCARD

		switch ( appState ) {
		case APPSTATE_FF_TERM:
			/* ff_test_term is not reentrant, blocks until exit */
			if ( !ff_test_term() ) {
				appState = APPSTATE_TESTMENU;
			}
			break;
		case APPSTATE_TESTMENU:
			/* misc_test_term is fully reentrant, main-loop keeps running
			 * but may be throttled by time-consuming routines */
			//if ( !misc_test_term() ) {
			//	appState = APPSTATE_FF_TERM;
			//}
			break;
		default:
			appState = APPSTATE_TESTMENU;
			break;
		}
#endif
	}

	return 1;
}

