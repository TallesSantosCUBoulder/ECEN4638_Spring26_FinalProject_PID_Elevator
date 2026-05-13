# PID Elevator

## Introduction

This project is a small elevator controlled by an Arduino microcontroller. It uses a PID (Proportional-Integral-Derivative) controller to move a platform between two floor positions. An ultrasonic sensor constantly measures the position of the platform, and the Arduino uses that information to adjust the motor speed. The goal was to build a working closed-loop control system and observe how PID behaves in a real physical system.

<img width="250" alt="Elevator_Complete" src="https://github.com/user-attachments/assets/5b07ed7e-ed50-40ff-8884-2a18916ef578" />

_Figure: Image of fully assembled elevator_

## Background

### Control System

A control system is a system designed to regulate the behavior of a device or process by comparing a desired input to an actual output and making corrections as needed. These systems can be open-loop or closed-loop, but both share the same fundamental components: the input, the controller, the actuator, the process, and the output. The input defines the desired goal, such as a target position. The controller processes the input and outputs a signal that tells the actuator how strongly to respond in order to reach the desired state. The actuator is the physical device that responds to that signal and acts on the system. The process is the physical system or component being controlled. The defining feature of a closed-loop system is the addition of a sensor that continuously measures the actual output and feeds it back to the controller, allowing the system to detect and correct any deviation from the desired value. This feedback mechanism is what makes closed-loop systems significantly more accurate and consistent than open-loop systems.

The elevator operates as a closed-loop control system. The target floor position serves as the input. The Arduino acts as the controller, computing the error between the target position and the measured position of the carriage. Based on that error, it outputs a PWM signal to the motor shield, which drives the DC motor. The motor reels in or releases the cable to move the carriage vertically through the shaft. The HC-SR04 ultrasonic sensor mounted at the top of the shaft continuously measures the distance to the carriage and sends that value back to the Arduino. The Arduino compares this measured position to the target and updates its output accordingly. This feedback loop runs continuously until the carriage reaches the target floor.

<img width="500" alt="Control_System_Diagram" src="https://github.com/user-attachments/assets/fa9e17ff-3ea9-4271-a2a0-b52aa2f4c46f" />

_Figure: Control system diagram_

### PID Controller

<img width="250" alt="Output_Response" src="https://github.com/user-attachments/assets/a0a13529-34b5-46b6-80a5-45b8953967ae" />

*Figure: The output response of a PID-controlled system.*

A PID controller is a widely used closed-loop controller that computes its output using three terms: proportional, integral, and derivative. Each term targets a different characteristic of the system response, as shown in Figure 2. The rise time (T<sub>r</sub>) describes how quickly the output reaches the desired level. Overshoot is how far past the target the output travels before settling. The peak time (T<sub>p</sub>) is how long it takes for that overshoot to decay to within approximately 1% of the target value. The steady-state error (e<sub>ss</sub>) is the remaining offset between the settled output and the desired value.

The proportional term creates an output directly proportional to the current error. A larger error produces a stronger response, which reduces rise time but tends to increase overshoot. The integral term accumulates error over time and applies an output based on its total magnitude and duration, which eliminates steady-state error but can contribute to additional overshoot. The derivative term responds to the rate of change of the error, applying a damping effect that reduces overshoot and helps stabilize the response, though it can amplify sensor noise if not carefully tuned. The combination of these three terms gives the controller the ability to react quickly, eliminate long-term error, and converge smoothly to the desired value. The complete PID control law is expressed in both the time domain and Laplace domain in Eq. 1 and Eq. 2. In this project, the Arduino executes the PID algorithm every loop cycle, using the distance error from the ultrasonic sensor to compute the appropriate PWM output and drive the motor, with the gains Kp, Ki, and Kd tuned to produce smooth and accurate carriage movement between floors.

## Methodology

### 3D Printing

Four parts were designed in Onshape, which is a free online CAD software, and 3D printed for this project. The first two parts are the DC motor housing top and bottom, which fit together to enclose and mount the DC motor securely to the frame. The third part is a spoke wheel, which attaches to the motor shaft and helps drive the elevator cable. The fourth part is a cable arch guide, which properly redirects the cable over the top of the elevator carriage so it moves within the elevator shaft without hitting the sides. All parts were printed in PLA with a 15% infill and oriented on the print bed so that the print lines run in the direction that gives each part the most strength.

