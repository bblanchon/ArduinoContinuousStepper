#pragma once

#include <set>
#include <vector>

class ClockWatcher {
public:
  virtual void timeChanged(unsigned long time) = 0;
};

class Clock {
public:
  void set(unsigned long time) {
    _time = time;
    std::vector<ClockWatcher *> watchers(_watchers.begin(), _watchers.end());
    for (auto watcher : watchers)
      watcher->timeChanged(_time);
  }

  unsigned long get() const {
    return _time;
  }

  void addWatcher(ClockWatcher *watcher) {
    _watchers.insert(watcher);
  }

  void removeWatcher(ClockWatcher *watcher) {
    _watchers.erase(watcher);
  }

private:
  unsigned long _time = 0;
  std::set<ClockWatcher *> _watchers;
};

extern Clock theClock;