/*
 * I2C.c
 *
 *  Created on: Nov 24, 2025
 *      Author: Sergey Lyuzzhukin
 */
#include "I2C.h"
#include "stm32f4xx_hal.h"

uint8_t aTxBuffer[8];
char string[100];
uint32_t ErrorMarker = 0;

void I2C_WriteBuffer(I2C_HandleTypeDef bus, uint8_t dev_addr, uint8_t size_buf)
{
	if (HAL_I2C_Master_Transmit(&bus, (uint16_t) dev_addr, (uint8_t*) &aTxBuffer, (uint16_t) size_buf, 1000) != HAL_OK)
	{
		ErrorMarker = HAL_I2C_GetError(&bus);
		switch (ErrorMarker)
		{
		case HAL_I2C_ERROR_BERR:
		{
			sprintf(string, "BERR error");
			LCD_SetPos(1, 8);
			LCD_String(string);
		}
		break;

		case HAL_I2C_ERROR_ARLO:
		{
			sprintf(string, "ARLO error");
			LCD_SetPos(1, 8);
			LCD_String(string);
		}
		break;

		case HAL_I2C_ERROR_AF:
		{
			sprintf(string, "No ACK bit from the slave");
			LCD_SetPos(1, 8);
			LCD_String(string);
		}
		break;

		case HAL_I2C_ERROR_OVR:
		{
			sprintf(string, "OVR error");
			LCD_SetPos(1, 8);
			LCD_String(string);
		}
		break;

		case HAL_I2C_ERROR_TIMEOUT:
		{
			sprintf(string, "Timeout Error");
			LCD_SetPos(1, 8);
			LCD_String(string);
		}
		break;

		case HAL_I2C_ERROR_SIZE:
		{
			sprintf(string, "Size Management error");
			LCD_SetPos(1, 8);
			LCD_String(string);
		}
		break;

		}//The end of switch - case
	}//The of "if" clause
}//The end of function
//========================================================================================================================================
void I2C_ReadBuffer(I2C_HandleTypeDef bus, uint8_t dev_addr, uint8_t size_buf)
{
	if (HAL_I2C_Master_Receive(&bus, (uint16_t) dev_addr, (uint8_t*) &aTxBuffer, (uint16_t) size_buf, 1000) != HAL_OK)
	{
		ErrorMarker = HAL_I2C_GetError(&bus);
		switch (ErrorMarker)
		{
		case HAL_I2C_ERROR_BERR:
		{
			sprintf(string, "BERR error");
			LCD_SetPos(1, 8);
			LCD_String(string);
		}
		break;

		case HAL_I2C_ERROR_ARLO:
		{
			sprintf(string, "ARLO error");
			LCD_SetPos(1, 8);
			LCD_String(string);
		}
		break;

		case HAL_I2C_ERROR_AF:
		{
			sprintf(string, "No ACK bit from the slave");
			LCD_SetPos(1, 8);
			LCD_String(string);
		}
		break;

		case HAL_I2C_ERROR_OVR:
		{
			sprintf(string, "OVR error");
			LCD_SetPos(1, 8);
			LCD_String(string);
		}
		break;

		case HAL_I2C_ERROR_TIMEOUT:
		{
			sprintf(string, "Timeout Error");
			LCD_SetPos(1, 8);
			LCD_String(string);
		}
		break;

		case HAL_I2C_ERROR_SIZE:
		{
			sprintf(string, "Size Management error");
			LCD_SetPos(1, 8);
			LCD_String(string);
		}
		break;

		}//The end of switch - case
	}//The of "if" clause
}//The end of function
