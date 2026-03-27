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
    this->led = led;
    this->locomotion = locomotion;
    this->rc = rc;
}

void Controller::init(){
    this->current_state = INIT;
}

void Controller::run() {
    switch (this->current_state) {
        case STRATEGY_CHOOSER: {

            //4 segundos para escolher a estrategia
            this->led.on();
            hal::mcu::sleep(1000);
            this->led.toggle();
            hal::mcu::sleep(1000);
            this->led.toggle();
            hal::mcu::sleep(1000);
            this->led.toggle();
            hal::mcu::sleep(1000);
            this->led.toggle();


            /*TABELA DO RC e qual estrategia*/
            //CH1 <= 0 e CH2 <= 0 (os dois para tras) => LEVEL_0
            //CH1 <= 0 e CH2 > 0 => LEVEL_1
            //CH1 > 0 e CH2 <= 0 => LEVEL_2
            //CH1 > 0 e CH2 > 0 (os dois para frente) => LEVEL_3
            //OBS: Se o controle estiver solto (0, 0), ele ira para level_0


            if(this->rc.get_speed_ch1() <= 0){
                if(this->rc.get_speed_ch2()<=0) this->strategy_run = LEVEL_0;
                else this->strategy_run = LEVEL_1;
            }
            else{
                if(this->rc.get_speed_ch2()<0) this->strategy_run = LEVEL_2;
                else this->strategy_run = LEVEL_3;
            }
            this->led.off();

            this->current_state = RUN;
            break;
        }
        case RUN: {
            this->strategy_run();

            uint32_t start_time = HAL_GetTick();
            while (HAL_GetTick() - start_time < 10000) { //tempo para poder controlar o robo
                this->move_robot(RC_INPUT)
            }
            this->current_state = STRATEGY_CHOOSER;
            while

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
        // TODO: Implementar a lógica de movimentação do robô
        case FORWARD: {
            this->locomotion.set_speed(80, 80);
            break;
        }
        case BACKWARD: {
            this->locomotion.set_speed(-80, -80);
            break;
        }
        case LEFT: {
            this->locomotion.set_speed(35, 80);
            break;
        }
        case RIGHT: {
            this->locomotion.set_speed(80, 35);
            break;
        }
        case STOPPED: {
            this->locomotion.stop();
            break;
        }
        case RC_INPUT: {
            this->locomotion.set_speed(this->rc.get_speed_ch1(),this->rc.get_speed_ch2());
            break;
        }
        default: {
            this->locomotion.stop(); //em teoria, nunca deve estar aqui
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
            //this->current_state = RUN;
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
            //this->current_state = RUN;
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
            //this->current_state = RUN;
            break;
        }

        default: {
            this->locomotion.stop();
            break;
        }
    }
}
