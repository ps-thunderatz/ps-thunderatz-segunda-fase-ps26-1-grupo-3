/**
 * @file locomotion.hpp
 *
 * @author Comp Thunderatz <comp@thunderatz.org>
 *
 * @brief Locomotion class definition.
 *
 * @date 04/2025
 */

#ifndef LOCOMOTION_HPP
#define LOCOMOTION_HPP

#include "motor.hpp"

/**
 * @brief locomotion class.
 */
class Locomotion {
public:
    /**
     * @brief Construct a new locomotion object.
     *
     */
    Locomotion(Motor& motor_left, Motor& motor_right);

    /**
     * @brief Set the speed of the locomotion.
     *
     * @param left_speed locomotion speed.
     * @param right_speed locomotion speed.
     *
     */
    void set_speed(int8_t left_speed, int8_t right_speed);

    /**
     * @brief Stop the locomotion.
     *
     */
    void stop();

private:
    Motor& motor_left;
    Motor& motor_right;
};

#endif  // LOCOMOTION_HPP
