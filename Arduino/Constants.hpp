#ifndef Constants_H
#define Constants_H

#include <Arduino.h>

#define BAUD_RATE                   115200

#define START_BUTTON_PIN            10

#define AMBER_LED_PIN               2
#define RED_LED_PIN                 3
#define GREEN_LED_PIN               4
#define AMBER_LED_FREQUENCY         2

#define LEFT_MOTOR_PORT             3
#define RIGHT_MOTOR_PORT            4
#define LEFT_MOTOR_NO_FLIP          true
#define RIGHT_MOTOR_NO_FLIP         true
#define RIGHT_TO_LEFT_FORWARD_POWER_RATIO   1.15
#define RIGHT_TO_LEFT_BACKWARD_POWER_RATIO  1.25
#define CRUISE_SPEED                255
#define ADJUSTMENT_INNER_SPEED      170
#define ADJUSTMENT_OUTER_SPEED      255

#define LEFT_SERVO_PIN              9
#define RIGHT_SERVO_PIN             8
#define LEFT_SERVO_GRAB_ANGLE       20
#define LEFT_SERVO_IDLE_ANGLE       105
#define RIGHT_SERVO_GRAB_ANGLE      110
#define RIGHT_SERVO_IDLE_ANGLE      25

#define ULTRASONIC_TRIGGER_PIN      12
#define ULTRASONIC_ECHO_PIN         13
#define ULTRASONIC_TIMEOUT_US       50000
#define ULTRASONIC_MM_CONVERSION    5.88
#define ULTRASONIC_LOWER_BOUND      10
#define ULTRASONIC_UPPER_BOUND      3000
#define ULTRASONIC_THRESHOLD        200

#define IR_ANALOG_PIN               0
#define IR_ADC_THRESHOLD            450

#define LINE_SENSOR_LEFT_PIN        5
#define LINE_SENSOR_CENTER_PIN      6
#define LINE_SENSOR_RIGHT_PIN       7

#define RAMP_DETECT_SUPPRESS_MS     1500
#define SECURE_BLOCK_MS             1500
#define FINAL_SWEEP_MS              2000
#define BACK_ROBOT_FIRST_MS         300
#define BACK_ROBOT_SECOND_MS        1000
#define BACK_ROBOT_LAST_MS          1400
#define BACK_ROBOT_CLASSSIFY_MS     1200
#define CLASSIFY_TIME_MS            2500
#define TURN_SUPPRESS_LINE_MS       2800
#define TURN_90DEG_MS               1600
#define REVERSE_TURN_MS             1500
#define CROSS_DETECT_SUPPRESS_MS    7000
#define FORWARD_AFTER_CROSS_MS      800
#define HOME_CROSS_DETECT_SUPPRESS_MS 500
#define FINAL_GRID_CROSS_SUPPRESS_MS 3000
#define GO_HOME_MS                  1700

#endif