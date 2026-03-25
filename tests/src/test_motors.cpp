/**
 * @file test_motors.cpp
 *
 * @author Comp Thunderatz <comp@thunderatz.org>
 *
 * @brief Test for Motors class.
 *
 * @date 06/2024
 */

#include "motor.hpp"
#include "mcu.hpp"
#include "target.hpp"
#include "led.hpp"

int main() {
    Motor motortesteE(MX_TIM1_Init, MOTORS_TIM_HANDLER, LEFT_MOTOR_FORWARD_TIM_CH, LEFT_MOTOR_BACKWARD_TIM_CH, min_speed, max_speed);
    Motor motortesteD(MX_TIM1_Init, MOTORS_TIM_HANDLER, RIGHT_MOTOR_FORWARD_TIM_CH, RIGHT_MOTOR_BACKWARD_TIM_CH, min_speed, max_speed);
    for (;;) {
        motortesteD.set_speed(int8_t 50);
        motortesteE.set_speed(int8_t 50);
        mcu::sleep(2000);
        motortesteD.stop();
        motortesteE.stop();
        mcu::sleep(2000);
    }

}
