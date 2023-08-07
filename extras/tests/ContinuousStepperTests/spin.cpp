#include <ContinuousStepper.h>
#include <TestFixtures.hpp>

TEST_CASE("ContinuousStepper<StepperDriver>::spin()") {
  ContinuousStepper<StepperDriver> stepper;

  GIVEN("begin(10, 11) was called") {
    stepper.begin(10, 11);

    AND_GIVEN("setAcceleration(1000) was called") {
      stepper.setAcceleration(1000);

      WHEN("spin(10) is called") {
        CLEAR_ARDUINO_LOG();
        stepper.spin(10);

        THEN("it should immediately reach target speed") {
          REQUIRE(stepper.speed() == 10);

          AND_WHEN("spin(-10) is called") {
            stepper.spin(-10);

            THEN("it should immediately reverse rotation") {
              REQUIRE(stepper.speed() == -10);
            }
          }
        }
      }

      WHEN("spin(100) is called") {
        CLEAR_ARDUINO_LOG();
        stepper.spin(100);

        THEN("it should accelerate and reach target speed") {
          loop_till(stepper, 100'000);
          REQUIRE(stepper.speed() == 100);

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
          });

          AND_WHEN("spin(-100) is called") {
            CLEAR_ARDUINO_LOG();
            stepper.spin(-100);

            THEN("it should deccelerate and reverse the rotation") {
              loop_for(stepper, 200'000);
              REQUIRE(stepper.speed() == -100);

              CHECK_ARDUINO_LOG({
                  {101'903, "digitalWrite(10, HIGH)"}, // 5.571 ms
                  {107'474, "digitalWrite(10, LOW)"},  // 5.94 ms
                  {113'414, "digitalWrite(10, HIGH)"}, // 6.391 ms
                  {119'805, "digitalWrite(10, LOW)"},  // 6.96 ms
                  {126'765, "digitalWrite(10, HIGH)"}, // 7.707 ms
                  {134'472, "digitalWrite(10, LOW)"},  // 8.746 ms
                  {143'218, "digitalWrite(10, HIGH)"}, // 10.325 ms
                  {153'543, "digitalWrite(10, LOW)"},  // 13.124 ms
                  {166'667, "digitalWrite(10, HIGH)"}, // 76.308 ms
                  {198'289, "digitalWrite(11, LOW)"},  // DIR
                  {242'975, "digitalWrite(10, LOW)"},  // 9.739 ms
                  {252'714, "digitalWrite(10, HIGH)"}, // 8.186 ms
                  {260'900, "digitalWrite(10, LOW)"},  // 7.219 ms
                  {268'119, "digitalWrite(10, HIGH)"}, // 6.537 ms
                  {274'656, "digitalWrite(10, LOW)"},  // 6.022 ms
                  {280'678, "digitalWrite(10, HIGH)"}, // 5.615 ms
                  {286'293, "digitalWrite(10, LOW)"},  // 5.282 ms
                  {291'575, "digitalWrite(10, HIGH)"}, // 5.003 ms
                  {296'578, "digitalWrite(10, LOW)"},  // ...
              });
            }
          }
        }
      }
    }

    AND_GIVEN("powerOff() was called") {
      stepper.powerOff();

      WHEN("spin(10) is called") {
        stepper.spin(10);

        THEN("speed should be null") {
          REQUIRE(stepper.speed() == 0);

          AND_WHEN("powerOn() is called") {
            stepper.powerOn();

            THEN("speed should be 10") {
              REQUIRE(stepper.speed() == 10);
            }
          }
        }
      }
    }
  }
}

TEST_CASE("ContinuousStepper<FourWireStepper>::spin()") {
  ContinuousStepper<FourWireStepper> stepper;

  GIVEN("begin(2, 3, 4, 5) was called") {
    stepper.begin(2, 3, 4, 5);

    AND_GIVEN("setAcceleration(1000) was called") {
      stepper.setAcceleration(1000);

      WHEN("spin(100) is called") {
        CLEAR_ARDUINO_LOG();
        stepper.spin(100);

        THEN("it should accelerate and reach target speed") {
          loop_till(stepper, 100'000);
          REQUIRE(stepper.speed() == 100);

          CHECK_ARDUINO_LOG({
              {31'622, "digitalWrite(2, LOW)"},  // 15.811 ms
              {31'622, "digitalWrite(3, HIGH)"}, //
              {31'622, "digitalWrite(4, HIGH)"}, //
              {31'622, "digitalWrite(5, LOW)"},  //
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
          });
        }
      }

      WHEN("spin(-100) is called") {
        CLEAR_ARDUINO_LOG();
        stepper.spin(-100);

        THEN("it should accelerate and reach target speed") {
          loop_till(stepper, 100'000);
          REQUIRE(stepper.speed() == -100);

          CHECK_ARDUINO_LOG({
              {31'622, "digitalWrite(2, HIGH)"}, // 15.811 ms
              {31'622, "digitalWrite(3, LOW)"},  //
              {31'622, "digitalWrite(4, LOW)"},  //
              {31'622, "digitalWrite(5, HIGH)"}, //
              {47'433, "digitalWrite(2, LOW)"},  // 12.649 ms
              {47'433, "digitalWrite(3, HIGH)"}, //
              {60'082, "digitalWrite(4, HIGH)"}, // 10.904 ms
              {60'082, "digitalWrite(5, LOW)"},  //
              {70'986, "digitalWrite(2, HIGH)"}, // 10 ms
              {70'986, "digitalWrite(3, LOW)"},  //
              {80'986, "digitalWrite(4, LOW)"},  // 10 ms
              {80'986, "digitalWrite(5, HIGH)"}, //
              {90'986, "digitalWrite(2, LOW)"},  // ...
              {90'986, "digitalWrite(3, HIGH)"}, //
          });
        }
      }
    }
  }
}
