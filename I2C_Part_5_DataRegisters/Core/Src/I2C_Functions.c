/*
 * I2C_Functions.c
 *
 *  Created on: Jun 28, 2025
 *      Author: Сергей
 */
//In this project the master will write data into different registers in a slave
#include "main.h"
#include "I2C_Functions.h"

extern I2C_HandleTypeDef hi2c1;

#define RxSIZE 11 //Buffer size of eleven bytes
#define RegSIZE 10

uint8_t I2C_Registers[RegSIZE] = {0,0,0,0,0,0,0,0,0,0};
uint8_t RxData[RxSIZE];
uint8_t rx_count = 0; //Variable to keep track of the buffer position

int countAddr = 0; //How many times the address has matched
int count_rxCplt = 0; //How many times a slave has received data
int countError = 0;

void process_data(void)
{
	//The function below writes 4 bytes into the slave registers starting from the 6th register
	//HAL_I2C_Mem_Write(&hi2c1, count_rxCplt, 6, 1, txData, 4, 1000);
	int startReg = RxData[0]; //The register address
	int numReg = rx_count - 1; //The quantity of registers (one less than the quantity of bytes)
	int endReg = startReg + numReg - 1; //The register address starts from 0

	if (endReg > RegSIZE - 1) Error_Handler();

	int indx = 1; //Variable to define how many bytes have been read from RxData excluding byte number 0
	for (int i = 0; i < numReg; ++i)
	{
		I2C_Registers[startReg++] = RxData[indx++]; //Copying data from the buffer to the registers
	}
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
		rx_count = 0; //New data will always be stored at the beginning of the buffer
		countAddr++;
		HAL_I2C_Slave_Seq_Receive_IT(hi2c, RxData + rx_count, 1, I2C_FIRST_FRAME); //Receiving 1 byte telling how many bytes will be sent next
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

	else if (rx_count == RxSIZE)
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
