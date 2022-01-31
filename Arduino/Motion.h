#ifndef Motor_H
#define Motor_H

#include <Arduino.h>
#include <Servo.h>
#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include "Constants.h"
#include "Logger.h"

enum class Direction : byte {
    Drive,
    Reverse,
    Neutral
};

class Motor {
    public:
        Motor(Adafruit_DCMotor *motorAdr, bool motorIsNotFlipped);
        void setMotion(Direction direction, byte speed = 0U);

    private:
        Adafruit_DCMotor motor;
        bool motorIsNotFlipped;
        Direction direction;
        byte speed;
        bool isNewCommand(Direction direction, byte speed = 0U);
};

class MotorController {
    public:
        void setup(Logger *logger);
        void goStraight();
        void adjustHeading(bool shouldTurnLeft);
        void rotate(bool shouldTurnLeft);

    private:
        Logger *logger;
        Motor leftMotor;
        Motor rightMotor;
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