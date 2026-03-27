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

#define MAX_DUTY_CYCLE 700

Motor::Motor(void (*tim_init)(), TIM_HandleTypeDef* forward_tim_handle, uint8_t forward_tim_ch,
             TIM_HandleTypeDef* backward_tim_handle, uint8_t backward_tim_ch,
             int8_t min_speed, int8_t max_speed) :
    forward_tim_handle(forward_tim_handle), forward_tim_ch(forward_tim_ch),
    backward_tim_handle(backward_tim_handle), backward_tim_ch(backward_tim_ch),
    min_speed(min_speed), max_speed(max_speed) {

    tim_init();

    HAL_TIM_PWM_Start(this->forward_tim_handle, this->forward_tim_ch);
    HAL_TIM_PWM_Start(this->backward_tim_handle, this->backward_tim_ch);
}

//void Motor::set_speed(int8_t speed) {
//    speed = constrain(speed, this->min_speed, this->max_speed);
//
//    if(speed<0){
//        __HAL_TIM_SET_COMPARE(this->backward_tim_handle,this->backward_tim_ch, map<uint32_t>(-speed, this->min_speed, this->max_speed, 0, MAX_DUTY_CYCLE));
//        __HAL_TIM_SET_COMPARE(this->forward_tim_handle,this->forward_tim_ch, 0);
//    }
//    else{
//        __HAL_TIM_SET_COMPARE(this->forward_tim_handle,this->forward_tim_ch, map<uint32_t>(speed, this->min_speed, this->max_speed, 0, MAX_DUTY_CYCLE));
//        __HAL_TIM_SET_COMPARE(this->backward_tim_handle,this->backward_tim_ch, 0);
//    }
//}

void Motor::set_speed(int8_t speed) {
    speed = constrain(speed, this->min_speed, this->max_speed);

    if (speed < 0) {
        uint32_t duty = map<uint32_t>((uint32_t)(-speed), 0, (uint32_t)(-this->min_speed), 0, MAX_DUTY_CYCLE);
        __HAL_TIM_SET_COMPARE(this->backward_tim_handle, this->backward_tim_ch, duty);
        __HAL_TIM_SET_COMPARE(this->forward_tim_handle,  this->forward_tim_ch,  0);
    } else {
        uint32_t duty = map<uint32_t>((uint32_t)(speed), 0, (uint32_t)(this->max_speed), 0, MAX_DUTY_CYCLE);
        __HAL_TIM_SET_COMPARE(this->forward_tim_handle,  this->forward_tim_ch,  duty);
        __HAL_TIM_SET_COMPARE(this->backward_tim_handle, this->backward_tim_ch, 0);
    }
}

void Motor::stop() {
    __HAL_TIM_SET_COMPARE(this->backward_tim_handle,this->backward_tim_ch, 0);
    __HAL_TIM_SET_COMPARE(this->forward_tim_handle,this->forward_tim_ch, 0);
}