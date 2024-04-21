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

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

int counter = 0;

void producer_sem(void *pvParameters)
{
	SemaphoreHandle_t *semaphores = (SemaphoreHandle_t *)pvParameters;
	SemaphoreHandle_t consumer_semaphore = semaphores[0];
	SemaphoreHandle_t producer_semaphore = semaphores[1];
	BaseType_t status1, status2;

	while (1)
	{
		status1 = xSemaphoreTake(consumer_semaphore, portMAX_DELAY);
		status2 = xSemaphoreTake(consumer_semaphore, portMAX_DELAY);
		if (status1 != pdPASS || status2 != pdPASS)
		{
			PRINTF("Failed to acquire consumer_semaphore\r\n");
			while (1)
				;
		}

		counter++;
		xSemaphoreGive(producer_semaphore);
		xSemaphoreGive(producer_semaphore);

		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void consumer1_sem(void *pvParameters)
{
	SemaphoreHandle_t *semaphores = (SemaphoreHandle_t *)pvParameters;
	SemaphoreHandle_t consumer_semaphore = semaphores[0];
	SemaphoreHandle_t producer_semaphore = semaphores[1];
	BaseType_t status;

	while (1)
	{
		xSemaphoreGive(consumer_semaphore);

		// Delay so semaphore does not take twice
		vTaskDelay(100 / portTICK_PERIOD_MS);

		status = xSemaphoreTake(producer_semaphore, portMAX_DELAY);
		if (status != pdPASS)
		{
			PRINTF("Failed to acquire producer_semaphore\r\n");
			while (1)
				;
		}

		PRINTF("Consumer 1 Received Value = %d\r\n", counter);
	}
}

void consumer2_sem(void *pvParameters)
{
	SemaphoreHandle_t *semaphores = (SemaphoreHandle_t *)pvParameters;
	SemaphoreHandle_t consumer_semaphore = semaphores[0];
	SemaphoreHandle_t producer_semaphore = semaphores[1];
	BaseType_t status;

	while (1)
	{
		xSemaphoreGive(consumer_semaphore);

		// Delay so semaphore does not take twice
		vTaskDelay(100 / portTICK_PERIOD_MS);

		status = xSemaphoreTake(producer_semaphore, portMAX_DELAY);
		if (status != pdPASS)
		{
			PRINTF("Failed to acquire producer_semaphore\r\n");
			while (1)
				;
		}

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

	SemaphoreHandle_t *semaphores = (SemaphoreHandle_t *)malloc(2 * sizeof(SemaphoreHandle_t));
	semaphores[0] = xSemaphoreCreateCounting(2, 2); // consumer_sem
	semaphores[1] = xSemaphoreCreateCounting(2, 0); // producer_sem

	status = xTaskCreate(producer_sem, "producer", 200, (void *)semaphores, 2, NULL);
	if (status != pdPASS)
	{
		PRINTF("Task creation failed!.\r\n");
		while (1)
			;
	}

	status = xTaskCreate(consumer1_sem, "consumer", 200, (void *)semaphores, 2, NULL);
	if (status != pdPASS)
	{
		PRINTF("Task creation failed!.\r\n");
		while (1)
			;
	}

	status = xTaskCreate(consumer2_sem, "consumer", 200, (void *)semaphores, 2, NULL);
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
