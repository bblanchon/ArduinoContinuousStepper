#include <Arduino.h>
#include <ContinuousStepper.h>

#include "helpers.hpp"

TEST_CASE("ContinuousStepper::powerOff()") {
  ContinuousStepper stepper;

  GIVEN("a stepper with enable pin configured") {
    stepper.begin(10, 11, 12);
    CLEAR_ARDUINO_LOG();

    WHEN("powerOff() is called") {
      stepper.powerOff();

      THEN("it should set enable pin to LOW") {
        CHECK_ARDUINO_LOG({
            {0'000, "digitalWrite(12, LOW)"},
        });
      }
    }
  }

  GIVEN("a stepper with no enable pin") {
    stepper.begin(10, 11);
    CLEAR_ARDUINO_LOG();

    WHEN("powerOff() is called") {
      stepper.powerOff();

      THEN("it should do nothing") {
        CHECK_ARDUINO_LOG({});
      }
    }
  }

  GIVEN("a spinning stepper") {
    stepper.begin(10, 11);
    stepper.spin(10);
    loop_till(stepper, 100'000);
    REQUIRE(stepper.isSpinning() == true);
    REQUIRE(stepper.speed() == 10);

    WHEN("powerOff() is called") {
      stepper.powerOff();

      THEN("it should abruptly stop the rotation") {
        CHECK(stepper.isSpinning() == false);
        CHECK(stepper.speed() == 0);
      }
    }
  }
}
