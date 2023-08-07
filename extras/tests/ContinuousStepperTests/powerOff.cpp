#include <ContinuousStepper.h>
#include <TestFixtures.hpp>

TEST_CASE("ContinuousStepper<StepperDriver>::powerOff()") {
  ContinuousStepper<StepperDriver> stepper;

  GIVEN("begin(10, 11) was called") {
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

TEST_CASE("ContinuousStepper<FourWireStepper>::powerOff()") {
  ContinuousStepper<FourWireStepper> stepper;

  GIVEN("begin(2, 3, 4, 5) was called") {
    stepper.begin(2, 3, 4, 5);

    WHEN("powerOff() is called") {
      CLEAR_ARDUINO_LOG();
      stepper.powerOff();

      THEN("it should set all pins to LOW") {
        CHECK_ARDUINO_LOG({
            {0'000, "digitalWrite(2, LOW)"},
            {0'000, "digitalWrite(3, LOW)"},
            {0'000, "digitalWrite(4, LOW)"},
            {0'000, "digitalWrite(5, LOW)"},
        });
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

        THEN("it should set all pins to LOW") {
          loop_till(stepper, 100'000);
          CHECK(stepper.isSpinning() == false);
          CHECK(stepper.speed() == 0);
          CHECK_ARDUINO_LOG({
              // pin 2 is already LOW
              {100'000, "digitalWrite(3, LOW)"},
              {100'000, "digitalWrite(4, LOW)"},
              // pin 5 is already LOW
          });
        }
      }
    }
  }
}
