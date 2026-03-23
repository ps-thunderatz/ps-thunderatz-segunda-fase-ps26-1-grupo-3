/**
 * @file led.hpp
 *
 * @author Comp Thunderatz <comp@thunderatz.org>
 *
 * @brief Led class definition.
 *
 * @date 04/2025
 */

#ifndef __LED_HPP__
#define __LED_HPP__

#include "gpio.h"

/**
 * @brief Led class.
 */
class Led {
public:
    /**
     * @brief Construct a new Led object
     *
     * @param port Led port
     * @param pin Led pin
     */
    Led(GPIO_TypeDef* port, uint16_t pin);

    /**
     * @brief Turn the led on
     */
    void on(void);

    /**
     * @brief Turn the led off
     */
    void off(void);

    /**
     * @brief Toggle the led
     */
    void toggle(void);

private:
    GPIO_TypeDef* port;
    uint16_t      pin;
};

#endif  // __LED_HPP__
