#include <C:/LB1_MC/Laboratory_Practice/Laboratory_Practice/Core/Inc/init.h>

int main(void) 
{
    GPIO_Init();
    while(1) {
        if(READ_GPIO_C13 != 0) 
        {
            RESET_GPIO_A5;
        }
        else 
        {
            SET_GPIO_A5;
        }
    }
}