<img width="250" alt="DC_Motor_Housing" src="https://github.com/user-attachments/assets/81e5d044-89a3-47b2-ab60-d1d153f5c730" />

_Figure: Image of CAD part 1 & 2_

<img width="250" alt="Spoke_Wheel" src="https://github.com/user-attachments/assets/d21c991b-a114-443d-9eb4-82cd043eea37" />

_Figure: Image of CAD part 3_

<img width="250" alt="Cable_Arch_Guide" src="https://github.com/user-attachments/assets/ddc9678f-0ee9-40a4-a2a1-88ec74bd7f63" />

_Figure: Image of CAD part 4_

### Circuit Design

The Arduino connects to a motor shield that controls both the speed and direction of the DC motor. The motor shield is controlled using three Arduino pins: pin 12 sets the motor direction, pin 3 sends the PWM signal to control motor speed, and pin 9 controls the brake to stop the motor when the carriage reaches the desired floor. The HC-SR04 ultrasonic sensor is used to continuously measure the height of the carriage and is wired to GND, 5V, trigger on pin 6 and echo is on pin 7. The motor runs on its own separate power supply to prevent voltage drops from affecting the Arduino and causing unreliable behavior.

<img width="250" alt="Circuit_Schematic" src="https://github.com/user-attachments/assets/e72b4f9b-c4c1-4157-ac3e-3e9ecb43ef92" />

_Figure: Circuit schematic_

## Hardware

### Materials List

* Arduino Uno
* DC motor
* Motor shield
* HC-SR04 ultrasonic sensor
* 3D printed parts: DC motor housing top and bottom, spoke wheel, cable arch guide
* Elevator shaft built by a previous class (three 2x4 wooden boards, plexiglass front panel, MDF top and base panel)
* Elevator carriage built by a previous class (laser cut birch plywood box)
* Cable or string
* Power supply
* Jumper wires

### Elevator Assembly

#### Construction Process

The elevator shaft was built by a previous class using three 2x4s, a plexiglass front panel, and an MDF top and base panel. The elevator carriage is a small box made from laser cut birch plywood and was also built by the previous class. The Arduino and motor shield were mounted to the top panel, and the ultrasonic sensor was mounted at the top center inside the shaft, pointing downward to measure the position of the elevator carriage. The top panel has a slot cut into it so that the cable arch guide can sit over it. This arch was then hot glued in place to keep it secure. The cable runs from the spoke wheel on the motor shaft, through the cable arch guide, and down into the shaft where it connects to the carriage, keeping it centered so it moves cleanly without hitting the sides.

<img width="250" alt="Elevator_Top" src="https://github.com/user-attachments/assets/cc382a65-2275-4e8e-b4b1-b2e1eb833d1d" />

_Figure: Image of top view of the elevator_

<img width="250" alt="Elevator_Front" src="https://github.com/user-attachments/assets/23bdce91-727c-450b-9d0a-7c401717db36" />

_Figure: Image of the front view of the elevator_

## Software

### System Overview

This project uses an Arduino script and a MATLAB script that work together to read the sensor, calculate the PID output, control the motor, and display the data. The Arduino code handles the real-time control while the MATLAB script runs on a laptop and displays the incoming data as a live graph. The Arduino keeps moving the elevator between the bottom floor (~38 cm) and the top floor (~11 cm), waiting one second at each stop. The MATLAB script allows the user to observe the system in real time, which makes it easier to spot any problems with the controller.

<img width="250" alt="System_Flowchart" src="https://github.com/user-attachments/assets/6dd110ef-5fa4-4fc0-a05e-64c02bae32c9" />

_Figure: Image of system flowchart_

### System Setup & Execution

To get the system running, first upload the Arduino sketch to the board using the Arduino IDE with the correct port and baud rate selected. Once the Arduino is running and the elevator is moving, open MATLAB and update the port name variable in the script to match the Arduino's serial port on your computer. Close the Arduino Serial Monitor, then run the MATLAB script, and it will begin reading data and displaying live graphs of the error and PWM output. If the elevator is overshooting, oscillating, or responding too slowly, the PID gains Kp, Ki, and Kd can be adjusted in the Arduino code and re-uploaded to fix the response as needed.

