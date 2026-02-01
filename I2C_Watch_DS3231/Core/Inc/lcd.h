/*
 * lcd.h
 *
 *  Created on: Nov 24, 2025
 *      Author: Sergey Lyuzzhukin
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "stm32f4xx_hal.h"
#include <stdio.h> //for using "sprintf()"

//Sending logical 1 to the LCD
#define D4_SET HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_SET)
#define D5_SET HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_SET)
#define D6_SET HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_SET)
#define D7_SET HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET)

//Sending logical 0 to the LCD
#define D4_RESET HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_RESET)
#define D5_RESET HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_RESET)
#define D6_RESET HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_RESET)
#define D7_RESET HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET)

#define E_RESET HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET) //Enable E to display data with logical 0
#define E_SET HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET) //High potential at pin E as default

#define RS_SET HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET) //Logical 1 is used to send data
#define RS_RESET HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET) //Logical 0 is used to send commands

#define DATA 1
#define COMMAND 0

void LCD_Init(void);
void LCD_WriteNibble(uint8_t byte);
void LCD_Clear(void);
void LCD_SendChar(char symbol);
void LCD_String(char *sentence);
void LCD_SetPos(uint8_t line, uint8_t position);

#endif /* INC_LCD_H_ */
