#include "Motion.h"

Motor::Motor(
    Logger *logger,
    MotorState *motorState,
    Adafruit_DCMotor* motorAdr,
    bool motorIsNotFlipped)
{
    this->logger = logger;
    this->motorState = motorState;
    this->motorAdr = motorAdr;
    this->motorIsNotFlipped = motorIsNotFlipped;

    motorState->direction.updateState(Direction::Drive);
    motorState->speed.updateState(1);

    isNewCommand(Direction::Neutral);
    logger->log("Motor initialised", LoggerLevel::Info);
}

void Motor::setMotion(Direction direction, byte speed = 0U)
{
    if (isNewCommand(direction, speed)) {
        motorAdr->setSpeed(speed);
        motorAdr->run(getMotorDirection(direction));

        motorState->direction.updateState(direction);
        motorState->speed.updateState(speed);
    }
}

byte Motor::getMotorDirection(Direction direction)
{
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

    return motorDirection;
}

bool Motor::isNewCommand(Direction direction, byte speed = 0U)
{
    if (motorState->direction.getState() == Direction::Neutral && direction == Direction::Neutral) return false;
    if (motorState->direction.getState() == direction && motorState->speed.getState() == speed) return false;
    
    return true;
}

MotorController::MotorController(
    Logger *logger = nullptr,
    StateMonitor *stateMonitor = nullptr)
{
    this->logger = logger;
    this->stateMonitor = stateMonitor;

    motorShield = Adafruit_MotorShield();

    if (!motorShield.begin()) {
        logger->log("Could not find Motor Shield. Check wiring.", Error);
        while (1);
    }
    logger->log("Motor Shield found.", Info);

    Adafruit_DCMotor *leftMotorAdr = motorShield.getMotor(LEFT_MOTOR_PORT);
    Adafruit_DCMotor *rightMotorAdr = motorShield.getMotor(RIGHT_MOTOR_PORT);
    leftMotor = Motor(
        logger,
        &stateMonitor->leftMotorState,
        leftMotorAdr,
        LEFT_MOTOR_NO_FLIP);
    rightMotor = Motor(
        logger,
        &stateMonitor->rightMotorState,
        rightMotorAdr,
        RIGHT_MOTOR_NO_FLIP);
    logger->log("Motor controller initialised", LoggerLevel::Info);
}

void MotorController::goStraight()
{
    // logger->log("Going straight", LoggerLevel::Debug);
    leftMotor.setMotion(Direction::Drive, CRUISE_SPEED);
    rightMotor.setMotion(Direction::Drive, CRUISE_SPEED / LEFT_TO_RIGHT_POWER_RATIO);
}

void MotorController::adjustHeading(bool shouldTurnLeft = true)
{
    if (shouldTurnLeft) {
        leftMotor.setMotion(Direction::Drive, ADJUSTMENT_INNER_SPEED);
        rightMotor.setMotion(Direction::Drive, ADJUSTMENT_OUTER_SPEED);
    }
    else {
        leftMotor.setMotion(Direction::Drive, ADJUSTMENT_OUTER_SPEED);
        rightMotor.setMotion(Direction::Drive, ADJUSTMENT_INNER_SPEED);
    }
}

void MotorController::rotate(bool shouldTurnLeft = true)
{
    if (shouldTurnLeft) {
        leftMotor.setMotion(Direction::Reverse, CRUISE_SPEED);
        rightMotor.setMotion(Direction::Drive, CRUISE_SPEED / LEFT_TO_RIGHT_POWER_RATIO);
    }
    else {
        leftMotor.setMotion(Direction::Drive, CRUISE_SPEED);
        rightMotor.setMotion(Direction::Reverse, CRUISE_SPEED / LEFT_TO_RIGHT_POWER_RATIO);
    }
}

void MotorController::release()
{
    leftMotor.setMotion(Direction::Neutral);
    rightMotor.setMotion(Direction::Neutral);
}

ServoController::ServoController(
    Logger *logger = nullptr,
    StateMonitor *stateMonitor = nullptr)
{
    this->logger = logger;
    this->stateMonitor = stateMonitor;

    servo.attach(SERVO_PIN);
    servo.write(SERVO_IDLE_ANGLE);
    stateMonitor->servoState.updateState(SERVO_IDLE_ANGLE);

    logger->log("Servo controller initialised", LoggerLevel::Info);
}

void ServoController::grab()
{
    servo.write(SERVO_GRAB_ANGLE);
    stateMonitor->servoState.updateState(SERVO_GRAB_ANGLE);
}

void ServoController::release()
{
    servo.write(SERVO_IDLE_ANGLE);
    stateMonitor->servoState.updateState(SERVO_IDLE_ANGLE);
}

LEDController::LEDController(
    Logger *logger = nullptr,
    StateMonitor *stateMonitor = nullptr)
{
    this->logger = logger;
    this->stateMonitor = stateMonitor;

    pinMode(AMBER_LED_PIN, OUTPUT);
    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(GREEN_LED_PIN, OUTPUT);
    digitalWrite(AMBER_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);
    AmberLED = 0;
    amberFlashPeriod = 1000 / AMBER_LED_FREQUENCY / 2;
    lastAmberFlashTime = 0;

    stateMonitor->ledAmberFlashState.updateState(false);
    stateMonitor->ledRedState.updateState(false);
    stateMonitor->ledGreenState.updateState(false);
    logger->log("LED controller initialised", LoggerLevel::Info);
}

void LEDController::flashAmber()
{
    unsigned long currentTime = millis();
    if (currentTime - lastAmberFlashTime > amberFlashPeriod) {
        AmberLED = !AmberLED;
        digitalWrite(AMBER_LED_PIN, (AmberLED)? HIGH : LOW);
        lastAmberFlashTime = currentTime;
    }
}

void LEDController::stopAmber()
{
    AmberLED = 0;
    digitalWrite(AMBER_LED_PIN, LOW);
    logger->log("Amber LED stopped flashing", LoggerLevel::Info);
    lastAmberFlashTime = millis();
}

void LEDController::toggleLED(Color color, bool state)
{
    switch (color) {
        case Color::Red:
            digitalWrite(RED_LED_PIN, (state)? HIGH : LOW);
            logger->log("Red LED state set", LoggerLevel::Info);
            break;

        case Color::Green:
            digitalWrite(GREEN_LED_PIN, (state)? HIGH : LOW);
            logger->log("Green LED state set", LoggerLevel::Info);
            break;

        default:
            logger->log("Invalid LED Color", LoggerLevel::Error);
            break;
    }
}