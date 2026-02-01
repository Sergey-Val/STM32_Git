/*
 * lcd.c
 *
 *  Created on: Dec 01, 2025
 *      Author: Sergey Lyuzzhukin
 */
#include "lcd.h"

extern I2C_HandleTypeDef hi2c1;
uint8_t buf[1] = {0};
char str[100];
uint8_t port_LCD; //Variable to store data from the microchip

void delay_us(uint32_t time)
{
	uint8_t i;
	for (i = 0; i < 168 * time; ++i)
	{
		//Empty cycle to make a delay of approximately 1 microsecond multiplied by "time"
	}
}
//-------------------------------------------------------------------------------------------------
void LCD_WriteByte_I2C(uint8_t byte)
{
	buf[0] = byte;
	HAL_I2C_Master_Transmit(&hi2c1, (uint16_t) 0x4E, buf, 1, 1000); //Parameter *nibble already contains an address
}
//------------------------------------------------------------------------------------------------
void LCD_SendNibble(int8_t nibble)
{
	nibble <<= 4;
	E_SET;
	delay_us(50);
	LCD_WriteByte_I2C(port_LCD | nibble);
	E_RESET;
	delay_us(50);
}
//------------------------------------------------------------------------------
void LCD_SendByte(int8_t byte, uint8_t mode)
{
	if (mode == 1) RS_SET;
	else if (mode == 0) RS_RESET;
	uint8_t HighNibble = byte >> 4; //High bits become low whereas low bits disappear
	LCD_SendNibble(HighNibble); //Only HIGH bits get sent
	LCD_SendNibble(HighNibble); //Only LOW bits get sent
}

void LCD_Init(void) //Initializing according to the datasheet
{
	HAL_Delay(15);
	LCD_SendByte(0x03, COMMAND);
	HAL_Delay(4);

	LCD_SendByte(0x03, COMMAND);
	delay_us(100);
	LCD_SendByte(0x03, COMMAND);
	HAL_Delay(1);
	LCD_SendByte(0x02, COMMAND);
	HAL_Delay(1);

	LCD_SendByte(0x28, COMMAND); //4-bit mode, 5x8 font.
	HAL_Delay(1);

	LCD_SendByte(0x0C, COMMAND); //Turn on the LCD and a cursor
	HAL_Delay(1);

	LCD_SendByte(0x01, COMMAND); //Turn off the cursor.
	HAL_Delay(2);

	LCD_SendByte(0x06, COMMAND); //Direction of writing from left to right.
	HAL_Delay(1);

	LCD_SendByte(0x02, COMMAND); //Putting back the cursor to the left top corner
	HAL_Delay(2);

	SET_LED; //Turn on backlight
	SET_WRITE; //Set the display for writing
}

void LCD_Clear(void)
{
	LCD_SendByte(0x01, COMMAND); //Turn off the cursor.
	HAL_Delay(2);
}
/*
void LCD_SendChar(char symbol) //This function isn't necessary
{
	LCD_SendByte(symbol, DATA);
	delay_us(1);
}
*/
void LCD_String(char *sentence)
{
	uint8_t i = 0;
	while (sentence[i] != '\0')
	{
		++i;
	}

	if (i > 20)
	{
		LCD_SendByte('E', DATA);
		LCD_SendByte('R', DATA);
		LCD_SendByte('R', DATA);
		LCD_SendByte('O', DATA);
		LCD_SendByte('R', DATA);
		LCD_SendByte('!', DATA);
	}
	else
	{
		for (i = 0; sentence[i] != '\0'; ++i)
		{
			LCD_SendByte(sentence[i], DATA);
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
