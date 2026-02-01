/*
 * lcd.h
 *
 *  Created on: Dec 01, 2025
 *      Author: Sergey Lyuzzhukin
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "stm32f4xx_hal.h"
#include <stdio.h> //for using "sprintf()"

#define E_RESET LCD_WriteByte_I2C(port_LCD &= ~0x04) //Enable E to display data with logical 0
#define E_SET LCD_WriteByte_I2C(port_LCD |= 0x04) //High potential at pin E as default

#define RS_SET LCD_WriteByte_I2C(port_LCD |= 0x01) //Logical 1 is used to send data
#define RS_RESET LCD_WriteByte_I2C(port_LCD &= ~0x04) //Logical 0 is used to send commands

#define SET_LED LCD_WriteByte_I2C(port_LCD |= 0x08)
#define SET_WRITE LCD_WriteByte_I2C(port_LCD &= ~0x02)

#define DATA 1
#define COMMAND 0

void LCD_Init(void);
void LCD_WriteNibble(uint8_t byte);
void LCD_Clear(void);
void LCD_SendChar(char symbol);
void LCD_String(char *sentence);
void LCD_SetPos(uint8_t line, uint8_t position);

#endif /* INC_LCD_H_ */
