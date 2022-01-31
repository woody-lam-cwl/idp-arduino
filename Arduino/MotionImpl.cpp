#include "Motion.h"

Motor::Motor(Adafruit_DCMotor* motorAdr, bool motorIsNotFlipped)
{
    motor = *motorAdr;
    this->motorIsNotFlipped = motorIsNotFlipped;
    direction = Direction::Drive;
    speed = 1;
    setMotion(Direction::Neutral);
}

void Motor::setMotion(Direction direction, byte speed = 0U)
{
    if (!isNewCommand(direction, speed)) return;

    byte motorDirection = RELEASE;

    switch (direction) {
        case Direction::Drive:
            motorDirection = (motorIsNotFlipped)? FORWARD : BACKWARD;
            break;

        case Direction::Reverse:
            motorDirection = (motorIsNotFlipped)? BACKWARD : FORWARD;
            break;

        default:
            break;
    }

    motor.setSpeed((motorDirection == RELEASE)? 0U : speed);
    motor.run(motorDirection);
}

bool Motor::isNewCommand(Direction direction, byte speed = 0U)
{
    if (this->direction == Direction::Neutral && direction == Direction::Neutral) return false;
    if (this->direction == direction && this->speed == speed) return false;
    this->direction = direction;
    this->speed = speed;
    return true;
}

void MotorController::setup(Logger *logger)
{
    this->logger = logger;
    Adafruit_MotorShield motorShield = Adafruit_MotorShield();
    motorShield.begin();
    Adafruit_DCMotor *leftMotorAdr = motorShield.getMotor(LEFT_MOTOR_PORT);
    Adafruit_DCMotor *rightMotorAdr = motorShield.getMotor(RIGHT_MOTOR_PORT);
    leftMotor = Motor(leftMotorAdr, LEFT_MOTOR_NO_FLIP);
    rightMotor = Motor(rightMotorAdr, LEFT_MOTOR_NO_FLIP);
    logger->log("Motor controller initialised", LoggerLevel::Info);
}

void MotorController::goStraight()
{
    leftMotor.setMotion(Direction::Drive, CRUISE_SPEED);
    rightMotor.setMotion(Direction::Drive, CRUISE_SPEED);
}

void MotorController::adjustHeading(bool shouldTurnLeft)
{
    if (shouldTurnLeft) {
        leftMotor.setMotion(Direction::Drive, CRUISE_SPEED);
        rightMotor.setMotion(Direction::Drive, ADJUSTMENT_SPEED);
    }
    else {
        leftMotor.setMotion(Direction::Drive, ADJUSTMENT_SPEED);
        rightMotor.setMotion(Direction::Drive, CRUISE_SPEED);
    }
}

void MotorController::rotate(bool shouldTurnLeft)
{
    if (shouldTurnLeft) {
        leftMotor.setMotion(Direction::Reverse, CRUISE_SPEED);
        rightMotor.setMotion(Direction::Drive, CRUISE_SPEED);
    }
    else {
        leftMotor.setMotion(Direction::Drive, CRUISE_SPEED);
        rightMotor.setMotion(Direction::Reverse, CRUISE_SPEED);
    }
}

void ServoController::setup(Logger *logger)
{
    this->logger = logger;
    servo.attach(SERVO_PIN);
    servo.write(SERVO_IDLE_ANGLE);
}

void ServoController::grab()
{
    servo.write(SERVO_GRAB_ANGLE);
}

void ServoController::release()
{
    servo.write(SERVO_IDLE_ANGLE);
}