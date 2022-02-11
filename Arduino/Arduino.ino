#include "Constants.hpp"
#include "Injection.hpp"
#include "UnitTest.hpp"
#include "Sequence.hpp"

Injection injection;
TaskSequence sequence(injection);
IUnitTest *testPtr;

void setup()
{
    // LineSensorTest test;
    // test.setup(&injection.logger);
    // testPtr = &test;

    injection.logger.setLevel(LoggerLevel::Info);
    injection.logger.log("System Initialised", Info);
}

void loop()
{
    // testPtr->loop();

    sequence.loop();
}