#pragma once

#include <string>
#include <utility>
#include <vector>

class EventLog {
public:
  using timestamp_t = unsigned long;
  using event_t = std::pair<timestamp_t, std::string>;

  EventLog() {}
  EventLog(std::initializer_list<event_t> events) : _events(events) {}

  void add(timestamp_t t, std::string event) {
    _events.emplace_back(t, std::move(event));
  }

  void clear() {
    _events.clear();
  }

  std::string diff(const EventLog &) const;

  bool operator!=(const EventLog &other) const {
    return _events != other._events;
  }

private:
  std::vector<event_t> _events;
};

extern EventLog theEventLog;

void logEvent(const char *format, ...);