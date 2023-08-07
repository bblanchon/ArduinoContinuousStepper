#pragma once

#include <ContinuousStepper/OutputPin.hpp>

namespace ArduinoContinuousStepper {

class TickListener {
public:
  virtual void tick() = 0;
};

class StepperListener {
public:
  virtual void stepperInitialized() = 0;
};

template <class TStepper, class TTicker>
class ContinuousStepperImpl : public TTicker, TickListener, public TStepper, StepperListener {
public:
  using float_t = double;
  using time_t = unsigned long;

  template <typename... Args>
  ContinuousStepperImpl(Args &&...args) : TTicker(this, args...), TStepper(this) {}

  void powerOn() {
    if (_status != OFF)
      return;

    TStepper::powerOn();
    updateSpeed();
  }

  void powerOff() {
    TStepper::powerOff();
    _status = OFF;
    _currentSpeed = 0;
    TTicker::setPeriod(0);
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
      TStepper::step();

    updateSpeedIfNeeded();
  }

  void updateSpeedIfNeeded() {
    if (_targetSpeed != _currentSpeed)
      updateSpeed();
  }

private:
  void stepperInitialized() override {
    _status = WAIT;
    TTicker::init();
  }

  void updateSpeed() {
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

    if (TStepper::needsDoubleSpeed())
      _period /= 2;

    if (_period)
      TStepper::setDirection(_currentSpeed < 0);

    TTicker::setPeriod(_period);
  }

  static const time_t oneSecond = 1e6;

  time_t _period = 0;
  float_t _targetSpeed = 0, _currentSpeed = 0, _acceleration = 1000, _minSpeedForAcceleration = sqrt(1000);

  enum Status {
    OFF,
    WAIT,
    STEP,
    SKIP,
  };

  Status _status = OFF;
};

} // namespace ArduinoContinuousStepper
