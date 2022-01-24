#ifndef Motor_H
#define Motor_H

#include <Arduino.h>
#include <Adafruit_MotorShield.h>
#include "../Constants.h"

class MotorController {
    private:
        Adafruit_MotorShield motorShield;
        Adafruit_DCMotor *leftMotor;
        Adafruit_DCMotor *rightMotor;

    public:
        MotorController();
};

class ServoController {
    public:
        void setup();
};

#endif