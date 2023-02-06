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

  template <typename... Args>
  void add(timestamp_t t, const char *format, Args... args) {
    char buffer[256];
    std::snprintf(buffer, sizeof(buffer), format, args...);
    _events.emplace_back(t, buffer);
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
