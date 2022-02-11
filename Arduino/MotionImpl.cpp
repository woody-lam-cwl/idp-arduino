#include "Motion.hpp"

Motor::Motor(
    Logger &logger,
    MotorState &motorState,
    Adafruit_DCMotor* motorAdr = nullptr,
    bool motorIsNotFlipped = true
) : logger {logger},
    motorState {motorState}
{
    this->motorState = motorState;
    this->motorAdr = motorAdr;
    this->motorIsNotFlipped = motorIsNotFlipped;

    motorState.direction.updateState(Direction::Drive);
    motorState.speed.updateState(1);

    isNewCommand(Direction::Neutral);
    logger.log("Motor initialised", LoggerLevel::Info);
}

void Motor::setMotion(Direction direction, byte speed = 0U)
{
    if (isNewCommand(direction, speed)) {
        motorAdr->setSpeed(speed);
        motorAdr->run(getMotorDirection(direction));

        motorState.direction.updateState(direction);
        motorState.speed.updateState(speed);
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
    if (motorState.direction.getState() == Direction::Neutral && direction == Direction::Neutral) return false;
    if (motorState.direction.getState() == direction && motorState.speed.getState() == speed) return false;
    
    return true;
}

MotorController::MotorController(
    Logger &logger,
    StateMonitor &stateMonitor
) : logger {logger},
    stateMonitor {stateMonitor}
{
    motorShield = new Adafruit_MotorShield();

    if (!motorShield->begin()) {
        logger.log("Could not find Motor Shield. Check wiring.", LoggerLevel::Error);
        while (1);
    }

    Adafruit_DCMotor *leftMotorAdr = motorShield->getMotor(LEFT_MOTOR_PORT);
    Adafruit_DCMotor *rightMotorAdr = motorShield->getMotor(RIGHT_MOTOR_PORT);

    leftMotor = new Motor(
        logger,
        stateMonitor.leftMotorState,
        leftMotorAdr,
        LEFT_MOTOR_NO_FLIP);
    rightMotor = new Motor(
        logger,
        stateMonitor.rightMotorState,
        rightMotorAdr,
        RIGHT_MOTOR_NO_FLIP);
    
    logger.log("Motor controller initialised", LoggerLevel::Info);
}

void MotorController::goStraight(bool forward = true)
{
    if (forward) logger.log("Motor going straight forward", LoggerLevel::DebugHardware);
    else logger.log("Motor going straight backward", LoggerLevel::DebugHardware);
    leftMotor->setMotion((forward)? Direction::Drive : Direction::Reverse, CRUISE_SPEED / RIGHT_TO_LEFT_POWER_RATIO);
    rightMotor->setMotion((forward)? Direction::Drive : Direction::Reverse, CRUISE_SPEED);
}

void MotorController::adjustHeading(bool shouldTurnLeft = true)
{
    if (shouldTurnLeft) {
        logger.log("Motor adjusting to left", LoggerLevel::DebugHardware);
        leftMotor->setMotion(Direction::Drive, ADJUSTMENT_INNER_SPEED / RIGHT_TO_LEFT_POWER_RATIO);
        rightMotor->setMotion(Direction::Drive, ADJUSTMENT_OUTER_SPEED);
    }
    else {
        logger.log("Motor adjusting to right", LoggerLevel::DebugHardware);
        leftMotor->setMotion(Direction::Drive, ADJUSTMENT_OUTER_SPEED / RIGHT_TO_LEFT_POWER_RATIO);
        rightMotor->setMotion(Direction::Drive, ADJUSTMENT_INNER_SPEED);
    }
}

void MotorController::rotate(bool shouldTurnLeft = true)
{
    logger.log("Robot turning", LoggerLevel::DebugHardware);
    if (shouldTurnLeft) {
        leftMotor->setMotion(Direction::Reverse, CRUISE_SPEED / RIGHT_TO_LEFT_POWER_RATIO);
        rightMotor->setMotion(Direction::Drive, CRUISE_SPEED);
    }
    else {
        leftMotor->setMotion(Direction::Drive, CRUISE_SPEED / RIGHT_TO_LEFT_POWER_RATIO);
        rightMotor->setMotion(Direction::Reverse, CRUISE_SPEED);
    }
}

void MotorController::neutral()
{
    logger.log("Motor released", LoggerLevel::DebugHardware);
    leftMotor->setMotion(Direction::Neutral);
    rightMotor->setMotion(Direction::Neutral);
}

ServoController::ServoController(
    Logger &logger,
    StateMonitor &stateMonitor
) : logger {logger},
    stateMonitor {stateMonitor}
{
    leftServo.attach(LEFT_SERVO_PIN);
    rightServo.attach(RIGHT_SERVO_PIN);
    release();
    logger.log("Servo controller initialised", LoggerLevel::Info);
}

void ServoController::grab()
{
    logger.log("Servo arms grabbed", LoggerLevel::DebugHardware);
    leftServo.write(LEFT_SERVO_GRAB_ANGLE);
    rightServo.write(RIGHT_SERVO_GRAB_ANGLE);
    stateMonitor.servoGrabbed.updateState(true);
}

void ServoController::release()
{
    logger.log("Servo arms released", LoggerLevel::DebugHardware);
    leftServo.write(LEFT_SERVO_IDLE_ANGLE);
    rightServo.write(RIGHT_SERVO_IDLE_ANGLE);
    stateMonitor.servoGrabbed.updateState(false);
}

LEDController::LEDController(
    Logger &logger,
    StateMonitor &stateMonitor
) : logger {logger},
    stateMonitor {stateMonitor},
    amberFlashPeriod {1000 / AMBER_LED_FREQUENCY / 2},
    lastAmberFlashTime {0}
{
    pinMode(AMBER_LED_PIN, OUTPUT);
    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(GREEN_LED_PIN, OUTPUT);
    stopAmber();
    resetBlockLED();
    logger.log("LED controller initialised", LoggerLevel::Info);
}

void LEDController::flashAmber()
{
    logger.log("Amber LED flashing", LoggerLevel::DebugHardware);
    stateMonitor.amberFlashing.updateState(true);
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
    logger.log("Amber LED stopped flashing", LoggerLevel::DebugHardware);
    stateMonitor.amberFlashing.updateState(false);
}

void LEDController::toggleLED(Color color, bool state)
{
    switch (color) {
        case Color::Red:
            stateMonitor.redOn.updateState(state);
            digitalWrite(RED_LED_PIN, (state)? HIGH : LOW);
            logger.log("Red LED state set", LoggerLevel::DebugHardware);
            break;

        case Color::Green:
            stateMonitor.greenOn.updateState(state);
            digitalWrite(GREEN_LED_PIN, (state)? HIGH : LOW);
            logger.log("Green LED state set", LoggerLevel::DebugHardware);
            break;

        default:
            logger.log("Invalid LED Color", LoggerLevel::DebugHardware);
            break;
    }
}

void LEDController::turnOnBlockLED(Color color)
{
    toggleLED(color, HIGH);
}

void LEDController::resetBlockLED()
{
    toggleLED(Color::Red, LOW);
    toggleLED(Color::Green, LOW);
}
