/*
 * max7219.c
 *
 *  Created on: Dec 12, 2025
 *      Author: Sergey Lyuzzhukin
 */
#include "max7219.h"
//------------------------------------------------------------------------------
extern SPI_HandleTypeDef hspi3;
uint8_t TxBuffer[1] = {0};
char dg = 8; //Quantity of ranks
//------------------------------------------------------------------------------
void Send_in_max7219(uint8_t reg, uint8_t data)
{
	CS_ACTIVE;
	TxBuffer[0] = reg;
	HAL_SPI_Transmit(&hspi3, (uint8_t*)TxBuffer, 1, 5000);
	TxBuffer[0] = data;
	HAL_SPI_Transmit(&hspi3, (uint8_t*)TxBuffer, 1, 5000);
	CS_PASSIVE;
}
//------------------------------------------------------------------------------
void Clear_7219(void)
{
	uint8_t i = dg;
	do
	{
		Send_in_max7219(i, 0xF); //Symbol of emptiness
	}
	while (--i);
}
//------------------------------------------------------------------------------
void DisplayNumber_7219(volatile long number)
{
	bool negative = false; //Marker if the number is negative
	uint8_t i = 0;
	if (number < 0)
	{
		negative = true;
		number *= -1;
	}
	do
	{
		Send_in_max7219(++i, number%10); //Symbol of a digit
		number /= 10;
	}
	while (number);
	if (negative) Send_in_max7219(i + 1, 0xA); //Symbol of a minus
}
//------------------------------------------------------------------------------
void Init_max7219(void)
{
	Send_in_max7219(0x09, 0xFF); //Turning on the decoding mode
	Send_in_max7219(0x0B, dg - 1); //Quantity of ranks used
	Send_in_max7219(0x0A, 0x02); //Intensity of glow
	Send_in_max7219(0x0C, 0x01); //Turning on the indicator
	Clear_7219();
}
