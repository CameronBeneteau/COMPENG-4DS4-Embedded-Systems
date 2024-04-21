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
#include "fsl_ftm.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

void pwm_red_setup();
void pwm_green_setup();
void pwm_blue_setup();

/*******************************************************************************
 * Code
 ******************************************************************************/

void pwm_red_setup()
{
	ftm_config_t ftmInfo;
	ftm_chnl_pwm_signal_param_t ftmParam;

	ftmParam.chnlNumber = kFTM_Chnl_1;
	ftmParam.level = kFTM_HighTrue;
	ftmParam.dutyCyclePercent = 0;
	ftmParam.firstEdgeDelayPercent = 0U;
	ftmParam.enableComplementary = false;
	ftmParam.enableDeadtime = false;

	FTM_GetDefaultConfig(&ftmInfo);

	FTM_Init(FTM3, &ftmInfo);
	FTM_SetupPwm(FTM3, &ftmParam, 1U, kFTM_EdgeAlignedPwm, 5000U, CLOCK_GetFreq(kCLOCK_BusClk));
	FTM_StartTimer(FTM3, kFTM_SystemClock);
}

void pwm_green_setup()
{
	ftm_config_t ftmInfo;
	ftm_chnl_pwm_signal_param_t ftmParam;

	ftmParam.chnlNumber = kFTM_Chnl_5;
	ftmParam.level = kFTM_HighTrue;
	ftmParam.dutyCyclePercent = 0;
	ftmParam.firstEdgeDelayPercent = 0U;
	ftmParam.enableComplementary = false;
	ftmParam.enableDeadtime = false;

	FTM_GetDefaultConfig(&ftmInfo);

	FTM_Init(FTM3, &ftmInfo);
	FTM_SetupPwm(FTM3, &ftmParam, 1U, kFTM_EdgeAlignedPwm, 5000U, CLOCK_GetFreq(kCLOCK_BusClk));
	FTM_StartTimer(FTM3, kFTM_SystemClock);
}

void pwm_blue_setup()
{
	ftm_config_t ftmInfo;
	ftm_chnl_pwm_signal_param_t ftmParam;

	ftmParam.chnlNumber = kFTM_Chnl_4;
	ftmParam.level = kFTM_HighTrue;
	ftmParam.dutyCyclePercent = 0;
	ftmParam.firstEdgeDelayPercent = 0U;
	ftmParam.enableComplementary = false;
	ftmParam.enableDeadtime = false;

	FTM_GetDefaultConfig(&ftmInfo);

	FTM_Init(FTM3, &ftmInfo);
	FTM_SetupPwm(FTM3, &ftmParam, 1U, kFTM_EdgeAlignedPwm, 5000U, CLOCK_GetFreq(kCLOCK_BusClk));
	FTM_StartTimer(FTM3, kFTM_SystemClock);
}

/*!
 * @brief Main function
 */
int main(void)
{
	char ch;
	int color = 0;

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitDebugConsole();

	pwm_red_setup();
	pwm_green_setup();
	pwm_blue_setup();

	/* Get hex colour input from user */
	scanf("%x", &color);

	/* Extract RGB values */
	int red = ((color >> 16) & 0xFF) / 2.55;  // RR byte
	int green = ((color >> 8) & 0xFF) / 2.55; // GG byte
	int blue = (color & 0xFF) / 2.55;		  // BB byte

	FTM_UpdatePwmDutycycle(FTM3, kFTM_Chnl_1, kFTM_EdgeAlignedPwm, red);
	FTM_UpdatePwmDutycycle(FTM3, kFTM_Chnl_5, kFTM_EdgeAlignedPwm, green);
	FTM_UpdatePwmDutycycle(FTM3, kFTM_Chnl_4, kFTM_EdgeAlignedPwm, blue);
	FTM_SetSoftwareTrigger(FTM3, true);

	while (1)
	{
	}
}
