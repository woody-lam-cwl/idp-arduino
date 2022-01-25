#include "Motion.h"

void ServoController::setup(Logger *logger)
{
    this->logger = logger;
    servo.attach(SERVO_PIN);
    servo.write(SERVO_IDLE_ANGLE);
}

void ServoController::grab()
{
    servo.write(SERVO_GRAB_ANGLE);
}

void ServoController::release()
{
    servo.write(SERVO_IDLE_ANGLE);
}