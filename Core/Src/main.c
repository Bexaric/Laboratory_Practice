#include <C:/LB1_MC/Laboratory_Practice/Laboratory_Practice/Core/Inc/init.h>

uint32_t BUTTON_1_STATE = 0; // состояние 1-ой внешней кнопки
uint32_t BUTTON_2_STATE = 0; // состояние 2-ой внешней кнопки
uint32_t BUTTON_3_STATE = 0; // состояние 3-ой внешней кнопки
uint32_t BUTTON_4_STATE = 0; // состояние 4-ой встроенной кнопки
uint8_t flag = 0;            // проверка на единичное нажатие 4-ой кнопки

uint8_t MODE = 0;            // режим работы
// режим 0:  зелёный, жёлтый,  красный
// режим 1:  красный, зелёный, жёлтый
// режим 2:  жёлтый,  красный, зелёный

// массив для включения светодиодов
const uint32_t MODE_SET[3][3] = 
{
    {GPIO_BSRR_BS0, GPIO_BSRR_BS1, GPIO_BSRR_BS4},
    
    {GPIO_BSRR_BS4, GPIO_BSRR_BS0, GPIO_BSRR_BS1},
    
    {GPIO_BSRR_BS1, GPIO_BSRR_BS4, GPIO_BSRR_BS0}
};

// массив для выключения светодиодов
const uint32_t MODE_RESET[3][3] = 
{
    {GPIO_BSRR_BR0, GPIO_BSRR_BR1, GPIO_BSRR_BR4},
    
    {GPIO_BSRR_BR4, GPIO_BSRR_BR0, GPIO_BSRR_BR1},
    
    {GPIO_BSRR_BR1, GPIO_BSRR_BR4, GPIO_BSRR_BR0}
};

// смена режима по состоянию 4 кнопки
void MODE_SELECTION() 
{
    if (BUTTON_4_STATE == 0 && flag == 0) 
    {
        flag = 1;
        MODE++;
        if (MODE > 2) 
        {
            MODE = 0;
        }
    }
    else if (BUTTON_4_STATE != 0 && flag) // проверка зажатия
    {
        flag = 0;
    }
}

// включение и выключение светодиодов
void LED_STATE() 
{
    // включение 1-го в списке светодиода (по режиму)
    if (BUTTON_1_STATE != 0) 
    {
        SET_BIT(GPIOA->BSRR, MODE_SET[MODE][0]);
    }
    else
    {
        SET_BIT(GPIOA->BSRR, MODE_RESET[MODE][0]);
    }
    
    // включение 2-го в списке светодиода (по режиму)
    if (BUTTON_2_STATE != 0) 
    {
        SET_BIT(GPIOA->BSRR, MODE_SET[MODE][1]);
    }
    else
    {
        SET_BIT(GPIOA->BSRR, MODE_RESET[MODE][1]);
    }

    // включение 3-го в списке светодиода (по режиму)
    if (BUTTON_3_STATE != 0) 
    {
        SET_BIT(GPIOA->BSRR, MODE_SET[MODE][2]);
    }
    else
    {
        SET_BIT(GPIOA->BSRR, MODE_RESET[MODE][2]);
    }
}

int main(void) 
{
    GPIO_Init(); // подключение портов GPIOA|GPIOB|GPIOC

    while(1) {
        // чтение состояния кнопки для управления светодиодами
        BUTTON_1_STATE = READ_BIT(GPIOB->IDR, GPIO_IDR_IDR_10);
        BUTTON_2_STATE = READ_BIT(GPIOB->IDR, GPIO_IDR_IDR_5);
        BUTTON_3_STATE = READ_BIT(GPIOB->IDR, GPIO_IDR_IDR_0);
        
        // чтение состояния кнопки для смены режима (инвертировано)
        BUTTON_4_STATE = READ_BIT(GPIOC->IDR, GPIO_IDR_IDR_13);
       
        // функция смены режима по состоянию 4 кнопки
        MODE_SELECTION();
        
        // функция включения и выключения светодиодов
        LED_STATE();
    }
}