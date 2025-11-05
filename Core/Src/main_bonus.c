// Кнопка 1
// Короткое нажатие: меняет частоту моргания светодиода в 3 значениях
// Длинное нажатие: переключает светодиод на один
// Светодиоды при длинном нажатии не горят
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
uint8_t flag1 = 0;
uint8_t flag2 = 0;  
uint8_t flag3 = 0; 
uint32_t counter_led = 0;        // переменная-счётчик для первой кнопки
uint32_t counter_led1 = 0;
uint32_t counter_led2 = 0;
uint32_t counter_led3 = 0;

uint8_t MODE11 = 0;            // режим работы
uint8_t MODE12 = 0;
uint8_t MODE13 = 0;

uint8_t MODE1_1 = 0;
// режим 0: зелёный светодиод
// режим 1: жёлтый светодиод
// режим 2: красный светодиод

int8_t MODE2 = -1;
// режим 0: один светодиод
// режим 1: два светодиода
// режим 2: три светодиода


const uint32_t frequency = 1000000; // примерно секунда
uint32_t frequency1;
uint32_t frequency2;
uint32_t frequency3;

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
            if (MODE1_1 == 0) 
            {
                MODE11++;
            } else if (MODE1_1 == 1) {
                MODE12++;
            } else {
                MODE13++;
            }
        }
        else if (counter >= frequency / 3)
        {
            MODE1_1++;
        }
    }

    if (MODE11 > 2) {
        MODE11 = 0;
    }

    if (MODE12 > 2) {
        MODE12 = 0;
    }

    if (MODE13 > 2) {
        MODE13 = 0;
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
            MODE2 = -1;
        }
        counter = 0;
        while(counter < 400000) 
        {
            counter++;
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
    if (BUTTON_1_STATE > 0) {
        MODE2 = -1;
        MODE1_1 = 0;
    }
    
    if (BUTTON_1_STATE > 0 || (BUTTON_2_STATE > 0 && flag == 0) || (BUTTON_2_STATE == 0 && flag == 1)) 
    {
        return 1;
    }
    else 
    {
        return 0;
    }
}

void LED_FREQUENCY(void) 
{
    if (MODE11 == 0) 
    {
        frequency1 = frequency / 10;
    } else if (MODE11 == 1) {
        frequency1 = frequency / 20;
    } else if (MODE11 == 2) {
        frequency1 = frequency / 30;
    }

    if (MODE12 == 0) 
    {
        frequency2 = frequency / 5;
    } else if (MODE12 == 1) {
        frequency2 = frequency / 20;
    } else if (MODE12 == 2) {
        frequency2 = frequency / 40;
    }

    if (MODE13 == 0) 
    {
        frequency3 = frequency / 5;
    } else if (MODE13 == 1) {
        frequency3 = frequency / 20;
    } else if (MODE13 == 2) {
        frequency3 = frequency / 40;
    }
}

void LED1_MODE20(void) {
    if (MODE2 == 0) {
        SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS0);
        SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR1);
        SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR4);
        counter_led = 0;
        counter_led1 = 0;
        while (counter_led <= frequency) 
        {
            counter_led++;
            counter_led1++;

            if (counter_led1 >= frequency1 && flag1 == 0) {
                SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS0);
                counter_led1 = 0;
                flag1 = 1;
            } else if (counter_led1 >= frequency1 && flag1 == 1) 
            {
                SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR0);
                counter_led1 = 0;
                flag1 = 0;
            }

            if (BUTTON_STATE()) 
            {
                SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR0);
                SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR1);
                SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR4);
                break;
            }
        }
        SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR0);
        SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR1);
        SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR4);  

        counter_led = 0;
        counter_led1 = 0;
        flag1 = 0;
    }
}

void LED2_MODE21(void) {
    if (MODE2 == 1) {
        counter_led = 0;
        counter_led1 = 0;
        counter_led2 = 0;
        while (counter_led <= frequency) 
        {
            counter_led++;
            counter_led1++;
            counter_led2++;

            if (counter_led1 >= frequency1 - 5 && flag1 == 0) {
                SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS0);
                counter_led1 = 0;
                flag1 = 1;
            } else if (counter_led1 >= frequency1 - 5 && flag1 == 1) 
            {
                SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR0);
                counter_led1 = 0;
                flag1 = 0;
            }

            if (counter_led2 >= frequency2 && flag2 == 0) {
                SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS1);
                counter_led2 = 0;
                flag2 = 1;
            } else if (counter_led2 >= frequency2 && flag2 == 1) 
            {
                SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR1);
                counter_led2 = 0;
                flag2 = 0;
            }

            if (BUTTON_STATE()) 
            {
                SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR0);
                SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR1);
                SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR4);
                break;
            }
        }
        
        SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR0);
        SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR1);
        SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR4);
        counter_led = 0;
        counter_led1 = 0;
        counter_led2 = 0;
        flag1 = 0;
        flag2 = 0;  
    }
}

void LED3_MODE22(void) {
    if (MODE2 == 2) {
        counter_led = 0;
        counter_led1 = 0;
        counter_led2 = 0;
        while (counter_led <= frequency) 
        {
            counter_led++;
            counter_led1++;
            counter_led2++;
            counter_led3++;

            if (counter_led1 >= frequency1 && flag1 == 0) {
                SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS0);
                counter_led1 = 0;
                flag1 = 1;
            } else if (counter_led1 >= frequency1 && flag1 == 1) 
            {
                SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR0);
                counter_led1 = 0;
                flag1 = 0;
            }

            if (counter_led2 >= frequency2 && flag2 == 0) {
                SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS1);
                counter_led2 = 0;
                flag2 = 1;
            } else if (counter_led2 >= frequency2 && flag2 == 1) 
            {
                SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR1);
                counter_led2 = 0;
                flag2 = 0;
            }

            if (counter_led3 >= frequency3 && flag3 == 0) {
                SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS4);
                counter_led3 = 0;
                flag3 = 1;
            } else if (counter_led3 >= frequency3 && flag3 == 1) 
            {
                SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR4);
                counter_led3 = 0;
                flag3 = 0;
            }

            if (BUTTON_STATE()) 
            {
                SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR0);
                SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR1);
                SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR4);
                break;
            }
        }
        
        SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR0);
        SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR1);
        SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR4);
        counter_led = 0;
        counter_led1 = 0;
        counter_led2 = 0;
        counter_led3 = 0;
        flag1 = 0;
        flag2 = 0;  
        flag3 = 0;
    }
}

void LED_MODE2(void) 
{
    LED1_MODE20();

    LED2_MODE21();
    
    LED3_MODE22();

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

        LED_FREQUENCY();

        LED_MODE2();
    }
}