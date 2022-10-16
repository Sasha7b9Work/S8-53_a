#include <stm32f207xx.h>
#include <stm32f2xx_hal.h>
#include <stm32f2xx_hal_tim.h>
#include <stm32f2xx_hal_gpio.h>
#include <stm32f2xx_hal_rcc.h>
#include <stm32f2xx_hal_dac.h>
#include "Hardware.h"
#include "ADC.h"
#include "Sound.h"
#include "Hardware/CLOCK.h"
#include "FSMC.h"
#include "Utils/GlobalFunctions.h"
#include "Hardware/Timer.h"
#include "Log.h"
#include "Ethernet/Ethernet.h"
#include "Display/Display.h"
#include "FlashDrive/FlashDrive.h"
#include "Panel/Panel.h"
#include <stm32f2xx_ll_dac.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static TIM_HandleTypeDef handleTIM13forTimer =
{
    TIM13,
    {
        119,                    // Init.Prescaler
        TIM_COUNTERMODE_UP,     // Init.CounterMode
        500,                    // Init.Period
        TIM_CLOCKDIVISION_DIV1  // Init.ClockDivision
    }
};

static CRC_HandleTypeDef crcHandle;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void SystemClock_Config();


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
    
void Hardware::Init(void)
{
    HAL_Init();

    SystemClock_Config();

    __GPIOA_CLK_ENABLE();
    __GPIOB_CLK_ENABLE();
    __GPIOC_CLK_ENABLE();
    __GPIOD_CLK_ENABLE();
    __GPIOE_CLK_ENABLE();
    __GPIOF_CLK_ENABLE();
    __GPIOG_CLK_ENABLE();
    __DMA1_CLK_ENABLE();        // ��� DAC1 (�������)
    
    __TIM6_CLK_ENABLE();        // ��� ������� �����������
    __TIM2_CLK_ENABLE();        // ��� �����
    __TIM7_CLK_ENABLE();        // ��� DAC1 (�������)
    __TIM13_CLK_ENABLE();
    __DAC_CLK_ENABLE();         // ��� �������
    __PWR_CLK_ENABLE();

    __SYSCFG_CLK_ENABLE();

    HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);

    // Timer  /////////////////////////////////////////////////////////////////
    //RCC_PCLK1Config(RCC_HCLK_Div1);

    // ������ ��� ��
    HAL_NVIC_SetPriority(TIM8_UP_TIM13_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);

    if (HAL_TIM_Base_Init(&handleTIM13forTimer) != HAL_OK)
    {
        HARDWARE_ERROR
    }

    if (HAL_TIM_Base_Start_IT(&handleTIM13forTimer) != HAL_OK)
    {
        HARDWARE_ERROR
    }

    // ������ ��� �����
    TIM_HandleTypeDef tim2handle =
    {
        TIM2,
        {
            0,
            TIM_COUNTERMODE_UP,
            0xffffffff,
            TIM_CLOCKDIVISION_DIV1
        }
    };

    if (HAL_TIM_Base_Init(&tim2handle) != HAL_OK)
    {
        HARDWARE_ERROR
    }

    if (HAL_TIM_Base_Start(&tim2handle) != HAL_OK)
    {
        HARDWARE_ERROR
    }

    Sound::Init();
    
    Panel::Init();

    FSMC::Init();

    ADConverter::Init();

    FlashDrive::Init();
    
// Analog and DAC programmable SPI ////////////////////////////////////////

    GPIO_InitTypeDef isGPIOG =
    {
        GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_5 | GPIO_PIN_7,     // GPIO_PIN_1 - ��� ������ � ��������
        GPIO_MODE_OUTPUT_PP,
        GPIO_NOPULL,
        GPIO_SPEED_HIGH,
        GPIO_AF0_MCO
    };
    HAL_GPIO_Init(GPIOG, &isGPIOG);

    isGPIOG.Pin = GPIO_PIN_1;
    isGPIOG.Mode = GPIO_MODE_OUTPUT_PP;
    isGPIOG.Pull = GPIO_NOPULL;

    HAL_GPIO_Init(GPIOG, &isGPIOG);
    
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_1, GPIO_PIN_RESET);                   // PG1 - ����� ����� 1, ������ �������, � ��������� ������� 0

    Clock::Init();

    crcHandle.Instance = CRC;
    if (HAL_CRC_Init(&crcHandle) != HAL_OK)
    {
        HARDWARE_ERROR;
    }
}

#ifdef __cplusplus
}
#endif



#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TIM8_UP_TIM13_IRQHandler(void)
{
    if (__HAL_TIM_GET_FLAG(&handleTIM13forTimer, TIM_FLAG_UPDATE) == SET && __HAL_TIM_GET_ITSTATUS(&handleTIM13forTimer, TIM_IT_UPDATE))
    {
        Timer::Update1ms();
        __HAL_TIM_CLEAR_FLAG(&handleTIM13forTimer, TIM_FLAG_UPDATE);
        __HAL_TIM_CLEAR_IT(&handleTIM13forTimer, TIM_IT_UPDATE);
    }
}


void DacUnderrunError_Callback(void)
{
    /* Note: Disable DAC interruption that caused this error before entering in */
    /*       infinite loop below.                                               */

    /* Disable interruption DAC channel1 underrun */
    LL_DAC_DisableIT_DMAUDR1(DAC1);

    /* Error from ADC */
//    LED_Blinking(LED_BLINK_ERROR);
}


void TIM6_DAC_IRQHandler(void)
{
    /* Check whether DAC channel1 underrun caused the DAC interruption */
    if (LL_DAC_IsActiveFlag_DMAUDR1(DAC1) != 0)
    {
        /* Clear flag DAC channel1 underrun */
        LL_DAC_ClearFlag_DMAUDR1(DAC1);

        /* Call interruption treatment function */
        DacUnderrunError_Callback();
    }
}

#ifdef __cplusplus
}
#endif

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void SystemClock_Config(void)
{
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_OscInitTypeDef RCC_OscInitStruct;

    // Enable HSE Oscillator and activate PLL with HSE as source
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 25;
    RCC_OscInitStruct.PLL.PLLN = 240;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 5;
    if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        // Initialization Error
        HARDWARE_ERROR
    }
    // Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers
    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
    if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
    {
        // Initialization Error
        HARDWARE_ERROR
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
uint Hardware::CalculateCRC32(uint address, uint numBytes)
{
    return HAL_CRC_Calculate(&crcHandle, (uint *)address, numBytes);
}
