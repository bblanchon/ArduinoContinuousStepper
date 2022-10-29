Arduino ContinuousStepper Library
=================================

An Arduino library to spin stepper motors in continuous motions.

Contrary to other stepper libraries, this one doesn't provide any function to move the shaft at a specific **angle**. Instead, it provides one function to spin the shaft at a specific **speed**. It smoothly accelerates and decelerates when the speed changes.

### Features

* Supports stepper drivers with *step* and *dir* pins
* Optionally supports the *enable* pin
* Optionally runs with [TimerOne](https://github.com/PaulStoffregen/TimerOne), [TimerThree](https://github.com/PaulStoffregen/TimerThree) or [TeensyTimerTool](https://github.com/luni64/TeensyTimerTool)
* Accelerates and decelerates smoothly
* Negative speed rotates backward
* Tiny footprint (about 150 lines of code)
* Uses neither `delay()` nor `delayMicroseconds()`

### Suggested applications

* Tape recorders
* Conveyors
* Wheels

### How to use the ContinousStepper library?

```c++
ContinuousStepper stepper;

void setup() {
  stepper.begin(stepPin, dirPin)
  stepper.spin(200); // rotate at 200 steps per seconds
}

void loop() {
  stepper.loop(); // this function must be called as frequently as possible
}
```

Alternatively, you can install the [TimerOne](https://github.com/PaulStoffregen/TimerOne) to have the `loop()` function called in the timer interrupt handler:

```c++
ContinuousStepper_Timer1 stepper;

void setup() {
  stepper.begin(stepPin, dirPin);
  stepper.spin(200);
}

void loop() {
  // no need to call stepper.loop()
  // it's called by the timer interrupt handler
}
```

### API

```c++
class ContinuousStepper {
public:
  // Initialize the class and attaches to the specified pins.
  void begin(pin_t stepPin, pin_t dirPin);

  // Configures the "enable" pin.
  // You can pass LOW as the second argument to invert the logic.
  // The pin is set to its active level unless powerOff() was called.
  void setEnablePin(pin_t pinNumber, bool activeLevel = HIGH);

  // Updates the status of the step and dir pins.
  // You must call this function as frequently as possible.
  void loop();

  // Sets the enable pin's level to its active level and restores the current speed.
  void powerOn();

  // Sets the enable pin's level to its inactive level.
  void powerOff();

  // Changes target speed.
  // The shaft will smoothly accelerate or decelerate to reach the
  // target speed.
  void spin(float_t speed);

  // Sets targets speed to 0.
  // The shaft will smoothly decelerate.
  // Call isSpinning() to know when the motion is complete.
  void stop();

  // Returns the current speed.
  // During accelerations and deccelerations, this value differs from the
  // target speed configured with spin().
  float_t speed() const;

  // Sets the acceleration in steps/s².
  void setAcceleration(float_t acceleration);

  // Tells wether the shaft is currently spinning.
  bool isSpinning() const;
};
```

`ContinuousStepper_Timer1` is identical, except it can only have one instance and it doesn't have the `loop()` function.

### Why use this library instead of AccelStepper

AccelStepper is an excellent library when you want to move a stepper motor shaft at a specific angle (for example, in a 3D printer), but it doesn't support applications that need continuous rotations.

AccelStepper provides a `runSpeed()` function for continuous motion, but it doesn't accelerate smoothly.

You could repeatedly call `move()`, but after a while, the 32-bit integer that stores the target position will overflow, causing the motor to reverse its rotation.

Moreover, even if you can control the speed with `setMaxSpeed()`, you'll see that it accelerates smoothly but decelerates abruptly.


### How to migrate from AccelStepper to ContinuousStepper

| AccelStepper         | ContinuousStepper   |
|:---------------------|:--------------------|
| `disableOutputs()`   | `powerOff()`        |
| `enableOutputs()`    | `powerOn()`         |
| `isRunning()`        | `isSpinning()`      |
| `move()`             | `spin()`            |
| `moveTo()`           | `spin()`            |
| `run()`              | `loop()`            |
| `setAcceleration()`  | `setAcceleration()` |
| `setEnablePin()`     | `setEnablePin()`    |
| `setMaxSpeed()`      | `spin()`            |
| `setMinPulseWidth()` | Automatic           |
| `stop()`             | `stop()`            |