#ifndef Motor_H
#define Motor_H

#include <Arduino.h>
#include <Adafruit_MotorShield.h>
#include "../Constants.h"
#include "Logger.h"

class MotorController {
    private:
        Adafruit_MotorShield motorShield;
        Adafruit_DCMotor *leftMotor;
        Adafruit_DCMotor *rightMotor;
        Logger *logger;
    public:
        MotorController(Logger *logger);
        void setup();
};

class ServoController {
    private:
        Logger *logger;
    public:
        ServoController(Logger *logger);
        void setup();
};

#endif