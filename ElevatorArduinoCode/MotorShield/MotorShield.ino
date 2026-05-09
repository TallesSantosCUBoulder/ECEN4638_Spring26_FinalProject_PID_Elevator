// simple safe motor test code
// prevents motor from running on startup
// improves safe stop behavior for arduino motor shield

int directionPin = 12; // controls motor direction
int pwmPin = 3;        // controls motor speed (pwm)
int brakePin = 9;      // controls motor braking

// alternative pins for channel b (if needed)
// int directionPin = 13;
// int pwmPin = 11;
// int brakePin = 8;

void setup() {

  // set motor control pins as outputs
  pinMode(directionPin, OUTPUT);
  pinMode(pwmPin, OUTPUT);
  pinMode(brakePin, OUTPUT);

  // safety startup behavior

  // make sure motor is off at startup
  analogWrite(pwmPin, 0);

  // immediately apply brake so motor cannot move
  digitalWrite(brakePin, HIGH);

  // set a default safe direction
  digitalWrite(directionPin, LOW);

  // wait for system to stabilize before running anything
  delay(1000);
}

void loop() {

  // motor run test

  // set motor direction forward
  digitalWrite(directionPin, HIGH);

  // release brake so motor can move
  digitalWrite(brakePin, LOW);

  // start motor at medium speed
  analogWrite(pwmPin, 180);

  // let motor run for 1 second
  delay(1000);

  // motor stop test

  // stop motor power first (important for safety)
  analogWrite(pwmPin, 0);

  // apply brake to stop motor quickly
  digitalWrite(brakePin, HIGH);

  // wait to ensure full stop
  delay(500);

  // optional safety step:
  // set direction low to reduce unwanted current flow
  digitalWrite(directionPin, LOW);

  // pause before repeating cycle
  delay(1000);
}