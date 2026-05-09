// ===== Motor Driver Pins =====
const int directionPin = 12;
const int pwmPin = 3;
const int brakePin = 9;

// ===== Ultrasonic Sensor Pins =====
const int trigPin = 6;
const int echoPin = 7;

// ===== Distance Limits =====
const float bottomDistance = 38.0; // cm = floor 3
const float topDistance = 12;     // cm = floor 4

// ===== Motor Speed =====
const int motorSpeed = 255;

void setup() {

  Serial.begin(9600);

  pinMode(directionPin, OUTPUT);
  pinMode(pwmPin, OUTPUT);
  pinMode(brakePin, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  digitalWrite(brakePin, LOW);
}

void loop() {

  moveToDistance(HIGH, bottomDistance, "Moving Down", true);

  delay(1000);

  moveToDistance(LOW, topDistance, "Moving Up", false);

  delay(1000);
}

void moveToDistance(int direction,
                    float targetDistance,
                    const char* message,
                    bool stopWhenGreater) {

  digitalWrite(directionPin, direction);

  while (true) {

    float distance = readDistance();

    Serial.print(message);
    Serial.print(" - Distance: ");
    Serial.println(distance, 1);

    analogWrite(pwmPin, motorSpeed);

    if ((stopWhenGreater && distance >= targetDistance) ||
        (!stopWhenGreater && distance <= targetDistance)) {

      stopMotor();
      break;
    }
  }
}

float readDistance() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);

  return duration * 0.0343 / 2.0;
}

void stopMotor() {

  analogWrite(pwmPin, 0);

  digitalWrite(brakePin, HIGH);
  delay(100);
  digitalWrite(brakePin, LOW);
}