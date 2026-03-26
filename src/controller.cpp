/**
 * @file controller.cpp
 *
 * @author Comp Thunderatz <comp@thunderatz.org>
 *
 * @brief Rock SemiAuto Controller Finite State Machine.
 *
 * @date 04/2025
 */

#include "mcu.hpp"
#include "controller.hpp"

Controller::Controller(Led led, Locomotion locomotion, Rc rc) : led(led), locomotion(locomotion), rc(rc) {
    // TODO: Adicionar a lógica de construção do objeto
}

void Controller::run() {
    switch (this->current_state) {
        case STRATEGY_CHOOSER: {
            // TODO: Implementar a lógica de escolha de estratégia
            break;
        }
        case RUN: {
            // TODO: Implementar a lógica de execução da estratégia
            break;
        }
        default: {
            // TODO: Implementar a lógica de estado padrão
            break;
        }
    }
}

void Controller::move_robot(Direction direction) {
    switch (direction) {
        // TODO: Implementar a lógica de movimentação do robô
        case FORWARD: {
            break;
        }
        case BACKWARD: {
            break;
        }
        case LEFT: {
            break;
        }
        case RIGHT: {
            break;
        }
        case STOPPED: {
            break;
        }
        case RC_INPUT: {
            break;
        }
        default: {
            break;
        }
    }
}

void Controller::strategy_run() {
    switch (this->current_level) {
        case LEVEL_0: {
            this->locomotion.stop();
            break;
        }

        case LEVEL_1: {
            this->led.on();

            this->locomotion.set_speed(80, 80);
            hal::mcu::sleep(2000);

            this->locomotion.stop();
            this->led.off();

            this->turn = RC_INPUT;
            this->current_state = RUN;
            break;
        }

        case LEVEL_2: {
            uint32_t start_time = HAL_GetTick();
            uint32_t blink_time = HAL_GetTick();

            this->locomotion.set_speed(80, 35);

            while (HAL_GetTick() - start_time < 3000) {
                if (HAL_GetTick() - blink_time >= 300) {
                    this->led.toggle();
                    blink_time = HAL_GetTick();
                }
            }

            this->locomotion.stop();
            this->led.off();

            this->turn = RC_INPUT;
            this->current_state = RUN;
            break;
        }

        case LEVEL_3: {
            const uint8_t  REPEATS = 3;
            const uint32_t FORWARD_MS = 400;
            const uint32_t SPIN_MS = 250;
            const uint32_t PAUSE_MS = 300;
            const uint32_t BLINK_RATE_MS = 100;

            uint32_t blink_time = HAL_GetTick();

            auto blink_step = [&]() {
                if (HAL_GetTick() - blink_time >= BLINK_RATE_MS) {
                    this->led.toggle();
                    blink_time = HAL_GetTick();
                }
            };

            auto timed_move = [&](int8_t left, int8_t right, uint32_t duration_ms) {
                uint32_t t0 = HAL_GetTick();
                this->locomotion.set_speed(left, right);
                while (HAL_GetTick() - t0 < duration_ms) {
                    blink_step();
                }
            };

            for (uint8_t i = 0; i < REPEATS; i++) {
                timed_move(80, 80, FORWARD_MS);
                timed_move(80, -80, SPIN_MS);
                timed_move(80, 80, FORWARD_MS);
                timed_move(-80, 80, SPIN_MS);
                timed_move(0, 0, PAUSE_MS);
            }

            this->locomotion.stop();
            this->led.off();

            this->turn = RC_INPUT;
            this->current_state = RUN;
            break;
        }

        default: {
            this->locomotion.stop();
            break;
        }
    }
}