#ifndef Motor_H
#define Motor_H

#include <Arduino.h>
#include <Servo.h>
#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include "Constants.hpp"
#include "Logger.hpp"
#include "StateMonitor.hpp"

enum class Color : byte {
    Red,
    Green
};

class Motor {
    public:
        Motor(
            Logger &logger,
            MotorState &motorState,
            Adafruit_DCMotor *motorAdr = nullptr,
            bool motorIsNotFlipped = true);
        void setMotion(Direction direction, byte speed = 0U);

    private:
        Logger &logger;
        MotorState &motorState;
        Adafruit_DCMotor *motorAdr;
        bool motorIsNotFlipped;
        byte getMotorDirection(Direction direction);
        bool isNewCommand(Direction direction, byte speed = 0U);
};

class MotorController {
    public:
        MotorController(
            Logger &logger,
            StateMonitor &stateMonitor
        );
        void goStraight(bool forward = true);
        void adjustHeading(bool shouldTurnLeft = true);
        void rotate(bool shouldTurnLeft = true);
        void release();

    private:
        Logger &logger;
        StateMonitor &stateMonitor;
        Adafruit_MotorShield *motorShield;
        Motor *leftMotor;
        Motor *rightMotor;
};

class ServoController {
    public:
        ServoController(
            Logger &logger,
            StateMonitor &stateMonitor
        );
        void grab();
        void release();

    private:
        Logger &logger;
        StateMonitor &stateMonitor;
        Servo leftServo;
        Servo rightServo;
};

class LEDController {
    public:
        LEDController(
            Logger &logger,
            StateMonitor &stateMonitor
        );
        void flashAmber();
        void stopAmber();
        void turnOnBlockLED(Color color);
        void resetBlockLED();

    private:
        Logger &logger;
        StateMonitor &stateMonitor;
        void toggleLED(Color color, bool state);
        unsigned int amberFlashPeriod;
        unsigned long lastAmberFlashTime;
        bool AmberLED;
};

#endif