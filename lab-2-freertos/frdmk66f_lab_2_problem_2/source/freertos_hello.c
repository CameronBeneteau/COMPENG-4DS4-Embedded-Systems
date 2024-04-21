/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "string.h"

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
char receivedStr[MAX_LEN];
int strLen;

void producer_queue(void *pvParameters)
{
	QueueHandle_t queue1 = (QueueHandle_t)pvParameters;
	BaseType_t status;
	int counter = 0;

	PRINTF("Input string\r\n");
	scanf("%s", str);
	strLen = strlen(str);
	PRINTF("Input received\r\n");

	while (1)
	{
		if (counter < strLen)
		{
			status = xQueueSendToBack(queue1, (void *)&str[counter], portMAX_DELAY);
			counter++;
			if (status != pdPASS)
			{
				PRINTF("Queue Send failed!.\r\n");
				while (1)
					;
			}
		}
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}

	vTaskDelete(NULL);
}

void consumer_queue(void *pvParameters)
{
	QueueHandle_t queue1 = (QueueHandle_t)pvParameters;
	BaseType_t status;
	int counter = 0;
	char c;

	while (1)
	{
		status = xQueueReceive(queue1, (void *)&c, portMAX_DELAY);
		receivedStr[counter] = c;
		counter++;
		if (status != pdPASS)
		{
			PRINTF("Queue Receive failed!.\r\n");
			while (1)
				;
		}
		PRINTF("Received Value = %c\r\n", c);

		if (counter == strLen)
		{
			receivedStr[counter] = '\0';

			while (1)
			{
				PRINTF("%s\r\n", receivedStr);
				vTaskDelay(1000 / portTICK_PERIOD_MS);
			}
		}
	}
}

int main(void)
{
	BaseType_t status;

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitDebugConsole();

	QueueHandle_t queue1 = xQueueCreate(1, sizeof(char));
	if (queue1 == NULL)
	{
		PRINTF("Queue creation failed!.\r\n");
		while (1)
			;
	}

	status = xTaskCreate(producer_queue, "producer", 200, (void *)queue1, 2, NULL);
	if (status != pdPASS)
	{
		PRINTF("Task creation failed!.\r\n");
		while (1)
			;
	}

	status = xTaskCreate(consumer_queue, "consumer", 200, (void *)queue1, 2, NULL);
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
