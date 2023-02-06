#include <ContinuousStepper.h>
#include <TestFixtures.hpp>

TEST_CASE("ContinuousStepper::begin()") {

  GIVEN("an uninitialized stepper") {
    ContinuousStepper stepper;

    WHEN("begin() is called with 2 arguments") {
      stepper.begin(10, 11);

      THEN("it should should configure both pins as OUTPUT") {
        CHECK_ARDUINO_LOG({
            {0'000, "pinMode(10, OUTPUT)"},
            {0'000, "pinMode(11, OUTPUT)"},
        });
      }
    }

    WHEN("begin() is called with 2 arguments") {
      stepper.begin(10, 11, 12);

      THEN("it should configure pins as OUTPUT and set power pin "
           "to HIGH") {
        CHECK_ARDUINO_LOG({
            {0'000, "pinMode(10, OUTPUT)"},
            {0'000, "pinMode(11, OUTPUT)"},
            {0'000, "pinMode(12, OUTPUT)"},
            {0'000, "digitalWrite(12, HIGH)"},
        });
      }
    }
  }
}
