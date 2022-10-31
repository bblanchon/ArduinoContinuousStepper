ContinuousStepper: changelog
============================

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
