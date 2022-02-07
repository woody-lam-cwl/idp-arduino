#include "Constants.h"
#include "RuntimeTest.h"
#include "Stages.h"
#include "Injection.h"

Injection *injectionPtr;
IUnitTest *testPtr;
IStage *stagePtr;
// MotorController *motorPtr;

void setup()
{
    bool bluetoothMode = false;
    Injection injection(bluetoothMode);
    injectionPtr = &injection;

    // LineSensorTest test;
    // test.setup(injectionPtr->logger);
    // testPtr = &test;

    // motorPtr = injectionPtr->motorController;

    stagePtr = injectionPtr->lineTracing;

    injectionPtr->logger->log("System Initialised", Info);
}

void loop()
{
    // injectionPtr->logger->log("In loop", Info);
    stagePtr->loop();
    // testPtr->loop();
    // bool shouldTurnLeft = true;
    // motorPtr->rotate(shouldTurnLeft);
    // motorPtr->goStraight();
}