#include <C:/LB1_MC/Laboratory_Practice/Laboratory_Practice/Core/Inc/init.h>

int main(void) 
{
    GPIO_Init();
    while(1) {
        if(READ_BIT(GPIOC->IDR, GPIO_IDR_IDR_13) !=0) 
        {
            SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR5);
        }
        else 
        {
            SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS5);
        }
    }
}