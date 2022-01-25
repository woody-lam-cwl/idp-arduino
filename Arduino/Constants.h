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
#define SERVO_PIN                   9

#define ULTRASONIC_TRIGGER_PIN      12
#define ULTRASONIC_ECHO_PIN         13
#define ULTRASONIC_TIMEOUT_US       50000
#define ULTRASONIC_MM_CONVERSION    5.88
#define ULTRASONIC_LOWER_BOUND      10
#define ULTRASONIC_UPPER_BOUND      2000

#define IR_ANALOG_PIN               3
#define IR_LOWER_BOUND_DIST_CM      20
#define IR_UPPER_BOUND_DIST_CM      150
#define IR_LOWER_BOUND_VOLTAGE      0.5
#define IR_UPPER_BOUND_VOLTAGE      2.5

#define LINE_SENSOR_1_PIN           5
#define LINE_SENSOR_2_PIN           6
#define LINE_SENSOR_3_PIN           7

#endif