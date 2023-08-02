#include <ContinuousStepper.h>
#include <TestFixtures.hpp>

TEST_CASE("ContinuousStepper::spin()") {
  ContinuousStepper stepper;

  GIVEN("begin() was called with 2 arguments") {
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
              {15'811, "digitalWrite(11, HIGH)"}, // DIR
              {15'811, "digitalWrite(10, HIGH)"}, // 7.905 ms
              {23'716, "digitalWrite(10, LOW)"},  // 7.905 ms
              {31'621, "digitalWrite(10, HIGH)"}, // 6.324 ms
              {37'945, "digitalWrite(10, LOW)"},  // 6.324 ms
              {44'269, "digitalWrite(10, HIGH)"}, // 5.452 ms
              {49'721, "digitalWrite(10, LOW)"},  // 5.452 ms
              {55'173, "digitalWrite(10, HIGH)"}, // 5 ms
              {60'173, "digitalWrite(10, LOW)"},  // 5 ms
              {65'173, "digitalWrite(10, HIGH)"}, // 5 ms
              {70'173, "digitalWrite(10, LOW)"},  // 5 ms
              {75'173, "digitalWrite(10, HIGH)"}, // 5 ms
              {80'173, "digitalWrite(10, LOW)"},  // 5 ms
              {85'173, "digitalWrite(10, HIGH)"}, // 5 ms
              {90'173, "digitalWrite(10, LOW)"},  // 5 ms
              {95'173, "digitalWrite(10, HIGH)"}, // ...
          });

          AND_WHEN("spin(-100) is called") {
            CLEAR_ARDUINO_LOG();
            stepper.spin(-100);

            THEN("it should deccelerate and reverse the rotation") {
              loop_for(stepper, 200'000);
              REQUIRE(stepper.speed() == -100);

              CHECK_ARDUINO_LOG({
                  {100'728, "digitalWrite(10, LOW)"},  // 5.555 ms
                  {106'283, "digitalWrite(10, HIGH)"}, // 6.338 ms
                  {112'621, "digitalWrite(10, LOW)"},  // 6.338 ms
                  {118'959, "digitalWrite(10, HIGH)"}, // 7.551 ms
                  {126'510, "digitalWrite(10, LOW)"},  // 7.551 ms
                  {134'061, "digitalWrite(10, HIGH)"}, // 9.782 ms
                  {143'843, "digitalWrite(10, LOW)"},  // 9.782 ms
                  {153'625, "digitalWrite(10, HIGH)"}, // 15.811 ms
                  {169'436, "digitalWrite(10, LOW)"},  // 47.395 ms
                  {216'831, "digitalWrite(11, LOW)"},  // DIR
                  {216'831, "digitalWrite(10, HIGH)"}, // 7.905 ms
                  {224'736, "digitalWrite(10, LOW)"},  // 7.905 ms
                  {232'641, "digitalWrite(10, HIGH)"}, // 6.324 ms
                  {238'965, "digitalWrite(10, LOW)"},  // 6.324 ms
                  {245'289, "digitalWrite(10, HIGH)"}, // 5.452 ms
                  {250'741, "digitalWrite(10, LOW)"},  // 5.452 ms
                  {256'193, "digitalWrite(10, HIGH)"}, // 5 ms
                  {261'193, "digitalWrite(10, LOW)"},  // 5 ms
                  {266'193, "digitalWrite(10, HIGH)"}, // 5 ms
                  {271'193, "digitalWrite(10, LOW)"},  // 5 ms
                  {276'193, "digitalWrite(10, HIGH)"}, // 5 ms
                  {281'193, "digitalWrite(10, LOW)"},  // 5 ms
                  {286'193, "digitalWrite(10, HIGH)"}, // 5 ms
                  {291'193, "digitalWrite(10, LOW)"},  // 5 ms
                  {296'193, "digitalWrite(10, HIGH)"}, // ...
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

  GIVEN("begin() was called with 3 arguments") {
    stepper.begin(10, 11, 12);

    AND_GIVEN("setAcceleration(1000) was called") {
      stepper.setAcceleration(1000);

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
}
