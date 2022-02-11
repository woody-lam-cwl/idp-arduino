#include "Constants.hpp"
#include "Injection.hpp"
#include "UnitTest.hpp"
#include "Sequence.hpp"

Injection injection;
TaskSequence sequence(injection);
IUnitTest *testPtr;

void setup()
{
    LineSensorTest test;
    test.setup(&injection.logger);
    testPtr = &test;
    injection.logger.log("System Initialised", Info);
}

void loop()
{
    sequence.loop();
    // testPtr->loop();
}