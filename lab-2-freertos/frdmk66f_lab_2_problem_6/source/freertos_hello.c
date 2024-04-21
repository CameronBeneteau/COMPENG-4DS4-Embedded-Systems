/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

/* Freescale includes. */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

#include "semphr.h"
#include "timers.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

SemaphoreHandle_t semaphore;

void timerCallbackFunction(TimerHandle_t timer_handle)
{
	xSemaphoreGive(semaphore);
}

static void hello_task(void *pvParameters)
{
	while (1)
	{
		xSemaphoreTake(semaphore, portMAX_DELAY);
		PRINTF("Hello world.\r\n");
	}
}

int main(void)
{
	BaseType_t status;

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitDebugConsole();

	semaphore = xSemaphoreCreateBinary();

	status = xTaskCreate(hello_task, "Hello_task", 200, NULL, 2, NULL);
	if (status != pdPASS)
	{
		PRINTF("Task creation failed!.\r\n");
		while (1)
			;
	}

	TimerHandle_t timer_handle = xTimerCreate("Periodic timer", 1000 / portTICK_PERIOD_MS, pdTRUE, NULL, timerCallbackFunction);

	status = xTimerStart(timer_handle, 0);
	if (status != pdPASS)
	{
		PRINTF("Couldn’t start the timer!.\r\n");
		while (1)
			;
	}

	vTaskStartScheduler();
	while (1)
	{
	}
}
