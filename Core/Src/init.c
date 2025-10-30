#include <C:/LB1_MC/Laboratory_Practice/Laboratory_Practice/Core/Inc/init.h>

void GPIO_Init(void) 
{
    //Включение тактирования портов GPIOA и GPIOC
    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN);

    // Режим порта 5-го пина GPIOA
    SET_BIT(GPIOA->MODER, GPIO_MODER_MODE5_0);

    // Настройка на Push-Pull 5-го пина GPIOA
    CLEAR_BIT(GPIOA->OTYPER, GPIO_OTYPER_OT5);

    // Настройка скорости работы 5-го пина GPIOA
    SET_BIT(GPIOA->OSPEEDR, GPIO_OSPEEDER_OSPEEDR5_0);

    // Настройка подтяжки (отключение)
    CLEAR_BIT(GPIOA->PUPDR, GPIO_PUPDR_PUPD5_0);
}