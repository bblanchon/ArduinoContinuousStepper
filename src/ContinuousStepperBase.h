#pragma once

#include <Arduino.h>
#include <assert.h>

#include <ContinuousStepper/StepperInterfaces.hpp>

namespace ArduinoContinuousStepper {

class ContinuousStepperBase {
public:
  ~ContinuousStepperBase() {
    delete _stepper;
  }

  void begin(pin_t stepPin, pin_t dirPin) {
    begin(new StepperDriver(stepPin, dirPin));
  }

  void begin(StepperInterface *stepper) {
    _stepper = stepper;
    _status = WAIT;
    initialize();
  }

  void setEnablePin(pin_t enablePin, bool activeLevel = HIGH) {
    pinMode(enablePin, OUTPUT);
    digitalWrite(enablePin, (_status == OFF) ^ activeLevel);
    _enablePin = enablePin;
    _enablePinActiveLevel = activeLevel;
  }

  void powerOn() {
    if (_status != OFF)
      return;

    if (_enablePin != NULL_PIN)
      digitalWrite(_enablePin, _enablePinActiveLevel);

    updateSpeed();
  }

  void powerOff() {
    if (_enablePin != NULL_PIN)
      digitalWrite(_enablePin, !_enablePinActiveLevel);

    _status = OFF;
    _currentSpeed = 0;
    setPeriod(0);
  }

  void spin(float_t speed) {
    _targetSpeed = speed;
    if (_status != OFF)
      updateSpeed();
  }

  void stop() {
    _targetSpeed = 0;
  }

  float_t speed() const {
    return _currentSpeed;
  }

  time_t period() const {
    return _period;
  }

  void setAcceleration(float_t acceleration) {
    _acceleration = acceleration;
    _minSpeedForAcceleration = sqrt(_acceleration);
  }

  bool isSpinning() const {
    return _status == STEP || _status == SKIP;
  }

protected:
  void tick() {
    if (_status == STEP)
      _stepper->step();

    updateSpeedIfNeeded();
  }

  void updateSpeedIfNeeded() {
    if (_targetSpeed != _currentSpeed)
      updateSpeed();
  }

private:
  void updateSpeed() {
    assert(_stepper != nullptr); // You must call begin() first

    float_t speedIncrement = _period ? _acceleration * _period / oneSecond : _minSpeedForAcceleration;

    if (_targetSpeed > _currentSpeed) {
      _currentSpeed = min(_currentSpeed + speedIncrement, _targetSpeed);
    }

    if (_targetSpeed < _currentSpeed) {
      _currentSpeed = max(_currentSpeed - speedIncrement, _targetSpeed);
    }

    if (abs(_currentSpeed) >= _minSpeedForAcceleration) {
      _period = oneSecond / abs(_currentSpeed);
      _status = STEP;
    } else if (abs(_targetSpeed) >= _minSpeedForAcceleration) {
      // crossing the zero on the speed graph
      _period = oneSecond / _minSpeedForAcceleration;
      _status = SKIP;
    } else if (_targetSpeed) {
      // target speed is not null but too low to allow a smooth acceleration
      _period = oneSecond / abs(_targetSpeed);
      _status = STEP;
    } else {
      // target speed is null
      _status = WAIT;
      _currentSpeed = 0;
      _period = 0;
    }

    if (_stepper->needsDoubleSpeed())
      _period /= 2;

    if (_period)
      _stepper->setDirection(_currentSpeed < 0);

    setPeriod(_period);
  }

  virtual void initialize(){};
  virtual void setPeriod(time_t period) = 0;

  static const pin_t NULL_PIN = 255;
  static const time_t oneSecond = 1e6;

  StepperInterface *_stepper = nullptr;
  pin_t _enablePin = NULL_PIN;
  time_t _period = 0;
  float_t _targetSpeed = 0, _currentSpeed = 0, _acceleration = 1000, _minSpeedForAcceleration = sqrt(1000);
  bool _enablePinActiveLevel = HIGH;

  enum Status {
    OFF,
    WAIT,
    STEP,
    SKIP,
  };

  Status _status = OFF;
};

} // namespace ArduinoContinuousStepper
