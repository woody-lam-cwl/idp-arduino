#include "Motor.h"

MotorController::MotorController() {
    motorShield = Adafruit_MotorShield();
    leftMotor = motorShield.getMotor(LEFT_MOTOR_PORT);
    rightMotor = motorShield.getMotor(RIGHT_MOTOR_PORT);
}