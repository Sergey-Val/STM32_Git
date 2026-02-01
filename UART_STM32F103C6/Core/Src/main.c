/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
#include "stdlib.h" //For using "sprintf"
#include "string.h" //For using "strlen"
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

void SendCharUART(uint8_t data)
{
	HAL_UART_Transmit(&huart1, &data, 1, 100);
}
//---------------------------------------------------
void SendStringUART(const char *str)
{
	HAL_UART_Transmit(&huart1, str, strlen(str), 100);
}
//===================================================
void SendCharUART_Reg(uint8_t symbol)
{
	USART1->CR1 &= ~USART_CR1_RE; //Turning off the receiver
	USART1->CR1 |= USART_CR1_TE; //Turning on the transmitter

	USART1->DR = symbol; //Sending the symbol
	while (!(USART1->SR & USART_SR_TC)); //Waiting for the transmission to finish

	USART1->CR1 &= ~USART_CR1_TE; //Turning off the transmitter
	USART1->CR1 |= USART_CR1_RE; //Turning on the receiver
}
//---------------------------------------------------
void SendStringUART_Reg(uint8_t string[])
{
	USART1->CR1 &= ~USART_CR1_RE; //Turning off the receiver
	USART1->CR1 |= USART_CR1_TE; //Turning on the transmitter

	for (unsigned int i = 0; i < strlen(string); ++i)
	{
		USART1->DR = string[i];
		while (!(USART1->SR & USART_SR_TC));
	}
	USART1->CR1 &= ~USART_CR1_TE; //Turning off the transmitter
	USART1->CR1 |= USART_CR1_RE; //Turning on the receiver
}
//===================================================
void GetCharUART_Reg()
{
	if (USART1->SR & USART_SR_RXNE) //This flag sets when the data is received and resets when the data is being read.
	{
		if (USART1->DR == 'A')
		{
			SendStringUART_Reg("Great");
			GPIOC->BRR |= GPIO_PIN_14; //Reset pin 14
			GPIOC->BSRR |= GPIO_PIN_13; //Set pin 13
		}
		else
		{
			SendStringUART_Reg("Not Great");
			GPIOC->BRR |= GPIO_PIN_14; //Reset pin 14
			GPIOC->BRR |= GPIO_PIN_13; //Set pin 13
		}
	}
	else
	{
		GPIOC->BSRR |= GPIO_PIN_14; //Set pin 14
		GPIOC->BRR |= GPIO_PIN_13; //Reset pin 13
	}
}
//---------------------------------------------------
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  char Number = 0;
  char String[10];
  float ADC = 0.0;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  //USART has to be enabled in Cube MX in advance!
  USART1->BRR = (4<<4) | 5; //Set Baud rate 115200
  //USART1->CR1 = (USART_CR1_UE | USART_CR1_TE); //UART Enable and Transmit Enable
  USART1->CR1 = (USART_CR1_UE | USART_CR1_RE); //UART Enable and Receiver Enable

  while (1)
  {
	  Number++;
	  ADC += 0.1;
	  //UART with Registers
	  USART1->DR = Number; //Sending data to the data register
	  while (!(USART1->SR & USART_SR_TC)); //Waiting for a transmission to complete
/*
	  SendCharUART_Reg('A');
	  SendStringUART_Reg("Hello world!");

	  SendCharUART(0x0D);
	  snprintf(String, sizeof(String), "%f", ADC);
	  */
	  //UART with HAL_library
	/*
    sprintf(String, "%d", Number); //Conversion a number into a string
    SendStringUART(String); //Sending the string via UART
    //snprintf(String, sizeof(String), "%f", ADC); //Conversion a float value into a string. (DISABLED)
    //------------------------------------------------------------
    SendStringUART("Letter - "); //Sending a string
    SendCharUART('A'); //Sending symbol 'A'
    SendCharUART(0x0D); //Next string
    HAL_Delay(200);
    */
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, Green_LED_Pin|Red_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : Green_LED_Pin Red_LED_Pin */
  GPIO_InitStruct.Pin = Green_LED_Pin|Red_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
