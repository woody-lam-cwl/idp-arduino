#include "Constants.h"
#include "Motion.h"
#include "RuntimeTest.h"

Logger* logger;
IUnitTest* testPtr;

void setup()
{
    bool bluetoothMode = false;
    Logger loggerObj(bluetoothMode);
    logger = &loggerObj;
    logger->setup("Test Initialised");
    InfraRedTest test;
    testPtr = &test;
    testPtr->setup(logger);
}

void loop()
{
    testPtr->loop();
}