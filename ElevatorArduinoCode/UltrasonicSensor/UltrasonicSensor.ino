/*
   HC-SR04 Ultrasonic Sensor Example
 
   This program measures the distance to an object
   using the HC-SR04 ultrasonic sensor and prints
   the result to the Serial Monitor.
 */

const int trigPin = 6;
const int echoPin = 7;

float duration, distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(100);
}
