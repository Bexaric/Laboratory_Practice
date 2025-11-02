#include <C:/LB1_MC/Laboratory_Practice/Laboratory_Practice/CMSIS/Devices/STM32F4xx/Inc/STM32F446xx/stm32f446xx.h>
#include <C:/LB1_MC/Laboratory_Practice/Laboratory_Practice/CMSIS/Devices/STM32F4xx/Inc/stm32f4xx.h>

// для управления светодиодом на пине PA0
#define RCC_GPIOA_EN              (1 << 0)
#define GPIOA_MODE_PIN0_OUT       (1 << 0)
#define GPIOA_OTYPE_PIN0_PP       (0 << 0)
#define GPIOA_OSPEED_PIN0_MID     (1 << 0)
#define GPIOA_PUPDR_PIN0_NOPUPD   (0 << 0)
#define GPIOA_BSRR_PIN0_SET       (1 << 0)
#define GPIOA_BSRR_PIN0_RESET     (1 << 16)

#define RCC_GPIO_EN               (*(uint32_t *)(0x40023800UL + 0x30UL)) 
#define GPIOA_MODER               (*(uint32_t *)(0x40020000UL + 0x00UL)) 
#define GPIOA_OTYPER              (*(uint32_t *)(0x40020000UL + 0x04UL)) 
#define GPIOA_OSPEEDR             (*(uint32_t *)(0x40020000UL + 0x08UL)) 
#define GPIOA_PUPDR               (*(uint32_t *)(0x40020000UL + 0x0CUL))
#define GPIOA_BSRR                (*(uint32_t *)(0x40020000UL + 0x18UL)) 

#define SET__BIT(REG, BIT)        (REG |= BIT)

void GPIO_Init(void);