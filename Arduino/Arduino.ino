#include "Constants.h"
#include "RuntimeTest.h"
#include "Stages.h"
#include "Injection.h"

Injection *injectionPtr;
IUnitTest *testPtr;
IStage *stagePtr;
UltrasonicSensor *ultrasonicPtr;

void setup()
{
    bool bluetoothMode = false;
    Injection injection(bluetoothMode);
    injectionPtr = &injection;

    UltrasonicTest test;
    test.setup(injectionPtr->logger);
    testPtr = &test;

    // ultrasonicPtr = injectionPtr->ultrasonicSensor;
    // stagePtr = injectionPtr->lineTracing;

    // injectionPtr->logger->log("System Initialised", Info);
}

void loop()
{
    // injectionPtr->logger->log("In loop", Info);
    // stagePtr->loop();
    testPtr->loop();
    // bool shouldTurnLeft = true;
    // motorPtr->rotate(shouldTurnLeft);
    // motorPtr->goStraight();
    // ultrasonicPtr->updateDistanceInMM();
}