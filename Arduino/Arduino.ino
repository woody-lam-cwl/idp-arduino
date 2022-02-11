#include "Constants.hpp"
#include "RuntimeTest.hpp"
#include "Stages.hpp"
#include "Injection.hpp"

Injection *injectionPtr;
IUnitTest *testPtr;
IStage *stagePtr;
LineSensor *lineSensor;

void setup()
{
    Injection injection;
    injectionPtr = &injection;

    LineSensorTest test;
    test.setup(&injectionPtr->logger);
    testPtr = &test;

    stagePtr = injectionPtr->getNewStage(nullptr, EnumStage::ForwardLineTracing);
    injectionPtr->logger.log("System Initialised", Info);
}

void loop()
{
    injectionPtr->lineSensor.getLineReading();
    LineReading reading = injectionPtr->stateMonitor.lineReading;
    injectionPtr->logger.log("MAIN:" + String(reading), LoggerLevel::Debug);
    // testPtr->loop();
}