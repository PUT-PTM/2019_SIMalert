/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32_tm1637.h"
#include "stdlib.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
int gotACK();
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

/* Private variables ---------------------------------------------------------*/
uint8_t at_UART[10] = {'A', 'T', '\r','\n'};
uint8_t at_cmgf1_UART[17] = {'A', 'T', '+', 'C', 'M', 'G', 'F','=','1', '\r','\n'};
uint8_t at_cmgf0_UART[17] = {'A', 'T', '+', 'C', 'M', 'G', 'F','=','0', '\r','\n'};
uint8_t at_cmgs_UART[30] = {'A', 'T', '+', 'C', 'M', 'G', 'S','=','"','+','4','8','6','6','4','9','4','2','3','3','3','"', '\r','\n'};
uint8_t atd_UART[27] = {'A', 'T', 'D',  '+','4','8','6','6','4','9','4','2','3','3','3',';', '\r','\n'};
uint8_t ath_UART[11] = {'A', 'T', 'H', '\r','\n'};
uint8_t msg_UART[11] = {'I', 'N', 'T', 'R','U','D','E','R','!','!', 26};
uint8_t end_UART[1] = {'1A'};

uint8_t receiveUART[2];
int ready=0;
int alert_go = 0;
// TM1637 and Keyboard variables
GPIO_PinState valueIO1;
GPIO_PinState valueIO2;
GPIO_PinState valueIO3;
GPIO_PinState valueIO4;
GPIO_PinState valueIO5;
int do_count = 0;
int counter = 3;
char value[4]="0000";
int int_value=0000;
int time = 0;
int start_code_int=0000;
int code_set = 0;
int end=0;
int endtim=9999;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM4_Init(void);
static void MX_USART3_UART_Init(void);
/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
   if(huart->Instance == USART3){
	   HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
       HAL_UART_Receive_IT(&huart3, receiveUART, sizeof(receiveUART));
       if(gotACK() == 1){
    	   ready=1;
       }
   }
}

void HAL_TIM_PeriodElapsedCallback ( TIM_HandleTypeDef *htim){
if (htim-> Instance == TIM4)
{
	if(do_count==1){
	if(time >= 25) {
		do_count = 0;
		time = 0;
		HAL_TIM_Base_Stop_IT (&htim4);
		alert_go = 1;
	}
	time = time +1;
}}
if(end == 1){
	tm1637DisplayDecimal(endtim,0);
	endtim=endtim-1;
}
}

void readButtons(){
	  GPIO_InitTypeDef GPIO_InitStruct;


 //Read Keys 1-4
	  /*Configure GPIO pin : PA1 */
	  	  	  	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
	  		  	  GPIO_InitStruct.Pin = GPIO_PIN_1;
	  		  	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  		  	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  		  	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  		  	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  /*Configure GPIO pins : PA2 PA3 PA4 PA5 */
	  		  	  GPIO_InitStruct.Pin =   GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5;
	  		  	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  		  	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  		  	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2)==GPIO_PIN_RESET){ value[counter]='0'; counter--; while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2)==GPIO_PIN_RESET); HAL_Delay(100); }
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3)==GPIO_PIN_RESET){ value[counter]='1'; counter--; while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3)==GPIO_PIN_RESET); HAL_Delay(100);}
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)==GPIO_PIN_RESET){ value[counter]='2'; counter--; while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)==GPIO_PIN_RESET); HAL_Delay(100);}
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)==GPIO_PIN_RESET){ value[counter]='3'; counter--; while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)==GPIO_PIN_RESET); HAL_Delay(100);}

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

	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3)==GPIO_PIN_RESET){ value[counter]='4'; counter--; while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3)==GPIO_PIN_RESET); HAL_Delay(100); }
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)==GPIO_PIN_RESET){ value[counter]='5'; counter--; while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)==GPIO_PIN_RESET); HAL_Delay(100);}
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)==GPIO_PIN_RESET){ value[counter]='6'; counter--; while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)==GPIO_PIN_RESET); HAL_Delay(100);}

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

	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)==GPIO_PIN_RESET){ value[counter]='7'; counter--; while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)==GPIO_PIN_RESET); HAL_Delay(100);}
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)==GPIO_PIN_RESET){ value[counter]='8'; counter--; while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)==GPIO_PIN_RESET); HAL_Delay(100);}

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

	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)==GPIO_PIN_RESET){ value[counter]='9'; counter--; while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)==GPIO_PIN_RESET); HAL_Delay(100);}
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1 |GPIO_PIN_2 |GPIO_PIN_3 |GPIO_PIN_4|GPIO_PIN_5, GPIO_PIN_SET);

	int_value = atoi(&value[0]);

	tm1637DisplayDecimal(int_value,0);
	//Display Section
	if(counter == -1) {
		counter = 3;

	}


}

