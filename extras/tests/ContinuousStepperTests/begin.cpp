#include <ContinuousStepper.h>
#include <TestFixtures.hpp>

TEST_CASE("ContinuousStepper::begin()") {
  ContinuousStepper stepper;

  WHEN("begin(10, 11) is called") {
    stepper.begin(10, 11);

    THEN("it should configure both pins as OUTPUT") {
      CHECK_ARDUINO_LOG({
          {0'000, "pinMode(10, OUTPUT)"},
          {0'000, "pinMode(11, OUTPUT)"},
      });
    }
  }

  WHEN("begin(2, 3, 4, 5) is called") {
    stepper.begin(2, 3, 4, 5);

    THEN("it should configure the four pins as OUTPUT") {
      CHECK_ARDUINO_LOG({
          {0'000, "pinMode(2, OUTPUT)"},
          {0'000, "pinMode(3, OUTPUT)"},
          {0'000, "pinMode(4, OUTPUT)"},
          {0'000, "pinMode(5, OUTPUT)"},
      });
    }
  }
}
