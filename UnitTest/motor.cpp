#include <Adafruit_MotorShield.h>

void setup()
{
    Adafruit_MotorShield motorShield = Adafruit_MotorShield();
    Adafruit_DCMotor *motor1 = motorShield.getMotor(1);
    Adafruit_DCMotor *motor2 = motorShield.getMotor(2);
    Adafruit_DCMotor *motor3 = motorShield.getMotor(3);
    Adafruit_DCMotor *motor4 = motorShield.getMotor(4);
}

void loop()
{
}