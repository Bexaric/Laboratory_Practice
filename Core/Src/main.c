#include <C:/LB1_MC/Laboratory_Practice/Laboratory_Practice/Core/Inc/init.h>

int main(void) 
{
    GPIO_Init();
    //while(1) {
    //    if(READ_GPIO_C13 != 0) 
    //    {
    //        RESET_GPIO_A5;
    //    }
    //    else 
    //    {
    //        SET_GPIO_A5;
    //    }
    //}

    // С использованием макросов
    while(1) {
        if(READ_BIT(GPIOC_IDR, GPIOC_IDR_PIN13)) 
        {
            SET_BIT(GPIOB_BSRR , GPIOB_BSRR_PIN5_RESET);
        }
        else 
        {
            SET_BIT(GPIOB_BSRR , GPIOB_BSRR_PIN5_SET);
        }
    }
}