/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define MEM_LOC(x) *((int *)x)

#define Loc1 MEM_LOC(0x20001000)
#define Loc2 MEM_LOC(0x20001001)
#define Loc3 MEM_LOC(0x20001005)
#define Loc4 MEM_LOC(0x20001007)

#define MODULE ((ARBITRARY_MODULE *)0x20001000)

typedef struct __attribute__((__packed__))
{
	int location_1;
	char location_2;
	int location_3;
} ARBITRARY_MODULE;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

void testFunction();
void testFunction2();

/*******************************************************************************
 * Code
 ******************************************************************************/

void testFunction()
{
	Loc1 = 0x000000AC;
	Loc2 = 0xAABBCCDD;
	Loc3 = 0xABCD;
	Loc4 = 0xAABBCCDD;

	int x1 = Loc1;
	int x2 = Loc2;
	int x3 = Loc3;
	int x4 = Loc4;
}

void testFunction2()
{
	MODULE->location_1 = 0xAAAAAAAA;
	MODULE->location_2 = 0xBB;
	MODULE->location_3 = 0xCCCCCCCC;
}

/*!
 * @brief Main function
 */
int main(void)
{
	char ch;

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitDebugConsole();

	PRINTF("hello world.\r\n");

	testFunction2();

	while (1)
	{
		ch = GETCHAR();
		PUTCHAR(ch);
	}
}
