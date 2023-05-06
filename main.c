#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "stdio.h"

int main() 
{
    // This function initialized stdio functionalities in the RPI-pico or else stdio functionalities doesn't work.
    stdio_init_all();
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while (true) {
        gpio_put(LED_PIN, 1);
        sleep_ms(250);
        printf("ON\n");
        gpio_put(LED_PIN, 0);
        sleep_ms(250);
        printf("OFF\n");
    }
}
