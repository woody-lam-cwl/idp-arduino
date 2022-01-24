#ifndef UnitTest_H
#define UnitTest_H

#include <Arduino.h>

class BaseTest {
    virtual void setup();
    virtual void loop();
};

/** Blinking LED test for fundamental Arduino response */
class ArduinoTest : BaseTest {
    bool ledState;
    unsigned long lastChangedTime;
    void setup();
    void loop();
};

#endif