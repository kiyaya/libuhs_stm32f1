/*
 * main.cpp
 *
 *  Created on: 2014-3-6
 *      Author: kiya
 */

#include <bsp/bsp.h>
#include "ff_test_term.h"

#ifndef USE_UHS20
#include "usb_bsp.h"
#include "usbh_core.h"
#include "usbh_usr.h"
#include "usbh_hid_core.h"

/** @defgroup USBH_USR_MAIN_Private_Variables
* @{
*/
#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*!< IAR Compiler */
    #pragma data_alignment=4
  #endif
#endif /* USB_OTG_HS_INTERNAL_DMA_ENABLED */
__ALIGN_BEGIN USB_OTG_CORE_HANDLE           USB_OTG_Core_dev __ALIGN_END ;

#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*!< IAR Compiler */
    #pragma data_alignment=4
  #endif
#endif /* USB_OTG_HS_INTERNAL_DMA_ENABLED */
__ALIGN_BEGIN USBH_HOST                     USB_Host __ALIGN_END ;
/**
* @}
*/
#else
//#include <library/usb/libuhs20.h>

int uhs_init(void);
#endif

void setup(void) {
	BSP_init();
	printf("\n\rWelcome to USB-Host-Dock project!\n\r");

#ifdef USE_UHS20
	if (uhs_init() != -1)
		xprintf("\nUsb is initialized.\n");
#else
	USBH_Init(&USB_OTG_Core_dev,
#ifdef USE_USB_OTG_FS
			USB_OTG_FS_CORE_ID,
#else
			USB_OTG_HS_CORE_ID,
#endif
			&USB_Host,
			&HID_cb,
			&USR_Callbacks);

#endif
}

int main(void)
{
#ifdef USE_SDCARD
	typedef enum {
		APPSTATE_FF_TERM,
		APPSTATE_TESTMENU,
		APPSTATE_USBHOST
	} AppState;
	AppState appState = APPSTATE_FF_TERM;
#endif
	setup();

	for(;;) {
#ifdef USE_UHS20

		//libuhs_task();

		delay_ms(20);	//delay(10);

#else
		/* Host Task handler */
		USBH_Process(&USB_OTG_Core_dev , &USB_Host);
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
