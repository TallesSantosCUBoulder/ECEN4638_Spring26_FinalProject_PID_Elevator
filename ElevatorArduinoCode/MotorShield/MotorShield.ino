// ======================================
// SIMPLE SAFE MOTOR TEST CODE
// Prevents motor from running on startup
// Better stop behavior for Arduino Motor Shield
// ======================================

int directionPin = 12;
int pwmPin = 3;
int brakePin = 9;

// Uncomment if using channel B
// int directionPin = 13;
// int pwmPin = 11;
// int brakePin = 8;

void setup() {

  // Define pins
  pinMode(directionPin, OUTPUT);
  pinMode(pwmPin, OUTPUT);
  pinMode(brakePin, OUTPUT);

  // ==================================
  // IMPORTANT STARTUP SAFETY
  // ==================================

  // Disable PWM
  analogWrite(pwmPin, 0);

  // Apply brake immediately
  digitalWrite(brakePin, HIGH);

  // Set default direction
  digitalWrite(directionPin, LOW);

  // Wait for system stabilization
  delay(1000);
}

void loop() {

  // ==================================
  // RUN MOTOR
  // ==================================

  // Set direction
  digitalWrite(directionPin, HIGH);

  // Release brake
  digitalWrite(brakePin, LOW);

  // Start motor slowly
  analogWrite(pwmPin, 180);

  // Run motor
  delay(1000);

  // ==================================
  // STOP MOTOR PROPERLY
  // ==================================

  // Stop PWM first
  analogWrite(pwmPin, 0);

  // Apply brake
  digitalWrite(brakePin, HIGH);

  // Small delay for full stop
  delay(500);

  // Optional:
  // Set direction LOW to reduce leakage
  digitalWrite(directionPin, LOW);

  // Pause
  delay(1000);
}
```
