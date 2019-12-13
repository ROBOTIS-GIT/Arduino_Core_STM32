/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "pins_arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

// Pin number
const PinName digitalPin[] = {
  PA_6,  // A0//VOLTAGE
  PA_7,  // A1//CURRENT
  
  PA_10, // 2/UART_RX
  PA_9,  // 3/UART_TX

  PA_3,  // 4/DXL_RX 
  PA_2,  // 5/DXL_TX
  PA_0,  // 6/DIR_PIN

  PA_5,  // 7//DIR_PWR_EN

  PA_1,  // 8/BUTTON
  PA_4,  // 9/LED

  // DUPLICATE
  PA_6,  // 10/A0
  PA_7   // 11/A1 
};

#ifdef __cplusplus
}
#endif

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif
#include <string.h>

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 32000000
  *            HCLK(Hz)                       = 32000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            HSE Frequency(Hz)              = 8000000
  *            HSI Frequency(Hz)              = 16000000
  *            PLLMUL                         = 8
  *            PLLDIV                         = 2
  *            Flash Latency(WS)              = 1
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  memset(&RCC_ClkInitStruct, 0, sizeof(RCC_ClkInitTypeDef));
  memset(&RCC_OscInitStruct, 0, sizeof(RCC_OscInitTypeDef));

  /** Configure the main internal regulator output voltage 
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL8;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLL_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    while(1);
  }

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    while(1);
  }
}

DMA_HandleTypeDef huart1dmatx, huart1dmarx;
DMA_HandleTypeDef huart2dmatx, huart2dmarx;

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART1)
  {
    __HAL_RCC_USART1_CLK_ENABLE();
    /* Enable DMA clock */
    __HAL_RCC_DMA1_CLK_ENABLE();

  //  /* Configure the DMA handler for Transmission process */
  //  huart1dmatx.Instance                 = DMA1_Channel4;
  //  huart1dmatx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
  //  huart1dmatx.Init.PeriphInc           = DMA_PINC_DISABLE;
  //  huart1dmatx.Init.MemInc              = DMA_MINC_ENABLE;
  //  huart1dmatx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  //  huart1dmatx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
  //  huart1dmatx.Init.Mode                = DMA_NORMAL;
  //  huart1dmatx.Init.Priority            = DMA_PRIORITY_LOW;

  //  HAL_DMA_Init(&huart1dmatx);

  //  /* Associate the initialized DMA handle to the the UART handle */
  //  __HAL_LINKDMA(huart, hdmatx, (huart1dmatx));

    /* Configure the DMA handler for reception process */
    huart1dmarx.Instance                 = DMA1_Channel5;
    huart1dmarx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
    huart1dmarx.Init.PeriphInc           = DMA_PINC_DISABLE;
    huart1dmarx.Init.MemInc              = DMA_MINC_ENABLE;
    huart1dmarx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    huart1dmarx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
    huart1dmarx.Init.Mode                = DMA_CIRCULAR;
    huart1dmarx.Init.Priority            = DMA_PRIORITY_HIGH;

    HAL_DMA_Init(&huart1dmarx);

    /* Associate the initialized DMA handle to the the UART handle */
    __HAL_LINKDMA(huart, hdmarx, huart1dmarx);

    /*##-4- Configure the NVIC for DMA #########################################*/
    // HAL_NVIC_SetPriority(DMA1_Channel4_IRQn, 0, 1);
    // HAL_NVIC_EnableIRQ(DMA1_Channel4_IRQn);

    HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 0, 1);
    HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);

    HAL_NVIC_SetPriority(USART1_IRQn, 10, 1);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  }

  if (huart->Instance == USART2)
  {
    __HAL_RCC_USART2_CLK_ENABLE();
    /* Enable DMA clock */
    __HAL_RCC_DMA1_CLK_ENABLE();

  //  /* Configure the DMA handler for Transmission process */
  //  huart2dmatx.Instance                 = DMA1_Channel7;
  //  huart2dmatx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
  //  huart2dmatx.Init.PeriphInc           = DMA_PINC_DISABLE;
  //  huart2dmatx.Init.MemInc              = DMA_MINC_ENABLE;
  //  huart2dmatx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  //  huart2dmatx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
  //  huart2dmatx.Init.Mode                = DMA_NORMAL;
  //  huart2dmatx.Init.Priority            = DMA_PRIORITY_LOW;

  //  HAL_DMA_Init(&huart2dmatx);

  //  /* Associate the initialized DMA handle to the the UART handle */
  //  __HAL_LINKDMA(huart, hdmatx, (huart2dmatx));

    /* Configure the DMA handler for reception process */
    huart2dmarx.Instance                 = DMA1_Channel6;
    huart2dmarx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
    huart2dmarx.Init.PeriphInc           = DMA_PINC_DISABLE;
    huart2dmarx.Init.MemInc              = DMA_MINC_ENABLE;
    huart2dmarx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    huart2dmarx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
    huart2dmarx.Init.Mode                = DMA_CIRCULAR;
    huart2dmarx.Init.Priority            = DMA_PRIORITY_HIGH;

    HAL_DMA_Init(&huart2dmarx);

    /* Associate the initialized DMA handle to the the UART handle */
    __HAL_LINKDMA(huart, hdmarx, huart2dmarx);

    /*##-4- Configure the NVIC for DMA #########################################*/
    // HAL_NVIC_SetPriority(DMA1_Channel7_IRQn, 0, 1);
    // HAL_NVIC_EnableIRQ(DMA1_Channel7_IRQn);

    HAL_NVIC_SetPriority(DMA1_Channel6_IRQn, 0, 1);
    HAL_NVIC_EnableIRQ(DMA1_Channel6_IRQn);

    HAL_NVIC_SetPriority(USART2_IRQn, 10, 1);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{

  if (huart->Instance == USART1)
  {
    __HAL_RCC_USART1_FORCE_RESET();
    __HAL_RCC_USART1_RELEASE_RESET();

    HAL_NVIC_DisableIRQ(USART1_IRQn);
    HAL_NVIC_DisableIRQ(DMA1_Channel4_IRQn);
    HAL_NVIC_DisableIRQ(DMA1_Channel5_IRQn);
  }

  if (huart->Instance == USART2)
  {
    __HAL_RCC_USART2_FORCE_RESET();
    __HAL_RCC_USART2_RELEASE_RESET();

    HAL_NVIC_DisableIRQ(USART2_IRQn);
    HAL_NVIC_DisableIRQ(DMA1_Channel7_IRQn);
    HAL_NVIC_DisableIRQ(DMA1_Channel6_IRQn);
  }
}

void DMA1_Channel4_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&huart1dmatx);
}

void DMA1_Channel5_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&huart1dmarx);
}

void DMA1_Channel7_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&huart2dmatx);
}

void DMA1_Channel6_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&huart2dmarx);
}

#ifdef __cplusplus
}
#endif
