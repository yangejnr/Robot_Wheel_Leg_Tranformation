# Wheel–Leg Transformation Robot Prototype

An embedded robotics experiment exploring a mobile mechanism that combines conventional wheel-driven movement with servo-actuated leg transformation.

## Objective

The prototype investigates a simple hybrid-mobility concept: use a DC motor for directional movement while a servo changes the position of a leg mechanism during a defined part of the motion cycle. This provides a small-scale platform for testing the coordination required by robots that transition between rolling and articulated configurations.

## Current Control Sequence

The ESP32 firmware currently demonstrates a deterministic bench sequence:

```text
Forward motion
     │
     ▼
Motor stop
     │
     ▼
Backward motion + servo movement
     │
     ▼
Servo returns to default position
     │
     ▼
Cycle repeats
```

The current test program drives forward for 30 seconds, then backward for 30 seconds while briefly moving the transformation servo to 90 degrees before returning it to its default position.

## Hardware Interfaces

- ESP32 controller
- DC motor and H-bridge-style direction/speed interface
- servo actuator
- red power LED
- green forward/status LED
- white reverse/status LED

## Technology

- ESP32
- C++ / Arduino framework
- PlatformIO
- ESP32Servo
- PWM motor control

## Repository Structure

The active PlatformIO project is located in `robot_wheel/`.

## Status

**Early robotics prototype / motion-sequencing experiment.** The current firmware validates basic motor/servo coordination. Autonomous terrain sensing, closed-loop locomotion and a mechanically validated wheel-to-leg transformation remain future work.

## Author

**Yange Henry Terzugwe**  
Robotics & Embedded Systems
