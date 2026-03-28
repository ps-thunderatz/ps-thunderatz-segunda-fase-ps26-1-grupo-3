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
    TIM_HandleTypeDef* backward_tim_handle, uint8_t backward_tim_ch, int8_t min_speed, int8_t max_speed) :
    forward_tim_handle(forward_tim_handle),
    forward_tim_ch(forward_tim_ch),
    backward_tim_handle(backward_tim_handle),
    backward_tim_ch(backward_tim_ch),
    min_speed(min_speed),
    max_speed(max_speed) {
    tim_init();

    HAL_TIM_PWM_Start(this->forward_tim_handle, this->forward_tim_ch);
    HAL_TIM_PWM_Start(this->backward_tim_handle, this->backward_tim_ch);

    this->stop();
}

void Motor::set_speed(int8_t speed) {
    int32_t command = abs(constrain(speed, this->min_speed, this->max_speed));

    auto forward_autoreload = __HAL_TIM_GET_AUTORELOAD(this->forward_tim_handle);
    auto backward_autoreload = __HAL_TIM_GET_AUTORELOAD(this->backward_tim_handle);

    auto forward_counter = map<uint32_t>(command, 0, this->max_speed, 0, forward_autoreload);
    auto backward_counter = map<uint32_t>(command, 0, this->max_speed, 0, backward_autoreload);

    if (abs(speed) <= BREAK_SPEED_THRESHOLD) {
        __HAL_TIM_SET_COMPARE(this->forward_tim_handle, this->forward_tim_ch, forward_autoreload);
        __HAL_TIM_SET_COMPARE(this->backward_tim_handle, this->backward_tim_ch, backward_autoreload);
        return;
    }

    if (speed > 0) {
        __HAL_TIM_SET_COMPARE(this->backward_tim_handle, this->backward_tim_ch, 0);
        __HAL_TIM_SET_COMPARE(this->forward_tim_handle, this->forward_tim_ch, forward_counter);

    } else {
        __HAL_TIM_SET_COMPARE(this->forward_tim_handle, this->forward_tim_ch, 0);
        __HAL_TIM_SET_COMPARE(this->backward_tim_handle, this->backward_tim_ch, backward_counter);
    }
}

void Motor::stop() {
    this->set_speed(0);
}