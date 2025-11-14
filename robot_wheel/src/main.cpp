#include <Arduino.h>
#include <ESP32Servo.h>

// Pin assignments
const int PIN_IN1      = 14;
const int PIN_IN2      = 27;
const int PIN_ENA      = 26;
const int PIN_SERVO    = 12;
const int PIN_LED_RED  = 25;
const int PIN_LED_WHITE= 32;
const int PIN_LED_GREEN= 33;

// Timing (milliseconds)
const unsigned long FORWARD_TIME   = 30000;  // 30 s
const unsigned long BACKWARD_TIME  = 30000;  // 30 s
const unsigned long SERVO_HOLD_TIME= 2000;   // 2 s at 90°

// Motor speed (0–255 for analogWrite-style PWM)
const int MOTOR_SPEED = 255;  // full speed

Servo legServo;

void stopMotor() {
  analogWrite(PIN_ENA, 0);
  digitalWrite(PIN_IN1, LOW);
  digitalWrite(PIN_IN2, LOW);
}

void driveForward() {
  digitalWrite(PIN_IN1, HIGH);
  digitalWrite(PIN_IN2, LOW);
  analogWrite(PIN_ENA, MOTOR_SPEED);
}

void driveBackward() {
  digitalWrite(PIN_IN1, LOW);
  digitalWrite(PIN_IN2, HIGH);
  analogWrite(PIN_ENA, MOTOR_SPEED);
}

void setServoAngle(int angle) {
  legServo.write(angle);
}

void setLeds(bool red, bool green, bool white) {
  digitalWrite(PIN_LED_RED,   red   ? HIGH : LOW);
  digitalWrite(PIN_LED_GREEN, green ? HIGH : LOW);
  digitalWrite(PIN_LED_WHITE, white ? HIGH : LOW);
}

void setup() {
  // Motor pins
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
  pinMode(PIN_ENA, OUTPUT);

  // LED pins
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_WHITE, OUTPUT);

  // Power LED always on
  digitalWrite(PIN_LED_RED, HIGH);

  // Servo attach
  legServo.attach(PIN_SERVO);
  setServoAngle(0);  // default position

  stopMotor();
}

void loop() {
  // FORWARD PHASE: 30 seconds
  setLeds(true, true, false);  // Red + Green (power + forward)
  setServoAngle(0);            // ensure servo at 0°
  driveForward();
  delay(FORWARD_TIME);

  stopMotor();

  // BACKWARD PHASE: 30 seconds
  setLeds(true, false, true);  // Red + White (power + backward)
  driveBackward();

  // Servo to 90° for 2 seconds, then back to 0°
  setServoAngle(90);
  delay(SERVO_HOLD_TIME);
  setServoAngle(0);  // return to default while still moving backward

  // Continue backward motion for remaining time
  delay(BACKWARD_TIME - SERVO_HOLD_TIME);

  stopMotor();

  // Loop repeats: forward 30 s, backward 30 s, etc.
}
