#include <stdio.h>
#include <string.h>
#include "stm32f7xx.h"
#include "uart.h"
#include "led.h"
#include "adc.h"
#include "tim.h"

float sensor_value[1500];
float y[1500] = {0};
float mapped_value[1500] = {0};
int j;

int main(void)
{
    SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2)); // settting  bits 20-23 for CP10 and CP11 
    uart3_tx_init();
    pa4_adc1_init();
    tim1_1hz_init();

    while (1)
    {
        // Reset sensor_value array to all zeros
        memset(sensor_value, 0, sizeof(sensor_value));


        for (int i = 0; i < 1500; i++)
        {
            sensor_value[i] = adc_get_data();
            while (!(TIM1->SR & SR_UIF));
            TIM1->SR &= ~SR_UIF;
        }

        for (int j = 2; j < 1500; j++)
        {
            if (j > 2)
            {
                y[j] = (double)(0.9847842466003875 * sensor_value[j] - 1.873170949748224 * sensor_value[j - 1] +0.9847842466003875 * sensor_value[j - 2] + 1.873170949748224 * y[j - 1] -0.9695684932007752 * y[j - 2]);

                // Map the value to the range 0 to 4096
                float min_value = y[2];
                float max_value = y[2];

                for (int k = 1; k < j; k++)
                {
                    if (y[k] < min_value)
                    {
                        min_value = y[k];
                    }
                    if (y[k] > max_value)
                    {

                        max_value = y[k];

                    }
                }

                mapped_value[j] = (y[j] - min_value) / (max_value - min_value) * 4096.0f;

                if (j >= 1000)
                {
                    // Print the last 1000 mapped values
                    printf("%f\n", mapped_value[j]);

                }
            }
        }
    }
}
