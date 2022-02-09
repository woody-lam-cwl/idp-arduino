#include "Constants.h"
#include "RuntimeTest.h"
#include "Stages.h"
#include "Injection.h"

Injection *injectionPtr;
IUnitTest *testPtr;
IStage *stagePtr;

void setup()
{
    bool bluetoothMode = false;
    Injection injection;
    injectionPtr = &injection;

    // InfraRedTest test;
    // test.setup(injectionPtr->logger);
    // testPtr = &test;

    stagePtr = injectionPtr->lineTracing;
    injectionPtr->logger->log("System Initialised", Info);
}

void loop()
{
    stagePtr = stagePtr->loop();
    // testPtr->loop();
}