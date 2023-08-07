#pragma once

#include <string>
#include <utility>
#include <vector>

class EventLog {
public:
  using timestamp_t = unsigned long;
  using event_t = std::pair<timestamp_t, std::string>;

  EventLog() {}
  EventLog(std::initializer_list<event_t> events) : events_(events) {}

  void add(timestamp_t t, std::string event) {
    events_.emplace_back(t, std::move(event));
  }

  void clear() {
    events_.clear();
  }

  std::string diff(const EventLog &) const;

  bool operator!=(const EventLog &other) const {
    return events_ != other.events_;
  }

private:
  std::vector<event_t> events_;
};

extern EventLog theEventLog;

void logEvent(const char *format, ...);