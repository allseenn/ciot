#include "main.h"
#include "stm32f1xx_hal.h"

#define LED_PORT                GPIOA
#define LED_PIN                 GPIO_PIN_0
#define YELLOW_PIN              GPIO_PIN_1
#define GREEN_PIN               GPIO_PIN_4
#define LED_PORT_CLK_ENABLE     __HAL_RCC_GPIOA_CLK_ENABLE

void SystemClock_Config(void);
void initGPIO(int led);
void SwitchLight(int led, int time);
void ToggleLight(int led, int time);

void initGPIO(int led)
{
    GPIO_InitTypeDef GPIO_Config;

    GPIO_Config.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_Config.Pull = GPIO_NOPULL;
    GPIO_Config.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_Config.Pin = led;

    LED_PORT_CLK_ENABLE();
    HAL_GPIO_Init(LED_PORT, &GPIO_Config);
}

void SwitchLight(int led, int time)
{
    HAL_GPIO_WritePin(LED_PORT, led, GPIO_PIN_SET);
    HAL_Delay(time);
    HAL_GPIO_WritePin(LED_PORT, led, GPIO_PIN_RESET);
}

void ToggleLight(int led, int time)
{
    for(int i = 0; i < 3; i++)
    {
        HAL_Delay(time);
        HAL_GPIO_WritePin(LED_PORT, led, GPIO_PIN_SET);
        HAL_Delay(time);
        HAL_GPIO_WritePin(LED_PORT, led, GPIO_PIN_RESET);
    }
}

int main(void)
{
    HAL_Init();
    SystemClock_Config();

    initGPIO(LED_PIN);
    initGPIO(YELLOW_PIN);
    initGPIO(GREEN_PIN);

    while (1)
    {
        SwitchLight(LED_PIN, 3000);
        SwitchLight(YELLOW_PIN, 1500);
        SwitchLight(GREEN_PIN, 3000);
        ToggleLight(GREEN_PIN, 500);
        SwitchLight(YELLOW_PIN, 1500);
    }

    return 0;
}

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
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                  | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
}

void Error_Handler(void)
{
    while(1)
    {
        // Stay here...
    }
}
