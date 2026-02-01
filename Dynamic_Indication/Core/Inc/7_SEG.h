/*
 * 7_SEG.h
 *
 *  Created on: Nov 17, 2025
 *      Author: Sergey Lyuzzhukin
 */

#ifndef INC_7_SEG_H_
#define INC_7_SEG_H_

#include "stm32f4xx_hal.h"

//Definition of the segments
#define A GPIO_PIN_7
#define B GPIO_PIN_8
#define C GPIO_PIN_9
#define D GPIO_PIN_10
#define E GPIO_PIN_11
#define F GPIO_PIN_12
#define G GPIO_PIN_13
#define DOT GPIO_PIN_14

//Definition of the state of the segments
#define A_SET HAL_GPIO_WritePin(GPIOE, A, GPIO_PIN_SET)
#define A_RESET HAL_GPIO_WritePin(GPIOE, A, GPIO_PIN_RESET)

#define B_SET HAL_GPIO_WritePin(GPIOE, B, GPIO_PIN_SET)
#define B_RESET HAL_GPIO_WritePin(GPIOE, B, GPIO_PIN_RESET)

#define C_SET HAL_GPIO_WritePin(GPIOE, C, GPIO_PIN_SET)
#define C_RESET HAL_GPIO_WritePin(GPIOE, C, GPIO_PIN_RESET)

#define D_SET HAL_GPIO_WritePin(GPIOE, D, GPIO_PIN_SET)
#define D_RESET HAL_GPIO_WritePin(GPIOE, D, GPIO_PIN_RESET)

#define E_SET HAL_GPIO_WritePin(GPIOE, E, GPIO_PIN_SET)
#define E_RESET HAL_GPIO_WritePin(GPIOE, E, GPIO_PIN_RESET)

#define F_SET HAL_GPIO_WritePin(GPIOE, F, GPIO_PIN_SET)
#define F_RESET HAL_GPIO_WritePin(GPIOE, F, GPIO_PIN_RESET)

#define G_SET HAL_GPIO_WritePin(GPIOE, G, GPIO_PIN_SET)
#define G_RESET HAL_GPIO_WritePin(GPIOE, G, GPIO_PIN_RESET)

#define DOT_SET HAL_GPIO_WritePin(GPIOE, DOT, GPIO_PIN_SET)
#define DOT_RESET HAL_GPIO_WritePin(GPIOE, DOT, GPIO_PIN_RESET)

void Display(uint8_t digit);
void GetNumber(uint16_t number); //The function breaks down a number into ranks

#endif /* INC_7_SEG_H_ */
