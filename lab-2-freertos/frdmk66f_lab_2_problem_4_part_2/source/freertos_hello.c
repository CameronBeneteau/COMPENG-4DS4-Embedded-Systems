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
#include "semphr.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define LEFT_BIT (1 << 0)
#define RIGHT_BIT (1 << 1)
#define UP_BIT (1 << 2)
#define DOWN_BIT (1 << 3)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

void producer_event(void *pvParameters)
{

	SemaphoreHandle_t *semaphores = (SemaphoreHandle_t *)pvParameters;
	SemaphoreHandle_t l_semaphore = semaphores[0];
	SemaphoreHandle_t r_semaphore = semaphores[1];
	SemaphoreHandle_t u_semaphore = semaphores[2];
	SemaphoreHandle_t d_semaphore = semaphores[3];
	BaseType_t status;
	char c;

	while (1)
	{
		scanf("%c", &c);

		switch (c)
		{
		case 'a':
			xSemaphoreGive(l_semaphore);
			break;
		case 's':
			xSemaphoreGive(d_semaphore);
			break;
		case 'd':
			xSemaphoreGive(r_semaphore);
			break;
		case 'w':
			xSemaphoreGive(u_semaphore);
			break;
		}
	}
}

void consumer_left(void *pvParameters)
{
	SemaphoreHandle_t *semaphores = (SemaphoreHandle_t *)pvParameters;
	SemaphoreHandle_t semaphore = semaphores[0];
	BaseType_t status;

	while (1)
	{
		status = xSemaphoreTake(semaphore, portMAX_DELAY);
		if (status != pdPASS)
		{
			PRINTF("Failed to acquire semaphore\r\n");
			while (1)
				;
		}

		PRINTF("LEFT\r\n");
	}
}

void consumer_right(void *pvParameters)
{
	SemaphoreHandle_t *semaphores = (SemaphoreHandle_t *)pvParameters;
	SemaphoreHandle_t semaphore = semaphores[1];
	BaseType_t status;

	while (1)
	{
		status = xSemaphoreTake(semaphore, portMAX_DELAY);
		if (status != pdPASS)
		{
			PRINTF("Failed to acquire semaphore\r\n");
			while (1)
				;
		}

		PRINTF("RIGHT\r\n");
	}
}

void consumer_up(void *pvParameters)
{
	SemaphoreHandle_t *semaphores = (SemaphoreHandle_t *)pvParameters;
	SemaphoreHandle_t semaphore = semaphores[2];
	BaseType_t status;

	while (1)
	{
		status = xSemaphoreTake(semaphore, portMAX_DELAY);
		if (status != pdPASS)
		{
			PRINTF("Failed to acquire semaphore\r\n");
			while (1)
				;
		}

		PRINTF("UP\r\n");
	}
}

void consumer_down(void *pvParameters)
{
	SemaphoreHandle_t *semaphores = (SemaphoreHandle_t *)pvParameters;
	SemaphoreHandle_t semaphore = semaphores[3];
	BaseType_t status;

	while (1)
	{
		status = xSemaphoreTake(semaphore, portMAX_DELAY);
		if (status != pdPASS)
		{
			PRINTF("Failed to acquire semaphore\r\n");
			while (1)
				;
		}

		PRINTF("DOWN\r\n");
	}
}

int main(void)
{
	BaseType_t status;
	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitDebugConsole();

	SemaphoreHandle_t *semaphores = (SemaphoreHandle_t *)malloc(4 * sizeof(SemaphoreHandle_t));
	semaphores[0] = xSemaphoreCreateBinary();
	semaphores[1] = xSemaphoreCreateBinary();
	semaphores[2] = xSemaphoreCreateBinary();
	semaphores[3] = xSemaphoreCreateBinary();

	status = xTaskCreate(producer_event, "producer", 200, (void *)semaphores, 2, NULL);
	if (status != pdPASS)
	{
		PRINTF("Task creation failed!.\r\n");
		while (1)
			;
	}

	status = xTaskCreate(consumer_left, "consumer_left", 200, (void *)semaphores, 3, NULL);
	if (status != pdPASS)
	{
		PRINTF("Task creation failed!.\r\n");
		while (1)
			;
	}

	status = xTaskCreate(consumer_right, "consumer_right", 200, (void *)semaphores, 3, NULL);
	if (status != pdPASS)
	{
		PRINTF("Task creation failed!.\r\n");
		while (1)
			;
	}

	status = xTaskCreate(consumer_up, "consumer_up", 200, (void *)semaphores, 3, NULL);
	if (status != pdPASS)
	{
		PRINTF("Task creation failed!.\r\n");
		while (1)
			;
	}

	status = xTaskCreate(consumer_down, "consumer_down", 200, (void *)semaphores, 3, NULL);
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
