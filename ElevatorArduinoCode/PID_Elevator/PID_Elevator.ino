// Motor driver pins
const int directionPin = 12; // Sets motor direction
const int pwmPin = 3;        // Controls motor speed using PWM
const int brakePin = 9;      // Activates motor brake

// Ultrasonic sensor pins
const int trigPin = 6; // Sends ultrasonic pulse
const int echoPin = 7; // Receives reflected pulse

// Target distances for each floor
const float bottomDistance = 38.0; // Floor 3 position in cm
const float topDistance = 11.0;    // Floor 4 position in cm

// Include PID library
#include <PID_v1.h>

// PID tuning values
// Kp = proportional gain
// Ki = integral gain
// Kd = derivative gain
double iKp = 15.0;
double iKi = 5.0;
double iKd = 7.5;

// PID variables
double input_var = 0.0;      // Current error value
double output_var = 0.0;     // PWM output value
double reference_var = 0.0;  // Desired error (target)

// Create PID controller object
PID height_PID(&input_var,
               &output_var,
               &reference_var,
               iKp,
               iKi,
               iKd,
               REVERSE);

void setup() {

  // Start serial monitor
  Serial.begin(115200);

  // Motor pins setup
  pinMode(directionPin, OUTPUT);
  pinMode(pwmPin, OUTPUT);
  pinMode(brakePin, OUTPUT);

  // Ultrasonic sensor setup
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Release brake at startup
  digitalWrite(brakePin, LOW);

  // Turn PID controller on
  height_PID.SetMode(AUTOMATIC);

  // Set minimum and maximum PWM output
  // Prevents motor from running too slowly
  height_PID.SetOutputLimits(70, 255);
}

void loop() {

  // Move elevator/platform downward to floor 3
  moveToDistance(HIGH,
                 bottomDistance,
                 "Moving Down",
                 true);

  // Pause for 1 second
  delay(1000);

  // Move elevator/platform upward to floor 4
  moveToDistance(LOW,
                 topDistance,
                 "Moving Up",
                 false);

  // Pause for 1 second
  delay(1000);
}

void moveToDistance(int direction,
                    float targetDistance,
                    const char* message,
                    bool stopWhenGreater) {

  // Set motor direction
  digitalWrite(directionPin, direction);

  // Keep moving until target distance is reached
  while (true) {

    // Read current distance from sensor
    float distance = readDistance();

    /*
    // Optional debug messages
    Serial.print(message);
    Serial.print(" - Distance: ");
    Serial.println(distance, 1);
    */

    // Calculate distance error
    // Error = how far away we are from target
    input_var = abs(distance - targetDistance);

    // Goal is zero error
    reference_var = 0.0;

    // Run PID calculation
    // Output will adjust motor speed automatically
    height_PID.Compute();

    // Print PID values for debugging
    Serial.print(input_var);     // Error
    Serial.print("  ");

    Serial.print(output_var);    // Motor PWM speed
    Serial.print("  ");

    Serial.print(reference_var); // Target error
    Serial.print("\n");

    // Apply PID output to motor speed
    analogWrite(pwmPin, (int)output_var);

    // Stop when target distance is reached
    if ((stopWhenGreater && distance >= targetDistance) ||
        (!stopWhenGreater && distance <= targetDistance)) {

      stopMotor();
      break;
    }

    // Small delay for stable readings
    delay(30);
  }
}

// Function: Read ultrasonic distance
float readDistance() {

  // Clear trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send ultrasonic pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure echo return time
  long duration = pulseIn(echoPin, HIGH);

  // Convert time into distance (cm)
  float distance = duration * 0.0343 / 2.0;

  return distance;
}

// Function: Stop motor
void stopMotor() {

  // Stop motor power
  analogWrite(pwmPin, 0);

  // Apply brake briefly
  digitalWrite(brakePin, HIGH);

  delay(100);

  // Release brake
  digitalWrite(brakePin, LOW);
}