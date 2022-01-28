#include "UnitTest.h"

void MotorTest::setup(Logger *logger = nullptr)
{
    this->logger = logger;
    Adafruit_MotorShield motorShieldObj = Adafruit_MotorShield();
    motorShield = &motorShieldObj;

    if (!motorShield->begin()) {
        logger->log("Could not find Motor Shield. Check wiring.", Error);
        while (1);
    }
    logger->log("Motor Shield found.", Info);

    leftMotor = motorShield->getMotor(LEFT_MOTOR_PORT);
    rightMotor = motorShield->getMotor(RIGHT_MOTOR_PORT);
}

void MotorTest::loop()
{   
    leftMotor->setSpeed(100);
    leftMotor->run((LEFT_MOTOR_NO_FLIP)? FORWARD : BACKWARD);
    delay(1000);
    leftMotor->run(RELEASE);
    delay(1000);
    logger->log("Checkpoint 1", Debug);

    rightMotor->setSpeed(100);
    rightMotor->run((RIGHT_MOTOR_NO_FLIP)? FORWARD : BACKWARD);
    delay(1000);
    rightMotor->run(RELEASE);
    delay(1000);
    logger->log("Checkpoint 2", Debug);
}