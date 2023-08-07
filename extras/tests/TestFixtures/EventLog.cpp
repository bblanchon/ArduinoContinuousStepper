#include "EventLog.hpp"
#include "Clock.hpp"

#include <dtl.hpp>

#include <cstdarg>
#include <cstdio>
#include <iomanip>
#include <sstream>

EventLog theEventLog;

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
  dtl::Diff<event_t> diff(expected.events_, events_);
  diff.compose();
  std::ostringstream message;
  diff.printSES(message);
  return message.str();
}

void logEvent(const char *format, ...) {
  char buffer[256];
  std::va_list args;
  va_start(args, format);
  std::vsnprintf(buffer, sizeof(buffer), format, args);
  va_end(args);
  theEventLog.add(theClock.get(), buffer);
}