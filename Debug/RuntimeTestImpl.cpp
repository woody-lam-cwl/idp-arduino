#include "RuntimeTest.h"

RuntimeTest::RuntimeTest(bool bluetoothLogger)
{
    Logger logger(bluetoothLogger);
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