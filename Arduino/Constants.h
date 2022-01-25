#ifndef Constants_H
#define Constants_H

#include <Arduino.h>

#define BAUD_RATE                   115200
#define WIRED_SERIAL_ENABLED        false
#define BLUETOOTH_SERIAL_ENABLED    true

#define LEFT_MOTOR_PORT             1
#define RIGHT_MOTOR_PORT            2
#define LEFT_MOTOR_FLIP_DIRECTION   false
#define RIGHT_MOTOR_FLIP_DIRECTION  false
#define LEFT_TO_RIGHT_POWER_RATIO   1

#define ULTRASONIC_TRIGGER_PIN      12
#define ULTRASONIC_ECHO_PIN         13
#define ULTRASONIC_TIMEOUT_US       50000
#define ULTRASONIC_MM_CONVERSION    5.88
#define ULTRASONIC_LOWER_BOUND      10
#define ULTRASONIC_UPPER_BOUND      2000

#endif