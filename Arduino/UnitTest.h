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
        virtual void setup(Logger *logger);
        virtual void loop();
};

/** Blinking LED test for fundamental Arduino response */
class ArduinoTest : BaseTest {
    public:
        void setup(Logger *logger = nullptr);
        void loop();

    private:
        Logger *logger;
        bool ledState;
        unsigned long lastChangedTime;
};

/** Test for serial writing communication with wired connection */
class SerialWriteTest : BaseTest {
    public:
        void setup(Logger *logger = nullptr);
        void loop();
};

/** Test for serial reading communication with wired connection */
class SerialReadTest : BaseTest {
    public:
        void setup(Logger *logger = nullptr);
        void loop();
};

/** Test for serial writing communication with bluetooth connection */
class BTSerialWriteTest : BaseTest {
    public:
        void setup(Logger *logger = nullptr);
        void loop();
};

/** Test for serial reading communication with bluetooth connection */
class BTSerialReadTest : BaseTest {
    public:
        void setup(Logger *logger = nullptr);
        void loop();
};

/** Test for three LEDs used in motion */
class LEDTest : BaseTest {
    public:
        void setup(Logger *logger = nullptr);
        void loop();
};

/** Test for two motors attached to motor shield */
class MotorTest : BaseTest {
    public:
        void setup(Logger *logger = nullptr);
        void loop();

    private:
        Adafruit_MotorShield *motorShield;
        Adafruit_DCMotor *leftMotor;
        Adafruit_DCMotor *rightMotor;
        Adafruit_DCMotor *motor3;
        Adafruit_DCMotor *motor4;
};

/** Test for servo attached to motor shield */
class ServoTest : BaseTest {
    public:
        void setup(Logger *logger = nullptr);
        void loop();
    
    private:
        Servo servo;
        byte position;
        bool isReverse;
};

/** Test for line sensors */
class LineSensorTest : BaseTest {
    public:
        void setup(Logger *logger);
        void loop();

    private:
        Logger *logger;
        byte sensor1Reading;
        byte sensor2Reading;
        byte sensor3Reading;
};

/** Test for ultrasonic sensor */
class UltrasonicTest : BaseTest {
    public:
        void setup(Logger *logger);
        void loop();

    private:
        Logger *logger;
        unsigned long pulseDuration;
        unsigned long distanceInMM;
};

/** Test for infrared sensor */
class InfraRedTest : BaseTest {
    public:
        void setup(Logger *logger);
        void loop();

    private:
        Logger *logger;
        int sensorReading;
};

#endif