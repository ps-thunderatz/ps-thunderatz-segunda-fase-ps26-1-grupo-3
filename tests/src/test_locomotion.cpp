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
    Motor motortesteE(MOTORS_TIM_INIT, &MOTORS_TIM_HANDLER, LEFT_MOTOR_FORWARD_TIM_CH, &MOTORS_TIM_HANDLER, LEFT_MOTOR_BACKWARD_TIM_CH, 10, 50);
    Motor motortesteD(MOTORS_TIM_INIT, &MOTORS_TIM_HANDLER, RIGHT_MOTOR_FORWARD_TIM_CH, &MOTORS_TIM_HANDLER, RIGHT_MOTOR_BACKWARD_TIM_CH, 10, 50);
    Locomotion locomocao(motortesteE, motortesteD);

    for (;;) {
        locomocao.set_speed(50, 50);
        hal::mcu::sleep(2000);
        locomocao.stop();
        hal::mcu::sleep(2000);
    }
}
