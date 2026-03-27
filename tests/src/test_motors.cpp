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
    hal::mcu::init();
    Motor motorTesteE(MOTORS_TIM_INIT, &MOTORS_TIM_HANDLER,
                 LEFT_MOTOR_FORWARD_TIM_CH,  &MOTORS_TIM_HANDLER, LEFT_MOTOR_BACKWARD_TIM_CH);
    Motor motorTesteD(MOTORS_TIM_INIT, &MOTORS_TIM_HANDLER,
                 RIGHT_MOTOR_FORWARD_TIM_CH, &MOTORS_TIM_HANDLER, RIGHT_MOTOR_BACKWARD_TIM_CH);

    for (;;) {
        motorTesteD.set_speed(100);
        motorTesteE.set_speed(100);
        hal::mcu::sleep(2000);

        motorTesteD.stop();
        motorTesteE.stop();
        hal::mcu::sleep(1000);

        motorTesteD.set_speed(-100);
        motorTesteE.set_speed(-100);
        hal::mcu::sleep(2000);

        motorTesteD.stop();
        motorTesteE.stop();
        hal::mcu::sleep(1000);
    }
}
