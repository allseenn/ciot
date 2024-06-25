#include "main.h"

#define TRAF_PORT                GPIOA
#define TRAF_GREEN               GPIO_PIN_0
#define TRAF_YELLOW              GPIO_PIN_1
#define TRAF_RED                 GPIO_PIN_4

#define WALK_PORT                GPIOB
#define WALK_RED                 GPIO_PIN_10
#define WALK_YELLOW              GPIO_PIN_4
#define WALK_GREEN               GPIO_PIN_5

#define BUTTON_PORT              GPIOB
#define BUTTON_PIN               GPIO_PIN_3

#define TRAF_PORT_CLK_ENABLE     __HAL_RCC_GPIOA_CLK_ENABLE
#define WALK_PORT_CLK_ENABLE     __HAL_RCC_GPIOB_CLK_ENABLE
#define BUTTON_PORT_CLK_ENABLE   __HAL_RCC_GPIOB_CLK_ENABLE

#define LIGHT_DELAY              20
#define WALK_DELAY               2000
#define BLINK_DELAY              500

void initGPIO(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
int trafGreenOn();
int trafYellowOn();
int trafRedOn();
void trafOff();
void walkOff();
int walkGreenOn();
int walkYellowOn();
int walkRedOn();
void cleanCounters();

int trafGreenCount = 0;
int trafYellowCount = 0;
int trafRedCount = 0;
int trafBlinks = 0;

int main(void)
{
    HAL_Init();

    // Включение тактирования для портов
    TRAF_PORT_CLK_ENABLE();
    WALK_PORT_CLK_ENABLE();
    BUTTON_PORT_CLK_ENABLE();

    // Инициализация GPIO пинов
    initGPIO(TRAF_PORT, TRAF_RED);
    initGPIO(TRAF_PORT, TRAF_YELLOW);
    initGPIO(TRAF_PORT, TRAF_GREEN);

    initGPIO(WALK_PORT, WALK_RED);
    initGPIO(WALK_PORT, WALK_YELLOW);
    initGPIO(WALK_PORT, WALK_GREEN);

    initGPIO(BUTTON_PORT, BUTTON_PIN); // Инициализация кнопки как входа

    while (1)
    {
        if (HAL_GPIO_ReadPin(BUTTON_PORT, BUTTON_PIN) == GPIO_PIN_SET)
        {
            // Секвенция для пешеходного светофора
        	trafOff();
            for (int i = 0; i < 3; i++)
            {
              trafYellowOn();
              HAL_Delay(BLINK_DELAY);
              trafOff();
              HAL_Delay(BLINK_DELAY/3);
            }
            trafGreenOn(); // Включить красный свет дорожного светофора (наоборот)
            cleanCounters();
            walkOff();
            walkYellowOn();
            HAL_Delay(WALK_DELAY);

            walkOff();
            walkGreenOn();
            HAL_Delay(WALK_DELAY*2);

            walkOff();
            for (int i = 0; i < 3; i++)
            {
              walkYellowOn();
              HAL_Delay(BLINK_DELAY);
              walkOff();
              HAL_Delay(BLINK_DELAY/3);
            }
            walkOff();
            walkRedOn();
            HAL_Delay(WALK_DELAY);
        }
        else
        {
            // Обычный цикл дорожного светофора
            if(trafGreenCount < LIGHT_DELAY){
                trafGreenCount += trafGreenOn();
                walkOff();
                walkRedOn();
            }
            else if(trafYellowCount < LIGHT_DELAY){
                trafYellowCount += trafYellowOn();
                walkOff();
                walkRedOn();
            }
            else if(trafRedCount < LIGHT_DELAY){
                trafRedCount += trafRedOn();
                walkOff();
                walkRedOn();
            }
            else if(trafBlinks < LIGHT_DELAY){
                walkOff();
                walkRedOn();
                trafYellowOn();
                HAL_Delay(BLINK_DELAY);
                trafOff();
                trafBlinks += 5;
            }

            if(trafGreenCount >= LIGHT_DELAY && trafYellowCount >= LIGHT_DELAY && trafRedCount >= LIGHT_DELAY && trafBlinks >= LIGHT_DELAY){
              cleanCounters();
            }
        }

        HAL_Delay(100);
    }
    return 0;
}

void cleanCounters()
{
    trafGreenCount = 0;
    trafYellowCount = 0;
    trafRedCount = 0;
    trafBlinks = 0;
}

void initGPIO(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = GPIO_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void trafOff()
{
  HAL_GPIO_WritePin(TRAF_PORT, TRAF_GREEN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(TRAF_PORT, TRAF_YELLOW, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(TRAF_PORT, TRAF_RED, GPIO_PIN_RESET);
}

void walkOff()
{
  HAL_GPIO_WritePin(WALK_PORT, WALK_GREEN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(WALK_PORT, WALK_YELLOW, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(WALK_PORT, WALK_RED, GPIO_PIN_RESET);
}

int trafGreenOn()
{
  HAL_GPIO_WritePin(TRAF_PORT, TRAF_GREEN, GPIO_PIN_SET);
  HAL_GPIO_WritePin(TRAF_PORT, TRAF_YELLOW, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(TRAF_PORT, TRAF_RED, GPIO_PIN_RESET);
  return 1;
}

int trafYellowOn()
{
  HAL_GPIO_WritePin(TRAF_PORT, TRAF_GREEN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(TRAF_PORT, TRAF_YELLOW, GPIO_PIN_SET);
  HAL_GPIO_WritePin(TRAF_PORT, TRAF_RED, GPIO_PIN_RESET);
  return 1;
}

int trafRedOn()
{
  HAL_GPIO_WritePin(TRAF_PORT, TRAF_GREEN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(TRAF_PORT, TRAF_YELLOW, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(TRAF_PORT, TRAF_RED, GPIO_PIN_SET);
  return 1;
}

int walkGreenOn()
{
  HAL_GPIO_WritePin(WALK_PORT, WALK_GREEN, GPIO_PIN_SET);
  HAL_GPIO_WritePin(WALK_PORT, WALK_YELLOW, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(WALK_PORT, WALK_RED, GPIO_PIN_RESET);
  return 1;
}

int walkYellowOn()
{
  HAL_GPIO_WritePin(WALK_PORT, WALK_GREEN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(WALK_PORT, WALK_YELLOW, GPIO_PIN_SET);
  HAL_GPIO_WritePin(WALK_PORT, WALK_RED, GPIO_PIN_RESET);
  return 1;
}

int walkRedOn()
{
  HAL_GPIO_WritePin(WALK_PORT, WALK_GREEN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(WALK_PORT, WALK_YELLOW, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(WALK_PORT, WALK_RED, GPIO_PIN_SET);
  return 1;
}
