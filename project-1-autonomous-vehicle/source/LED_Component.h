#ifndef LED_COMPONENT_H
#define LED_COMPONENT_H

#include "pin_mux.h"
#include "fsl_port.h"
#include "fsl_ftm.h"
#include "fsl_debug_console.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "Motor_Control_Component.h"
#include "Terminal_Component.h"

#include <stdarg.h>

#define FTM_LED FTM3
#define FTM_RED_CHANNEL	  // Define red LED channel
#define FTM_GREEN_CHANNEL // Define green LED channel
#define FTM_BLUE_CHANNEL  // Define blue LED channel

extern QueueHandle_t led_queue;

typedef struct
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} LED_PWM;

void setupLEDComponent();
void setupLEDs();
void setupLEDPins();
void convertModeToPWM(uint8_t mode, LED_PWM *led_pwm);

void ledTask(void *pvParameters);

#endif /* TERMINAL_COMPONENT_H */
