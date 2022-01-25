#include "UnitTest.h"

void ServoTest::setup()
{
    position = 0;
    servo.attach(SERVO_PIN);
    servo.write(position);
}

void ServoTest::loop()
{
    if (position == 0) isReverse = false;
    if (position == 180) isReverse = true;
    position += isReverse? -1 : 1;
    servo.write(position);
    delay(50);
}