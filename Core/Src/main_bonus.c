// Кнопка 1
// Короткое нажатие: меняет частоту моргания светодиода в 3 значениях
// Длинное нажатие: переключает светодиод на один (если два на два)
// Светодиоды при длинном не горят
// Кнопка 2
// Единичное нажатие: меняет количество светодиодов (если 2 - оба моргают с частотой)

#include <C:/LB1_MC/Laboratory_Practice/Laboratory_Practice/Core/Inc/init.h>

uint8_t LED_1_STATE = 0; 
uint8_t LED_2_STATE = 0;
uint8_t LED_3_STATE = 0;  

uint32_t BUTTON_1_STATE = 0; // состояние 1-ой внешней кнопки
uint32_t BUTTON_2_STATE = 0; // состояние 2-ой внешней кнопки
uint32_t counter = 0;        // переменная-счётчик для первой кнопки
uint8_t flag = 0;            // проверка на единичное нажатие 2-ой кнопки
uint32_t counter_led = 0;        // переменная-счётчик для первой кнопки

uint8_t MODE1 = 0;            // режим работы
// режим 0:  2 Гц
// режим 1:  5 Гц
// режим 2:  10 Гц

uint8_t MODE1_1 = 0;
// режим 0: зелёный светодиод
// режим 1: жёлтый светодиод
// режим 2: красный светодиод

uint8_t MODE2 = 0;
// режим 0: один светодиод
// режим 1: два светодиода
// режим 2: три светодиода


const uint32_t frequency = 1000000 * 1.1; // примерно секунда

// массив для включения светодиодов
uint32_t MODE_1[3][3] = 
{
    {GPIO_BSRR_BS0, GPIO_BSRR_BR1, GPIO_BSRR_BR4},
    
    {GPIO_BSRR_BR0, GPIO_BSRR_BS1, GPIO_BSRR_BR4},
    
    {GPIO_BSRR_BR0, GPIO_BSRR_BR1, GPIO_BSRR_BS4}
};

// массив для выключения светодиодов
const uint32_t MODE_RESET[3][3] = 
{
    {GPIO_BSRR_BR0, GPIO_BSRR_BR1, GPIO_BSRR_BR4},
    
    {GPIO_BSRR_BR4, GPIO_BSRR_BR0, GPIO_BSRR_BR1},
    
    {GPIO_BSRR_BR1, GPIO_BSRR_BR4, GPIO_BSRR_BR0}
};

void MODE_SELECTION_BUT1(void) 
{
    counter = 0;
    while(BUTTON_1_STATE != 0) 
    {
        counter++;
        BUTTON_1_STATE = READ_BIT(GPIOB->IDR, GPIO_IDR_IDR_10);
    }

    if (counter != 0) 
    {
        if (counter > 20000 && counter < frequency / 3) 
        {
            MODE1++;
        }
        else if (counter >= frequency / 3)
        {
            MODE1_1++;
        }
    }

    if (MODE1 > 2) {
        MODE1 = 0;
    }

    if (MODE1_1 > 2) {
        MODE1_1 = 0;
    }
}

// смена режима по состоянию 4 кнопки
void MODE_SELECTION_BUT2(void) 
{
    if (BUTTON_2_STATE > 0 && flag == 0) 
    {
        flag = 1;
        MODE2++;
        if (MODE2 > 2) 
        {
            MODE2 = 0;
        }
    }
    else if (BUTTON_2_STATE == 0 && flag) // проверка зажатия
    {
        flag = 0;
    }
}

uint8_t BUTTON_STATE(void) 
{
    BUTTON_1_STATE = READ_BIT(GPIOB->IDR, GPIO_IDR_IDR_10);
    BUTTON_2_STATE = READ_BIT(GPIOB->IDR, GPIO_IDR_IDR_5);
    if (BUTTON_1_STATE > 0 || (BUTTON_2_STATE > 0 && flag == 0) || (BUTTON_2_STATE == 0 && flag == 1)) 
    {
        return 1;
    }
    else 
    {
        return 0;
    }
}

