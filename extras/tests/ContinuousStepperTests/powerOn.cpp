#include <ContinuousStepper.h>
#include <TestFixtures.hpp>

TEST_CASE("ContinuousStepper::powerOn()") {
  ContinuousStepper stepper;

  GIVEN("begin(10, 11, 12)") {
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

  GIVEN("begin(10, 11) was called") {
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
                {31'621, "digitalWrite(10, HIGH)"},
                {37'945, "digitalWrite(10, LOW)"},
                {44'269, "digitalWrite(10, HIGH)"},
                {49'721, "digitalWrite(10, LOW)"},
                {55'173, "digitalWrite(10, HIGH)"},
                {60'173, "digitalWrite(10, LOW)"},
                {65'173, "digitalWrite(10, HIGH)"},
                {70'173, "digitalWrite(10, LOW)"},
                {75'173, "digitalWrite(10, HIGH)"},
                {80'173, "digitalWrite(10, LOW)"},
                {85'173, "digitalWrite(10, HIGH)"},
                {90'173, "digitalWrite(10, LOW)"},
                {95'173, "digitalWrite(10, HIGH)"},
            })
          }
        }
      }
    }

    AND_GIVEN("setEnablePin(12, HIGH)") {
      stepper.setEnablePin(12, HIGH);

      WHEN("powerOn() is called") {
        CLEAR_ARDUINO_LOG();
        stepper.powerOn();

        THEN("it should do nothing") {
          CHECK_ARDUINO_LOG({});
        }
      }

      AND_GIVEN("powerOff() was called") {
        stepper.powerOff();

        WHEN("powerOn() is called") {
          CLEAR_ARDUINO_LOG();
          stepper.powerOn();

          THEN("it should set pin 12 to HIGH") {
            CHECK_ARDUINO_LOG({
                {0, "digitalWrite(12, HIGH)"},
            })
          }
        }
      }
    }

    AND_GIVEN("setEnablePin(12, LOW)") {
      stepper.setEnablePin(12, LOW);

      WHEN("powerOn() is called") {
        CLEAR_ARDUINO_LOG();
        stepper.powerOn();

        THEN("it should do nothing") {
          CHECK_ARDUINO_LOG({});
        }
      }

      AND_GIVEN("powerOff() was called") {
        stepper.powerOff();

        WHEN("powerOn() is called") {
          CLEAR_ARDUINO_LOG();
          stepper.powerOn();

          THEN("it should set pin 12 to LOW") {
            CHECK_ARDUINO_LOG({
                {0, "digitalWrite(12, LOW)"},
            })
          }
        }
      }
    }
  }
}
