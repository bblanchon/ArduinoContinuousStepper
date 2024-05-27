ContinuousStepper: changelog
============================

3.1.0
-----

* Add `acceleration()` getter
* Add `isPowered()` (issue #17)

3.0.2
-----

* Respect `tone()`'s minimum frequency (issue #14)
* Ignore repeated calls to `spin()` with the same values (issue #14)

3.0.1
-----

* Fix ticker includes in examples (was `.h` instead of `.hpp`)

3.0.0
-----

* Remove deprecated 3-parameter `begin()` (use `setEnablePin()` instead)
* Add support for four-wire stepper motors
* `ContinuousStepper` is now a template class with two parameters, see the first table below.
* Add `ContinuousStepper.hpp` that keeps everything in the `ArduinoContinuousStepper` namespace.
* Some include files have been renamed, see the second table below.

| Before                                | After                                                       |
|---------------------------------------|-------------------------------------------------------------|
| `ContinuousStepper`                   | `ContinuousStepper<StepperDriver>`                          |
| `ContinuousStepper_AWF`               | `ContinuousStepper<StepperDriver, AwfTicker>`               |
| `ContinuousStepper_KhoiH<Teensy_PWM>` | `ContinuousStepper<StepperDriver, KhoihTicker<Teensy_PWM>>` |
| `ContinuousStepper_TeensyTimerTool`   | `ContinuousStepper<StepperDriver, TeensyTimerToolTicker>`   |
| `ContinuousStepper_Timer1`            | `ContinuousStepper<StepperDriver, TimerOneTicker>`          |
| `ContinuousStepper_Timer3`            | `ContinuousStepper<StepperDriver, TimerThreeTicker>`        |
| `ContinuousStepper_Tone`              | `ContinuousStepper<StepperDriver, ToneTicker>`              |

| Before                                | After                                                |
|---------------------------------------|------------------------------------------------------|
| `ContinuousStepper_AWF.h`             | `ContinuousStepper/Tickers/AnalogWriteFrequency.hpp` |
| `ContinuousStepper_KhoiH.h`           | `ContinuousStepper/Tickers/Khoih_PWM.hpp`            |
| `ContinuousStepper_TeensyTimerTool.h` | `ContinuousStepper/Tickers/TeensyTimerTool.hpp`      |
| `ContinuousStepper_Timer1.h`          | `ContinuousStepper/Tickers/TimerOne.hpp`             |
| `ContinuousStepper_Timer3.h`          | `ContinuousStepper/Tickers/TimerThree.hpp`           |
| `ContinuousStepper_Tone.h`            | `ContinuousStepper/Tickers/Tone.hpp`                 |

2.2.0
-----

* Fix occasional missed ticks on timer-based implementations
* Add `ContinuousStepper_Tone` which uses `tone()` instead of `digitalWrite()` for the step pin
* Add `ContinuousStepper_AWF` which uses `analogWriteFrequency()` on Teensy 3 and 4
* Add `ContinuousStepper_KhoiH` which uses Khoi Hoang's PWM libraries

2.1.0
-----

* Set *dir* pin level only when it changes (used to be on each tick)
* Fix acceleration bug after reversing the rotation (issue #7)
* Add `setEnablePin()` and allow inverting the pin's level (issue #6)
* Stop timer when `powerOff()` is called

2.0.0
-----

* Add `begin()` which now receives the pin numbers
* Add class `ContinuousStepper_TeensyTimerTool` to support the `TeensyTimerTool` library

1.2.0
-----

* Remove call to `delayMicroseconds()`
* Remove `setPulseWidth()`

1.1.1
-----

* Fix error when the `TimerOne` library is not available
* Add class `ContinuousStepper_Timer3` to support the `TimerThree` library

1.1.0
-----

* Add class `ContinuousStepper_Timer1` to support the `TimerOne` library
