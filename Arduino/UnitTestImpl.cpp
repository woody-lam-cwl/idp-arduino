#include "UnitTest.h"

void ArduinoTest::setup(Logger *logger = nullptr)
{
    ledState = false;
    lastChangedTime = 0;
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
}

void ArduinoTest::loop()
{
    unsigned long currentTime = millis();
    if (currentTime - lastChangedTime > 500)
    {
        lastChangedTime = currentTime;
        digitalWrite(LED_BUILTIN, (ledState ? HIGH : LOW));
        ledState = !ledState;
    }
}

void SerialWriteTest::setup(Logger *logger = nullptr)
{
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(BAUD_RATE);
    digitalWrite(LED_BUILTIN, LOW);
    while (!Serial);
}

void SerialWriteTest::loop()
{
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("Serial writing from Arduino");
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
}

void SerialReadTest::setup(Logger *logger = nullptr)
{
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(BAUD_RATE);
    digitalWrite(LED_BUILTIN, LOW);
    while (!Serial);
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("Arduino ready to receive serial message");
}

void SerialReadTest::loop()
{
    if (Serial.available() > 0) {
        digitalWrite(LED_BUILTIN, LOW);
        char data = Serial.read();
        Serial.print("Data received: ");
        Serial.println(data);
        delay(500);
        digitalWrite(LED_BUILTIN, HIGH);
    }
}

// NINA Component to be setup using SerialToSerialBT programme before use
void BTSerialWriteTest::setup(Logger *logger = nullptr)
{
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(NINA_RESETN, OUTPUT);
    digitalWrite(NINA_RESETN, LOW);
    SerialNina.begin(BAUD_RATE);
    digitalWrite(LED_BUILTIN, LOW);
    while (!SerialNina);
}

void BTSerialWriteTest::loop()
{
    digitalWrite(LED_BUILTIN, HIGH);
    SerialNina.println("Serial writing from Arduino");
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
}

void BTSerialReadTest::setup(Logger *logger = nullptr)
{
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(NINA_RESETN, OUTPUT);
    digitalWrite(NINA_RESETN, LOW);
    SerialNina.begin(BAUD_RATE);
    digitalWrite(LED_BUILTIN, LOW);
    while (!SerialNina);
    digitalWrite(LED_BUILTIN, HIGH);
    SerialNina.println("Arduino ready to receive serial message");
}

void BTSerialReadTest::loop()
{
    if (SerialNina.available() > 0) {
        digitalWrite(LED_BUILTIN, LOW);
        char data = SerialNina.read();
        SerialNina.print("Data received: ");
        SerialNina.println(data);
        delay(500);
        digitalWrite(LED_BUILTIN, HIGH);
    }
}

void LEDTest::setup(Logger *logger = nullptr)
{
    pinMode(AMBER_LED_PIN, OUTPUT);
    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(BLUE_LED_PIN, OUTPUT);
    digitalWrite(AMBER_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, LOW);
}

void LEDTest::loop()
{
    digitalWrite(AMBER_LED_PIN, HIGH);
    delay(500);
    digitalWrite(AMBER_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);
    delay(500);
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, HIGH);
    delay(500);
    digitalWrite(BLUE_LED_PIN, LOW);
}

void MotorTest::setup(Logger *logger = nullptr)
{
    this->logger = logger;
    motorShield = Adafruit_MotorShield();

    if (!motorShield.begin()) {
        logger->log("Could not find Motor Shield. Check wiring.", Error);
        while (1);
    }
    logger->log("Motor Shield found.", Info);

    leftMotor = motorShield.getMotor(LEFT_MOTOR_PORT);
    rightMotor = motorShield.getMotor(RIGHT_MOTOR_PORT);

    leftMotor->setSpeed(255);
    leftMotor->run((LEFT_MOTOR_NO_FLIP)? FORWARD : BACKWARD);
    rightMotor->setSpeed(255);
    rightMotor->run((RIGHT_MOTOR_NO_FLIP)? FORWARD : BACKWARD);
}

void MotorTest::loop()
{       
    leftMotor->setSpeed(255);
    leftMotor->run((LEFT_MOTOR_NO_FLIP)? FORWARD : BACKWARD);
    rightMotor->setSpeed(255);
    rightMotor->run((RIGHT_MOTOR_NO_FLIP)? FORWARD : BACKWARD);
    delay(200);

    // leftMotor->setSpeed(100);
    // leftMotor->run((LEFT_MOTOR_NO_FLIP)? FORWARD : BACKWARD);
    // delay(1000);
    // leftMotor->run(RELEASE);
    // delay(1000);
    // rightMotor->setSpeed(100);
    // rightMotor->run((RIGHT_MOTOR_NO_FLIP)? FORWARD : BACKWARD);
    // delay(1000);
    // rightMotor->run(RELEASE);
    // delay(1000);
}

void ServoTest::setup(Logger *logger = nullptr)
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

void LineSensorTest::setup(Logger *logger)
{
    this->logger = logger;
    pinMode(LINE_SENSOR_LEFT_PIN, INPUT);
    pinMode(LINE_SENSOR_CENTER_PIN, INPUT);
    pinMode(LINE_SENSOR_RIGHT_PIN, INPUT);
    this->logger->log("Line sensor test initialised", Info);
}

void LineSensorTest::loop()
{
    leftSensorReading = digitalRead(LINE_SENSOR_LEFT_PIN);
    centerSensorReading = digitalRead(LINE_SENSOR_CENTER_PIN);
    rightSensorReading = digitalRead(LINE_SENSOR_RIGHT_PIN);
    String message = "Line sensor reading: " + String(leftSensorReading, DEC) + " " + String(centerSensorReading, DEC) + " " + String(rightSensorReading, DEC);
    logger->log(message, LoggerLevel::Info);
    delay(500);
}

void UltrasonicTest::setup(Logger *logger)
{
    this->logger = logger;
    pinMode(ULTRASONIC_TRIGGER_PIN, OUTPUT);
    digitalWrite(ULTRASONIC_TRIGGER_PIN, LOW);
    pinMode(ULTRASONIC_ECHO_PIN, INPUT);
    this->logger->log("Ultrasonic test initialised", Info);
}

void UltrasonicTest::loop()
{
    delay(500);
    digitalWrite(ULTRASONIC_TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(ULTRASONIC_TRIGGER_PIN, LOW);
    unsigned long pulseDuration = pulseIn(ULTRASONIC_ECHO_PIN, HIGH, ULTRASONIC_TIMEOUT_US);
    unsigned long distanceInMM = pulseDuration / ULTRASONIC_MM_CONVERSION;
    if (distanceInMM < ULTRASONIC_LOWER_BOUND || distanceInMM > ULTRASONIC_UPPER_BOUND) {
        logger->log("Invalid reading from ultrasonic sensor", LoggerLevel::Error);
        return;
    }
    String message = "Ultrasonic sensor measured: " + String(distanceInMM, DEC);
    logger->log(message, LoggerLevel::Info);
}

void InfraRedTest::setup(Logger *logger)
{
    this->logger = logger;
    this->logger->log("Infrared test initialised", Info);
}

void InfraRedTest::loop()
{
    sensorReading = analogRead(IR_ANALOG_PIN);
    String message = "IR sensor ADC output: " + String(sensorReading, DEC);
    logger->log(message, LoggerLevel::Info);
    delay(500);
}