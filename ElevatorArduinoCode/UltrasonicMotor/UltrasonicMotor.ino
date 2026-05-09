// Motor driver pins
// These pins control the motor driver
const int directionPin = 12; // Controls motor direction (up or down)
const int pwmPin = 3;        // Controls motor speed
const int brakePin = 9;      // Stops the motor quickly

// Ultrasonic sensor pins
// These pins connect to the HC-SR04 sensor
const int trigPin = 6; // Sends ultrasonic pulse
const int echoPin = 7; // Receives reflected pulse

// Distance limits
// Distances used to stop the elevator/platform
const float bottomDistance = 38.0; // Distance for floor 3
const float topDistance = 12;      // Distance for floor 4

// Motor speed
// Maximum motor speed (0–255)
const int motorSpeed = 255;

void setup() {

  // Start Serial Monitor for debugging
  Serial.begin(9600);

  // Set motor driver pins as outputs
  pinMode(directionPin, OUTPUT);
  pinMode(pwmPin, OUTPUT);
  pinMode(brakePin, OUTPUT);

  // Set ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Release brake at startup
  digitalWrite(brakePin, LOW);
}

void loop() {

  // Move downward until the bottom distance is reached
  moveToDistance(HIGH, bottomDistance, "Moving Down", true);

  // Wait 1 second
  delay(1000);

  // Move upward until the top distance is reached
  moveToDistance(LOW, topDistance, "Moving Up", false);

  // Wait 1 second
  delay(1000);
}

void moveToDistance(int direction,
                    float targetDistance,
                    const char* message,
                    bool stopWhenGreater) {

  // Set motor direction
  digitalWrite(directionPin, direction);

  // Keep running until target distance is reached
  while (true) {

    // Read current distance from sensor
    float distance = readDistance();

    // Print movement status and distance
    Serial.print(message);
    Serial.print(" - Distance: ");
    Serial.println(distance, 1);

    // Run motor at selected speed
    analogWrite(pwmPin, motorSpeed);

    // Stop motor if target distance condition is met
    if ((stopWhenGreater && distance >= targetDistance) ||
        (!stopWhenGreater && distance <= targetDistance)) {

      stopMotor();
      break;
    }
  }
}

float readDistance() {

  // Clear trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send 10 microsecond pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure echo return time
  long duration = pulseIn(echoPin, HIGH);

  // Convert time into distance in centimeters
  return duration * 0.0343 / 2.0;
}

void stopMotor() {

  // Stop motor speed
  analogWrite(pwmPin, 0);

  // Briefly activate brake
  digitalWrite(brakePin, HIGH);
  delay(100);

  // Release brake again
  digitalWrite(brakePin, LOW);
}