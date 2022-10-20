#include "EventLog.hpp"

#include <dtl.hpp>

#include <iomanip>
#include <sstream>

std::ostream &operator<<(std::ostream &os, const EventLog::event_t &value) {
  auto timestamp = value.first;
  auto content = value.second;
  os << "{" << std::setfill('0');
  if (timestamp >= 1'000'000) {
    os << (timestamp / 1'000'000) << "'" << std::setw(3);
    timestamp %= 1'000'000;
  }
  return os << (timestamp / 1000) << "'" << std::setw(3) << (timestamp % 1000) << ", \"" << content << "\"},";
}

std::string EventLog::diff(const EventLog &expected) const {
  dtl::Diff<event_t> diff(expected._events, _events);
  diff.compose();
  std::ostringstream message;
  diff.printSES(message);
  return message.str();
}
