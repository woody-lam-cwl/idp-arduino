#include "Constants.h"
#include "RuntimeTest.h"
#include "Stages.h"
#include "Injection.h"

Injection *injectionPtr;
IUnitTest *testPtr;
IStage *stagePtr;

void setup()
{
    Injection injection;
    injectionPtr = &injection;

    LineSensorTest test;
    test.setup(injectionPtr->logger);
    testPtr = &test;

    stagePtr = injectionPtr->lineTracing;
    injectionPtr->logger->log("System Initialised", Info);
}

void loop()
{
    stagePtr = stagePtr->loop();
    // testPtr->loop();
}