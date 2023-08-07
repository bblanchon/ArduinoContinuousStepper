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
    time_ = time;
    std::vector<ClockWatcher *> watchers(watchers_.begin(), watchers_.end());
    for (auto watcher : watchers)
      watcher->timeChanged(time_);
  }

  unsigned long get() const {
    return time_;
  }

  void addWatcher(ClockWatcher *watcher) {
    watchers_.insert(watcher);
  }

  void removeWatcher(ClockWatcher *watcher) {
    watchers_.erase(watcher);
  }

private:
  unsigned long time_ = 0;
  std::set<ClockWatcher *> watchers_;
};

extern Clock theClock;