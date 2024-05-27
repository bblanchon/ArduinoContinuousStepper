#include <ContinuousStepper.h>
#include <TestFixtures.hpp>

TEST_CASE("ContinuousStepper<StepperDriver>::isPowered()") {
  ContinuousStepper<StepperDriver> stepper;

  GIVEN("begin(10, 11) was called") {
    stepper.begin(10, 11);

    THEN("isPowered() should return true") {
      CHECK(stepper.isPowered() == true);
    }

    AND_GIVEN("powerOff() is called") {
      stepper.powerOff();

      THEN("isPowered() should return false") {
        CHECK(stepper.isPowered() == false);
      }

      AND_GIVEN("powerOn() is called") {
        stepper.powerOn();

        THEN("isPowered() should return true") {
          CHECK(stepper.isPowered() == true);
        }
      }
    }
  }
}

TEST_CASE("ContinuousStepper<FourWireStepper>::isPowered()") {
  ContinuousStepper<FourWireStepper> stepper;

  GIVEN("begin(2, 3, 4, 5) was called") {
    stepper.begin(2, 3, 4, 5);

    THEN("isPowered() should return true") {
      CHECK(stepper.isPowered() == true);
    }

    AND_GIVEN("powerOff() is called") {
      stepper.powerOff();

      THEN("isPowered() should return false") {
        CHECK(stepper.isPowered() == false);
      }

      AND_GIVEN("powerOn() is called") {
        stepper.powerOn();

        THEN("isPowered() should return true") {
          CHECK(stepper.isPowered() == true);
        }
      }
    }
  }
}
