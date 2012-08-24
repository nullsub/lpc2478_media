
#include <stdio.h>
#include "FreeRTOS.h"

#include "leds.h"


void led_task(void * params)
{
	ALL_LED_ACTIVE();
	ALL_LED_OFF();

	for (;;) {
		BLUE_LED_TOGGLE();
		vTaskDelay(100);
	}

}