void LED_MODE1(void) 
{
    if (MODE1 == 0) 
    {
        SET_BIT(GPIOA->BSRR, MODE_1[MODE1_1][0]);
        SET_BIT(GPIOA->BSRR, MODE_1[MODE1_1][1]);
        SET_BIT(GPIOA->BSRR, MODE_1[MODE1_1][2]);
        counter_led = 0;
        while (counter_led < frequency / 2) 
        {
            counter_led++;
            if (BUTTON_STATE()) 
            {
                SET_BIT(GPIOA->BSRR, MODE_RESET[MODE1_1][0]);
                SET_BIT(GPIOA->BSRR, MODE_RESET[MODE1_1][1]);
                SET_BIT(GPIOA->BSRR, MODE_RESET[MODE1_1][2]);
                break;
            }
        }

        SET_BIT(GPIOA->BSRR, MODE_RESET[MODE1_1][0]);
        SET_BIT(GPIOA->BSRR, MODE_RESET[MODE1_1][1]);
        SET_BIT(GPIOA->BSRR, MODE_RESET[MODE1_1][2]);  
        
        counter_led = 0;
        while (counter_led < frequency / 2) 
        {
            counter_led++;
            if (BUTTON_STATE()) 
            {
                SET_BIT(GPIOA->BSRR, MODE_RESET[MODE1_1][0]);
                SET_BIT(GPIOA->BSRR, MODE_RESET[MODE1_1][1]);
                SET_BIT(GPIOA->BSRR, MODE_RESET[MODE1_1][2]);
                break;
            }
        }

    }
    else if (MODE1 == 1) 
    {
        SET_BIT(GPIOA->BSRR, MODE_1[MODE1_1][0]);
        SET_BIT(GPIOA->BSRR, MODE_1[MODE1_1][1]);
        SET_BIT(GPIOA->BSRR, MODE_1[MODE1_1][2]);
        counter_led = 0;
        while (counter_led < frequency / 10) 
        {
            counter_led++;
            if (BUTTON_STATE()) 
            {
                SET_BIT(GPIOA->BSRR, MODE_RESET[MODE1_1][0]);
                SET_BIT(GPIOA->BSRR, MODE_RESET[MODE1_1][1]);
                SET_BIT(GPIOA->BSRR, MODE_RESET[MODE1_1][2]);
                break;
            }
        }

        SET_BIT(GPIOA->BSRR, MODE_RESET[MODE1_1][0]);
        SET_BIT(GPIOA->BSRR, MODE_RESET[MODE1_1][1]);
        SET_BIT(GPIOA->BSRR, MODE_RESET[MODE1_1][2]);

        counter_led = 0;
        while (counter_led < frequency / 10) 
        {
            counter_led++;
            if (BUTTON_STATE()) 
            {
                SET_BIT(GPIOA->BSRR, MODE_RESET[MODE1_1][0]);
                SET_BIT(GPIOA->BSRR, MODE_RESET[MODE1_1][1]);
                SET_BIT(GPIOA->BSRR, MODE_RESET[MODE1_1][2]);
                break;
            }
        }

    }
    else 
    {
        SET_BIT(GPIOA->BSRR, MODE_1[MODE1_1][0]);
        SET_BIT(GPIOA->BSRR, MODE_1[MODE1_1][1]);
        SET_BIT(GPIOA->BSRR, MODE_1[MODE1_1][2]);
        counter_led = 0;
        while (counter_led < frequency / 15) 
        {
            counter_led++;
            if (BUTTON_STATE()) 
            {
                SET_BIT(GPIOA->BSRR, MODE_RESET[MODE1_1][0]);
                SET_BIT(GPIOA->BSRR, MODE_RESET[MODE1_1][1]);
                SET_BIT(GPIOA->BSRR, MODE_RESET[MODE1_1][2]);
                break;
            }
        }

        SET_BIT(GPIOA->BSRR, MODE_RESET[MODE1_1][0]);
        SET_BIT(GPIOA->BSRR, MODE_RESET[MODE1_1][1]);
        SET_BIT(GPIOA->BSRR, MODE_RESET[MODE1_1][2]);

        counter_led = 0;
        while (counter_led < frequency / 15) 
        {
            counter_led++;
            if (BUTTON_STATE()) 
            {
                SET_BIT(GPIOA->BSRR, MODE_RESET[MODE1_1][0]);
                SET_BIT(GPIOA->BSRR, MODE_RESET[MODE1_1][1]);
                SET_BIT(GPIOA->BSRR, MODE_RESET[MODE1_1][2]);
                break;
            }
        }

    }
}

void LED_MODE2(void) 
{
    if (MODE2 == 0) 
    {
        MODE_1[0][0] = GPIO_BSRR_BS0;
        MODE_1[0][1] = GPIO_BSRR_BR1;
        MODE_1[0][2] = GPIO_BSRR_BR4;

        MODE_1[1][0] = GPIO_BSRR_BR0;
        MODE_1[1][1] = GPIO_BSRR_BS1;
        MODE_1[1][2] = GPIO_BSRR_BR4;

        MODE_1[2][0] = GPIO_BSRR_BR0;
        MODE_1[2][1] = GPIO_BSRR_BR1;
        MODE_1[2][2] = GPIO_BSRR_BS4;
    }
    else if (MODE2 == 1) 
    {
        MODE_1[0][0] = GPIO_BSRR_BS0;
        MODE_1[0][1] = GPIO_BSRR_BS1;
        MODE_1[0][2] = GPIO_BSRR_BR4;

        MODE_1[1][0] = GPIO_BSRR_BR0;
        MODE_1[1][1] = GPIO_BSRR_BS1;
        MODE_1[1][2] = GPIO_BSRR_BS4;

        MODE_1[2][0] = GPIO_BSRR_BS0;
        MODE_1[2][1] = GPIO_BSRR_BR1;
        MODE_1[2][2] = GPIO_BSRR_BS4;
    }
    else 
    {
        MODE_1[0][0] = GPIO_BSRR_BS0;
        MODE_1[0][1] = GPIO_BSRR_BS1;
        MODE_1[0][2] = GPIO_BSRR_BS4;

        MODE_1[1][0] = GPIO_BSRR_BS0;
        MODE_1[1][1] = GPIO_BSRR_BS1;
        MODE_1[1][2] = GPIO_BSRR_BS4;

        MODE_1[2][0] = GPIO_BSRR_BS0;
        MODE_1[2][1] = GPIO_BSRR_BS1;
        MODE_1[2][2] = GPIO_BSRR_BS4;
    }
}

int main(void) 
{
    GPIO_Init(); // подключение портов GPIOA|GPIOB|GPIOC

    while(1) {
        // чтение состояния кнопки для управления светодиодами
        BUTTON_1_STATE = READ_BIT(GPIOB->IDR, GPIO_IDR_IDR_10);

        if (BUTTON_1_STATE > 0) {
            BUTTON_2_STATE = 0;
        }
        else 
        {
            BUTTON_2_STATE = READ_BIT(GPIOB->IDR, GPIO_IDR_IDR_5);
        }
        MODE_SELECTION_BUT2();
       
        MODE_SELECTION_BUT1();

        LED_MODE2();
        LED_MODE1();
    }
}