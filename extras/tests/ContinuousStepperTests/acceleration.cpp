#include <ContinuousStepper.h>
#include <TestFixtures.hpp>

TEST_CASE("ContinuousStepper<StepperDriver>::acceleration()") {
  ContinuousStepper<StepperDriver> stepper;

  GIVEN("setAcceleration() was NOT called") {
    WHEN("acceleration() is called") {
      THEN("it should return the default acceleration") {
        CHECK(stepper.acceleration() == 1000);
      }
    }
  }

  GIVEN("setAcceleration(10) was called") {
    stepper.setAcceleration(10);

    WHEN("acceleration() is called") {
      THEN("it should return 10") {
        CHECK(stepper.acceleration() == 10);
      }
    }
  }
}
