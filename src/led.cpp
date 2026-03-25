/**
 * @file led.cpp
 *
 * @author Comp Thunderatz <comp@thunderatz.org>
 *
 * @brief Led class implementation.
 *
 * @date 04/2025
 */

#include "led.hpp"

Led::Led(GPIO_TypeDef* port, uint16_t pin, GPIO_PinState on_state) : port(port), pin(pin), on_state(on_state) {
    this->off();
}

void Led::on(void) {
    HAL_GPIO_WritePin(this->port, this->pin, this->on_state);
}

void Led::off(void) {
    GPIO_PinState off_state = ((this->on_state == GPIO_PIN_RESET) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(this->port, this->pin, off_state);
}

void Led::toggle(void) {
    HAL_GPIO_TogglePin(this->port, this->pin);
}
