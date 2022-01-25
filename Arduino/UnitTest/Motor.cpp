#include "UnitTest.h"

void MotorTest::setup()
{
    Adafruit_MotorShield motorShield = Adafruit_MotorShield();
    leftMotor = motorShield.getMotor(LEFT_MOTOR_PORT);
    rightMotor = motorShield.getMotor(RIGHT_MOTOR_PORT);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    motorShield.begin();
}

void MotorTest::loop()
{
    leftMotor->setSpeed(200);
    leftMotor->run((LEFT_MOTOR_FLIP_DIRECTION)? BACKWARD : FORWARD);
    delay(1000);
    leftMotor->run(RELEASE);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    rightMotor->setSpeed(200);
    rightMotor->run((RIGHT_MOTOR_FLIP_DIRECTION)? BACKWARD : FORWARD);
    delay(1000);
    rightMotor->run(RELEASE);
    delay(1000);
    digitalWrite(LED_BUILTIN, HIGH);
}