#ifndef Constants_H
#define Constants_H

#include <Arduino.h>

#define BAUD_RATE                   115200
#define WIRED_SERIAL_OVERRIDE       false

#define AMBER_LED_PIN               2
#define RED_LED_PIN                 3
#define BLUE_LED_PIN                4
#define AMBER_LED_FREQUENCY         2

#define LEFT_MOTOR_PORT             3
#define RIGHT_MOTOR_PORT            4
#define LEFT_MOTOR_NO_FLIP          true
#define RIGHT_MOTOR_NO_FLIP         true
#define LEFT_TO_RIGHT_POWER_RATIO   1
#define CRUISE_SPEED                150
#define ADJUSTMENT_INNER_SPEED      90
#define ADJUSTMENT_OUTER_SPEED      180

#define SERVO_PIN                   9
#define SERVO_GRAB_ANGLE            90
#define SERVO_IDLE_ANGLE            0

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

#define LINE_SENSOR_LEFT_PIN        5
#define LINE_SENSOR_CENTER_PIN      6
#define LINE_SENSOR_RIGHT_PIN       7

#endif