#include "Clock.hpp"
#include "EventLog.hpp"

#include <catch2/catch_session.hpp>
#include <catch2/reporters/catch_reporter_event_listener.hpp>
#include <catch2/reporters/catch_reporter_registrars.hpp>

namespace {
class TestRunListener : public Catch::EventListenerBase {
public:
  using Catch::EventListenerBase::EventListenerBase;

  // void sectionStarting(Catch::SectionInfo const &sectionInfo) override {
  //   theEventLog.clear();
  //   theClock.set(0);
  // }

  void sectionEnded(Catch::SectionStats const &sectionStats) override {
    theEventLog.clear();
    theClock.set(0);
  }
};
} // namespace

CATCH_REGISTER_LISTENER(TestRunListener)

int main(int argc, char *argv[]) {
  return Catch::Session().run(argc, argv);
}