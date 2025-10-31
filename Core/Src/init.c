#include <C:/LB1_MC/Laboratory_Practice/Laboratory_Practice/Core/Inc/init.h>

void GPIO_Init(void) 
{
    //Включение тактирования портов GPIOA|GPIOB|GPIOC
    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN);

    // Режим порта 1-го и 4-го пинов GPIOA
    SET_BIT(GPIOA->MODER, GPIO_MODER_MODE1_0);
    SET_BIT(GPIOA->MODER, GPIO_MODER_MODE4_0);

    SET_BIT(GPIOA->MODER, GPIO_MODER_MODE0_0);

    // Настройка на Push-Pull 1-го и 4-го пинов GPIOA
    CLEAR_BIT(GPIOA->OTYPER, GPIO_OTYPER_OT1);
    CLEAR_BIT(GPIOA->OTYPER, GPIO_OTYPER_OT4);

    CLEAR_BIT(GPIOA->OTYPER, GPIO_OTYPER_OT0);

    // Настройка скорости работы 1-го и 4-го пинов GPIOA
    SET_BIT(GPIOA->OSPEEDR, GPIO_OSPEEDER_OSPEEDR1_0);
    SET_BIT(GPIOA->OSPEEDR, GPIO_OSPEEDER_OSPEEDR4_0);

    SET_BIT(GPIOA->OSPEEDR, GPIO_OSPEEDER_OSPEEDR0_0);

    // Настройка подтяжки (отключение)
    SET_BIT(GPIOA->PUPDR, GPIO_PUPDR_PUPD1);
    SET_BIT(GPIOA->PUPDR, GPIO_PUPDR_PUPD4);

    SET_BIT(GPIOA->PUPDR, GPIO_PUPDR_PUPD0);

    // настройка пина PA0
    //RCC_GPIO_EN |= RCC_GPIOA_EN; // Включение тактирования портов GPIOA
    //GPIOA_MODER |= GPIOA_MODE_PIN0_OUT; // Режим порта 0-го пина GPIOA
    //GPIOA_OTYPER |= GPIOA_OTYPE_PIN0_PP; // Настройка на Push-Pull 0-го пина GPIOA
    //GPIOA_OSPEEDR |= GPIOA_OSPEED_PIN0_MID; // Настройка скорости работы 0-го пина GPIOA
    //GPIOA_PUPDR |= GPIOA_PUPDR_PIN0_NOPUPD; // Настройка подтяжки (отключение)
}