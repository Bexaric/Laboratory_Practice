// Собрать схему с включением 3-и светодиодов и 4-х кнопок. 
// Базовый функционал кнопок, указанный ниже, меняется кнопкой 4:
// 1) При удержании, включает зеленый светодиод на отладочной плате.
// 2) При удержании, включает синий светодиод на отладочной плате.
// 3) При удержании, включает красный светодиод на отладочной плате.
// 4) При нажатии меняет функционал у кнопок смещая цвет светодиода 
// вниз по списку.
// То есть, при первом нажатии 4-ой кнопки, кнопка-1 будет включать 
// красный светодиод, кнопка-2 зелёный, кнопка-3 синий. 
// Каждое третье нажатие на кнопку 4 возвращает функционал всех 
// кнопок к базовому.

#include <C:/LB1_MC/Laboratory_Practice/Laboratory_Practice/Core/Inc/init.h>

uint8_t LED_1_STATE = 0; 
uint8_t LED_2_STATE = 0;
uint8_t LED_3_STATE = 0;  

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
void MODE_SELECTION(void) 
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

// функционал кнопок для режима №0
void LED_MODE0(void) 
{
    // включение 1-го в списке светодиода (по режиму)
    if (BUTTON_1_STATE != 0) 
    {
        // PA0
        SET__BIT(GPIOA_BSRR, GPIOA_BSRR_PIN0_SET);
        //SET_BIT(GPIOA->BSRR, MODE_SET[MODE][0]);
        LED_1_STATE = 1; 
    }
    else
    {
        SET__BIT(GPIOA_BSRR, GPIOA_BSRR_PIN0_RESET);
        //SET_BIT(GPIOA->BSRR, MODE_RESET[MODE][0]);
        LED_1_STATE = 0;
    }

    // включение 2-го в списке светодиода (по режиму)
    if (BUTTON_2_STATE != 0) 
    {
        // PA1
        *(uint32_t *)(0x640020000UL + 0x18UL) |= (1 << 1);
        //SET_BIT(GPIOA->BSRR, MODE_SET[MODE][1]);
        LED_2_STATE = 1;
    }
    else
    {
        *(uint32_t *)(0x640020000UL + 0x18UL) |= (1 << 17);
        //SET_BIT(GPIOA->BSRR, MODE_RESET[MODE][1]);
        LED_2_STATE = 0;
    }

    // включение 1-го в списке светодиода (по режиму)
    if (BUTTON_3_STATE != 0) 
    {
        // PA4
        SET_BIT(GPIOA->BSRR, MODE_SET[MODE][2]);
        LED_3_STATE = 1;
    }
    else
    {
        SET_BIT(GPIOA->BSRR, MODE_RESET[MODE][2]);
        LED_3_STATE = 0;
    }

}

// функционал кнопок для режима №1
void LED_MODE1(void) 
{
    // включение 1-го в списке светодиода (по режиму)
    if (BUTTON_1_STATE != 0) 
    {
        SET_BIT(GPIOA->BSRR, MODE_SET[MODE][0]);
        LED_3_STATE = 1;
    }
    else
    {
        SET_BIT(GPIOA->BSRR, MODE_RESET[MODE][0]);
        LED_3_STATE = 0;
    }
    
    // включение 2-го в списке светодиода (по режиму)
    if (BUTTON_2_STATE != 0) 
    {
        // PA0
        SET__BIT(GPIOA_BSRR, GPIOA_BSRR_PIN0_SET);
        //SET_BIT(GPIOA->BSRR, MODE_SET[MODE][0]);
        LED_1_STATE = 1;
    }
    else
    {
        SET__BIT(GPIOA_BSRR, GPIOA_BSRR_PIN0_RESET);
        //SET_BIT(GPIOA->BSRR, MODE_RESET[MODE][0]);
        LED_1_STATE = 0;
    }

    // включение 3-го в списке светодиода (по режиму)
    if (BUTTON_3_STATE != 0) 
    {
        // PA1
        *(uint32_t *)(0x640020000UL + 0x18UL) |= (1 << 1);
        //SET_BIT(GPIOA->BSRR, MODE_SET[MODE][1]);
        LED_2_STATE = 1;
    }
    else
    {
        *(uint32_t *)(0x640020000UL + 0x18UL) |= (1 << 17);
        //SET_BIT(GPIOA->BSRR, MODE_RESET[MODE][1]);
        LED_2_STATE = 0;
    }
}

// функционал кнопок для режима №2
void LED_MODE2(void) 
{
    // включение 1-го в списке светодиода (по режиму)
    if (BUTTON_1_STATE != 0) 
    {
        // PA1
        *(uint32_t *)(0x640020000UL + 0x18UL) |= (1 << 1);
        //SET_BIT(GPIOA->BSRR, MODE_SET[MODE][1]);
        LED_2_STATE = 1;
    }
    else
    {
        *(uint32_t *)(0x640020000UL + 0x18UL) |= (1 << 17);
        //SET_BIT(GPIOA->BSRR, MODE_RESET[MODE][1]);
        LED_2_STATE = 0;
    }
    
    // включение 2-го в списке светодиода (по режиму)
    if (BUTTON_2_STATE != 0) 
    {
        SET_BIT(GPIOA->BSRR, MODE_SET[MODE][1]);
        LED_3_STATE = 1;
    }
    else
    {
        SET_BIT(GPIOA->BSRR, MODE_RESET[MODE][1]);
        LED_3_STATE = 0;
    }

    // включение 3-го в списке светодиода (по режиму)
    if (BUTTON_3_STATE != 0) 
    {
        // PA0
        SET__BIT(GPIOA_BSRR, GPIOA_BSRR_PIN0_SET);
        //SET_BIT(GPIOA->BSRR, MODE_SET[MODE][0]);
        LED_1_STATE = 1;
    }
    else
    {
        SET__BIT(GPIOA_BSRR, GPIOA_BSRR_PIN0_RESET);
        //SET_BIT(GPIOA->BSRR, MODE_RESET[MODE][0]);
        LED_1_STATE = 0;
    }
}

// включение и выключение светодиодов
void LED_STATE(void) 
{
    if (MODE == 0) {
        LED_MODE0();
    }
    else if (MODE == 1) {
        LED_MODE1();
    }
    else if (MODE == 2) {
        LED_MODE2();
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