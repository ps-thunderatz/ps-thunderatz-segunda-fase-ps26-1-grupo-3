#include <cstdint>
#include "led.hpp"
#include "rc.hpp"
#include "mcu.hpp"
#include "target.hpp"
#include "motor.hpp"
#include "utils.hpp"
#include "locomotion.hpp"
#include "controller.hpp"

static volatile int16_t left_speed;
static volatile int16_t right_speed;
static volatile int16_t channel_1;
static volatile int16_t channel_2;

int main() {
    hal::mcu::init();

    Led led(LED_GPIO_Port, LED_Pin);
    led.on();

    Motor leftMotor(
        MOTORS_TIM_INIT, &MOTORS_TIM_HANDLER, LEFT_MOTOR_FORWARD_TIM_CH, &MOTORS_TIM_HANDLER, LEFT_MOTOR_BACKWARD_TIM_CH
    );

    Motor rightMotor(
        MOTORS_TIM_INIT, &MOTORS_TIM_HANDLER, RIGHT_MOTOR_FORWARD_TIM_CH, &MOTORS_TIM_HANDLER,
        RIGHT_MOTOR_BACKWARD_TIM_CH
    );

    Locomotion locomotion(leftMotor, rightMotor);

    Rc rc(RC_RECEIVER_TIM_INIT, &RC_RECEIVER_CH1_TIM_HANDLER, RC_RECEIVER_CH1_TIM_CH, RC_RECEIVER_CH2_TIM_CH);

    uint32_t led_timer = HAL_GetTick();
    uint8_t led_blink_count = 0;

    Controller controller(led, locomotion, rc);

    controller.init();
    for (;;) {
        controller.run();
        //locomotion.set_speed(rc.get_speed_ch1(), rc.get_speed_ch2());
        }
    return 0;
}

extern "C" void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef* htim) {
    Rc::handle_global_callback(htim);
}
