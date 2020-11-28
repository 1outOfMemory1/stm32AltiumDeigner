/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
RTC_HandleTypeDef hrtc;

TIM_HandleTypeDef htim1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_RTC_Init(void);
static void MX_TIM1_Init(void);
/* USER CODE BEGIN PFP */






// 清空单个数码管 
void clearAll1(){
	HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(DP_GPIO_Port, DP_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(POINT_GPIO_Port, POINT_Pin, GPIO_PIN_SET);
}
// 让4个片选信号都失效 也就是让4个数码管都不良
void clearAll_K(){
	HAL_GPIO_WritePin(K1_GPIO_Port, K1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(K2_GPIO_Port, K2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(K3_GPIO_Port, K3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(K4_GPIO_Port, K4_Pin, GPIO_PIN_RESET);
}

// 将数字转换为对应的管脚亮与否的执行语句
void numberToLed(int num){
	switch(num){
		case 0:   // 显示数字0
			clearAll1();
			HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_RESET);
			break;
		case 1:  
			clearAll1();
			HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_RESET);
			break;
		case 2:  
			clearAll1();
			HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, GPIO_PIN_RESET);
			break;
		case 3:  
			clearAll1();
			HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, GPIO_PIN_RESET);
			break;
		case 4:  
			clearAll1();
			HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, GPIO_PIN_RESET);
			break;
		case 5: 
			clearAll1();
			HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, GPIO_PIN_RESET);
			break;
		case 6:  
			clearAll1();
			HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, GPIO_PIN_RESET);
			break;
		case 7:  
			clearAll1();
			HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_RESET);
			break;
		case 8:  
			clearAll1();
			HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, GPIO_PIN_RESET);
			break;
		case 9:  
			clearAll1();
			HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, GPIO_PIN_RESET);
			break;
	}
}
int a =0; 
long long seconds = 86000;
int hour = 0;
int minute = 0;
int second = 0;
// 自己写的delay函数 展示数字的时候会用到
void myDelay(int num){
		for(int i=0;i<num;i++){
			;
		}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	//定时器用来算数
	if(htim->Instance == TIM1){
		// 因为为了方便录制视频演示 把时钟调快了 否则应该是每分钟切换变换一次数据
		// 下方这个if就可以进行切换的时间间隔
		//if(a%10 == 0){
		
				seconds++; // 总秒数+1
				hour = seconds / 3600;  // 算出小时  
				minute =  (seconds %3600 )/	60; // 算出分钟
				second = (seconds % 3600) %60;
			  if(hour >= 24) // 如果大于24小时了 seconds就清零了
					seconds = 0;
				if(minute >= 60 && hour == 23)
					seconds += 60; 
				
		//}
		a++;
		if(a %5 ==0)  
			// 闪烁中间的led 因为proteus不准所以就所谓了
			HAL_GPIO_TogglePin(POINT_GPIO_Port, POINT_Pin);
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
  MX_RTC_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
	HAL_GPIO_WritePin(K1_GPIO_Port, K1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(K2_GPIO_Port, K2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(K3_GPIO_Port, K3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(K4_GPIO_Port, K4_Pin, GPIO_PIN_SET);
	HAL_TIM_Base_Start_IT(&htim1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

    /* USER CODE END WHILE */
		clearAll_K(); // 关闭 所有数码管 不显示
		// 先把k4 打开 (打开第四个数码管)
		HAL_GPIO_WritePin(K4_GPIO_Port, K4_Pin, GPIO_PIN_SET);
		// 写入分钟数 的个位数部分
		numberToLed(minute%10);
		myDelay(5000);
		//HAL_Delay(10);
		
		
		
		clearAll_K(); // 关闭 所有k 不显示
		// 把k3 打开 
		HAL_GPIO_WritePin(K3_GPIO_Port, K3_Pin, GPIO_PIN_SET);
		// 写入分钟数 的十位数部分
		numberToLed(minute/10);
		myDelay(5000);
		
		
		
		clearAll_K(); // 关闭 所有k 不显示
		// 先把k2 打开 
		HAL_GPIO_WritePin(K2_GPIO_Port, K2_Pin, GPIO_PIN_SET);
		// 写入小时数 的个位数部分
		numberToLed(hour%10);
		myDelay(5000);
		
		
		clearAll_K();
		// 把k1 打开 
		HAL_GPIO_WritePin(K1_GPIO_Port, K1_Pin, GPIO_PIN_SET);
		// 写入小时数 的十位数部分
		numberToLed(hour/10);
		myDelay(5000);
		
		
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL8;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef DateToUpdate = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */
  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_ALARM;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 0x0;
  sTime.Minutes = 0x0;
  sTime.Seconds = 0x0;

  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  DateToUpdate.WeekDay = RTC_WEEKDAY_MONDAY;
  DateToUpdate.Month = RTC_MONTH_JANUARY;
  DateToUpdate.Date = 0x1;
  DateToUpdate.Year = 0x0;

  if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 64000;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 1;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, K4_Pin|KEY1_Pin|D_Pin|G_Pin
                          |F_Pin|A_Pin|POINT_Pin|B_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, KEY0_Pin|K2_Pin|C_Pin|E_Pin
                          |DP_Pin|K3_Pin|K1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : K4_Pin KEY1_Pin D_Pin G_Pin
                           F_Pin A_Pin POINT_Pin B_Pin */
  GPIO_InitStruct.Pin = K4_Pin|KEY1_Pin|D_Pin|G_Pin
                          |F_Pin|A_Pin|POINT_Pin|B_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : KEY0_Pin K2_Pin C_Pin E_Pin
                           DP_Pin K3_Pin K1_Pin */
  GPIO_InitStruct.Pin = KEY0_Pin|K2_Pin|C_Pin|E_Pin
                          |DP_Pin|K3_Pin|K1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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
