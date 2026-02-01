/*
 * I2C_Functions.c
 *
 *  Created on: Jun 28, 2025
 *      Author: Сергей
 */

//In this project the master defines how many bytes it is going to send
#include "main.h"
#include "I2C_Functions.h"
#include <stdbool.h> //For using boolean

extern I2C_HandleTypeDef hi2c1;

#define RxSIZE 6 //Buffer size of six bytes

uint8_t RxData[RxSIZE];
uint8_t rx_count = 0; //Variable to keep track of the buffer position

bool is_first_recvd = false; //Variable defines whether the 1st byte has been received or not (for part 4).

int countAddr = 0; //How many times the address has matched
int count_rxCplt = 0;
int countError = 0;

void process_data(void)
{
	//The code of the functions
	//memcpu (mainbuf, RxData + 1, rx_count - 1)
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
		if (!is_first_recvd)
		{
			rx_count = 0; //New data will always be stored at the beginning of the buffer
			countAddr++;
			HAL_I2C_Slave_Seq_Receive_IT(hi2c, RxData + rx_count, 1, I2C_FIRST_FRAME); //Receiving the 1st byte that shows how many bytes
			//of data the master is going to send next
		}
	}
	else //The master requests data which is an error
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
	if (!is_first_recvd)
	{
		rx_count++; //New data will be stored at a new location in the buffer
		is_first_recvd = true;
		HAL_I2C_Slave_Seq_Receive_IT(hi2c, RxData + rx_count, RxData[0], I2C_LAST_FRAME); //No more data required
	}
	else
	{
		rx_count = rx_count + RxData[0];
		is_first_recvd = false;
		process_data();
	}
}
