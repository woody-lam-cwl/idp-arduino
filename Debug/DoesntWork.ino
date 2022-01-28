#include "Constants.h"
#include "RuntimeTest.h"

Logger* logger;
BaseTest* testPtr;

void setup()
{
    bool bluetoothMode = false;
    Logger loggerObj(bluetoothMode);
    logger = &loggerObj;
    logger->setup("Test Initialised");
    MotorTest test;
    testPtr = &test;
    testPtr->setup(logger);
}

void loop()
{
    testPtr->loop();
}