#include <ContinuousStepper.h>
#include <ContinuousStepper/Tickers/KhoiH_PWM.hpp>
#include <Teensy_PWM.h>
#include <TestFixtures.hpp>

TEST_CASE(
    "ContinuousStepper<StepperDriver, KhoihTicker<Teensy_PWM>>") {

  ContinuousStepper<StepperDriver, KhoihTicker<Teensy_PWM>> stepper;

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
              {0'000, "Teensy_PWM::setPWM(10, 10, 50)"},
          });

          AND_WHEN("spin(-10) is called") {
            CLEAR_ARDUINO_LOG();
            stepper.spin(-10);

            THEN("it should immediately reverse rotation") {
              REQUIRE(stepper.speed() == -10);

              CHECK_ARDUINO_LOG({
                  {0'000, "digitalWrite(11, LOW)"},
                  {0'000, "Teensy_PWM::setPWM(10, 10, 50)"},
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
              {0'000, "Teensy_PWM::setPWM(10, 31, 50)"},
              {31'622, "Teensy_PWM::setPWM(10, 63, 50)"},
              {47'433, "Teensy_PWM::setPWM(10, 79, 50)"},
              {60'082, "Teensy_PWM::setPWM(10, 91, 50)"},
              {70'986, "Teensy_PWM::setPWM(10, 100, 50)"},
          });

          AND_WHEN("spin(-100) is called") {
            CLEAR_ARDUINO_LOG();
            stepper.spin(-100);

            THEN("it should deccelerate and reverse the rotation") {
              loop_for(stepper, 200'000);
              REQUIRE(stepper.speed() == -100);

              CHECK_ARDUINO_LOG({
                  {100'000, "Teensy_PWM::setPWM(10, 90, 50)"},
                  {102'097, "Teensy_PWM::setPWM(10, 78, 50)"},
                  {114'773, "Teensy_PWM::setPWM(10, 66, 50)"},
                  {129'875, "Teensy_PWM::setPWM(10, 51, 50)"},
                  {149'440, "Teensy_PWM::setPWM(10, 31, 50)"},
                  {181'062, "digitalWrite(11, LOW)"},
                  {181'062, "Teensy_PWM::setPWM(10, 31, 50)"},
                  {212'684, "Teensy_PWM::setPWM(10, 31, 50)"},
                  {244'231, "Teensy_PWM::setPWM(10, 63, 50)"},
                  {260'042, "Teensy_PWM::setPWM(10, 79, 50)"},
                  {272'691, "Teensy_PWM::setPWM(10, 91, 50)"},
                  {283'595, "Teensy_PWM::setPWM(10, 100, 50)"},
              });
            }
          }
        }
      }
    }
  }
}
