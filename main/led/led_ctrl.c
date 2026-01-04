/* LED control implementation */
#include "led/led_ctrl.h"
#include <driver/ledc.h>
#include <esp_log.h>

#define LED_GPIO        4
#define LEDC_TIMER      LEDC_TIMER_0
#define LEDC_MODE       LEDC_LOW_SPEED_MODE
#define LEDC_CHANNEL    LEDC_CHANNEL_0
#define LEDC_DUTY_RES   LEDC_TIMER_13_BIT   // 0..8191
#define LEDC_FREQUENCY  5000                // 5 kHz

static const char *TAG = "led_ctrl";

void led_pwm_init(void)
{
    ledc_timer_config_t timer = {
        .speed_mode       = LEDC_MODE,
        .timer_num        = LEDC_TIMER,
        .duty_resolution  = LEDC_DUTY_RES,
        .freq_hz          = LEDC_FREQUENCY,
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ledc_timer_config(&timer);

    ledc_channel_config_t channel = {
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL,
        .timer_sel      = LEDC_TIMER,
        .gpio_num       = LED_GPIO,
        .duty           = 0,
        .hpoint         = 0
    };
    ledc_channel_config(&channel);

    ESP_LOGI(TAG, "LED PWM initialized on GPIO %d", LED_GPIO);
}

void led_set_duty_percent(int percent)
{
    if (percent < 0) percent = 0;
    if (percent > 100) percent = 100;

    uint32_t max_duty = (1 << LEDC_DUTY_RES) - 1;
    uint32_t duty = (percent >= 100)
        ? max_duty
        : (max_duty * (uint32_t)percent) / 100u;

    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, duty);
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
}
