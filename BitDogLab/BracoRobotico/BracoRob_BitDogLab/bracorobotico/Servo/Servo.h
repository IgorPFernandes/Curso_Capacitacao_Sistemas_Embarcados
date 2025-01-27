#ifndef SERVO_H
#define SERVO_H

#include "pico/stdlib.h"

typedef struct {
    uint8_t pin;
    uint slice_num;
} Servo;

Servo* servo_create(uint8_t gp);
void servo_destroy(Servo* servo);
void servo_go_degree(Servo* servo, float degree);

#endif /* SERVO_H */