### Arduino Code Explanation

The Arduino code uses the PID_v1 library to implement the PID controller that adjusts motor speed based on how far the carriage is from its target position. During each loop cycle, the ultrasonic sensor is read, the distance error is calculated, and that error is passed into the PID library, which computes the appropriate PWM output. That PWM value is then written to the motor shield to set the motor speed, and this process repeats until the carriage reaches the target floor. The PWM output is limited between 70 and 255 so the motor always has enough power to move and never stalls at low speeds. When the target is reached, the motor is stopped and the brake is briefly activated to prevent the carriage from moving.

### MATLAB Code Explanation

The Arduino sends three values to MATLAB over a serial connection at 115200 baud during each control cycle: the current distance error, PWM motor output, and reference target value. The MATLAB script reads the incoming serial data one character at a time, builds complete lines, extracts the three numeric values, and stores them efficiently in a matrix. Every 100 samples, MATLAB updates two live subplots showing the position error and motor PWM output over time, helping evaluate PID controller performance and tune the gains.

## Results

The elevator successfully moves between the two floors smoothly. The ultrasonic sensor provided consistent distance readings up to 50 cm, and the manually tuned PID controller responded well by reducing motor speed as the carriage approached each target.

The MATLAB plots clearly showed the error converging toward zero on each trip and the PWM output dropping off as the carriage slowed down near the destination. Some tuning of the PID gains was needed early on to reduce overshoot and achieve a clean stop at each floor without bouncing. Once the gains were dialed in, the system ran reliably with no major issues.

<img width="250" alt="Elevator_Movement" src="https://github.com/user-attachments/assets/ebf5a3b3-430d-4854-8f4c-a6b430b6a455" />

_Figure: GIF of PID controlled elevator_

<img width="500" alt="PID_1 0_1 0_1 0" src="https://github.com/user-attachments/assets/6bb9b1aa-fcfd-4412-aea5-69c5465c0ed9" />

_Figure: Image of MATLAB PID data set 1_

<img width="500" alt="PID_1 0_5 0_10 0" src="https://github.com/user-attachments/assets/e0ba15ed-1fd3-43d2-b786-371adedf28f4" />

_Figure: Image of MATLAB PID data set 2_

<img width="500" alt="PID_1 0_10 0_5 0" src="https://github.com/user-attachments/assets/8923a07e-9fc0-4c71-ae24-f1b98d4cd4c3" />

_Figure: Image of MATLAB PID data set 3_

<img width="500" alt="PID_15 0_5 0_7 5" src="https://github.com/user-attachments/assets/632b3842-33ff-487e-8d79-88f8e6f36d65" />

_Figure: Image of MATLAB PID data set 4_

## Conclusion

This project successfully demonstrated how a PID controller can be used to accurately control the position of a physical system like an elevator. The combination of an ultrasonic sensor for feedback and a DC motor for actuation gave the Arduino everything it needed to make real-time adjustments and consistently reach the correct floors. The MATLAB data monitoring script was useful for understanding what the controller was doing and helped the user make informed decisions about how to tune the gains. Overall, the project is a good example of how PID control, sensors, and real-time monitoring can be combined into a complete closed-loop control system.

## Equations

```math
controller(t) = u(t) = K_p e(t) + K_i\int e(t)\,\mathrm{d}t + K_d\frac{\mathrm{d}e(t)}{\mathrm{d}t}
```

<p align="right"><em>Equation 1: PID Control Law (Time Domain)</em></p>

```math
Controller(s) = U(s) = K_p + \frac{K_i}{s} + K_ds
```

<p align="right"><em>Equation 2: PID Control Law (Laplace Domain)</em></p>

## References

<table>
<tr>
<td valign="top">[1]</td>
<td>
T. Santos, <i>PingPongLevitator</i>, GitHub repository.<br>
Available: https://github.com/TallesSantosCUBoulder/PingPongLevitator
</td>
</tr>
</table>



