/*
 * I2C_Functions.c
 *
 *  Created on: Jun 26, 2025
 *      Author: Сергей
 */

//In this project the data will get processed after receiving
#include "main.h"
#include "I2C_Functions.h"

extern I2C_HandleTypeDef hi2c1;

#define RxSIZE 6 //Buffer size of six bytes

uint8_t RxData[RxSIZE];
uint8_t rx_count = 0; //Variable to keep track of the buffer position

int count = 0; //Variable to count how many times the slave has received data (for part 1)
int countAddr = 0; //How many times the address has matched (for part 2)
int count_rxCplt = 0; //The same as "count" but for part 2
int countError = 0;

void process_data(void)
{
	//The code of the functions
}

//The function is called when a slave device gets a request from the master, and an interrupt triggers
void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *hi2c)
{
	HAL_I2C_EnableListen_IT(&hi2c1); //The peripheral device will look for another request from the master again
}
//-------------------------------------------------------------------------------------------------------
//The function below is called when the address sent by the master matches the address of the device
//The parameters are: 1 - an I2C instance, 2 - Read or write mode, 3 - the address of the slave device
void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode)
{
	if (TransferDirection == I2C_DIRECTION_TRANSMIT) //The master transmits data to the peripheral
	{
		//HAL_I2C_Slave_Seq_Receive_IT(hi2c1, RxData, RxSIZE, I2C_FIRST_AND_LAST_FRAME);
		//FIRST means a non-sequential mode
		//LAST_FRAME means that a slave will send a "NACK" response after receiving data of RxSIZE bytes

		rx_count = 0; //New data will always be stored at the beginning of the buffer
		countAddr++;
		HAL_I2C_Slave_Seq_Receive_IT(hi2c, RxData + rx_count, 1, I2C_FIRST_FRAME); //Receiving 1 byte
	}
	else //The master requests data
	{
		Error_Handler();
	}
}
//-------------------------------------------------------------------------------
//This function is called when a slave has received data of RxSIZE bytes.
//If data is less than RxSIZE bytes, the last frame is never triggered, and the slave never sends a NACK response, the function is NOT called.
//If data is more than RxSIZE bytes, the slave will send a NACK response
void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	//++count;
	rx_count++; //New data will be stored at a new location in the buffer
	if (rx_count < RxSIZE)
	{
		if (rx_count == RxSIZE - 1)
		{
			HAL_I2C_Slave_Seq_Receive_IT(hi2c, RxData + rx_count, 1, I2C_LAST_FRAME);
		}
		else
		{
			HAL_I2C_Slave_Seq_Receive_IT(hi2c, RxData + rx_count, 1, I2C_NEXT_FRAME);
		}
	}

	if (rx_count == RxSIZE)
	{
		process_data();
	}
}
//-------------------------------------------------------------------------------
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c) //The function is called when the data is less than RxSIZE bytes
{
	countError++;
	uint32_t ErrorCode = HAL_I2C_GetError(hi2c);
	if (ErrorCode == 4) //Acknowledgment failure
	{
		process_data();
	}
	HAL_I2C_EnableListen_IT(hi2c); //The peripheral device will look for another request from the master again
}
