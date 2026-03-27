/**
 * @file test_led.cpp
 *
 * @author Comp Thunderatz <comp@thunderatz.org>
 *
 * @brief Test for Led class.
 *
 * @date 06/2024
 */

#include "led.hpp"
#include "mcu.hpp"
#include "target.hpp"

int main() {
    hal::mcu::init();
    Led led_test(LED_PORT, LED_PIN);

    for (;;) {
        led_test.on();
        hal::mcu::sleep(3000);
        led_test.off();
        hal::mcu::sleep(3000);
    }
}
