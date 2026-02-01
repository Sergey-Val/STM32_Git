/*
 * I2C.h
 *
 *  Created on: Nov 24, 2025
 *      Author: Sergey Lyuzzhukin
 */

#ifndef I2C_H_
#define I2C_H_

#include "lcd.h"

void I2C_WriteBuffer(I2C_HandleTypeDef bus, uint8_t dev_addr, uint8_t size_buf);
void I2C_ReadBuffer(I2C_HandleTypeDef bus, uint8_t dev_addr, uint8_t size_buf);

#endif /* I2C_H_ */
