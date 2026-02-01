/*
 * RTC.c
 *
 *  Created on: Nov 24, 2025
 *      Author: Sergey Lyuzzhukin
 */
//This translation unit is created for conversion from digital form to readable one
#include "RTC.h"

uint8_t RTC_ConvertFromDec_toBin(uint8_t byte)
{
	uint8_t ch = ((byte >> 4) * 10 + (0x0F & byte));
	return ch;
}

uint8_t RTC_ConvertFromBin_toDec(uint8_t byte)
{
	uint8_t ch = ((byte / 10) << 4) | (byte % 10);
	return ch;
}
