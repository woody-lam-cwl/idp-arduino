#ifndef Constants_H
#define Constants_H

#include <Arduino.h>

#define BAUD_RATE                   115200

#define AMBER_LED_PIN               2
#define RED_LED_PIN                 3
#define GREEN_LED_PIN               4
#define AMBER_LED_FREQUENCY         2

#define LEFT_MOTOR_PORT             3
#define RIGHT_MOTOR_PORT            4
#define LEFT_MOTOR_NO_FLIP          true
#define RIGHT_MOTOR_NO_FLIP         true
#define LEFT_TO_RIGHT_POWER_RATIO   1.055
#define CRUISE_SPEED                245
#define ADJUSTMENT_INNER_SPEED      220
#define ADJUSTMENT_OUTER_SPEED      255

#define LEFT_SERVO_PIN              8
#define RIGHT_SERVO_PIN             9
#define LEFT_SERVO_GRAB_ANGLE       35
#define LEFT_SERVO_IDLE_ANGLE       60
#define RIGHT_SERVO_GRAB_ANGLE      95
#define RIGHT_SERVO_IDLE_ANGLE      70

#define ULTRASONIC_TRIGGER_PIN      12
#define ULTRASONIC_ECHO_PIN         13
#define ULTRASONIC_TIMEOUT_US       50000
#define ULTRASONIC_MM_CONVERSION    5.88
#define ULTRASONIC_LOWER_BOUND      10
#define ULTRASONIC_UPPER_BOUND      2000
#define ULTRASONIC_THRESHOLD        70

#define IR_ANALOG_PIN               0
#define IR_ADC_THRESHOLD            500

#define LINE_SENSOR_LEFT_PIN        5
#define LINE_SENSOR_CENTER_PIN      6
#define LINE_SENSOR_RIGHT_PIN       7

#define REBOUNCE_TIME_MS            1500
#define TURN_SUPPRESS_LINE_TIME_MS  2000
#define TURN_90DEG_TIME_MS          2000
#define CROSS_DETECT_SUPPRESS_MS    10000

#endif