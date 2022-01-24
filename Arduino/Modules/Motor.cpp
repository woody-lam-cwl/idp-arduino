#include "Motor.h"

void MotorController::setup() {
    motorShield = Adafruit_MotorShield();
    leftMotor = motorShield.getMotor(LEFT_MOTOR_PORT);
    rightMotor = motorShield.getMotor(RIGHT_MOTOR_PORT);
}
