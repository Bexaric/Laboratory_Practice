#include <C:/LB1_MC/Laboratory_Practice/Laboratory_Practice/Core/Inc/init.h>

// настройка пина PA1
void PA1_MEMORY(void) 
{
    // Включение тактирования на GPIOAEN
    //*(uint32_t *)(0x40023800UL + 0x30UL) |= (1 << 0);

    *(uint32_t *)(0x40020000UL + 0x00UL) |= (1 << 2); // Режим порта PA1
    // Input mode (00). Режим считывания сигнала с порта микроконтроллера.
    // General Purpose Output mode (01). Режим вывода сигнала на порт микроконтроллера
    // Alternate function mode (10). Режим альтернативных функций.
    // Analog mode (11). Аналоговый режим.
    
    *(uint32_t *)(0x40020000UL + 0x04UL) |= 0x00; // PA1
    // Output Push-Pull (PP) 0 – Стандартный двухтактный выход.
    // Output Open-Drain (OD) 1 – Выход с открытым стоком.

    *(uint32_t *)(0x40020000UL + 0x08UL) |= (1 << 2); // скорость одного бита PA1
    // 00: Low speed / Низкая скорость – диапазон частот от 2 до 8 МГц
    // 01: Medium speed / Средняя скорость – диапазон частот от 10 до 50 МГц
    // 10: High speed / Высокая скорость – диапазон частот от 25 до 100 МГц
    // 11: Very high speed / Очень высокая скорость – диапазон частот от 42,5 до 180 МГц

    *(uint32_t *)(0x40020000UL + 0x0CUL) |= (0x00); // настройка подтяжки
    // 00: No pull-up, pull-down – Нед подтяжки к питанию и стяжки на общий провод.
    // 01: Pull-up – Подтяжка к положительному напряжению через резистор.
    // 10: Pull-down – Стяжка к общему проводу через резистор.
    // 11: Reserved – Зарезервированное состояние, не используется в настройке
    
}

// настройка пина PA0
void PA0_MACRO(void) 
{
    //RCC_GPIO_EN |= RCC_GPIOA_EN; // Включение тактирования портов GPIOA
    GPIOA_MODER |= GPIOA_MODE_PIN0_OUT; // Режим порта 0-го пина GPIOA
    GPIOA_OTYPER |= GPIOA_OTYPE_PIN0_PP; // Настройка на Push-Pull 0-го пина GPIOA
    GPIOA_OSPEEDR |= GPIOA_OSPEED_PIN0_MID; // Настройка скорости работы 0-го пина GPIOA
    GPIOA_PUPDR |= GPIOA_PUPDR_PIN0_NOPUPD; // Настройка подтяжки (отключение)
}

// настройка пина PA4
void PA4_CMSIS(void) 
{
    SET_BIT(GPIOA->MODER, GPIO_MODER_MODE4_0);

    // Настройка на Push-Pull 4-го пина GPIOA
    CLEAR_BIT(GPIOA->OTYPER, GPIO_OTYPER_OT4);

    // Настройка скорости работы 4-го пина GPIOA
    SET_BIT(GPIOA->OSPEEDR, GPIO_OSPEEDER_OSPEEDR4_0);

    // Настройка подтяжки (отключение)
    SET_BIT(GPIOA->PUPDR, GPIO_PUPDR_PUPD4);
}

void GPIO_Init(void) 
{
    //Включение тактирования портов GPIOA|GPIOB|GPIOC
    
    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN);

    // Прямое обращение к памяти (PA1)
    PA1_MEMORY();

    // Собственные директивы и макросы (PA0)
    PA0_MACRO();

    // Использование CMSIS (PA0)
    PA4_CMSIS();
}