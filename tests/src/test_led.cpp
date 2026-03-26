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
    // TODO: Adicionar a lógica de teste para o LED.
    hal::mcu::init();
    Led led_test(GPIOA, GPIO_PIN_4);

    for (;;) {
        led_test.on();
    }
}
