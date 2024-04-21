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

#define MAX_LEN 20

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

char str[MAX_LEN];
char strCap[MAX_LEN];

void task_1(void *pvParameters)
{
	SemaphoreHandle_t semaphore = ((SemaphoreHandle_t *)pvParameters)[0];

	PRINTF("Input string (lower case letters only)\r\n");
	scanf("%s", str);
	PRINTF("Input received\r\n");
	xSemaphoreGive(semaphore);

	vTaskDelete(NULL);
}

void task_2(void *pvParameters)
{
	SemaphoreHandle_t semaphore = ((SemaphoreHandle_t *)pvParameters)[0];
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

		PRINTF("%s\r\n", str);
		xSemaphoreGive(semaphore);

		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}

	vTaskDelete(NULL);
}

void task_3(void *pvParameters)
{
	SemaphoreHandle_t semaphore = ((SemaphoreHandle_t *)pvParameters)[0];
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

		for (int i = 0; i < strlen(str); i++)
		{
			strCap[i] = str[i] - 32;
		}

		PRINTF("%s\r\n", strCap);
		xSemaphoreGive(semaphore);

		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}

	vTaskDelete(NULL);
}

int main(void)
{
	BaseType_t status;

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitDebugConsole();

	SemaphoreHandle_t *semaphore = (SemaphoreHandle_t *)malloc(sizeof(SemaphoreHandle_t));
	semaphore[0] = xSemaphoreCreateBinary();

	status = xTaskCreate(task_1, "Task 1", 200, (void *)semaphore, 2, NULL);
	if (status != pdPASS)
	{
		PRINTF("Task creation failed!.\r\n");
		while (1)
			;
	}

	status = xTaskCreate(task_2, "Task 2", 200, (void *)semaphore, 3, NULL);
	if (status != pdPASS)
	{
		PRINTF("Task creation failed!.\r\n");
		while (1)
			;
	}

	status = xTaskCreate(task_3, "Task 3", 200, (void *)semaphore, 3, NULL);
	if (status != pdPASS)
	{
		PRINTF("Task creation failed!.\r\n");
		while (1)
			;
	}

	vTaskStartScheduler();
	for (;;)
		;
}
