/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

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
/* USER CODE BEGIN Variables */

osThreadId defaultTaskHandle;
osThreadId led_blink_varHandle;
osThreadId led_blink_equalHandle;
osThreadId button_pressedHandle;

int frequency=1;	//Hz
/* USER CODE END Variables */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

void StartDefaultTask(void const * argument);
void StartTask0(void const * argument);
void StartTask1(void const * argument);
void StartTask2(void const * argument);

/* USER CODE END FunctionPrototypes */

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  //osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  //defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

	// uncoment tasks for right application

	//app 1-Prepare a simple FreeRTOS application, capable of blinking led light with a frequency equal to 10Hz

  //osThreadDef(led_blink_equal, StartTask0, osPriorityIdle, 0, 128);
  //led_blink_equalHandle = osThreadCreate(osThread(led_blink_equal), NULL);

  //app 2-Prepare an application that has 2 tasks running in parallel

  //task1
  osThreadDef(led_blink_var, StartTask1, osPriorityIdle, 0, 128);
  led_blink_varHandle = osThreadCreate(osThread(led_blink_var), NULL);
  //task2
  osThreadDef(button_pressed, StartTask2, osPriorityIdle, 0, 128);
  button_pressedHandle = osThreadCreate(osThread(button_pressed), NULL);


  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
	  osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}
void StartTask0(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
	//Prepare a simple FreeRTOS application, capable of blinking led light with a frequency equal to 10Hz
  /* Infinite loop */
  for(;;)
  {
	  HAL_GPIO_TogglePin(GPIOA,LD2_Pin);
	  osDelay(100);	//100ms-> 0.1 s -> 10Hz
  }
  /* USER CODE END StartDefaultTask */
}

void StartTask1(void const * argument)
{
  /* USER CODE BEGIN StartTask02 */
	//blinks a LED with the frequency defined as a modifiable parameter with some initial value e.g. 10,
	// frequency in HZ
  /* Infinite loop */
  for(;;)
  {
		HAL_GPIO_TogglePin(GPIOA,LD2_Pin);
	    osDelay(1000/frequency);	//100ms-> 0.1 s -> 10Hz
  }
  /* USER CODE END StartTask22 */
}
void StartTask2(void const * argument)
{
  /* USER CODE BEGIN StartTask02 */
	//runs periodically every 1s for checking whether the button has ever been pressed (no matter what amount of times).
	//When the press was detected, the modifiable parameter shall be increased with an additional chosen value
  /* Infinite loop */
	const int inc_value=1; // Hz
  for(;;)
  {
	  if(button_pressed==true)
	  {
		  frequency+=inc_value;
		  button_pressed=false;
	  }
	  osDelay(1000);
  }

  /* USER CODE END StartTask22 */
}


/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the led_blink thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */

//void StartTask02(void const * argument)
//{
//  /* USER CODE BEGIN StartTask02 */
//  /* Infinite loop */
//  for(;;)
//  {
//		HAL_GPIO_TogglePin(GPIOA,LD2_Pin);
//	    osDelay(100+count);
//  }
//  /* USER CODE END StartTask02 */
//}

/* USER CODE BEGIN Header_StartTask03 */
/**
* @brief Function implementing the button_press thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask03 */
//void StartTask03(void const * argument)
//{
//  /* USER CODE BEGIN StartTask03 */
//  /* Infinite loop */
//  for(;;)
//  {
//
//    osDelay(1);
//  }
//  /* USER CODE END StartTask03 */
//}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
