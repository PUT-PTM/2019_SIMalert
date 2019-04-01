
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"
#include "stm32_tm1637.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
GPIO_PinState valueIO1;
GPIO_PinState valueIO2;
GPIO_PinState valueIO3;
GPIO_PinState valueIO4;
GPIO_PinState valueIO5;

int counter = 0;
int multiplier = 1000;
/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

// Temporary functions (Not used at the moment)
void test(){
	  valueIO1 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1);
		  if(valueIO1 == GPIO_PIN_RESET) {
		  tm1637DisplayDecimal(valueIO1, 0);
		  }
		  else{
			  tm1637DisplayDecimal(997, 0);
		  }
}
void readAllPins(){
	 valueIO1 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1);
	 valueIO2 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2);
	 valueIO3 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3);
	 valueIO4 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4);
	 valueIO5 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5);
}
void scanKeys(){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
	//readAllPins();

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
	//readAllPins();

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
	//readAllPins();

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	//readAllPins();

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	readAllPins();
}
int ReadButtons_5IOKeys() {
	GPIO_InitTypeDef GPIO_InitStruct;

	  // Start reading the Joystick keys
	 /*Configure GPIO pin : PA0 */
		  	  GPIO_InitStruct.Pin = GPIO_PIN_0;
		  	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		  	  GPIO_InitStruct.Pull = GPIO_NOPULL;
		  	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		  	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
		  	  /*Configure GPIO pins : PA1 PA2 PA3 PA4
		  	                           PA5 */
		  	  GPIO_InitStruct.Pin =  GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4
		  	                          |GPIO_PIN_5;
		  	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		  	  GPIO_InitStruct.Pull = GPIO_PULLUP;
		  	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1)==GPIO_PIN_RESET){while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1)==GPIO_PIN_RESET); return 11;}
	  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2)==GPIO_PIN_RESET){while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2)==GPIO_PIN_RESET); return 12;}
	  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3)==GPIO_PIN_RESET){while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3)==GPIO_PIN_RESET); return 13;}
	  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)==GPIO_PIN_RESET){while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)==GPIO_PIN_RESET); return 14;}
	  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)==GPIO_PIN_RESET){while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)==GPIO_PIN_RESET); return 15;}

	  // Start reading the K1-K4 push keys

	  	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);

	  	  /*Configure GPIO pin : PA1 */
	  	  GPIO_InitStruct.Pin = GPIO_PIN_1;
	  	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
	  	  /*Configure GPIO pins : PA0 PA2 PA3 PA4
	  	                           PA5 */
	  	  GPIO_InitStruct.Pin =  GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4
	  	                          |GPIO_PIN_5;
	  	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2)==GPIO_PIN_RESET){while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2)==GPIO_PIN_RESET); return 1;}
	  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3)==GPIO_PIN_RESET){while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3)==GPIO_PIN_RESET); return 2;}
	  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)==GPIO_PIN_RESET){while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)==GPIO_PIN_RESET); return 3;}
	  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)==GPIO_PIN_RESET){while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)==GPIO_PIN_RESET); return 4;}

	  // Start reading the K5-K7 push keys
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);

	  	  	  /*Configure GPIO pin : PA2 */
	  	  	  GPIO_InitStruct.Pin = GPIO_PIN_2;
	  	  	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  	  	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  	  	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  	  	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	  	      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
	  	  	  /*Configure GPIO pins : PA0 PA1 PA3 PA4
	  	  	                           PA5 */
	  	  	  GPIO_InitStruct.Pin =  GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_4
	  	  	                          |GPIO_PIN_5;
	  	  	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  	  	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  	  	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3)==GPIO_PIN_RESET){while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3)==GPIO_PIN_RESET); return 5;}
	  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)==GPIO_PIN_RESET){while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)==GPIO_PIN_RESET); return 6;}
	  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)==GPIO_PIN_RESET){while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)==GPIO_PIN_RESET); return 7;}

	  // Start reading the K8-K9 push keys
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);

	  	  	  	  /*Configure GPIO pin : PA3 */
	  	  	  	  GPIO_InitStruct.Pin = GPIO_PIN_3;
	  	  	  	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  	  	  	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  	  	  	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  	  	  	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	  	  	      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
	  	  	  	  /*Configure GPIO pins : PA0 PA1 PA2 PA4
	  	  	  	                           PA5 */
	  	  	  	  GPIO_InitStruct.Pin =  GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_4
	  	  	  	                          |GPIO_PIN_5;
	  	  	  	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  	  	  	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  	  	  	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)==GPIO_PIN_RESET){while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)==GPIO_PIN_RESET); return 8;}
	  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)==GPIO_PIN_RESET){while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)==GPIO_PIN_RESET); return 9;}

	  // Start reading the 1K0 push key
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);

	 	  	  	  	  /*Configure GPIO pin : PA4 */
	 	  	  	  	  GPIO_InitStruct.Pin = GPIO_PIN_4;
	 	  	  	  	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	 	  	  	  	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	 	  	  	  	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	 	  	  	  	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	 	  	  	      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	 	  	  	  	  /*Configure GPIO pins : PA0 PA1 PA2 PA3
	 	  	  	  	                           PA5 */
	 	  	  	  	  GPIO_InitStruct.Pin =  GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
	 	  	  	  	                          |GPIO_PIN_5;
	 	  	  	  	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	 	  	  	  	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	 	  	  	  	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	 if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)==GPIO_PIN_RESET){while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)==GPIO_PIN_RESET); return 10;}

	 // Back to pullUp
	 GPIO_InitStruct.Pin =  GPIO_PIN_4;
	 GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	 GPIO_InitStruct.Pull = GPIO_PULLUP;

	 return 0; //No key pressed

}

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  tm1637Init();
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  GPIO_InitTypeDef GPIO_InitStruct;
	//Read Joystick
	  /*Configure GPIO pins : PA1 PA2 PA3 PA4 PA5

	  	  		  	  GPIO_InitStruct.Pin = GPIO_PIN_1| GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4 |GPIO_PIN_5;
	  	  		  	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  	  		  	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  	  		  	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET){
		tm1637DisplayDecimal(0, 1);
		while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1)==GPIO_PIN_RESET);
	}
*/

   //Read Keys 1-4
	  /*Configure GPIO pin : PA1 */
	  	  	  	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
	  		  	  GPIO_InitStruct.Pin = GPIO_PIN_1;
	  		  	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  		  	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  		  	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  		  	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  		  	  /*Configure GPIO pins : PA2 PA3 PA4
	  		  	                           PA5 */
	  		  	  GPIO_InitStruct.Pin =   GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4
	  		  	                          |GPIO_PIN_5;
	  		  	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  		  	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  		  	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2)==GPIO_PIN_RESET){ tm1637DisplayDecimal(0, 0); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2)==GPIO_PIN_RESET); }
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3)==GPIO_PIN_RESET){ tm1637DisplayDecimal(1, 0); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3)==GPIO_PIN_RESET); }
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)==GPIO_PIN_RESET){ tm1637DisplayDecimal(2, 0); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)==GPIO_PIN_RESET); }
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)==GPIO_PIN_RESET){ tm1637DisplayDecimal(3, 0); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)==GPIO_PIN_RESET); }

	//Read Keys 5-7
	  /*Configure GPIO pin : PA2 */
	  	  	  	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
	  		  	  GPIO_InitStruct.Pin = GPIO_PIN_2;
	  		  	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  		  	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  		  	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  		  	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	  		    /*Configure GPIO pins : PA1*/
	  		    	  		  	  GPIO_InitStruct.Pin =   GPIO_PIN_1;
	  		    	  		  	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  		    	  		  	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  		    	  		  	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3)==GPIO_PIN_RESET){ tm1637DisplayDecimal(4, 0); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3)==GPIO_PIN_RESET); }
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)==GPIO_PIN_RESET){ tm1637DisplayDecimal(5, 0); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)==GPIO_PIN_RESET); }
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)==GPIO_PIN_RESET){ tm1637DisplayDecimal(6, 0); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)==GPIO_PIN_RESET); }

	//Read Keys 8-9
	  /*Configure GPIO pin : PA3 */
	  	  	  	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
	  		  	  GPIO_InitStruct.Pin = GPIO_PIN_3;
	  		  	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  		  	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  		  	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  		  	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	  		    /*Configure GPIO pins : PA2*/
	  		    	  		    	  		  	  GPIO_InitStruct.Pin =   GPIO_PIN_2;
	  		    	  		    	  		  	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  		    	  		    	  		  	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  		    	  		    	  		  	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)==GPIO_PIN_RESET){ tm1637DisplayDecimal(7, 0); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)==GPIO_PIN_RESET); }
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)==GPIO_PIN_RESET){ tm1637DisplayDecimal(8, 0); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)==GPIO_PIN_RESET); }

	//Read Key 10
	  /*Configure GPIO pin : PA4 */
	  	  	  	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	  		  	  GPIO_InitStruct.Pin = GPIO_PIN_4;
	  		  	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  		  	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  		  	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  		  	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	  		    /*Configure GPIO pins : PA3*/
	  		    	  		    	  		  	  GPIO_InitStruct.Pin =   GPIO_PIN_3;
	  		    	  		    	  		  	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  		    	  		    	  		  	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  		    	  		    	  		  	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)==GPIO_PIN_RESET){ tm1637DisplayDecimal(9, 0); while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)==GPIO_PIN_RESET); }
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1 |GPIO_PIN_2 |GPIO_PIN_3 |GPIO_PIN_4|GPIO_PIN_5, GPIO_PIN_SET);
	  }
  }
  /* USER CODE END WHILE */
  /* USER CODE BEGIN 3 */

  /* USER CODE END 3 */

/**
  * @brief System Clock Configuration
  * @retval None
  */

void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pins : PA1 PA2 PA3 PA4
                           PA5 */
  GPIO_InitStruct.Pin =  GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
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
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
