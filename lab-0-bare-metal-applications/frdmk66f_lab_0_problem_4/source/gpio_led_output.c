/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_gpio.h"
#include "gpio_led_output.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief delay a while.
 */
void delay(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

void delay(void)
{
	volatile uint32_t i = 0;

	for (i = 0; i < 8000000; ++i)
	{
		__asm("NOP"); /* delay */
	}
}

void PinClockMuxEnable()
{
	CLOCK_EnableClock(kCLOCK_PortC);
	CLOCK_EnableClock(kCLOCK_PortD);

	PORT_SetPinMux(PORTC, 8U, kPORT_MuxAsGpio);
	PORT_SetPinMux(PORTC, 9U, kPORT_MuxAsGpio);
	PORT_SetPinMux(PORTD, 1U, kPORT_MuxAsGpio);
}

void PinInit(GPIO_Struct *base, uint32_t pin, const gpio_pin_config_t *config)
{
	assert(NULL != config);

	if (config->pinDirection == kGPIO_DigitalInput)
	{
		base->PDDR &= (~(1UL << pin));
	}
	else
	{
		base->PDDR |= (1UL << pin);
	}
}

void PortToggle(GPIO_Struct *base, uint32_t mask)
{
	base->PTOR = (1U << mask);
}

/*!
 * @brief Main function
 */

int main(void)
{
	/* Define the init structure for the output LED pin*/
	gpio_pin_config_t led_config = {
		kGPIO_DigitalOutput,
		0,
	};

	/* Board pin, clock, debug console init */
	// BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitDebugConsole();

	/* Print a note to terminal. */
	PRINTF("\r\n GPIO Driver example\r\n");
	PRINTF("\r\n The LED is blinking.\r\n");

	// Enable port clocks and muxes
	PinClockMuxEnable();

	// Init output LED GPIOs
	PinInit(BOARD_LED_GPIO_C, BOARD_LED_GPIO_PIN_BLUE, &led_config);
	PinInit(BOARD_LED_GPIO_C, BOARD_LED_GPIO_PIN_GREEN, &led_config);
	PinInit(BOARD_LED_GPIO_D, BOARD_LED_GPIO_PIN_RED, &led_config);

	while (1)
	{
		delay();
		PortToggle(BOARD_LED_GPIO_C, BOARD_LED_GPIO_PIN_BLUE);
		delay();
		PortToggle(BOARD_LED_GPIO_C, BOARD_LED_GPIO_PIN_BLUE);
		PortToggle(BOARD_LED_GPIO_C, BOARD_LED_GPIO_PIN_GREEN);
		delay();
		PortToggle(BOARD_LED_GPIO_C, BOARD_LED_GPIO_PIN_GREEN);
		PortToggle(BOARD_LED_GPIO_D, BOARD_LED_GPIO_PIN_RED);
		delay();
		PortToggle(BOARD_LED_GPIO_D, BOARD_LED_GPIO_PIN_RED);
	}
}
