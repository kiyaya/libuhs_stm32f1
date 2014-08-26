/*
 * main.cpp
 *
 *  Created on: 2014-3-6
 *      Author: kiya
 */

#include <bsp/bsp.h>
#include "ff_test_term.h"
#include "misc_test_term.h"

#include <library/usb/libuhs20.h>

int uhs_init(void);

typedef enum
{
	APPSTATE_FF_TERM,
	APPSTATE_TESTMENU,
	APPSTATE_USBHOST
} AppState;

void setup(void)
{
	BSP_init();
	xprintf("\n\rWelcome to USB-Host-Dock project!\n\r");

	if (uhs_init() != -1)
	{
		xprintf("\nUsb is initialized.\n");
	}

}

int main(void)
{

	AppState appState = APPSTATE_FF_TERM;

	setup();

	for(;;) {

		libuhs_task();

		delay_ms(20);	//delay(10);

		switch ( appState )
		{
			case APPSTATE_FF_TERM:
				/* ff_test_term is not reentrant, blocks until exit */
				if ( !ff_test_term() ) {
					appState = APPSTATE_TESTMENU;
				}
				break;
			case APPSTATE_TESTMENU:
				/* misc_test_term is fully reentrant, main-loop keeps running
				 * but may be throttled by time-consuming routines */
				if ( !misc_test_term() ) {
					appState = APPSTATE_FF_TERM;
				}
				break;
			default:
				appState = APPSTATE_TESTMENU;
				break;
		}

	}

	return 1;
}

int uhs_init(void)
{
	register_libuhs_callback();

	/* --- Hub class --- */
	libuhs_class_hub_init();

	/* --- HID boot class --- */
	/*
	 * --- MSC class ---
	 * Initialize generic storage. This must be done before USB starts.
	 */
	//libuhs_class_msc_init();

	/* --- Printer class --- */
	/* --- CDC FTDI class --- */

	/* --- kernel init --- */
	//return libuhs_kernel_init();

}
