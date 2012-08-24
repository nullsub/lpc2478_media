
#ifndef _LEDS_H_
#define _LEDS_H_

#include "FreeRTOS.h"
#include "task.h"




/////////////////////////////////////////////////////////////////////////////////////////
/**
* Author: Steffen Graf
* Date: 15.11.09
* Version: 1.0
* Description: I thinks it's self explaining
**/

#include "lpc24xx.h"

#define RED_LED_ACTIVE()	FIO2DIR |= (1<<27); 	
#define RED_LED_ON()		FIO2SET |= (1<<27)
#define RED_LED_OFF()		FIO2CLR |= (1<<27)

#define GREEN_LED_ACTIVE()	FIO2DIR |= (1<<26)	
#define GREEN_LED_ON()		FIO2SET |= (1<<26)
#define GREEN_LED_OFF()		FIO2CLR |= (1<<26)

#define BLUE_LED_ACTIVE()	FIO2DIR |= (1<<25)	
#define BLUE_LED_ON()		FIO2SET |= (1<<25)
#define BLUE_LED_OFF()		FIO2CLR |= (1<<25)

#define ALL_LED_ACTIVE()	FIO2DIR |= (1<<27);FIO2DIR |= (1<<26);FIO2DIR |= (1<<25)
#define ALL_LED_ON()		FIO2SET |= (1<<27);FIO2SET |= (1<<26);FIO2SET |= (1<<25)
#define ALL_LED_OFF()		FIO2CLR |= (1<<27);FIO2CLR |= (1<<26);FIO2CLR |= (1<<25)

#define RED_LED_TOGGLE()	if(FIO2PIN & (1<<27)) RED_LED_OFF(); else RED_LED_ON();
#define GREEN_LED_TOGGLE()	if(FIO2PIN & (1<<26)) GREEN_LED_OFF(); else GREEN_LED_ON();
#define BLUE_LED_TOGGLE()	if(FIO2PIN & (1<<25)) BLUE_LED_OFF(); else BLUE_LED_ON();


//////////////////////////////////////////////////////////////////////////////////////////






#define LEDS_LED18        18            // The IO pin that the LED is attached to P1.18
#define LEDS_LED13        13            // The IO pin that the LED is attached to P1.13
#define LEDS_REG_IOPIN  IOPIN1  // IOPIN register corresponding to LEDS_LED pin
#define LEDS_REG_IODIR  IODIR1  // IODIR register corresponding to LEDS_LED pin
#define LEDS_REG_IOSET  IOSET1  // IOSET register corresponding to LEDS_LED pin
#define LEDS_REG_IOCLR  IOCLR1  // IOCLR register corresponding to LEDS_LED pin


void led_task(void *);


#endif
