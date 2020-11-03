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
TIM_HandleTypeDef htim1;

/* USER CODE BEGIN PV */
unsigned char breath_dir=0;// 记录流水灯方向  0是从灭到亮 
unsigned char breath_rt=0;// 流水灯计时器
unsigned char breath_speed_cnt=0;// 速度
unsigned char breath_Ton=0;//亮的时间占比
void setAllClear(){  // 清除函数 用于在转换灯的时候将其他灯熄灭 否则其他灯的状态可能亮着
	HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin,GPIO_PIN_SET);
	// 相关的流水灯的全局变量清空 
	breath_dir=0;
	breath_rt=0;
	breath_speed_cnt=0;
	breath_Ton=0;
}
void Breath_Light(unsigned char breath_speed,unsigned char breath_Ta,int currentLedNum)// 三个参数 呼吸速度 呼吸时间 当前进行的是那个呼吸灯
{
	// breath_Ta  是传入的值 这个值很重要
    // 是指的亮的总时间 他和基准频率 也就是这个函数调用的时间间隔共同决定了呼吸灯一个呼吸的时间
    // 举个例子 如果 这个函数每 0.1ms == 100μ s 调用一次 而且 breath_Ta =100    
    // 那么一个呼吸(从完全不亮 -> 亮 -> 完全不亮) 需要两秒 其中的数学关系我就不研究了 每啥意思
	GPIO_TypeDef * current_Led_GPIO_Port;   //当前led灯
	uint16_t current_Led_Pin;
	switch(currentLedNum){
		case 0: 
			current_Led_GPIO_Port = LED0_GPIO_Port;
			current_Led_Pin = LED0_Pin;
			break;
		case 1: 			
			current_Led_GPIO_Port = LED1_GPIO_Port;
			current_Led_Pin = LED1_Pin;
			break;
		case 2: 
			current_Led_GPIO_Port = LED2_GPIO_Port;
			current_Led_Pin = LED2_Pin;
			break;
		case 3: 
			current_Led_GPIO_Port = LED3_GPIO_Port;
			current_Led_Pin = LED3_Pin;
			break;
		case 4: 
			current_Led_GPIO_Port = LED4_GPIO_Port;
			current_Led_Pin = LED4_Pin;
			break;
		case 5: 
			current_Led_GPIO_Port = LED5_GPIO_Port;
			current_Led_Pin = LED5_Pin;
			break;
		case 6: 
			current_Led_GPIO_Port = LED6_GPIO_Port;
			current_Led_Pin = LED6_Pin;
			break;
		case 7: 
			current_Led_GPIO_Port = LED7_GPIO_Port;
			current_Led_Pin = LED7_Pin;
			break;
	}
	// 核心函数 
	/*   流水灯的原理  
	* 代表不亮  - 代表亮
	***************  无光
	-**************
	--*************
	---************
	----***********
	-----**********
	------********* 中等亮度
	-------********
	--------*******
	---------******
	----------*****
	-----------****
	------------***
	-------------**
	--------------*
	--------------- 最亮
	*/
	if(!breath_dir) // 如果breath_dir == 0 说明需要从不亮到全亮   
	{
		if(breath_Ta<breath_rt)// breath_rt 是用来计数的 到达breath_Ta 之后就需要进行增加亮度时间占比
							   //breath_Ta  是传入的值 这个值很重要
							   // 是指的亮的总时间 他和基准频率 也就是这个函数调用的时间间隔共同决定了呼吸灯一个呼吸的时间
							   // 举个例子 如果 这个函数每 0.1ms == 100μ s 调用一次 而且 breath_Ta =100    
							   // 那么一个呼吸(从完全不亮 -> 亮 -> 完全不亮) 需要两秒 其中的数学关系我就不研究了 每啥意思
		{
			breath_rt=0; // 归零 该进行下一周期的活动了  
			if(0==breath_speed_cnt++%breath_speed)	
			{
				breath_speed_cnt=0;
				breath_Ton++;//亮度占比增加
			}				
		}		
		else  //
		{
			breath_rt++;//计数器增加
		}
		if(breath_Ton>=breath_Ta)
		{		
			breath_dir=1;  // 当亮的时间占比已经全满的时候 说明这个时候亮度最高了 需要切换模式了
			breath_Ton=breath_Ta;  // 亮度时间不能超过总时间 所以要重置
		}	
		// 判断一下 如果breath_rt(计数器) 没有超过灯亮时间(亮度占比) 那么就把灯点亮(reset是点亮 因为reset是0 我的led灯是共阳极)
		// 因为灯亮时间(亮度占比) 一开始是个很小的数 breath_rt 很容易就能超过它 所以一开始肯定亮度低 		
		(breath_Ton>breath_rt)?(HAL_GPIO_WritePin(current_Led_GPIO_Port, current_Led_Pin,GPIO_PIN_RESET)):
													(HAL_GPIO_WritePin(current_Led_GPIO_Port, current_Led_Pin,GPIO_PIN_SET));	//Ton?????	
	}
	else  // 从最亮 延展到熄灭  和上方过程证号相反 差不多的代码 就不注释了
	{
		if(breath_Ta<breath_rt)
		{
			breath_rt=0; 
			if(0==breath_speed_cnt++%breath_speed)	
			{
				breath_speed_cnt=0;
				breath_Ton--;
			}		
		}		
		else  //
		{
			breath_rt++;
		}
		if(0>=breath_Ton)
		{		
			breath_dir=0;
			breath_Ton=0;
		}
		(breath_Ton>breath_rt)?(HAL_GPIO_WritePin(current_Led_GPIO_Port, current_Led_Pin,GPIO_PIN_RESET)):
													(HAL_GPIO_WritePin(current_Led_GPIO_Port, current_Led_Pin,GPIO_PIN_SET));	
	}
}

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
/* USER CODE BEGIN PFP */
int count = 0;  // 用于控制多少时间切换一次灯 
int currentLedNum = 0; // 用于控制当前灯
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	/*
	count++;
	if(count %2500 == 0)
		if(htim->Instance == TIM1){
			HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
		}
	*/
	if(htim->Instance == TIM1){
		Breath_Light(1,50,currentLedNum);//第一个参数是速度 没啥用 第二个是呼吸时间的一半 第三参数是当前的led的数字
		count++; // 计数器累加
		if(count % 5000 ==0){  // 这里分频后设置的时钟频率是64M 预分频6400
								// 然后每两次才触发更新事件 最终的时间间隔就是 (64M / 6400) * 2 = 0.2ms = 200μs 
								// 而这里 count * 0.2ms = 1s 所以每隔1s切换灯
			currentLedNum = (currentLedNum + 1) % 8; // 因为有8个灯 所以进行取模运算
			setAllClear();  // 每次切换的时候 把所有灯都设置不亮 然后清空流水灯相关的全局变量参数
			count = 0;  // 最好清一下0 不清也行
		}
	}

}

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
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
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
	// 启动定时器  tim1
	HAL_TIM_Base_Start_IT(&htim1);
  /* USER CODE END 2 */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
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
	// 这里分频后设置的时钟频率是64M 预分频6400
	// 然后每两次才触发更新事件 最终的时间间隔就是 (64M / 6400) * 2 = 0.2ms = 200μs 
  htim1.Instance = TIM1;  
  htim1.Init.Prescaler = 6400;  //64M 预分频6400  
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 2;  // 每2次进行一次更新事件
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
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED0_Pin|LED1_Pin|LED2_Pin|LED3_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED4_Pin|LED5_Pin|LED6_Pin|LED7_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : LED0_Pin LED1_Pin LED2_Pin LED3_Pin */
  GPIO_InitStruct.Pin = LED0_Pin|LED1_Pin|LED2_Pin|LED3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : LED4_Pin */
  GPIO_InitStruct.Pin = LED4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED4_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LED5_Pin LED6_Pin LED7_Pin */
  GPIO_InitStruct.Pin = LED5_Pin|LED6_Pin|LED7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

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
