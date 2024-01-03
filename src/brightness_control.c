#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/flash.h"

#define FLASH_TARGET_OFFSET (256 * 1024)
#define NUM_VOLT_LEVELS 5 // Number of voltage levels

// Define the GPIO pin for the button
#define BUTTON_PIN 2
#define GPIO_LED 1

const uint8_t *flash_target_contents = (const uint8_t *)(XIP_BASE + FLASH_TARGET_OFFSET);

// Fixed-point representation of voltage levels (multiply by a factor to get actual voltage)
const uint16_t voltage_levels[NUM_VOLT_LEVELS] = {0, 800, 1600, 2400, 3300};

int main() {
    stdio_init_all();

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);

    gpio_init(GPIO_LED);
    gpio_set_dir(GPIO_LED, GPIO_OUT);

    uint8_t stored_index;
    flash_range_read(FLASH_TARGET_OFFSET, &stored_index, sizeof(stored_index));

    gpio_put(GPIO_LED, state);

    bool button_was_pressed = false;

    while (1) {
        if (gpio_get(BUTTON_PIN) == 0) { // Button is pressed
            if (!button_was_pressed) { // Check if button was not pressed in the previous iteration
                // Change brightness based on the stored index
                uint16_t voltage = voltage_levels[stored_index];
                printf("Button pressed. Changing brightness to %d mV\n", voltage);

                // Add your brightness control logic here
                // For example, set a variable that controls the brightness level in your display code

                // Increment the index for the next button press
                stored_index = (stored_index + 1) % FLASH_DATA_SIZE;

                // Store the updated index in flash
                flash_range_program(FLASH_TARGET_OFFSET, &stored_index, sizeof(stored_index));

                button_was_pressed = true;
            }
        } else {
            button_was_pressed = false; // Reset the flag when the button is released
        }
    }
    return 0;
}
