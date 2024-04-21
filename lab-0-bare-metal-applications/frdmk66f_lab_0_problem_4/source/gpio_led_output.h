/*
 * gpio_led_output.h
 *
 *  Created on: Jan 19, 2024
 *  Author: Cameron Beneteau & Shaqif Ahmed
 */

#ifndef GPIO_LED_OUTPUT_H_
#define GPIO_LED_OUTPUT_H_

typedef struct
{
    __IO uint32_t PDOR; /**< Port Data Output Register, offset: 0x0 */
    __O uint32_t PSOR;  /**< Port Set Output Register, offset: 0x4 */
    __O uint32_t PCOR;  /**< Port Clear Output Register, offset: 0x8 */
    __O uint32_t PTOR;  /**< Port Toggle Output Register, offset: 0xC */
    __I uint32_t PDIR;  /**< Port Data Input Register, offset: 0x10 */
    __IO uint32_t PDDR; /**< Port Data Direction Register, offset: 0x14 */
} GPIO_Struct;

#define BOARD_LED_GPIO_C ((GPIO_Struct *)GPIOC_BASE)
#define BOARD_LED_GPIO_D ((GPIO_Struct *)GPIOD_BASE)

#define BOARD_LED_GPIO_PIN_BLUE 8
#define BOARD_LED_GPIO_PIN_GREEN 9
#define BOARD_LED_GPIO_PIN_RED 1

void PinClockMuxEnable();
void PinInit(GPIO_Struct *base, uint32_t pin, const gpio_pin_config_t *config);
void PortToggle(GPIO_Struct *base, uint32_t mask);

#endif
