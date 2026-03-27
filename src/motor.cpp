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
) : forward_tim_handle(forward_tim_handle), forward_tim_ch(forward_tim_ch), backward_tim_handle(backward_tim_handle), backward_tim_ch(backward_tim_ch), min_speed(min_speed), max_speed(max_speed)  {
tim_init();
}

void Motor::set_speed(int8_t speed) {
speed = constrain(speed,this->max_speed,this->min_speed);
if(speed<0){
    __HAL_TIM_SET_COMPARE(this->backward_tim_handle,this->backward_tim_ch, map<uint32_t>(-speed, this->min_speed, this->max_speed, 0,700));
    __HAL_TIM_SET_COMPARE(this->forward_tim_handle,this->forward_tim_ch, 0);
}
else{
    __HAL_TIM_SET_COMPARE(this->forward_tim_handle,this->forward_tim_ch, map<uint32_t>(speed, this->min_speed, this->max_speed, 0,700));
    __HAL_TIM_SET_COMPARE(this->backward_tim_handle,this->backward_tim_ch, 0);

}

}

void Motor::stop() {
    __HAL_TIM_SET_COMPARE(this->backward_tim_handle,this->backward_tim_ch, 0);
    __HAL_TIM_SET_COMPARE(this->forward_tim_handle,this->forward_tim_ch, 0);
}
