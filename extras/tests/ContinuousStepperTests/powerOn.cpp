#include <ContinuousStepper.h>
#include <TestFixtures.hpp>

TEST_CASE("ContinuousStepper<StepperDriver>::powerOn()") {
  ContinuousStepper<StepperDriver> stepper;

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
                {0'000, "digitalWrite(11, HIGH)"},  // DIR
                {15'811, "digitalWrite(10, HIGH)"}, // 10.541 ms
                {26'352, "digitalWrite(10, LOW)"},  // 8.624 ms
                {34'976, "digitalWrite(10, HIGH)"}, // 7.507 ms
                {42'483, "digitalWrite(10, LOW)"},  // 6.747 ms
                {49'230, "digitalWrite(10, HIGH)"}, // 6.184 ms
                {55'414, "digitalWrite(10, LOW)"},  // 5.744 ms
                {61'158, "digitalWrite(10, HIGH)"}, // 5.389 ms
                {66'547, "digitalWrite(10, LOW)"},  // 5.093 ms
                {71'640, "digitalWrite(10, HIGH)"}, // 5 ms
                {76'640, "digitalWrite(10, LOW)"},  // 5 ms
                {81'640, "digitalWrite(10, HIGH)"}, // 5 ms
                {86'640, "digitalWrite(10, LOW)"},  // 5 ms
                {91'640, "digitalWrite(10, HIGH)"}, // 5 ms
                {96'640, "digitalWrite(10, LOW)"},  // ...
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

TEST_CASE("ContinuousStepper<FourWireStepper>::powerOn()") {
  ContinuousStepper<FourWireStepper> stepper;

  GIVEN("begin(2, 3, 4, 5) was called") {
    stepper.begin(2, 3, 4, 5);

    AND_GIVEN("powerOff() was called") {
      stepper.powerOff();

      WHEN("powerOn() is called") {
        CLEAR_ARDUINO_LOG();
        stepper.powerOn();

        THEN("it should set pin 2 and 4 to HIGH") {
          CHECK_ARDUINO_LOG({
              {0, "digitalWrite(2, HIGH)"},
              {0, "digitalWrite(4, HIGH)"},
          })
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
                {0'000, "digitalWrite(2, HIGH)"},  // 31.622 ms
                {0'000, "digitalWrite(4, HIGH)"},  //
                {31'622, "digitalWrite(2, LOW)"},  // 15.811 ms
                {31'622, "digitalWrite(3, HIGH)"}, //
                {47'433, "digitalWrite(4, LOW)"},  // 12.649 ms
                {47'433, "digitalWrite(5, HIGH)"}, //
                {60'082, "digitalWrite(2, HIGH)"}, // 10.904 ms
                {60'082, "digitalWrite(3, LOW)"},  //
                {70'986, "digitalWrite(4, HIGH)"}, // 10 ms
                {70'986, "digitalWrite(5, LOW)"},  //
                {80'986, "digitalWrite(2, LOW)"},  // 10 ms
                {80'986, "digitalWrite(3, HIGH)"}, //
                {90'986, "digitalWrite(4, LOW)"},  // ...
                {90'986, "digitalWrite(5, HIGH)"}, //
            })
          }
        }
      }
    }

    AND_GIVEN("powerOn() was already called") {
      stepper.powerOn();

      WHEN("powerOn() is called") {
        CLEAR_ARDUINO_LOG();
        stepper.powerOn();

        THEN("it should do nothing") {
          CHECK_ARDUINO_LOG({});
        }
      }
    }
  }
}
