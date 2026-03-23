/**
 * @file rc.cpp
 *
 * @author Comp Thunderatz <comp@thunderatz.org>
 *
 * @brief rc class implementation.
 *
 * @date 04/2025
 */

#ifndef RC_HPP
#define RC_HPP
#include <cstdint>
#include <tim.h>
#include "utils.hpp"

class Rc {
public:
    /**
     * @brief Construct a new Rc object.
     *
     * @param tim_init Function to initialize the timer.
     * @param tim_handle Pointer to the timer handle.
     * @param tim_ch1 Left timer channel.
     * @param tim_ch2 Right timer channel.
     */
    Rc(void (*tim_init)(), TIM_HandleTypeDef* tim_handle, uint8_t tim_ch1, uint8_t tim_ch2);

    /**
     * @brief Get the speed from the channel ch1.
     *
     * @return int16_t Speed from the channel ch1.
     */
    int16_t get_speed_ch1();

    /**
     * @brief Get the speed from the channel ch2.
     *
     * @return int16_t Speed from the channel ch2.
     */
    int16_t get_speed_ch2();

    /**
     * @brief Get the channel high time.
     *
     * @param channel Channel number.
     * @return uint32_t channel high time.
     */
    uint16_t get_ch_high_time(uint8_t channel);

    /**
     * @brief Convert pulse width to speed.
     *
     * @param pulse Pulse width.
     * @return int16_t Speed.
     */
    int16_t pulse_to_speed(uint16_t pulse);

    static void handle_global_callback(TIM_HandleTypeDef* htim);

private:
    static Rc* rc_instance;

    TIM_HandleTypeDef* tim_handle;

    uint8_t tim_ch1;
    uint8_t tim_ch2;

    uint16_t ch1_rising_time = 0;
    uint16_t ch1_falling_time = 0;
    uint16_t ch2_rising_time = 0;
    uint16_t ch2_falling_time = 0;
    uint16_t ch1_high_time = 0;
    uint16_t ch2_high_time = 0;

    void process_input_capture(TIM_HandleTypeDef* htim);
};
#endif  // RC_HPP
