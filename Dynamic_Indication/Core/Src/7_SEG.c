/*
 * 7_SEG.c
 *
 *  Created on: Nov 17, 2025
 *      Author: Sergey Lyuzzhukin
 */
#include "7_SEG.h"

uint8_t thousands = 0, hundreds = 0, decades = 0, units = 0; //Variables to display ranks
//===========================================================================
void Display(uint8_t digit)
{
	switch(digit)
	{
	case 0: A_SET; B_SET; C_SET; D_SET; E_SET; F_SET; G_RESET;
		break;
	case 1: A_RESET; B_SET; C_SET; D_RESET; E_RESET; F_RESET; G_RESET;
		break;
	case 2: A_SET; B_SET; C_RESET; D_SET; E_SET; F_RESET; G_SET;
		break;
	case 3: A_SET; B_SET; C_SET; D_SET; E_RESET; F_RESET; G_SET;
		break;
	case 4: A_RESET; B_SET; C_SET; D_RESET; E_RESET; F_SET; G_SET;
		break;
	case 5: A_SET; B_RESET; C_SET; D_SET; E_RESET; F_SET; G_SET;
		break;
	case 6: A_SET; B_RESET; C_SET; D_SET; E_SET; F_SET; G_SET;
		break;
	case 7: A_SET; B_SET; C_SET; D_RESET; E_RESET; F_RESET; G_RESET;
		break;
	case 8: A_SET; B_SET; C_SET; D_SET; E_SET; F_SET; G_SET;
		break;
	case 9: A_SET; B_SET; C_SET; D_SET; E_RESET; F_SET; G_SET;
		break;
	}
}
//==============================================================================
void GetNumber(uint16_t number)
{
	thousands = number / 1000;
	hundreds = number % 1000 / 100;
	decades = number % 100 / 10;
	units = number % 10;
}
