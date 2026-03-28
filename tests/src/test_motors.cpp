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
    Led led_test(LED_PORT, LED_PIN);
    Motor motortesteE(MOTORS_TIM_INIT, &MOTORS_TIM_HANDLER, LEFT_MOTOR_FORWARD_TIM_CH, &MOTORS_TIM_HANDLER, LEFT_MOTOR_BACKWARD_TIM_CH);
    Motor motortesteD(MOTORS_TIM_INIT, &MOTORS_TIM_HANDLER, RIGHT_MOTOR_FORWARD_TIM_CH, &MOTORS_TIM_HANDLER, RIGHT_MOTOR_BACKWARD_TIM_CH);
    for (;;) {
        motortesteD.stop();
        motortesteE.set_speed(70);
        led_test.on();
        hal::mcu::sleep(2000);
        motortesteD.set_speed(70);
        motortesteE.stop();
        led_test.off();
        hal::mcu::sleep(2000);
    }

}
