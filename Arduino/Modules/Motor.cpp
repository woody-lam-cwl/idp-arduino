#include "Motor.h"

MotorController::MotorController(Logger *logger) {
    this->logger = logger;
}

void MotorController::setup() {
    motorShield = Adafruit_MotorShield();
    leftMotor = motorShield.getMotor(LEFT_MOTOR_PORT);
    rightMotor = motorShield.getMotor(RIGHT_MOTOR_PORT);
    logger->log("Motor controller initialised", LoggerLevel::Info);
}
