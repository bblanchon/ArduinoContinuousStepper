#include <ContinuousStepper.h>
#include <TestFixtures.hpp>

TEST_CASE("ContinuousStepper<StepperDriver>::setEnablePin()") {
  ContinuousStepper<StepperDriver> stepper;

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

    WHEN("setEnablePin(12, HIGH) is called") {
      CLEAR_ARDUINO_LOG();
      stepper.setEnablePin(12, HIGH);

      THEN("it should set pin 12 to HIGH") {
        CHECK_ARDUINO_LOG({
            {0, "pinMode(12, OUTPUT)"},
            {0, "digitalWrite(12, HIGH)"},
        })
      }
    }

    WHEN("setEnablePin(12, LOW) is called") {
      CLEAR_ARDUINO_LOG();
      stepper.setEnablePin(12, LOW);

      THEN("it should set pin 12 to LOW") {
        CHECK_ARDUINO_LOG({
            {0, "pinMode(12, OUTPUT)"},
            {0, "digitalWrite(12, LOW)"},
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

      WHEN("setEnablePin(12, HIGH) is called") {
        CLEAR_ARDUINO_LOG();
        stepper.setEnablePin(12, HIGH);

        THEN("it should set pin 12 to LOW") {
          CHECK_ARDUINO_LOG({
              {0, "pinMode(12, OUTPUT)"},
              {0, "digitalWrite(12, LOW)"},
          })
        }
      }

      WHEN("setEnablePin(12, LOW) is called") {
        CLEAR_ARDUINO_LOG();
        stepper.setEnablePin(12, LOW);

        THEN("it should set pin 12 to HIGH") {
          CHECK_ARDUINO_LOG({
              {0, "pinMode(12, OUTPUT)"},
              {0, "digitalWrite(12, HIGH)"},
          })
        }
      }
    }
  }
}

TEST_CASE("ContinuousStepper<FourWireStepper>::setEnablePin()") {
  ContinuousStepper<FourWireStepper> stepper;

  GIVEN("begin(2, 3, 4, 5) was called") {
    stepper.begin(2, 3, 4, 5);

    WHEN("setEnablePin(6) is called") {
      CLEAR_ARDUINO_LOG();
      stepper.setEnablePin(6);

      THEN("it should set pin 6 to HIGH") {
        CHECK_ARDUINO_LOG({
            {0, "pinMode(6, OUTPUT)"},
            {0, "digitalWrite(6, HIGH)"},
        });
      }
    }
  }
}