#include "Servo.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include <stdio.h>
#include <stdlib.h> // Adicione este cabeçalho

#define ROTATE_0 700 // Rotate to 0° position
#define ROTATE_180 2300

Servo* servo_create(uint8_t gp) {
    Servo* servo = (Servo*)malloc(sizeof(Servo));
    if (servo == NULL) {
        return NULL;
    }

    servo->pin = gp;
    gpio_init(gp);

    // Setup up PWM
    gpio_set_function(gp, GPIO_FUNC_PWM);
    pwm_set_gpio_level(gp, 0);
    servo->slice_num = pwm_gpio_to_slice_num(gp);

    // Get clock speed and compute divider for 50 Hz
    uint32_t clk = clock_get_hz(clk_sys);
    uint32_t div = clk / (20000 * 50);

    // Check div is in range
    if (div < 1) {
        div = 1;
    }
    if (div > 255) {
        div = 255;
    }

    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, (float)div);

    // Set wrap so the period is 20 ms
    pwm_config_set_wrap(&config, 20000);

    // Load the configuration
    pwm_init(servo->slice_num, &config, false);
    pwm_set_enabled(servo->slice_num, true);

    return servo;
}

void servo_destroy(Servo* servo) {
    if (servo != NULL) {
        free(servo);
    }
}

void servo_go_degree(Servo* servo, float degree) {
    if (servo == NULL) {
        return;
    }
    if (degree > 180.0) {
        return;
    }
    if (degree < 0) {
        return;
    }

    int duty = (((float)(ROTATE_180 - ROTATE_0) / 180.0) * degree) + ROTATE_0;

    printf("PWM for %f deg is %d duty\n", degree, duty);
    pwm_set_gpio_level(servo->pin, duty);
}
