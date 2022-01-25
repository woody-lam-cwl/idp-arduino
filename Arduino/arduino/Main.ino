#include "../Constants.h"
#include "../Modules/Motion.h"
#include "../RuntimeTest/RuntimeTest.h"

RuntimeTest *runtimeTest;

void setup()
{
    bool bluetoothMode = true;
    RuntimeTest test(bluetoothMode);
    runtimeTest = &test;
}

void loop()
{
    runtimeTest->testLoop();
}