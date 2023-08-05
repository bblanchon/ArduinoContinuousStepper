#pragma once

class Clock {
public:
  void set(unsigned long time) {
    _time = time;
  }

  unsigned long get() const {
    return _time;
  }

private:
  unsigned long _time = 0;
};

extern Clock theClock;