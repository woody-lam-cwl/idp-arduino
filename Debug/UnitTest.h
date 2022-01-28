#ifndef UnitTest_H
#define UnitTest_H

#include <String.h>
#include <Arduino.h>
#include <Servo.h>
#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include "Constants.h"
#include "Logger.h"

class BaseTest {
    public:
        virtual void setup(Logger *logger) = 0;
        virtual void loop() = 0;
};

/** Test for two motors attached to motor shield */
class MotorTest : public BaseTest {
    public:
        void setup(Logger *logger = nullptr);
        void loop();

    private:
        Logger *logger;
        Adafruit_MotorShield *motorShield;
        Adafruit_DCMotor *leftMotor;
        Adafruit_DCMotor *rightMotor;
};

#endif