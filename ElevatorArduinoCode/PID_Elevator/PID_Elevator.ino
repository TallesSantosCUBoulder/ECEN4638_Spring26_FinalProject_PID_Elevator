// ===== Motor Driver Pins =====
const int directionPin = 12;
const int pwmPin = 3;
const int brakePin = 9;

// ===== Ultrasonic Sensor Pins =====
const int trigPin = 6;
const int echoPin = 7;

// ===== Distance Limits =====
const float bottomDistance = 38.0; // cm = floor 3 
const float topDistance = 11.0;    // cm = floor 4

// ===== PID Controller =====
#include <PID_v1.h>

double iKp = 15.0;
double iKi = 5.0;
double iKd = 7.5;

double input_var = 0.0;
double output_var = 0.0;
double reference_var = 0.0;

PID height_PID(&input_var,
               &output_var,
               &reference_var,
               iKp,
               iKi,
               iKd,
               REVERSE);

void setup() {

  Serial.begin(115200);

  // Motor pins
  pinMode(directionPin, OUTPUT);
  pinMode(pwmPin, OUTPUT);
  pinMode(brakePin, OUTPUT);

  // Ultrasonic pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Release brake
  digitalWrite(brakePin, LOW);

  // PID setup
  height_PID.SetMode(AUTOMATIC);

  // PWM output range
  height_PID.SetOutputLimits(70, 255);
}

void loop() {

  // Move down to floor 3
  moveToDistance(HIGH,
                 bottomDistance,
                 "Moving Down",
                 true);

  delay(1000);

  // Move up to floor 4
  moveToDistance(LOW,
                 topDistance,
                 "Moving Up",
                 false);

  delay(1000);
}

void moveToDistance(int direction,
                    float targetDistance,
                    const char* message,
                    bool stopWhenGreater) {

  digitalWrite(directionPin, direction);

  while (true) {

    float distance = readDistance();
/*
    Serial.print(message);
    Serial.print(" - Distance: ");
    Serial.println(distance, 1);
    Serial.print(" - Distance: ");
*/
    // PID error
    input_var = abs(distance - targetDistance);

    // Goal is zero error
    reference_var = 0.0;

    // Compute PID
    height_PID.Compute();

    Serial.print(input_var);
    Serial.print("  ");
    Serial.print(output_var);
    Serial.print("  ");
    Serial.print(reference_var);
    Serial.print("\n");

    // Apply PWM
    analogWrite(pwmPin, (int)output_var);

    // Stop conditions
    if ((stopWhenGreater && distance >= targetDistance) ||
        (!stopWhenGreater && distance <= targetDistance)) {

      stopMotor();
      break;
    }

    delay(30);
  }
}

// ===================================
// FUNCTION: Read Ultrasonic Distance
// ===================================
float readDistance() {

  // Clear trigger
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo
  long duration = pulseIn(echoPin, HIGH);

  // Convert to cm
  float distance = duration * 0.0343 / 2.0;

  return distance;
}

// =====================
// FUNCTION: Stop Motor
// =====================
void stopMotor() {

  analogWrite(pwmPin, 0);

  digitalWrite(brakePin, HIGH);

  delay(100);

  digitalWrite(brakePin, LOW);
}