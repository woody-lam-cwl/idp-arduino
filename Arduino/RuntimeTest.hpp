#ifndef RuntimeTest_H
#define RuntimeTest_H

#include <Arduino.h>
#include "Constants.hpp"
#include "Logger.hpp"
#include "UnitTest.hpp"

enum TestState : byte {
    Idle,
    Initialising,
    Running,
    Stopping
};

enum TestType : byte {
    NoTest = 17U,
    TestLED = 18U,
    TestMotor = 19U,
    TestServo = 20U,
    TestLineSensor = 21U,
    TestUltrasonic = 22U,
    TestInfraRed = 23U
};


class RuntimeTest {
    public:
        RuntimeTest();
        void testLoop();

    private:
        Logger *logger;
        TestState currentState;
        IUnitTest *currentTest;
        void handleSerialIn(byte byteIn);
        IUnitTest* handleTest(byte byteIn);
};

#endif