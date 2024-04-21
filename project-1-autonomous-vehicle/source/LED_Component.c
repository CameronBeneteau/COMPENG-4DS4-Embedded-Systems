#include "LED_Component.h"

QueueHandle_t led_queue;

void setupLEDComponent()
{
	setupLEDPins();

	setupLEDs();

	/*************** LED Task ***************/
	// Create LED Queue

	led_queue = xQueueCreate(1, sizeof(uint8_t));

	// Create LED Task

	BaseType_t status;

	status = xTaskCreate(ledTask, "LED Task", 200, NULL, 4, NULL);
	if (status != pdPASS)
	{
		PRINTF("Task creation failed!.\r\n");
		while (1)
			;
	}
}

void setupLEDPins()
{
	// Configure LED pins

	CLOCK_EnableClock(kCLOCK_PortC);
	CLOCK_EnableClock(kCLOCK_PortD);

	PORT_SetPinMux(PORTD, 1U, kPORT_MuxAlt4); // Red
	PORT_SetPinMux(PORTC, 9U, kPORT_MuxAlt3); // Green
	PORT_SetPinMux(PORTC, 8U, kPORT_MuxAlt3); // Blue
}

void setupLEDs()
{
	// Initialize PWM for the LEDs

	ftm_config_t ftmInfo;
	ftm_chnl_pwm_signal_param_t ftmParam[3];

	ftmParam[0].chnlNumber = kFTM_Chnl_1; // Red
	ftmParam[1].chnlNumber = kFTM_Chnl_5; // Green
	ftmParam[2].chnlNumber = kFTM_Chnl_4; // Blue

	for (int i = 0; i < 3; i++)
	{
		ftmParam[i].level = kFTM_HighTrue;
		ftmParam[i].dutyCyclePercent = 0;
		ftmParam[i].firstEdgeDelayPercent = 0U;
		ftmParam[i].enableComplementary = false;
		ftmParam[i].enableDeadtime = false;
	}

	FTM_GetDefaultConfig(&ftmInfo);

	FTM_Init(FTM3, &ftmInfo);
	FTM_SetupPwm(FTM3, ftmParam, 3U, kFTM_EdgeAlignedPwm, 5000U, CLOCK_GetFreq(kCLOCK_BusClk));
	FTM_StartTimer(FTM3, kFTM_SystemClock);
}

void convertModeToPWM(uint8_t mode, LED_PWM *led_pwm)
{
	switch (mode)
	{
	// Fastest (Red)
	case 0:
		led_pwm->red = 100;
		led_pwm->green = 0;
		led_pwm->blue = 0;
		break;
	// Medium (Yellow)
	case 1:
		led_pwm->red = 100;
		led_pwm->green = 100;
		led_pwm->blue = 0;
		break;
	// Slowest (Green)
	case 2:
		led_pwm->red = 0;
		led_pwm->green = 100;
		led_pwm->blue = 0;
		break;
	}
}

void ledTask(void *pvParameters)
{
	BaseType_t status;

	LED_PWM ledPwm;
	uint8_t mode = 0;

	while (1)
	{
		status = xQueueReceive(led_queue, (void *)&mode, portMAX_DELAY);

		if (status != pdPASS)
		{
			PRINTF("Queue Receive failed!.\r\n");
			while (1)
				;
		}

		convertModeToPWM(mode, &ledPwm);

		FTM_UpdatePwmDutycycle(FTM3, kFTM_Chnl_1, kFTM_EdgeAlignedPwm, ledPwm.red);
		FTM_UpdatePwmDutycycle(FTM3, kFTM_Chnl_5, kFTM_EdgeAlignedPwm, ledPwm.green);
		FTM_UpdatePwmDutycycle(FTM3, kFTM_Chnl_4, kFTM_EdgeAlignedPwm, ledPwm.blue);
		FTM_SetSoftwareTrigger(FTM3, true);
	}
}
