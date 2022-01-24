#ifndef UnitTest_H
#define UnitTest_H

#include <Arduino.h>

#define BAUD_RATE 115200

class BaseTest {
    public:
        virtual void setup();
        virtual void loop();
};

/** Blinking LED test for fundamental Arduino response */
class ArduinoTest : BaseTest {
    public:
        bool ledState;
        unsigned long lastChangedTime;
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

class TestCollection {
    public:
        ArduinoTest arduinoTest;
        SerialWriteTest serialWriteTest;
        SerialReadTest serialReadTest;
};

#endif