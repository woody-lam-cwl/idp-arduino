#ifndef UnitTest_H
#define UnitTest_H

#include <Arduino.h>
#include <Adafruit_MotorShield.h>
#include "../Constants.h"

class BaseTest {
    public:
        virtual void setup();
        virtual void loop();
};

/** Blinking LED test for fundamental Arduino response */
class ArduinoTest : BaseTest {
    private:
        bool ledState;
        unsigned long lastChangedTime;

    public:
        void setup();
        void loop();
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
    private:
        Adafruit_DCMotor *leftMotor;
        Adafruit_DCMotor *rightMotor;

    public:
        void setup();
        void loop();
};

/** Test for servo attached to motor shield */
class ServoTest : BaseTest {
    public:
        void setup();
        void loop();
};

/** Test for servo attached to motor shield */
class LineSensorTest : BaseTest {
    public:
        void setup();
        void loop();
};

/** Test for servo attached to motor shield */
class UltrasonicTest : BaseTest {
    public:
        void setup();
        void loop();
};

/** Test for servo attached to motor shield */
class InfraRedTest : BaseTest {
    public:
        void setup();
        void loop();
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