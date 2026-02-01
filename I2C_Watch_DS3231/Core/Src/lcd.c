/*
 * lcd.c
 *
 *  Created on: Nov 24, 2025
 *      Author: Sergey Lyuzzhukin
 */
#include "lcd.h"

void delay_us(uint32_t time)
{
	uint8_t i;
	for (i = 0; i < 168 * time; ++i)
	{
		//Empty cycle to make a delay of approximately 1 microsecond multiplied by "time"
	}
}

void LCD_WriteNibble(uint8_t nibble)
{
	nibble &= 0b00001111; //Erase data at HIGH bits just in case

	E_SET;
	delay_us(50);

	if (nibble & 0x01) D4_SET;
	else D4_RESET;

	if ((nibble >> 1) & 0x01) D5_SET;
	else D5_RESET;

	if ((nibble >> 2) & 0x01) D6_SET;
	else D6_RESET;

	if ((nibble >> 3) & 0x01) D7_SET;
	else D7_RESET;

	E_RESET;
	delay_us(50);
}

void LCD_SendByte(int8_t byte, uint8_t mode)
{
	if (mode == 0) RS_RESET; //Sending a command
	else RS_SET; //Sending data

	uint8_t HighNibble = byte >> 4; //High bits become low
	LCD_WriteNibble(HighNibble); //As the title suggests we can only send low bits. But since we have made high bits low, we can now send them with this function
	LCD_WriteNibble(byte); //Only low bits get sent
}

void LCD_Init(void) //Initializing according to the datasheet
{
	HAL_Delay(40);
	LCD_SendByte(0x03, COMMAND);
	HAL_Delay(5);

	LCD_SendByte(0x03, COMMAND);
	delay_us(100);
	LCD_SendByte(0x03, COMMAND);

	LCD_SendByte(0x28, COMMAND); //4-bit mode, 5x8 font.
	HAL_Delay(1);
	LCD_SendByte(0x28, COMMAND); //The previous command one more time
	HAL_Delay(1);

	LCD_SendByte(0x0F, COMMAND); //Turn on the LCD and a cursor
	HAL_Delay(1);

	LCD_SendByte(0x01, COMMAND); //Turn off the cursor.
	HAL_Delay(2);

	LCD_SendByte(0x06, COMMAND); //Direction of writing from left to right.
	HAL_Delay(1);

	LCD_SendByte(0x02, COMMAND); //Putting back the cursor to the left top corner
	HAL_Delay(2);
}

void LCD_Clear(void)
{
	LCD_SendByte(0x01, COMMAND); //Refer to the datasheet for this command.
	HAL_Delay(2);
}

void LCD_SendChar(char symbol) //See if this function is necessary
{
	LCD_SendByte(symbol, DATA);
	delay_us(1);
}

void LCD_String(char *sentence)
{
	uint8_t i = 0;
	while (sentence[i] != '\0')
	{
		++i;
	}

	if (i > 20)
	{
		LCD_SendChar('E');
		LCD_SendChar('R');
		LCD_SendChar('R');
		LCD_SendChar('O');
		LCD_SendChar('R');
		LCD_SendChar('!');
	}
	else
	{
		for (i = 0; sentence[i] != '\0'; ++i)
		{
			LCD_SendChar(sentence[i]);
		}
	}
}

void LCD_SetPos(uint8_t line, uint8_t position)
{
	switch(line)
	{
	case 1:
		LCD_SendByte(0x80 | position, COMMAND); //0x80 is the command to set a position of the cursor on LCD
		delay_us(39); //This delay is defined in the datasheet
		break;
	case 2:
		LCD_SendByte(0x80 | (position + 0x40), COMMAND); //The shift "+ 0x40" is defined in the datasheet
		delay_us(39);
		break;
	case 3:
		LCD_SendByte(0x80 | (position + 0x14), COMMAND);
		delay_us(39);
		break;
	case 4:
		LCD_SendByte(0x80 | (position + 0x54), COMMAND);
		delay_us(39);
		break;
	}

}
