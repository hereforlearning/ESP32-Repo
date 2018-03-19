#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

//definitions
#define BLINK_GPIO 2

//constants used
const char *pcTextForTask1 = "Task 1\n";
const char *pcTextForTask2 = "Task 2\n";
const TickType_t xDelay250ms = pdMS_TO_TICKS(250);

//functions used
void blink_task(void *pvParameters);
void print_task(void *pvParameters);

//DONE, Change the Project Name in Makefile
//DONE, Test this with ESP32
void app_main()
{
    xTaskCreate(&blink_task, "blink_task", configMINIMAL_STACK_SIZE, NULL, 5, NULL);

    //Adding the Parameter here
    xTaskCreate(&print_task, "print_task 1", 2048, (void *)pcTextForTask1, 5, NULL);
    xTaskCreate(&print_task, "print_task 2", 2048, (void *)pcTextForTask2, 5, NULL);
}

void blink_task(void *pvParameters)
{
    /* Configure the IOMUX register for pad BLINK_GPIO (some pads are
       muxed to GPIO on reset already, but some default to other
       functions and need to be switched to GPIO. Consult the
       Technical Reference for a list of pads and their default
       functions.)
    */

	gpio_pad_select_gpio(BLINK_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

    while(1)
    {
        /* Blink off (output low) */
        gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(xDelay250ms);

        /* Blink on (output high) */
        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(xDelay250ms);
    }

    vTaskDelete(NULL);
}

void print_task(void *pvParameters)
{
	char *pcTaskName;
	pcTaskName = (char *)pvParameters;

	while(1)
	{
		printf("Parameter: %s", pcTaskName);
		vTaskDelay(xDelay250ms);
	}

	vTaskDelete(NULL);
}
