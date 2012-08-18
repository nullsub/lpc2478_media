
#include <stdio.h>
#include "FreeRTOS.h"


#include "leds.h"


static portTASK_FUNCTION(vLEDTask, pvParameters __attribute__((unused)))
{
	ALL_LED_ACTIVE();
	ALL_LED_OFF();

  for (;;)
  {

		BLUE_LED_TOGGLE();
		vTaskDelay(100);
  }

}


signed portBASE_TYPE ledsTaskStart (void)
{
  return xTaskCreate (vLEDTask,  (const signed portCHAR * const) "LED", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
}
