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
    Motor motortesteE(MOTORS_TIM_INIT, &MOTORS_TIM_HANDLER, LEFT_MOTOR_FORWARD_TIM_CH, &MOTORS_TIM_HANDLER, LEFT_MOTOR_BACKWARD_TIM_CH, 10, 50);
    Motor motortesteD(MOTORS_TIM_INIT, &MOTORS_TIM_HANDLER, RIGHT_MOTOR_FORWARD_TIM_CH, &MOTORS_TIM_HANDLER, RIGHT_MOTOR_BACKWARD_TIM_CH, 10, 50);
    for (;;) {
        motortesteD.set_speed(50);
        motortesteE.set_speed(50);
        hal::mcu::sleep(2000);
        motortesteD.stop();
        motortesteE.stop();
        hal::mcu::sleep(2000);
    }

}
