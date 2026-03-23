/**
 * @file rc.cpp
 *
 * @author Comp Thunderatz<comp @thunderatz.org>
 *
 * @brief rc class implementation.
 *
 * @date 04 / 2025
 */

#include "rc.hpp"
#include "target.hpp"

Rc* Rc::rc_instance = nullptr;

Rc::Rc(void (*tim_init)(), TIM_HandleTypeDef* tim_handle, uint8_t tim_ch1, uint8_t tim_ch2) :
    tim_handle{tim_handle}, tim_ch1{tim_ch1}, tim_ch2{tim_ch2} {
    rc_instance = this;
    tim_init();
    HAL_TIM_Base_Start(this->tim_handle);
    HAL_TIM_IC_Start_IT(this->tim_handle, this->tim_ch1);
    HAL_TIM_IC_Start_IT(this->tim_handle, this->tim_ch2);
}

int16_t Rc::get_speed_ch1() {
    return pulse_to_speed(this->get_ch_high_time(this->tim_ch1));
}

int16_t Rc::get_speed_ch2() {
    return pulse_to_speed(this->get_ch_high_time(this->tim_ch2));
}

uint16_t Rc::get_ch_high_time(uint8_t channel) {
    if (channel == this->tim_ch1) {
        return this->ch1_high_time;
    } else if (channel == this->tim_ch2) {
        return this->ch2_high_time;
    }
    return 0;
}

int16_t Rc::pulse_to_speed(uint16_t pulse) {
    return map<int16_t>(pulse, 1000, 2000, -100, 100);
}

void Rc::process_input_capture(TIM_HandleTypeDef* htim) {
    if (htim->Instance == this->tim_handle->Instance) {
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
            if (HAL_GPIO_ReadPin(CH1_GPIO_Port, CH1_Pin) != 0U) {
                this->ch1_rising_time = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
            } else {
                this->ch1_falling_time = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
                this->ch1_high_time = this->ch1_falling_time - this->ch1_rising_time;
            }
        }

        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2) {
            if (HAL_GPIO_ReadPin(CH2_GPIO_Port, CH2_Pin) != 0U) {
                this->ch2_rising_time = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
            } else {
                this->ch2_falling_time = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
                this->ch2_high_time = this->ch2_falling_time - this->ch2_rising_time;
            }
        }
    }
}

void Rc::handle_global_callback(TIM_HandleTypeDef* htim) {
    if (rc_instance != nullptr) {
        rc_instance->process_input_capture(htim);
    }
}
