#include <ContinuousStepper_Tone.h>
#include <TestFixtures.hpp>

TEST_CASE("ContinuousStepper_Tone::spin()") {
  ContinuousStepper_Tone stepper;

  GIVEN("begin() was called with 2 arguments") {
    stepper.begin(10, 11);

    AND_GIVEN("setAcceleration(1000) was called") {
      stepper.setAcceleration(1000);

      WHEN("spin(10) is called") {
        CLEAR_ARDUINO_LOG();
        stepper.spin(10);

        THEN("it should immediately reach target speed") {
          REQUIRE(stepper.speed() == 10);

          CHECK_ARDUINO_LOG({
              {0'000, "digitalWrite(11, HIGH)"},
              {0'000, "tone(10, 10)"},
          });

          AND_WHEN("spin(-10) is called") {
            CLEAR_ARDUINO_LOG();
            stepper.spin(-10);

            THEN("it should immediately reverse rotation") {
              REQUIRE(stepper.speed() == -10);

              CHECK_ARDUINO_LOG({
                  {0'000, "digitalWrite(11, LOW)"},
                  {0'000, "tone(10, 10)"},
              });
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
              {0'000, "digitalWrite(11, HIGH)"},
              {0'000, "tone(10, 31)"},
              {31'622, "tone(10, 63)"},
              {47'433, "tone(10, 79)"},
              {60'082, "tone(10, 91)"},
              {70'986, "tone(10, 100)"},
          });

          AND_WHEN("spin(-100) is called") {
            CLEAR_ARDUINO_LOG();
            stepper.spin(-100);

            THEN("it should deccelerate and reverse the rotation") {
              loop_for(stepper, 200'000);
              REQUIRE(stepper.speed() == -100);

              CHECK_ARDUINO_LOG({
                  {100'000, "tone(10, 90)"},
                  {102'097, "tone(10, 78)"},
                  {114'773, "tone(10, 66)"},
                  {129'875, "tone(10, 51)"},
                  {149'440, "tone(10, 31)"},
                  {181'062, "digitalWrite(11, LOW)"},
                  {181'062, "tone(10, 31)"},
                  {212'684, "tone(10, 31)"},
                  {244'231, "tone(10, 63)"},
                  {260'042, "tone(10, 79)"},
                  {272'691, "tone(10, 91)"},
                  {283'595, "tone(10, 100)"},
              });
            }
          }
        }
      }
    }
  }
}
