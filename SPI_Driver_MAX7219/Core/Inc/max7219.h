/*
 * max7219.h
 *
 *  Created on: Dec 12, 2025
 *      Author: Sergey Lyuzzhukin
 */

#ifndef INC_max7219_H_
#define INC_max7219_H_

#include "stm32f4xx_hal.h"
#include <stdbool.h>
//------------------------------------------------------------------------------
#define CS_ACTIVE HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_RESET)
#define CS_PASSIVE HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_SET)
//------------------------------------------------------------------------------
void Send_in_max7219(uint8_t reg, uint8_t data);
void Clear_7219(void);
void DisplayNumber_7219(volatile long number);

#endif /* INC_max7219_H_ */
