/*
 * RTC.h
 *
 *  Created on: Nov 24, 2025
 *      Author: Sergey Lyuzzhukin
 */

#ifndef INC_RTC_H_
#define INC_RTC_H_

#include "stm32f4xx_hal.h"

uint8_t RTC_ConvertFromDec_toBin(uint8_t byte);
uint8_t RTC_ConvertFromBin_toDec(uint8_t byte);

#endif /* INC_RTC_H_ */
