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

#include "event_groups.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define C1_BIT (1 << 0)
#define C2_BIT (1 << 1)
#define P1_BIT (1 << 2)
#define P2_BIT (1 << 3)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

int counter = 0;

void producer_sem(void *pvParameters)
{
	EventGroupHandle_t event_group = (EventGroupHandle_t)pvParameters;
	EventBits_t bits;

	while (1)
	{

		xEventGroupWaitBits(event_group, C1_BIT | C2_BIT, pdTRUE, pdTRUE, portMAX_DELAY);

		counter++;

		xEventGroupSetBits(event_group, P1_BIT);
		xEventGroupSetBits(event_group, P2_BIT);

		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void consumer1_sem(void *pvParameters)
{
	EventGroupHandle_t event_group = (EventGroupHandle_t)pvParameters;

	while (1)
	{
		xEventGroupSetBits(event_group, C1_BIT);
		xEventGroupWaitBits(event_group, P1_BIT, pdTRUE, pdTRUE, portMAX_DELAY);
		PRINTF("Consumer 1 Received Value = %d\r\n", counter);
	}
}

void consumer2_sem(void *pvParameters)
{
	EventGroupHandle_t event_group = (EventGroupHandle_t)pvParameters;

	while (1)
	{
		xEventGroupSetBits(event_group, C2_BIT);
		xEventGroupWaitBits(event_group, P2_BIT, pdTRUE, pdTRUE, portMAX_DELAY);
		PRINTF("Consumer 2 Received Value = %d\r\n", counter);
	}
}

int main(void)
{
	BaseType_t status;

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitDebugConsole();

	EventGroupHandle_t event_group = xEventGroupCreate();

	status = xTaskCreate(producer_sem, "producer_sem", 200, (void *)event_group, 2, NULL);
	if (status != pdPASS)
	{
		PRINTF("Task creation failed!.\r\n");
		while (1)
			;
	}

	status = xTaskCreate(consumer1_sem, "consumer1_sem", 200, (void *)event_group, 2, NULL);
	if (status != pdPASS)
	{
		PRINTF("Task creation failed!.\r\n");
		while (1)
			;
	}

	status = xTaskCreate(consumer2_sem, "consumer2_sem", 200, (void *)event_group, 2, NULL);
	if (status != pdPASS)
	{
		PRINTF("Task creation failed!.\r\n");
		while (1)
			;
	}

	vTaskStartScheduler();
	while (1)
	{
	}
}
