#ifndef RuntimeTest_H
#define RuntimeTest_H

#include <Arduino.h>
#include "Constants.h"
#include "Logger.h"
#include "UnitTest.h"

enum class TestState : byte {
    Idle,
    Initialising,
    Running,
    Stopping
};

enum class TestType : byte {
    NoTest,
    LED,
    Motor,
    Servo,
    LineSensor,
    Ultrasonic,
    InfraRed
};

class RuntimeTest {
    public:
        RuntimeTest(bool bluetoothLogger);
        void testLoop();

    private:
        Logger *logger;
        TestState currentState;
        BaseTest *currentTest;
        void handleSerialIn(byte byteIn);
        void handleState(byte byteIn);
        void handleTest(byte byteIn);
};

#endif