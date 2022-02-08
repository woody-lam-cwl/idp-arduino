#include "RuntimeTest.h"

RuntimeTest::RuntimeTest()
{
    Logger logger;
    this->logger = &logger;
    currentState = TestState::Idle;
    currentTest = nullptr;
}

void RuntimeTest::testLoop()
{

}

void RuntimeTest::handleSerialIn(byte byteIn)
{

}

IUnitTest* handleTest(byte byteIn)
{
    IUnitTest* testPtr;

    switch(byteIn)
    {
        case TestType::NoTest:
            testPtr = nullptr;
            break;

        case TestType::TestMotor:
            testPtr = new MotorTest();
            break;

        case TestType::TestServo:
            testPtr = new ServoTest();
            break;

        case TestType::TestUltrasonic:
            testPtr = new UltrasonicTest();
            break;

        case TestType::TestLineSensor:
            testPtr = new LineSensorTest();
            break;

        case TestType::TestInfraRed:
            testPtr = new InfraRedTest();
            break;

        case TestType::TestLED:
            testPtr = new LEDTest();
            break;
    }

    return testPtr;
}