void setPassword(){

	 GPIO_InitTypeDef GPIO_InitStruct;

 //Read Keys 1-4
	  /*Configure GPIO pin : PA1 */


	  	  	  	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
	  		  	  GPIO_InitStruct.Pin = GPIO_PIN_1;
	  		  	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  		  	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  		  	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  		  	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  /*Configure GPIO pins : PA2 PA3 PA4 PA5 */
	  		  	  GPIO_InitStruct.Pin =   GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5;
	  		  	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  		  	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  		  	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2)==GPIO_PIN_RESET){ value[counter]='0'; counter--; while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2)==GPIO_PIN_RESET); HAL_Delay(100); }
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3)==GPIO_PIN_RESET){ value[counter]='1'; counter--; while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3)==GPIO_PIN_RESET); HAL_Delay(100);}
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)==GPIO_PIN_RESET){ value[counter]='2'; counter--; while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)==GPIO_PIN_RESET); HAL_Delay(100);}
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)==GPIO_PIN_RESET){ value[counter]='3'; counter--; while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)==GPIO_PIN_RESET); HAL_Delay(100);}

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

	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3)==GPIO_PIN_RESET){ value[counter]='4'; counter--; while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3)==GPIO_PIN_RESET); HAL_Delay(100); }
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)==GPIO_PIN_RESET){ value[counter]='5'; counter--; while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)==GPIO_PIN_RESET); HAL_Delay(100); }
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)==GPIO_PIN_RESET){ value[counter]='6'; counter--; while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)==GPIO_PIN_RESET); HAL_Delay(100); }

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

	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)==GPIO_PIN_RESET){ value[counter]='7'; counter--; while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)==GPIO_PIN_RESET); HAL_Delay(100); }
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)==GPIO_PIN_RESET){ value[counter]='8'; counter--; while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)==GPIO_PIN_RESET); HAL_Delay(100); }

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

	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)==GPIO_PIN_RESET){ value[counter]='9'; counter--; while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)==GPIO_PIN_RESET); HAL_Delay(100); }
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1 |GPIO_PIN_2 |GPIO_PIN_3 |GPIO_PIN_4|GPIO_PIN_5, GPIO_PIN_SET);

	//Display Section

	start_code_int = atoi(&value[0]);
	tm1637DisplayDecimal(start_code_int,0);
			if(counter == -1){
				counter = 3;
			    code_set = 1;
			    HAL_Delay(500);
			   resetValue();
			    tm1637DisplayDecimal(0000,0);
			}

}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void resetValue(){
	 for(int i=0; i<4; i++)
	 {
		value[i]=0;
	 }
}
int gotACK(){

	if(receiveUART[0]=='O' && receiveUART[1]=='K')
	       {
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
	    	   receiveUART[0]='1';
	    	   receiveUART[1]='2';
	    	   return 1;
	       } else return 0;
}
void alarm(){
	//Blinking led that shows that trigger worked
	 for(int a=0; a<5; a++)
	 {
		 HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
		 HAL_Delay(500);
	 }

	//AT command sending to SIM module
	{
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
		HAL_UART_Transmit_IT(&huart3, at_UART, strlen(at_UART));
		HAL_Delay(200);
	} while(ready==0);
	ready=0;

	/*Change mode to SMS mode
	do
	{
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
		HAL_UART_Transmit_IT(&huart3, at_cmgf1_UART, strlen(at_cmgf1_UART));
		HAL_Delay(200);
	} while(ready==0);
	ready=0;
*/

	//Setting number for sending SMS
	//HAL_UART_Transmit_IT(&huart3, at_cmgs_UART, strlen(at_cmgs_UART));
	//HAL_Delay(200);

	//Sending content of the message
	//HAL_UART_Transmit_IT(&huart3, msg_UART, strlen(msg_UART));
	//HAL_Delay(200);

	//Change mode to CALLING mode
	do
	{
		HAL_UART_Transmit_IT(&huart3, at_cmgf1_UART, strlen(at_cmgf1_UART));
		HAL_Delay(400);
	} while(ready==0);
	ready=0;
	end=1;
	for(int i=0; i<5; i++)
	{
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
		HAL_Delay(400);
	 }
	//Making a CALL 5 times
	for(int call=0; call<1; call++)
	{
		//Making a call
		do
		{
			HAL_UART_Transmit_IT(&huart3, atd_UART, strlen(atd_UART));
			HAL_Delay(400);
		} while(ready==0);
		ready=0;

		//Hanging up a CALL
		HAL_Delay(20000);
		do
		{
			HAL_UART_Transmit_IT(&huart3, ath_UART, strlen(ath_UART));
			HAL_Delay(300);
		} while(ready==0);
		ready=0;
	}
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  tm1637Init();
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
  MX_TIM4_Init();
  TIM4->PSC = 16800;
  TIM4->ARR = 5000;
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart3, receiveUART, sizeof(receiveUART));


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {		  // Set Password
	  if(code_set == 0){
		  setPassword();
	  }
	  else {
	  //trigger operation when movement detected

	  if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_5) == GPIO_PIN_SET)
		  {
		  	 HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
		  	HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
		  	if(end==0){
		  	do_count = 1;}

  	  	  	  }

			//Reading keyboard and displaying Values on screen
	  if(do_count == 1){
		  HAL_TIM_Base_Start_IT (&htim4);

		  while(do_count == 1){

			  readButtons();

			  // Jesli kod poprawny zatrzymaj zegar i wyjdz z petli
			  if(start_code_int == int_value)
			  {
		      time = 0;
		      do_count = 0;
		      HAL_TIM_Base_Stop_IT (&htim4);
		      start_code_int=0;
		      int_value=1;
		      end=1;
		      resetValue();
		      tm1637DisplayDecimal(0000,1);
		      HAL_Delay(5000);
		      for(int i4=7; i4>=0; i4--)
		      		 		  {
		      		  tm1637SetBrightness(i4);
		      		  HAL_Delay(100);
		      		 		  }
		      		  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14|GPIO_PIN_13|GPIO_PIN_12|GPIO_PIN_15, GPIO_PIN_RESET);
		      		  break;
		      }
	   }
	}
	  if(end == 1 && do_count==1) {
		  int i=0;

		  for(int i4=5; i4>=0; i4--)
		  {
			  value[3]=i4+48;
			  for(int i3=9; i3>=0; i3--)
			  {
				  value[2]=i3+48;
				  for(int i2=9; i2>=0; i2--)
				  {
					  value[1]=i2+48;
					  for(int i1=9; i1>=0; i1--)
					  {
						  value[0]=i1+48;
						  int_value=atoi(&value[0]);
						  tm1637SetBrightness(0);
						  tm1637SetBrightness(7);
						  tm1637DisplayDecimal(int_value,1);
						  HAL_Delay(10);
					  			  }
				  			  }
			  }

		  }
		  for(int i4=7; i4>=0; i4--)
		 		  {
		  tm1637SetBrightness(i4);
		  HAL_Delay(100);
		 		  }
		  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14|GPIO_PIN_13|GPIO_PIN_12|GPIO_PIN_15, GPIO_PIN_RESET);
		  break;
	  }
	  if(alert_go == 1) alarm();
	  }
}

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

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

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
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
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 8399;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 499;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 57600;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin : PE5 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PA2 PA3 PA4 PA5 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PD12 PD13 PD14 PD15 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

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
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
