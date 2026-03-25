/**
 * @file locomotion.cpp
 *
 * @author Comp Thunderatz <comp@thunderatz.org>
 *
 * @brief locomotion class implementation.
 *
 * @date 04/2025
 */

#include "locomotion.hpp"
#include "motor.hpp"

Locomotion::Locomotion(Motor& motor_left, Motor& motor_right) : motor_left(motor_left), motor_right(motor_right) {
    //this->motor_left = motor_left;
    //this->motor_right = motor_right;
}

void Locomotion::set_speed(int8_t left_speed, int8_t right_speed) {
    motor_left.set_speed(left_speed);
    motor_right.set_speed(right_speed);
}

void Locomotion::stop() {
motor_left.stop();
}
