/**
 * @file motor.cpp
 *
 * @author Comp Thunderatz <comp@thunderatz.org>
 *
 * @brief Motor class implementation.
 *
 * @date 06/2024
 */

#include "motor.hpp"
#include "utils.hpp"

#define BREAK_SPEED_THRESHOLD 5

Motor::Motor(
    void (*tim_init)(), TIM_HandleTypeDef* forward_tim_handle, uint8_t forward_tim_ch,
    TIM_HandleTypeDef* backward_tim_handle, uint8_t backward_tim_ch, int8_t min_speed, int8_t max_speed
) {
    // Implemente aqui o criador da classe Motor.
}

void Motor::set_speed(int8_t speed) {
    // Implemente aqui a função para definir a velocidade do motor.
}

void Motor::stop() {
    // Implemente aqui a função para parar o motor.
}
