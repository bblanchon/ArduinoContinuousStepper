Arduino ContinuousStepper Library
=================================

An Arduino library to spin stepper motors in continuous motions.

Contrary to other stepper libraries, this one doesn't provide any function to move the shaft at a specific **angle**. Instead, it provides one function to spin the shaft at a specific **speed**. It smoothly accelerates and decelerates when the speed changes.

### Features

* Supports multiple stepper types:
  - stepper drivers with *step* and *dir* pins (and optionally *enable* pin)
  - four-wire stepper motors
* Optionally runs with [TimerOne](https://github.com/PaulStoffregen/TimerOne), [TimerThree](https://github.com/PaulStoffregen/TimerThree) or [TeensyTimerTool](https://github.com/luni64/TeensyTimerTool)
* Optionally uses `tone()` instead of `digitalWrite()` for the *step* pin
* Optionally uses PWM with `analogWriteFrequency()` on Teensy 3 and 4
* Optionally uses [Khoi Hoang](https://github.com/khoih-prog)'s PWM libraries (RP2040_PWM, SAMD_PWM, AVR_PWM, STM32_PWM, Teensy_PWM...)
* Accelerates and decelerates smoothly
* Negative speed rotates backward
* Uses neither `delay()` nor `delayMicroseconds()`

### Suggested applications

* Tape recorders
* Conveyors
* Wheels

### How to use the ContinousStepper library?

#### Basic example with a stepper driver

```c++
#include <ContinuousStepper.h>

ContinuousStepper<StepperDriver> stepper;

void setup() {
  stepper.begin(stepPin, dirPin)
  stepper.spin(200); // rotate at 200 steps per seconds
}

void loop() {
  stepper.loop(); // this function must be called as frequently as possible
}
```

#### Basic example with a four-wire stepper motor

```c++
#include <ContinuousStepper.h>

ContinuousStepper<FourWireStepper> stepper;

void setup() {
  stepper.begin(pin1, pin2, pin3, pin4);
  stepper.spin(200); // rotate at 200 steps per seconds
}

void loop() {
  stepper.loop(); // this function must be called as frequently as possible
}
```

#### Using the Tone library for the step pin

In the basic example above, the level of the *step* pin is changed with `digitalWrite()`. We can offload this task to the `tone()` function, which uses a timer to generate a square wave.

```c++
#include <ContinuousStepper.h>
#include <ContinuousStepper/Tickers/Tone.hpp>

ContinuousStepper<StepperDriver, ToneTicker> stepper;

void setup() {
  stepper.begin(stepPin, dirPin);

  stepper.spin(200);
}

void loop() {
  stepper.loop();
}
```

Of course, this only work for `StepperDriver`, don't try to use it with `FourWireStepper`. The same remark applies to `AwfTicker` and `KhoiTicker`.

#### Using the TimerOne library to call `loop()` automatically

Alternatively, you can install the [TimerOne](https://github.com/PaulStoffregen/TimerOne) to have the `loop()` function called in the timer interrupt handler:

```c++
#include <ContinuousStepper.h>
#include <ContinuousStepper/Tickers/TimerOne.hpp>

ContinuousStepper<FourWireStepper, TimerOneTicker> stepper;

void setup() {
  stepper.begin(pin1, pin2, pin3, pin4);

  stepper.spin(200);
}

void loop() {
  // no need to call stepper.loop()
}
```

You can do this for either `StepperDriver` or `FourWireStepper`.

CAUTION: this example only proved to work correctly on Teensy 3.1.

### API

Here is the general overview of the `ContinuousStepper` class:

```c++
template <class TStepper, class TTicker = LoopTicker>
class ContinuousStepper {
public:
  // Initialize the class and attaches to the specified pins.
  void begin(/* depends, see below */);

  // Updates the status of the step and dir pins.
  // You must call this function as frequently as possible.
  void loop();

  // Turn the power on and restores the current speed.
  // See StepperDriver and FourWireStepper below for details.
  void powerOn();

  // Turn the power off.
  // See StepperDriver and FourWireStepper below for details.
  void powerOff();

  // Tells whether the power is on.
  bool isPowered() const;

  // Sets the target speed.
  // The shaft will smoothly accelerate or decelerate to reach the
  // target speed.
  void spin(float_t speed);

  // Sets the target speed to 0.
  // The shaft will smoothly decelerate.
  // Call isSpinning() to know when the motion is complete.
  void stop();

  // Gets the acceleration in steps/s².
  float_t acceleration() const;

  // Returns the current speed.
  // During accelerations and decelerations, this value differs from the
  // target speed configured with spin().
  float_t speed() const;

  // Sets the acceleration in steps/s².
  void setAcceleration(float_t acceleration);

  // Tells whether the shaft is currently spinning.
  bool isSpinning() const;
};
```

In addition, `ContinuousStepper` inherits some functions the `TStepper` class:

```c++
class StepperDriver {
  // Configures the stepper with the specified pins.
  void begin(uint8_t stepPin, uint8_t dirPin);

  // Configures the "enable" pin.
  // You can pass LOW as the second argument to invert the logic.
  // The pin is set to its active level unless powerOff() was called.
  void setEnablePin(uint8_t pin, bool activeLevel = HIGH);

  // Sets the enable pin's level to its active level and restores the current speed.
  void powerOn();

  // Sets the enable pin's level to its inactive level.
  void powerOff();
}

class FourWireStepper {
  // Configures the stepper with the specified pins.
  void begin(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4);

  // Restore current in the coils and restores the current speed.
  void powerOn();

  // Set the four pins to LOW, hereby stopping all current in the coils.
  void powerOff();
}
```


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