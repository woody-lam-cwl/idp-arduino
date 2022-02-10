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

enum class Color : byte {
    Red,
    Green
};

class MotorState {
    public:
        byte speed;
        Direction direction;
};

class Motor {
    public:
        Motor(
            Logger *logger = nullptr,
            MotorState *motorState = nullptr,
            Adafruit_DCMotor *motorAdr = nullptr,
            bool motorIsNotFlipped = true);
        void setMotion(Direction direction, byte speed = 0U);

    private:
        Logger *logger;
        MotorState *motorState;
        Adafruit_DCMotor *motorAdr;
        bool motorIsNotFlipped;
        byte getMotorDirection(Direction direction);
        bool isNewCommand(Direction direction, byte speed = 0U);
};

class MotorController {
    public:
        MotorController(Logger *logger = nullptr);
        void goStraight();
        void adjustHeading(bool shouldTurnLeft = true);
        void rotate(bool shouldTurnLeft = true);
        void release();

    private:
        Logger *logger;
        Adafruit_MotorShield *motorShield;
        Motor *leftMotor;
        Motor *rightMotor;
};

class ServoController {
    public:
        ServoController(Logger *logger = nullptr);
        void grab();
        void release();

    private:
        Logger *logger;
        Servo leftServo;
        Servo rightServo;
};

class LEDController {
    public:
        LEDController(Logger *logger = nullptr);
        void flashAmber();
        void stopAmber();
        void toggleLED(Color color, bool state);

    private:
        Logger *logger;
        unsigned int amberFlashPeriod;
        unsigned long lastAmberFlashTime;
        bool AmberLED;
};

#endif