/**
 * @file test_locomotion.cpp
 *
 * @author Comp Thunderatz <comp@thunderatz.org>
 *
 * @brief Test for locomotion class.
 *
 * @date 04/2025
 */

#include "motor.hpp"
#include "mcu.hpp"
#include "target.hpp"
#include "led.hpp"
#include "locomotion.hpp"

int main() {
    // TODO: Adicionar a lógica de teste para os motores.
    hal::mcu::init();
    Led led_test(LED_PORT, LED_PIN);
    Motor motortesteE(MOTORS_TIM_INIT, &MOTORS_TIM_HANDLER, LEFT_MOTOR_FORWARD_TIM_CH, &MOTORS_TIM_HANDLER, LEFT_MOTOR_BACKWARD_TIM_CH);
    Motor motortesteD(MOTORS_TIM_INIT, &MOTORS_TIM_HANDLER, RIGHT_MOTOR_FORWARD_TIM_CH, &MOTORS_TIM_HANDLER, RIGHT_MOTOR_BACKWARD_TIM_CH);
    Locomotion locomocao(motortesteE, motortesteD);

    for (;;) {
        locomocao.set_speed(80, 80);
        led_test.on();
        hal::mcu::sleep(2000);
        locomocao.stop();
        led_test.off();
        hal::mcu::sleep(2000);
    }
}
