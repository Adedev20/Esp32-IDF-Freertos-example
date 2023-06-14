#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>
#include <driver/gpio.h>

#define LED GPIO_NUM_23
#define LED_2 GPIO_NUM_22
TaskHandle_t myTaskHandle = NULL;
TaskHandle_t myTaskHandle2 = NULL;
TaskHandle_t myTaskHandle3 = NULL;

void blink_Led1();
void blink_Led2();
void configure_Led();
void blinkLED1_Task(void *arg);
void blinkLED2_Task(void *arg);
void scrnPrint_Task(void *arg);

void app_main(void)
{

    xTaskCreate(blinkLED1_Task, "Demo Task1", 4096, NULL, 10, &myTaskHandle);
    xTaskCreate(blinkLED2_Task, "Demo Task 3", 4096, NULL, 10, &myTaskHandle3);
    xTaskCreatePinnedToCore(scrnPrint_Task, "Demo Task2", 4096, NULL, 10, &myTaskHandle2, 1);
}

void blink_Led1()
{

    for (;;)
    {

        gpio_set_level(LED, 1);
        printf("LED ON!!!!\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);

        gpio_set_level(LED, 0);
        printf("LED OFF!!!!\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void blink_Led2()
{

    for (;;)
    {
        gpio_set_level(LED_2, 1);
        printf("LED2 ON!!!\n");
        vTaskDelay(300 / portTICK_PERIOD_MS);

        gpio_set_level(LED_2, 0);
        printf("LED2 OFF!!!");
        vTaskDelay(300 / portTICK_PERIOD_MS);
    }
}

void configure_Led()
{
    esp_rom_gpio_pad_select_gpio(LED);
    esp_rom_gpio_pad_select_gpio(LED_2);
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_2, GPIO_MODE_OUTPUT);
}

void blinkLED1_Task(void *arg)
{
    configure_Led();
    blink_Led1();
}

void blinkLED2_Task(void *arg)
{
    configure_Led();
    blink_Led2();
}

void scrnPrint_Task(void *arg)
{

    for (;;)
    {

        printf("HELLO WORLD\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}