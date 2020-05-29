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
  PA_11, // 0/OTG_FS_N
  PA_12, // 1/OTG_FS_P

  PD_6,  // 2/UART_RX
  PD_5,  // 3/UART_TX

  PB_7,  // 4/DXL_RX 
  PB_6,  // 5/DXL_TX
  PB_8,  // 6/DIR_PIN

  PC_12, // 8/BUTTON
  PC_11, // 9/LED

  PA_1,  // 10/ETH_REF_CLK
  PA_7,  // 11/ETH_CRS_DV
  PA_2,  // 12/ETH_MDIO
  PC_1,  // 13/ETH_MDC
  PC_0,  // 14/ETH_RXER
  PC_4,  // 15/ETH_RXD0
  PC_5,  // 16/ETH_RXD1
  PB_11, // 17/ETH_RX_EN
  PB_12, // 18/ETH_TXD0
  PB_13  // 19/ETH_TXD1
};

#ifdef __cplusplus
}
#endif

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 168000000
  *            HCLK(Hz)                       = 168000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 25000000
  *            PLL_M                          = 25
  *            PLL_N                          = 336
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale2 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  HAL_StatusTypeDef ret = HAL_OK;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);

  if(ret != HAL_OK)
  {
    while(1) { ; }
  }

//  HAL_PWREx_EnableOverDrive();

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_HCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
  if(ret != HAL_OK){
    while(1) { ; }
  }

  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_CLK48|RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_USART2;
  PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48SOURCE_PLL;
  PeriphClkInitStruct.Usart1ClockSelection = RCC_USART1CLKSOURCE_SYSCLK;
  PeriphClkInitStruct.Usart2ClockSelection = RCC_USART2CLKSOURCE_SYSCLK;
  ret = HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);
  if(ret != HAL_OK){
    while(1) { ; }
  }
}


