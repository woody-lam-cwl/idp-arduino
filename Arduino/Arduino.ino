#include "Constants.h"
#include "Motion.h"
#include "RuntimeTest.h"

Logger* logger;
LEDTest* testPtr;

void setup()
{
    bool bluetoothMode = false;
    Logger loggerObj(bluetoothMode);
    logger = &loggerObj;
    logger->setup("Test Initialised");
    LEDTest test;
    testPtr = &test;
    testPtr->setup(logger);
}

void loop()
{
    testPtr->loop();
}
