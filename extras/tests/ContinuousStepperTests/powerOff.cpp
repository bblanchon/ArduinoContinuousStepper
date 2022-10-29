#include <Arduino.h>
#include <ContinuousStepper.h>

#include "helpers.hpp"

TEST_CASE("ContinuousStepper::powerOff()") {
  ContinuousStepper stepper;

  GIVEN("begin(10, 11, 12) was called") {
    stepper.begin(10, 11, 12);

    WHEN("powerOff() is called") {
      CLEAR_ARDUINO_LOG();
      stepper.powerOff();

      THEN("it should set pin 12 to LOW") {
        CHECK_ARDUINO_LOG({
            {0'000, "digitalWrite(12, LOW)"},
        });
      }
    }
  }

  GIVEN("begin(10, 11)") {
    stepper.begin(10, 11);

    WHEN("powerOff() is called") {
      CLEAR_ARDUINO_LOG();
      stepper.powerOff();

      THEN("it should do nothing") {
        CHECK_ARDUINO_LOG({});
      }
    }

    AND_GIVEN("spin(10) was called") {
      stepper.spin(10);
      loop_till(stepper, 100'000);
      REQUIRE(stepper.isSpinning() == true);
      REQUIRE(stepper.speed() == 10);

      WHEN("powerOff() is called") {
        CLEAR_ARDUINO_LOG();
        stepper.powerOff();

        THEN("it should abruptly stop the rotation") {
          loop_till(stepper, 100'000);
          CHECK(stepper.isSpinning() == false);
          CHECK(stepper.speed() == 0);
          CHECK_ARDUINO_LOG({});
        }
      }
    }

    AND_GIVEN("setEnablePin(12, HIGH) was called") {
      stepper.setEnablePin(12, HIGH);

      WHEN("powerOff() is called") {
        CLEAR_ARDUINO_LOG();
        stepper.powerOff();

        THEN("it should set pin 12 to LOW") {
          CHECK_ARDUINO_LOG({
              {0, "digitalWrite(12, LOW)"},
          });
        }
      }
    }

    AND_GIVEN("setEnablePin(12, LOW) was called") {
      stepper.setEnablePin(12, LOW);

      WHEN("powerOff() is called") {
        CLEAR_ARDUINO_LOG();
        stepper.powerOff();

        THEN("it should set pin 12 to HIGH") {
          CHECK_ARDUINO_LOG({
              {0, "digitalWrite(12, HIGH)"},
          });
        }
      }
    }
  }
}
