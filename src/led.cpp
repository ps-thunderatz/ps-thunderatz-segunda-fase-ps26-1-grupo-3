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

Led::Led(GPIO_TypeDef* port, uint16_t pin) : port(port), pin(pin) {
    this->off();
}

void Led::on(void) {
    HAL_GPIO_WritePin(this->port, this->pin, GPIO_PIN_RESET);
}

void Led::off(void) {
    HAL_GPIO_WritePin(this->port, this->pin, GPIO_PIN_SET);
}

void Led::toggle(void) {
    HAL_GPIO_TogglePin(this->port, this->pin);
}
