#include <Arduino.h>
#include <ContinuousStepper.h>

#include "helpers.hpp"

TEST_CASE("ContinuousStepper::setEnablePin()") {
  ContinuousStepper stepper;

  GIVEN("begin(10, 11) was called") {
    stepper.begin(10, 11);

    WHEN("setEnablePin(12) is called") {
      CLEAR_ARDUINO_LOG();
      stepper.setEnablePin(12);

      THEN("it should set pin 12 to HIGH") {
        CHECK_ARDUINO_LOG({
            {0, "pinMode(12, OUTPUT)"},
            {0, "digitalWrite(12, HIGH)"},
        })
      }
    }

    AND_GIVEN("powerOff() was called") {
      stepper.powerOff();

      WHEN("setEnablePin(12) is called") {
        CLEAR_ARDUINO_LOG();
        stepper.setEnablePin(12);

        THEN("it should set pin 12 to LOW") {
          CHECK_ARDUINO_LOG({
              {0, "pinMode(12, OUTPUT)"},
              {0, "digitalWrite(12, LOW)"},
          })
        }
      }
    }
  }
}