#pragma once

#include "stm32f4xx_hal.h"

#define LED_GPIO GPIOC
#define LED_PIN  GPIO_PIN_4

class Board
{
public:
    Board(){};

    void Init(void)
    {
        HAL_Init();

        SystemClock_Config();

        __HAL_RCC_SYSCFG_CLK_ENABLE();
        __HAL_RCC_PWR_CLK_ENABLE();
        __HAL_RCC_GPIOC_CLK_ENABLE();
        
        LED_GPIO_Init();
    }

    void LED_Toggle(void)
    {
        HAL_GPIO_TogglePin(LED_GPIO, LED_PIN);
    }
    
    uint64_t Micros(void)
    {
        uint64_t ms;
        uint64_t value;
        ms = HAL_GetTick();
        value = ms * 1000 + (SysTick->LOAD - SysTick->VAL) * 1000 / SysTick->LOAD;
        return value;
    }

private:
    void SystemClock_Config(void)
    {
        RCC_OscInitTypeDef RCC_OscInitStruct = {0};
        RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

        /** Configure the main internal regulator output voltage*/
        __HAL_RCC_PWR_CLK_ENABLE();
        __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
        /** Initializes the RCC Oscillators according to the specified parameters
        * in the RCC_OscInitTypeDef structure.*/
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
        /** Initializes the CPU, AHB and APB buses clocks*/
        RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
        RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
        RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
        RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
        RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

        if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
        {
            Error_Handler();
        }
    }

    void LED_GPIO_Init(void)
    {
        GPIO_InitTypeDef GPIO_InitStruct;

        GPIO_InitStruct.Pin = LED_PIN;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        HAL_GPIO_Init(LED_GPIO, &GPIO_InitStruct);
    }

    void Error_Handler(void){};
};

#ifdef __cplusplus
extern "C"
{
#endif
    /******************************************************************************/
    /*           Cortex-M4 Processor Interruption and Exception Handlers          */
    /******************************************************************************/

    void NMI_Handler(void) {}

    void MemManage_Handler(void)
    {
        while (1)
        {
        }
    }

    void HardFault_Handler(void)
    {
        while (1)
        {
        }
    }

    void UsageFault_Handler(void)
    {
        while (1)
        {
        }
    }

    void BusFault_Handler(void)
    {
        while (1)
        {
        }
    }

    void SVC_Handler(void) {}

    void DebugMon_Handler(void) {}

    void PendSV_Handler(void) {}

    void SysTick_Handler(void)
    {
        HAL_IncTick();
    }

#ifdef __cplusplus
}
#endif
