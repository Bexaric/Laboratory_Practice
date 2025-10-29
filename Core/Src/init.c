#include "C:/LB1_MC/Laboratory_Practice/Laboratory_Practice/Core/Inc/init.h"

int GPIO_Init(void) 
{
    RCC_GPIO_EN |= RCC_GPIOA_EN; // Включение тактирования портов GPIOA
    RCC_GPIO_EN |= RCC_GPIOC_EN; // Включение тактирования портов GPIOC
    GPIOA_MODER |= GPIOA_MODE_PIN5_OUT; // Режим порта 5-го пина GPIOA
    GPIOA_OTYPER |= GPIOA_OTYPE_PIN5_PP; // Настройка на Push-Pull 5-го пина GPIOA
    GPIOA_OSPEEDR |= GPIOA_OSPEED_PIN5_MID; // Настройка скорости работы 7-го пина GPIOA
    GPIOA_PUPDR |= GPIOA_PUPDR_PIN5_NOPUPD; // Настройка подтяжки (отключение)
}