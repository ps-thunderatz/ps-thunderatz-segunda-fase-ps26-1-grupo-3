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

Controller::Controller(Led& led, Locomotion& locomotion, Rc& rc)
    : led(&led), locomotion(&locomotion), rc(&rc) {
}

void Controller::init() {
    this->current_state = STRATEGY_CHOOSER;
}

void Controller::run() {
    switch (this->current_state) {
        case STRATEGY_CHOOSER: {
            // 4 segundos para escolher a estratégia
            this->led->on();
            hal::mcu::sleep(1000);
            this->led->toggle();
            hal::mcu::sleep(1000);
            this->led->toggle();
            hal::mcu::sleep(1000);
            this->led->toggle();
            hal::mcu::sleep(1000);
            this->led->toggle();

            /*TABELA DO RC e qual estratégia*/
            // CH1 <= 0 e CH2 <= 0 (os dois para trás) => LEVEL_0
            // CH1 <= 0 e CH2 >  0                     => LEVEL_1
            // CH1 >  0 e CH2 <= 0                     => LEVEL_2
            // CH1 >  0 e CH2 >  0 (os dois para frente) => LEVEL_3
            // OBS: Se o controle estiver solto (0, 0), vai para LEVEL_0

            if (this->rc->get_speed_ch1() <= 0) {
                if (this->rc->get_speed_ch2() <= 0) {
                    this->current_level = LEVEL_0;
                } else {
                    this->current_level = LEVEL_1;
                }
            } else {
                if (this->rc->get_speed_ch2() <= 0) {
                    this->current_level = LEVEL_2;
                } else {
                    this->current_level = LEVEL_3;
                }
            }

            this->led->off();
            this->current_state = RUN;
            break;
        }

        case RUN: {
            this->strategy_run();

            uint32_t start_time = HAL_GetTick();
            while (HAL_GetTick() - start_time < 10000) {
                this->move_robot(this->turn);
            }

            this->current_state = STRATEGY_CHOOSER;
            break;
        }

        default: {
            this->current_state = STRATEGY_CHOOSER;
            break;
        }
    }
}

void Controller::move_robot(Direction direction) {
    switch (direction) {
        case FORWARD: {
            this->locomotion->set_speed(80, 80);
            break;
        }
        case BACKWARD: {
            this->locomotion->set_speed(-80, -80);
            break;
        }
        case LEFT: {
            this->locomotion->set_speed(35, 80);
            break;
        }
        case RIGHT: {
            this->locomotion->set_speed(80, 35);
            break;
        }
        case STOPPED: {
            this->locomotion->stop();
            break;
        }
        case RC_INPUT: {
             int8_t ch1 = this->rc->get_speed_ch1();
             int8_t ch2 = this->rc->get_speed_ch2();

             int8_t left_speed = ch1 + ch2;
             int8_t right_speed = ch1 - ch2;

             left_speed = constrain(left_speed, -100, 100);
             right_speed = constrain(right_speed, -100, 100);

             this->locomotion->set_speed(left_speed, right_speed);

            break;
        }
        default: {
            this->locomotion->stop();
            break;
        }
    }
}

