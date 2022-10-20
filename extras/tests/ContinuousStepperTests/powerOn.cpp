#include <Arduino.h>
#include <ContinuousStepper.h>

#include "helpers.hpp"

TEST_CASE("ContinuousStepper::powerOn()") {
  ContinuousStepper stepper;

  GIVEN("a stepper with enable pin configured") {
    stepper.begin(10, 11, 12);

    WHEN("powerOn() is called") {
      CLEAR_ARDUINO_LOG();
      stepper.powerOn();

      THEN("it should do nothing") {
        CHECK_ARDUINO_LOG({})
      }
    }

    AND_GIVEN("powerOff() was called") {
      stepper.powerOff();

      WHEN("powerOn() is called") {
        CLEAR_ARDUINO_LOG();
        stepper.powerOn();

        THEN("it should set enable pin to HIGH") {
          CHECK_ARDUINO_LOG({
              {0'000, "digitalWrite(12, HIGH)"},
          })
        }
      }
    }
  }

  GIVEN("a stepper with no enable pin") {
    stepper.begin(10, 11);

    AND_GIVEN("powerOff() was called") {
      stepper.powerOff();

      WHEN("powerOn() is called") {
        CLEAR_ARDUINO_LOG();
        stepper.powerOn();

        THEN("it should do nothing") {
          CHECK_ARDUINO_LOG({})
        }
      }

      AND_GIVEN("spin() was called") {
        stepper.spin(100);

        WHEN("powerOn() is called") {
          CLEAR_ARDUINO_LOG();
          stepper.powerOn();

          THEN("should smoothly restore the rotation") {
            loop_for(stepper, 100'000);

            REQUIRE(stepper.isSpinning() == true);
            CHECK(stepper.speed() == 100);
            CHECK_ARDUINO_LOG({
                {15'811, "digitalWrite(11, HIGH)"},
                {15'811, "digitalWrite(10, HIGH)"},
                {23'716, "digitalWrite(10, LOW)"},
                {31'621, "digitalWrite(11, HIGH)"},
                {31'621, "digitalWrite(10, HIGH)"},
                {37'945, "digitalWrite(10, LOW)"},
                {44'269, "digitalWrite(11, HIGH)"},
                {44'269, "digitalWrite(10, HIGH)"},
                {49'721, "digitalWrite(10, LOW)"},
                {55'173, "digitalWrite(11, HIGH)"},
                {55'173, "digitalWrite(10, HIGH)"},
                {60'173, "digitalWrite(10, LOW)"},
                {65'173, "digitalWrite(11, HIGH)"},
                {65'173, "digitalWrite(10, HIGH)"},
                {70'173, "digitalWrite(10, LOW)"},
                {75'173, "digitalWrite(11, HIGH)"},
                {75'173, "digitalWrite(10, HIGH)"},
                {80'173, "digitalWrite(10, LOW)"},
                {85'173, "digitalWrite(11, HIGH)"},
                {85'173, "digitalWrite(10, HIGH)"},
                {90'173, "digitalWrite(10, LOW)"},
                {95'173, "digitalWrite(11, HIGH)"},
                {95'173, "digitalWrite(10, HIGH)"},
            })
          }
        }
      }
    }
  }
}
