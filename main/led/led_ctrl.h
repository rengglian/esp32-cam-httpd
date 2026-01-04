/* LED control API */
#ifndef LED_CTRL_H
#define LED_CTRL_H

#include <stdint.h>

void led_pwm_init(void);
void led_set_duty_percent(int percent);

#endif // LED_CTRL_H
