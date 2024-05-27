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
    if (status_ != OFF)
      return;

    TStepper::powerOn();
    updateSpeed();
  }

  void powerOff() {
    TStepper::powerOff();
    status_ = OFF;
    currentSpeed_ = 0;
    TTicker::setPeriod(0);
  }

  bool isPowered() const {
    return status_ != OFF;
  }

  void spin(float_t speed) {
    if (targetSpeed_ == speed)
      return;
    targetSpeed_ = speed;
    if (status_ != OFF)
      updateSpeed();
  }

  void stop() {
    targetSpeed_ = 0;
  }

  float_t acceleration() const {
    return acceleration_;
  }

  float_t speed() const {
    return currentSpeed_;
  }

  time_t period() const {
    return period_;
  }

  void setAcceleration(float_t acceleration) {
    acceleration_ = acceleration;
    minSpeedForAcceleration_ = sqrt(acceleration_);
  }

  bool isSpinning() const {
    return status_ == STEP || status_ == SKIP;
  }

protected:
  void tick() {
    if (status_ == STEP)
      TStepper::step();

    updateSpeedIfNeeded();
  }

  void updateSpeedIfNeeded() {
    if (targetSpeed_ != currentSpeed_)
      updateSpeed();
  }

private:
  void stepperInitialized() override {
    status_ = WAIT;
    TTicker::init();
  }

  void updateSpeed() {
    float_t speedIncrement = period_ ? acceleration_ * period_ / oneSecond : minSpeedForAcceleration_;

    if (targetSpeed_ > currentSpeed_) {
      currentSpeed_ = min(currentSpeed_ + speedIncrement, targetSpeed_);
    }

    if (targetSpeed_ < currentSpeed_) {
      currentSpeed_ = max(currentSpeed_ - speedIncrement, targetSpeed_);
    }

    if (abs(currentSpeed_) >= minSpeedForAcceleration_) {
      period_ = oneSecond / abs(currentSpeed_);
      status_ = STEP;
    } else if (abs(targetSpeed_) >= minSpeedForAcceleration_) {
      // crossing the zero on the speed graph
      period_ = oneSecond / minSpeedForAcceleration_;
      status_ = SKIP;
    } else if (targetSpeed_) {
      // target speed is not null but too low to allow a smooth acceleration
      period_ = oneSecond / abs(targetSpeed_);
      status_ = STEP;
    } else {
      // target speed is null
      status_ = WAIT;
      currentSpeed_ = 0;
      period_ = 0;
    }

    if (TStepper::needsDoubleSpeed())
      period_ /= 2;

    if (period_)
      TStepper::setDirection(currentSpeed_ < 0);

    TTicker::setPeriod(period_);
  }

  static const time_t oneSecond = 1e6;

  time_t period_ = 0;
  float_t targetSpeed_ = 0, currentSpeed_ = 0, acceleration_ = 1000, minSpeedForAcceleration_ = sqrt(1000);

  enum Status {
    OFF,
    WAIT,
    STEP,
    SKIP,
  };

  Status status_ = OFF;
};

} // namespace ArduinoContinuousStepper
