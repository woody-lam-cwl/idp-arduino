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

class IUnitTest {
    public:
        virtual void setup(Logger *logger) = 0;
        virtual void loop() = 0;
};

/** Blinking LED test for fundamental Arduino response */
class ArduinoTest : public IUnitTest {
    public:
        void setup(Logger *logger = nullptr);
        void loop();

    private:
        bool ledState;
        unsigned long lastChangedTime;
};

/** Test for serial writing communication with wired connection */
class SerialWriteTest : public IUnitTest {
    public:
        void setup(Logger *logger = nullptr);
        void loop();
};

/** Test for serial reading communication with wired connection */
class SerialReadTest : public IUnitTest {
    public:
        void setup(Logger *logger = nullptr);
        void loop();
};

/** Test for serial writing communication with bluetooth connection */
class BTSerialWriteTest : public IUnitTest {
    public:
        void setup(Logger *logger = nullptr);
        void loop();
};

/** Test for serial reading communication with bluetooth connection */
class BTSerialReadTest : public IUnitTest {
    public:
        void setup(Logger *logger = nullptr);
        void loop();
};

/** Test for three LEDs used in motion */
class LEDTest : public IUnitTest {
    public:
        void setup(Logger *logger = nullptr);
        void loop();
};

/** Test for two motors attached to motor shield */
class MotorTest : public IUnitTest {
    public:
        void setup(Logger *logger = nullptr);
        void loop();

    private:
        Logger *logger;
        Adafruit_MotorShield motorShield;
        Adafruit_DCMotor *leftMotor;
        Adafruit_DCMotor *rightMotor;
};

/** Test for servo attached to motor shield */
class ServoTest : public IUnitTest {
    public:
        void setup(Logger *logger = nullptr);
        void loop();
    
    private:
        Servo servo;
        byte position;
        bool isReverse;
};

/** Test for line sensors */
class LineSensorTest : public IUnitTest {
    public:
        void setup(Logger *logger);
        void loop();

    private:
        Logger *logger;
        byte leftSensorReading;
        byte centerSensorReading;
        byte rightSensorReading;
};

/** Test for ultrasonic sensor */
class UltrasonicTest : public IUnitTest {
    public:
        void setup(Logger *logger);
        void loop();

    private:
        Logger *logger;
        unsigned long pulseDuration;
        unsigned long distanceInMM;
};

/** Test for infrared sensor */
class InfraRedTest : public IUnitTest {
    public:
        void setup(Logger *logger);
        void loop();

    private:
        Logger *logger;
        int sensorReading;
};

#endif