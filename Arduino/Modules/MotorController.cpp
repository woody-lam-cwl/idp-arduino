#include "Motion.h"

void MotorController::setup(Logger *logger) {
    this->logger = logger;
    Adafruit_MotorShield motorShield = Adafruit_MotorShield();
    motors[0] = motorShield.getMotor(LEFT_MOTOR_PORT);
    motors[1] = motorShield.getMotor(RIGHT_MOTOR_PORT);
    motorShield.begin();
    logger->log("Motor controller initialised", LoggerLevel::Info);
}

void MotorController::moveForward(byte speed)
{

}

void MotorController::rotate(byte clockwiseAngle)
{

}