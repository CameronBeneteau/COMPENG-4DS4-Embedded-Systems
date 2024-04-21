/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_uart.h"
#include "fsl_ftm.h"
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define FTM_MOTOR FTM0
#define FTM_CHANNEL_DC_MOTOR kFTM_Chnl_0
#define FTM_CHANNEL_SERVO kFTM_Chnl_3

#define TARGET_UART UART4

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

void setupPWM_Motor()
{
	ftm_config_t ftmInfo;
	ftm_chnl_pwm_signal_param_t ftmParam;
	ftm_pwm_level_select_t pwmLevel = kFTM_HighTrue;

	ftmParam.chnlNumber = FTM_CHANNEL_DC_MOTOR;
	ftmParam.level = pwmLevel;
	ftmParam.dutyCyclePercent = 7;
	ftmParam.firstEdgeDelayPercent = 0U;
	ftmParam.enableComplementary = false;
	ftmParam.enableDeadtime = false;

	FTM_GetDefaultConfig(&ftmInfo);
	ftmInfo.prescale = kFTM_Prescale_Divide_128;

	FTM_Init(FTM_MOTOR, &ftmInfo);
	FTM_SetupPwm(FTM_MOTOR, &ftmParam, 1U, kFTM_EdgeAlignedPwm, 50U, CLOCK_GetFreq(kCLOCK_BusClk));
	FTM_StartTimer(FTM_MOTOR, kFTM_SystemClock);
}

void setupPWM_Servo()
{
	ftm_config_t ftmInfo;
	ftm_chnl_pwm_signal_param_t ftmParam;
	ftm_pwm_level_select_t pwmLevel = kFTM_HighTrue;

	ftmParam.chnlNumber = FTM_CHANNEL_SERVO;
	ftmParam.level = pwmLevel;
	ftmParam.dutyCyclePercent = 7;
	ftmParam.firstEdgeDelayPercent = 0U;
	ftmParam.enableComplementary = false;
	ftmParam.enableDeadtime = false;

	FTM_GetDefaultConfig(&ftmInfo);
	ftmInfo.prescale = kFTM_Prescale_Divide_128;

	FTM_Init(FTM_MOTOR, &ftmInfo);
	FTM_SetupPwm(FTM_MOTOR, &ftmParam, 1U, kFTM_EdgeAlignedPwm, 50U, CLOCK_GetFreq(kCLOCK_BusClk));
	FTM_StartTimer(FTM_MOTOR, kFTM_SystemClock);
}

void updatePWM_dutyCycle(ftm_chnl_t channel, float dutyCycle)
{
	uint32_t cnv, cnvFirstEdge = 0, mod;

	/* The CHANNEL_COUNT macro returns -1 if it cannot match the FTM instance */
	assert(-1 != FSL_FEATURE_FTM_CHANNEL_COUNTn(FTM_MOTOR));

	mod = FTM_MOTOR->MOD;
	if (dutyCycle == 0U)
	{
		/* Signal stays low */
		cnv = 0;
	}
	else
	{
		cnv = mod * dutyCycle;
		/* For 100% duty cycle */
		if (cnv >= mod)
		{
			cnv = mod + 1U;
		}
	}

	FTM_MOTOR->CONTROLS[channel].CnV = cnv;
}

void setupUART()
{
	uart_config_t config;

	UART_GetDefaultConfig(&config);
	config.baudRate_Bps = 57600;
	config.enableTx = true;
	config.enableRx = true;
	config.enableRxRTS = true;
	config.enableTxCTS = true;

	UART_Init(TARGET_UART, &config, CLOCK_GetFreq(kCLOCK_BusClk));
}

int main(void)
{
	char ch;
	char txbuff[] = "Hello World\r\n";

	int inputMotor, inputServo;
	float dutyCycleMotor, dutyCycleServo;

	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitDebugConsole();

	setupPWM_Motor();
	setupPWM_Servo();
	setupUART();
	/******* Delay *******/
	for (volatile int i = 0U; i < 1000000; i++)
		__asm("NOP");

	updatePWM_dutyCycle(FTM_CHANNEL_DC_MOTOR, 0.075);
	updatePWM_dutyCycle(FTM_CHANNEL_SERVO, 0.075);

	FTM_SetSoftwareTrigger(FTM_MOTOR, true);

	printf("%s", txbuff);
	UART_WriteBlocking(TARGET_UART, txbuff, sizeof(txbuff) - 1);

	while (1)
	{
		char motorStr[5] = "0000";
		int motorCharIndex = 0;

		printf("\nEnter motor speed | Range -100 to 100 | Format XXXX\n");

		for (int i = 0; i < 4; i++)
		{
			UART_ReadBlocking(TARGET_UART, &ch, 1);
			printf("%c", ch);
			motorStr[i] = ch;
		}

		int motorInt = atoi(motorStr);

		char servoStr[5] = "0000";
		int servoCharIndex = 0;

		printf("\nEnter servo angle | Range -100 to 100 | Format XXXX\n");

		for (int i = 0; i < 4; i++)
		{
			UART_ReadBlocking(TARGET_UART, &ch, 1);
			printf("%c", ch);
			servoStr[i] = ch;
		}

		int servoInt = atoi(servoStr);

		dutyCycleMotor = motorInt * 0.025f / 100.0f + 0.075;
		dutyCycleServo = servoInt * 0.025f / 100.0f + 0.075;

		updatePWM_dutyCycle(FTM_CHANNEL_DC_MOTOR, dutyCycleMotor);
		updatePWM_dutyCycle(FTM_CHANNEL_SERVO, dutyCycleServo);

		FTM_SetSoftwareTrigger(FTM_MOTOR, true);

		printf("\nUpdated motor and servo values\n");
	}
}