void Controller::strategy_run() {
    switch (this->current_level) {
        case LEVEL_0: {
            this->locomotion->stop();
            this->turn = STOPPED;
            break;
        }

        case LEVEL_1: {
            this->led->on();

            this->locomotion->set_speed(80, 80);
            hal::mcu::sleep(2000);

            this->locomotion->stop();
            this->led->off();

            this->turn = RC_INPUT;
            break;
        }

        case LEVEL_2: {
            uint32_t start_time = HAL_GetTick();
            uint32_t blink_time = HAL_GetTick();

            this->locomotion->set_speed(80, 35);

            while (HAL_GetTick() - start_time < 3000) {
                if (HAL_GetTick() - blink_time >= 300) {
                    this->led->toggle();
                    blink_time = HAL_GetTick();
                }
            }

            this->locomotion->stop();
            this->led->off();

            this->turn = RC_INPUT;
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
                    this->led->toggle();
                    blink_time = HAL_GetTick();
                }
            };

            auto timed_move = [&](int8_t left, int8_t right, uint32_t duration_ms) {
                uint32_t t0 = HAL_GetTick();
                this->locomotion->set_speed(left, right);
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

            this->locomotion->stop();
            this->led->off();

            this->turn = RC_INPUT;
            break;
        }

        default: {
            this->locomotion->stop();
            break;
        }
    }
}
///**
// * @file controller.cpp
// *
// * @author Comp Thunderatz <comp@thunderatz.org>
// *
// * @brief Rock SemiAuto Controller Finite State Machine.
// *
// * @date 04/2025
// */
//
//#include "mcu.hpp"
//#include "controller.hpp"
//
//Controller::Controller(Led led, Locomotion locomotion, Rc rc) : led(led), locomotion(locomotion), rc(rc) {
//    // TODO: Adicionar a lógica de construção do objeto
//}
//
//void Controller::run() {
//    switch (this->current_state) {
//        case STRATEGY_CHOOSER: {
//            // TODO: Implementar a lógica de escolha de estratégia
//            break;
//        }
//        case RUN: {
//            // TODO: Implementar a lógica de execução da estratégia
//            break;
//        }
//        default: {
//            // TODO: Implementar a lógica de estado padrão
//            break;
//        }
//    }
//}
//
//void Controller::move_robot(Direction direction) {
//    switch (direction) {
//        // TODO: Implementar a lógica de movimentação do robô
//        case FORWARD: {
//            break;
//        }
//        case BACKWARD: {
//            break;
//        }
//        case LEFT: {
//            break;
//        }
//        case RIGHT: {
//            break;
//        }
//        case STOPPED: {
//            break;
//        }
//        case RC_INPUT: {
//            break;
//        }
//        default: {
//            break;
//        }
//    }
//}
//void Controller::strategy_run() {
//    switch (this->current_level) {
//        case LEVEL_0: {
//            this->locomotion.stop();
//            break;
//        }
//
//        case LEVEL_1: {
//            this->led.on();
//
//            this->locomotion.set_speed(80, 80);
//            hal::mcu::sleep(2000);
//
//            this->locomotion.stop();
//            this->led.off();
//
//            this->turn = RC_INPUT;
//            this->current_state = RUN;
//            break;
//        }
//
//        case LEVEL_2: {
//            uint32_t start_time = HAL_GetTick();
//            uint32_t blink_time = HAL_GetTick();
//
//            this->locomotion.set_speed(80, 35);
//
//            while (HAL_GetTick() - start_time < 3000) {
//                if (HAL_GetTick() - blink_time >= 300) {
//                    this->led.toggle();
//                    blink_time = HAL_GetTick();
//                }
//            }
//
//            this->locomotion.stop();
//            this->led.off();
//
//            this->turn = RC_INPUT;
//            this->current_state = RUN;
//            break;
//        }
//
//        case LEVEL_3: {
//            const uint8_t  REPEATS = 3;
//            const uint32_t FORWARD_MS = 400;
//            const uint32_t SPIN_MS = 250;
//            const uint32_t PAUSE_MS = 300;
//            const uint32_t BLINK_RATE_MS = 100;
//
//            uint32_t blink_time = HAL_GetTick();
//
//            auto blink_step = [&]() {
//                if (HAL_GetTick() - blink_time >= BLINK_RATE_MS) {
//                    this->led.toggle();
//                    blink_time = HAL_GetTick();
//                }
//            };
//
//            auto timed_move = [&](int8_t left, int8_t right, uint32_t duration_ms) {
//                uint32_t t0 = HAL_GetTick();
//                this->locomotion.set_speed(left, right);
//                while (HAL_GetTick() - t0 < duration_ms) {
//                    blink_step();
//                }
//            };
//
//            for (uint8_t i = 0; i < REPEATS; i++) {
//                timed_move(80, 80, FORWARD_MS);
//                timed_move(80, -80, SPIN_MS);
//                timed_move(80, 80, FORWARD_MS);
//                timed_move(-80, 80, SPIN_MS);
//                timed_move(0, 0, PAUSE_MS);
//            }
//
//            this->locomotion.stop();
//            this->led.off();
//
//            this->turn = RC_INPUT;
//            this->current_state = RUN;
//            break;
//        }
//
//        default: {
//            this->locomotion.stop();
//            break;
//        }
//    }
//}