#if 0
DMA_HandleTypeDef huart1dmatx, huart1dmarx;
DMA_HandleTypeDef huart2dmatx, huart2dmarx;

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART1)
  {
    __HAL_RCC_USART1_CLK_ENABLE();
    /* Enable DMA clock */
    __HAL_RCC_DMA2_CLK_ENABLE();

  //  /* Configure the DMA handler for Transmission process */
  //  huart1dmatx.Instance                 = DMA2_Stream7;
  //  huart1dmatx.Init.Channel             = DMA_CHANNEL_4;
  //  huart1dmatx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
  //  huart1dmatx.Init.PeriphInc           = DMA_PINC_DISABLE;
  //  huart1dmatx.Init.MemInc              = DMA_MINC_ENABLE;
  //  huart1dmatx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  //  huart1dmatx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
  //  huart1dmatx.Init.Mode                = DMA_NORMAL;
  //  huart1dmatx.Init.Priority            = DMA_PRIORITY_LOW;
  //  huart1dmatx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
  //  huart1dmatx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
  //  huart1dmatx.Init.MemBurst            = DMA_MBURST_INC4;
  //  huart1dmatx.Init.PeriphBurst         = DMA_PBURST_INC4;  

  //  HAL_DMA_Init(&huart1dmatx);

  //  /* Associate the initialized DMA handle to the the UART handle */
  //  __HAL_LINKDMA(huart, hdmatx, (huart1dmatx));

    /* Configure the DMA handler for reception process */
    huart1dmarx.Instance                 = DMA2_Stream5;
    huart1dmarx.Init.Channel             = DMA_CHANNEL_4;
    huart1dmarx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
    huart1dmarx.Init.PeriphInc           = DMA_PINC_DISABLE;
    huart1dmarx.Init.MemInc              = DMA_MINC_ENABLE;
    huart1dmarx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    huart1dmarx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
    huart1dmarx.Init.Mode                = DMA_CIRCULAR;
    huart1dmarx.Init.Priority            = DMA_PRIORITY_HIGH;
    huart1dmarx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
    huart1dmarx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
    huart1dmarx.Init.MemBurst            = DMA_MBURST_INC4;
    huart1dmarx.Init.PeriphBurst         = DMA_PBURST_INC4;

    HAL_DMA_Init(&huart1dmarx);

    /* Associate the initialized DMA handle to the the UART handle */
    __HAL_LINKDMA(huart, hdmarx, huart1dmarx);

    /*##-4- Configure the NVIC for DMA #########################################*/
    // HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 0, 1);
    // HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);

    HAL_NVIC_SetPriority(DMA2_Stream5_IRQn, 0, 1);
    HAL_NVIC_EnableIRQ(DMA2_Stream5_IRQn);

    HAL_NVIC_SetPriority(USART1_IRQn, 10, 1);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  }

  if (huart->Instance == USART2)
  {
    __HAL_RCC_USART2_CLK_ENABLE();
    /* Enable DMA clock */
    __HAL_RCC_DMA1_CLK_ENABLE();

  //  /* Configure the DMA handler for Transmission process */
  //  huart2dmatx.Instance                 = DMA1_Stream6;
  //  huart2dmatx.Init.Channel             = DMA_CHANNEL_4;  
  //  huart2dmatx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
  //  huart2dmatx.Init.PeriphInc           = DMA_PINC_DISABLE;
  //  huart2dmatx.Init.MemInc              = DMA_MINC_ENABLE;
  //  huart2dmatx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  //  huart2dmatx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
  //  huart2dmatx.Init.Mode                = DMA_NORMAL;
  //  huart2dmatx.Init.Priority            = DMA_PRIORITY_LOW;
  //  huart2dmatx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
  //  huart2dmatx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
  //  huart2dmatx.Init.MemBurst            = DMA_MBURST_INC4;
  //  huart2dmatx.Init.PeriphBurst         = DMA_PBURST_INC4;  

  //  HAL_DMA_Init(&huart2dmatx);

  //  /* Associate the initialized DMA handle to the the UART handle */
  //  __HAL_LINKDMA(huart, hdmatx, (huart2dmatx));

    /* Configure the DMA handler for reception process */
    huart2dmarx.Instance                 = DMA1_Stream5;
    huart2dmarx.Init.Channel             = DMA_CHANNEL_4;
    huart2dmarx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
    huart2dmarx.Init.PeriphInc           = DMA_PINC_DISABLE;
    huart2dmarx.Init.MemInc              = DMA_MINC_ENABLE;
    huart2dmarx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    huart2dmarx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
    huart2dmarx.Init.Mode                = DMA_CIRCULAR;
    huart2dmarx.Init.Priority            = DMA_PRIORITY_HIGH;
    huart2dmatx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
    huart2dmatx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
    huart2dmatx.Init.MemBurst            = DMA_MBURST_INC4;
    huart2dmatx.Init.PeriphBurst         = DMA_PBURST_INC4;      

    HAL_DMA_Init(&huart2dmarx);

    /* Associate the initialized DMA handle to the the UART handle */
    __HAL_LINKDMA(huart, hdmarx, huart2dmarx);

    /*##-4- Configure the NVIC for DMA #########################################*/
    // HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, 0, 1);
    // HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);

    HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 0, 1);
    HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);

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
    HAL_NVIC_DisableIRQ(DMA2_Stream5_IRQn);
    HAL_NVIC_DisableIRQ(DMA2_Stream7_IRQn);
  }

  if (huart->Instance == USART2)
  {
    __HAL_RCC_USART2_FORCE_RESET();
    __HAL_RCC_USART2_RELEASE_RESET();

    HAL_NVIC_DisableIRQ(USART2_IRQn);
    HAL_NVIC_DisableIRQ(DMA1_Stream5_IRQn);
    HAL_NVIC_DisableIRQ(DMA1_Stream6_IRQn);
  }
}

void DMA2_Channel7_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&huart1dmatx);
}

void DMA2_Channel5_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&huart1dmarx);
}

void DMA1_Channel6_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&huart2dmatx);
}

void DMA1_Channel5_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&huart2dmarx);
}
#endif

#ifdef __cplusplus
}
#endif
