/*
 * Copyright 2019 ,2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v9.0
processor: MK66FN2M0xxx18
package_id: MK66FN2M0VMD18
mcu_data: ksdk2_0
processor_version: 9.0.0
board: FRDM-K66F
pin_labels:
- {pin_num: B9, pin_signal: PTD9/I2C0_SDA/LPUART0_TX/FB_A17, label: 'U8[6]/U19[12]/I2C0_SDA', identifier: ACCEL_SDA}
- {pin_num: C9, pin_signal: PTD8/LLWU_P24/I2C0_SCL/LPUART0_RX/FB_A16, label: 'U8[4]/U19[11]/I2C0_SCL', identifier: ACCEL_SCL}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

#include "fsl_common.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "pin_mux.h"

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 *
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void)
{
    BOARD_InitPins();

    CLOCK_EnableClock(kCLOCK_PortA);
    CLOCK_EnableClock(kCLOCK_PortB);

    // Accelerometer VDD
    PORT_SetPinMux(PORTB, 8U, kPORT_MuxAsGpio); // VDD_3V3_SENSORS_EN (B8)

    // SPI Pins
    PORT_SetPinMux(PORTB, 10U, kPORT_MuxAlt2); // nSPI1_CS0_ACCEL MAG (B10)
    PORT_SetPinMux(PORTB, 11U, kPORT_MuxAlt2); // SPI1_SCK_INTERNAL (B11)
    PORT_SetPinMux(PORTB, 16U, kPORT_MuxAlt2); // SPI1_MOSI_INTERNAL (B16)
    PORT_SetPinMux(PORTB, 17U, kPORT_MuxAlt2); // SPI1_MISO_INTERNAL (B17)
    PORT_SetPinMux(PORTA, 25U, kPORT_MuxAsGpio); // SPI1_RST_ACCEL_MAG (A25)
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: E10, peripheral: UART0, signal: RX, pin_signal: TSI0_CH9/PTB16/SPI1_SOUT/UART0_RX/FTM_CLKIN0/FB_AD17/SDRAM_D17/EWM_IN/TPM_CLKIN0}
  - {pin_num: E9, peripheral: UART0, signal: TX, pin_signal: TSI0_CH10/PTB17/SPI1_SIN/UART0_TX/FTM_CLKIN1/FB_AD16/SDRAM_D16/EWM_OUT_b/TPM_CLKIN1, direction: OUTPUT}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPins(void)
{
    /* Port B Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortB);

    /* PORTB16 (pin E10) is configured as UART0_RX */
    PORT_SetPinMux(BOARD_DEBUG_UART_RX_PORT, BOARD_DEBUG_UART_RX_PIN, kPORT_MuxAlt3);

    /* PORTB17 (pin E9) is configured as UART0_TX */
    PORT_SetPinMux(BOARD_DEBUG_UART_TX_PORT, BOARD_DEBUG_UART_TX_PIN, kPORT_MuxAlt3);

    SIM->SOPT5 = ((SIM->SOPT5 &
                   /* Mask bits to zero which are setting */
                   (~(SIM_SOPT5_UART0TXSRC_MASK)))

                  /* UART 0 transmit data source select: UART0_TX pin. */
                  | SIM_SOPT5_UART0TXSRC(SOPT5_UART0TXSRC_UART_TX));
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_I2C_ConfigurePins:
- options: {callFromInitBoot: 'false', prefix: BOARD_I2C_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: C9, peripheral: I2C0, signal: SCL, pin_signal: PTD8/LLWU_P24/I2C0_SCL/LPUART0_RX/FB_A16, slew_rate: fast, open_drain: enable, pull_select: up, pull_enable: enable,
    passive_filter: disable, digital_filter: disable}
  - {pin_num: B9, peripheral: I2C0, signal: SDA, pin_signal: PTD9/I2C0_SDA/LPUART0_TX/FB_A17, slew_rate: fast, open_drain: enable, pull_select: up, pull_enable: enable,
    digital_filter: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_I2C_ConfigurePins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_I2C_ConfigurePins(void)
{
    /* Port D Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortD);
    /* Configure digital filter */
    PORT_EnablePinsDigitalFilter(
        /* Digital filter is configured on port D */
        PORTD,
        /* Digital filter is configured for PORTD0 */
          PORT_DFER_DFE_8_MASK
            /* Digital filter is configured for PORTD1 */
            | PORT_DFER_DFE_9_MASK,
        /* Disable digital filter */
        false);

    const port_pin_config_t ACCEL_SCL = {/* Internal pull-up resistor is enabled */
                                         kPORT_PullUp,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is enabled */
                                         kPORT_OpenDrainEnable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as I2C0_SCL */
                                         kPORT_MuxAlt2,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTD8 (pin C9) is configured as I2C0_SCL */
    PORT_SetPinConfig(BOARD_I2C_ACCEL_SCL_PORT, BOARD_I2C_ACCEL_SCL_PIN, &ACCEL_SCL);

    const port_pin_config_t ACCEL_SDA = {/* Internal pull-up resistor is enabled */
                                         kPORT_PullUp,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is enabled */
                                         kPORT_OpenDrainEnable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as I2C0_SDA */
                                         kPORT_MuxAlt2,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTD9 (pin B9) is configured as I2C0_SDA */
    PORT_SetPinConfig(BOARD_I2C_ACCEL_SDA_PORT, BOARD_I2C_ACCEL_SDA_PIN, &ACCEL_SDA);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_GPIO_ConfigurePins:
- options: {callFromInitBoot: 'false', prefix: BOARD_GPIO_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: B9, peripheral: GPIOD, signal: 'GPIO, 9', pin_signal: PTD9/I2C0_SDA/LPUART0_TX/FB_A17, direction: OUTPUT, gpio_init_state: 'true'}
  - {pin_num: C9, peripheral: GPIOD, signal: 'GPIO, 8', pin_signal: PTD8/LLWU_P24/I2C0_SCL/LPUART0_RX/FB_A16, direction: OUTPUT, gpio_init_state: 'true'}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_GPIO_ConfigurePins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_GPIO_ConfigurePins(void)
{
    /* Port D Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortD);

    gpio_pin_config_t ACCEL_SCL_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U
    };
    /* Initialize GPIO functionality on pin PTD8 (pin C9)  */
    GPIO_PinInit(BOARD_GPIO_ACCEL_SCL_GPIO, BOARD_GPIO_ACCEL_SCL_PIN, &ACCEL_SCL_config);

    gpio_pin_config_t ACCEL_SDA_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U
    };
    /* Initialize GPIO functionality on pin PTD9 (pin B9)  */
    GPIO_PinInit(BOARD_GPIO_ACCEL_SDA_GPIO, BOARD_GPIO_ACCEL_SDA_PIN, &ACCEL_SDA_config);

    /* PORTD8 (pin C9) is configured as PTD8 */
    PORT_SetPinMux(BOARD_GPIO_ACCEL_SCL_PORT, BOARD_GPIO_ACCEL_SCL_PIN, kPORT_MuxAsGpio);

    /* PORTD9 (pin B9) is configured as PTD9 */
    PORT_SetPinMux(BOARD_GPIO_ACCEL_SDA_PORT, BOARD_GPIO_ACCEL_SDA_PIN, kPORT_MuxAsGpio);
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/