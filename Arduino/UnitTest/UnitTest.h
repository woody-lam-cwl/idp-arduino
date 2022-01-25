#ifndef UnitTest_H
#define UnitTest_H

#include <String.h>
#include <Arduino.h>
#include <Servo.h>
#include <Adafruit_MotorShield.h>
#include "../Constants.h"
#include "../Modules/Logger.h"

class BaseTest {
    public:
        virtual void setup();
        virtual void loop();
};

/** Blinking LED test for fundamental Arduino response */
class ArduinoTest : BaseTest {
    public:
        void setup();
        void loop();

    private:
        bool ledState;
        unsigned long lastChangedTime;
};

/** Test for serial writing communication with wired connection */
class SerialWriteTest : BaseTest {
    public:
        void setup();
        void loop();
};

/** Test for serial reading communication with wired connection */
class SerialReadTest : BaseTest {
    public:
        void setup();
        void loop();
};

/** Test for serial writing communication with bluetooth connection */
class BTSerialWriteTest : BaseTest {
    public:
        void setup();
        void loop();
};

/** Test for serial reading communication with bluetooth connection */
class BTSerialReadTest : BaseTest {
    public:
        void setup();
        void loop();
};

/** Test for two motors attached to motor shield */
class MotorTest : BaseTest {
    public:
        void setup();
        void loop();

    private:
        Adafruit_DCMotor *leftMotor;
        Adafruit_DCMotor *rightMotor;
};

/** Test for servo attached to motor shield */
class ServoTest : BaseTest {
    public:
        void setup();
        void loop();
    
    private:
        Servo servo;
        byte position;
        bool isReverse;
};

/** Test for line sensors */
class LineSensorTest : BaseTest {
    public:
        void setup();
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
        void setup();
        void loop();

    private:
        Logger *logger;
        unsigned long pulseDuration;
        unsigned long distanceInMM;
};

/** Test for infrared sensor */
class InfraRedTest : BaseTest {
    public:
        void setup();
        void loop();

    private:
        Logger *logger;
        int sensorReading;
};

class TestCollection {
    public:
        ArduinoTest arduinoTest;
        SerialWriteTest serialWriteTest;
        SerialReadTest serialReadTest;
        BTSerialWriteTest btSerialWriteTest;
        BTSerialReadTest btSerialReadTest;
        MotorTest motorTest;
        ServoTest servoTest;
        LineSensorTest lineSensorTest;
        UltrasonicTest ultrasonicTest;
        InfraRedTest infraRedTest;
};

#endif