#include "stdint.h"

#define RCC_GPIOA_EN              (1 << 0)
#define RCC_GPIOC_EN              (1 << 2) 
#define GPIOA_MODE_PIN5_OUT       (1 << 10) 
#define GPIOA_OTYPE_PIN5_PP       0x0000UL 
#define GPIOA_OSPEED_PIN5_MID     (1 << 10)
#define GPIOA_PUPDR_PIN5_NOPUPD   0x0000UL
#define GPIOB_BSRR_PIN5_SET       (1 << 5)
#define GPIOB_BSRR_PIN5_RESET     (1 << 21)
#define GPIOC_IDR_PIN13           0x2000UL

#define RCC_GPIO_EN               (*(uint32_t*)(0x40023800UL + 0x30UL)) 
#define GPIOA_MODER               (*(uint32_t*)(0x40020000UL + 0x00UL)) 
#define GPIOA_OTYPER              (*(uint32_t*)(0x40020000UL + 0x04UL)) 
#define GPIOA_OSPEEDR             (*(uint32_t*)(0x40020000UL + 0x08UL)) 
#define GPIOA_PUPDR               (*(uint32_t*)(0x40020000UL + 0x0CUL))
#define GPIOB_BSRR                (*(uint32_t*)(0x40020000UL + 0x18UL)) 
#define GPIOC_IDR                 (*(uint32_t*)(0x40020800UL + 0x10UL)) 

//#define SET_GPIO_A5               (*(uint32_t *)(0x40020000UL + 0x18UL) |= (1 << 5)) 
//#define RESET_GPIO_A5             (*(uint32_t *)(0x640020000UL + 0x18UL) |= (1 << 21))

#define SET_BIT(REG, BIT)         (REG |= BIT)
#define READ_BIT(REG, BIT)        (REG & BIT)

int GPIO_Init(void);