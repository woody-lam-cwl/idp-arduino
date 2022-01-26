#ifndef Motor_H
#define Motor_H

#include <Arduino.h>
#include <Servo.h>
#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include "Constants.h"
#include "Logger.h"

class MotorController {
    public:
        void setup(Logger *logger);
        void moveForward(byte speed);
        void rotate(byte clockwiseAngle);

    private:
        Adafruit_DCMotor *motors[2];
        Logger *logger;
        byte motorSpeeds[2];
        byte motorDirections[2];
};

class ServoController {
    public:
        void setup(Logger *logger);
        void grab();
        void release();

    private:
        Logger *logger;
        Servo servo;
};

#endif