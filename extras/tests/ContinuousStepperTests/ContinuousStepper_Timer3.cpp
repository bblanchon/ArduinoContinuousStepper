#include <ContinuousStepper.h>
#include <ContinuousStepper/Tickers/TimerThree.hpp>
#include <TestFixtures.hpp>

TEST_CASE("ContinuousStepper<StepperDriver, TimerThreeTicker>") {
  ContinuousStepper<StepperDriver, TimerThreeTicker> stepper;

  GIVEN("begin(10, 11) was called") {
    stepper.begin(10, 11);

    THEN("it should configure pins and call PeriodicTimer::begin()") {
      CHECK_ARDUINO_LOG({
          {0'000, "pinMode(10, OUTPUT)"},
          {0'000, "pinMode(11, OUTPUT)"},
          {0'000, "TimerThree::initialize()"},
          {0'000, "TimerThree::attachInterrupt()"},
      });
    }

    AND_GIVEN("setAcceleration(1000) was called") {
      stepper.setAcceleration(1000);

      WHEN("spin(10) is called") {
        CLEAR_ARDUINO_LOG();
        stepper.spin(10);

        THEN("it should immediately reach target speed") {
          REQUIRE(stepper.speed() == 10);

          CHECK_ARDUINO_LOG({
              {0'000, "digitalWrite(11, HIGH)"},
              {0'000, "TimerThree::stop()"},
              {0'000, "TimerThree::setPeriod(50000)"},
              {0'000, "TimerThree::start()"},
          });

          AND_WHEN("spin(-10) is called") {
            CLEAR_ARDUINO_LOG();
            stepper.spin(-10);

            THEN("it should immediately reverse rotation") {
              REQUIRE(stepper.speed() == -10);

              CHECK_ARDUINO_LOG({
                  {0'000, "digitalWrite(11, LOW)"},
                  {0'000, "TimerThree::stop()"},
                  {0'000, "TimerThree::setPeriod(50000)"},
                  {0'000, "TimerThree::start()"},
              });
            }
          }
        }
      }

      WHEN("spin(100) is called") {
        CLEAR_ARDUINO_LOG();
        stepper.spin(100);

        THEN("it should accelerate and reach target speed") {
          wait_till(100'000);
          REQUIRE(stepper.speed() == 100);

          CHECK_ARDUINO_LOG({
              {0'000, "digitalWrite(11, HIGH)"},
              {0'000, "TimerThree::stop()"},
              {0'000, "TimerThree::setPeriod(15811)"},
              {0'000, "TimerThree::start()"},
              {15'811, "digitalWrite(10, HIGH)"},
              {15'811, "TimerThree::stop()"},
              {15'811, "TimerThree::setPeriod(10541)"},
              {15'811, "TimerThree::start()"},
              {26'352, "digitalWrite(10, LOW)"},
              {26'352, "TimerThree::stop()"},
              {26'352, "TimerThree::setPeriod(8624)"},
              {26'352, "TimerThree::start()"},
              {34'976, "digitalWrite(10, HIGH)"},
              {34'976, "TimerThree::stop()"},
              {34'976, "TimerThree::setPeriod(7507)"},
              {34'976, "TimerThree::start()"},
              {42'483, "digitalWrite(10, LOW)"},
              {42'483, "TimerThree::stop()"},
              {42'483, "TimerThree::setPeriod(6747)"},
              {42'483, "TimerThree::start()"},
              {49'230, "digitalWrite(10, HIGH)"},
              {49'230, "TimerThree::stop()"},
              {49'230, "TimerThree::setPeriod(6184)"},
              {49'230, "TimerThree::start()"},
              {55'414, "digitalWrite(10, LOW)"},
              {55'414, "TimerThree::stop()"},
              {55'414, "TimerThree::setPeriod(5744)"},
              {55'414, "TimerThree::start()"},
              {61'158, "digitalWrite(10, HIGH)"},
              {61'158, "TimerThree::stop()"},
              {61'158, "TimerThree::setPeriod(5389)"},
              {61'158, "TimerThree::start()"},
              {66'547, "digitalWrite(10, LOW)"},
              {66'547, "TimerThree::stop()"},
              {66'547, "TimerThree::setPeriod(5093)"},
              {66'547, "TimerThree::start()"},
              {71'640, "digitalWrite(10, HIGH)"},
              {71'640, "TimerThree::stop()"},
              {71'640, "TimerThree::setPeriod(5000)"},
              {71'640, "TimerThree::start()"},
              {76'640, "digitalWrite(10, LOW)"},
              {81'640, "digitalWrite(10, HIGH)"},
              {86'640, "digitalWrite(10, LOW)"},
              {91'640, "digitalWrite(10, HIGH)"},
              {96'640, "digitalWrite(10, LOW)"},
          });

          AND_WHEN("spin(-100) is called") {
            CLEAR_ARDUINO_LOG();
            stepper.spin(-100);

            THEN("it should deccelerate and reverse the rotation") {
              wait_for(200'000);
              REQUIRE(stepper.speed() == -100);

              CHECK_ARDUINO_LOG({
                  {100'000, "TimerThree::stop()"},
                  {100'000, "TimerThree::setPeriod(5263)"},
                  {100'000, "TimerThree::start()"},
                  {101'903, "digitalWrite(10, HIGH)"},
                  {101'903, "TimerThree::stop()"},
                  {101'903, "TimerThree::setPeriod(5571)"},
                  {101'903, "TimerThree::start()"},
                  {107'474, "digitalWrite(10, LOW)"},
                  {107'474, "TimerThree::stop()"},
                  {107'474, "TimerThree::setPeriod(5940)"},
                  {107'474, "TimerThree::start()"},
                  {113'414, "digitalWrite(10, HIGH)"},
                  {113'414, "TimerThree::stop()"},
                  {113'414, "TimerThree::setPeriod(6391)"},
                  {113'414, "TimerThree::start()"},
                  {119'805, "digitalWrite(10, LOW)"},
                  {119'805, "TimerThree::stop()"},
                  {119'805, "TimerThree::setPeriod(6960)"},
                  {119'805, "TimerThree::start()"},
                  {126'765, "digitalWrite(10, HIGH)"},
                  {126'765, "TimerThree::stop()"},
                  {126'765, "TimerThree::setPeriod(7707)"},
                  {126'765, "TimerThree::start()"},
                  {134'472, "digitalWrite(10, LOW)"},
                  {134'472, "TimerThree::stop()"},
                  {134'472, "TimerThree::setPeriod(8746)"},
                  {134'472, "TimerThree::start()"},
                  {143'218, "digitalWrite(10, HIGH)"},
                  {143'218, "TimerThree::stop()"},
                  {143'218, "TimerThree::setPeriod(10325)"},
                  {143'218, "TimerThree::start()"},
                  {153'543, "digitalWrite(10, LOW)"},
                  {153'543, "TimerThree::stop()"},
                  {153'543, "TimerThree::setPeriod(13124)"},
                  {153'543, "TimerThree::start()"},
                  {166'667, "digitalWrite(10, HIGH)"},
                  {166'667, "TimerThree::stop()"},
                  {166'667, "TimerThree::setPeriod(15811)"},
                  {166'667, "TimerThree::start()"},
                  {182'478, "TimerThree::stop()"},
                  {182'478, "TimerThree::setPeriod(15811)"},
                  {182'478, "TimerThree::start()"},
                  {198'289, "digitalWrite(11, LOW)"},
                  {198'289, "TimerThree::stop()"},
                  {198'289, "TimerThree::setPeriod(15811)"},
                  {198'289, "TimerThree::start()"},
                  {214'100, "TimerThree::stop()"},
                  {214'100, "TimerThree::setPeriod(15811)"},
                  {214'100, "TimerThree::start()"},
                  {229'911, "TimerThree::stop()"},
                  {229'911, "TimerThree::setPeriod(13064)"},
                  {229'911, "TimerThree::start()"},
                  {242'975, "digitalWrite(10, LOW)"},
                  {242'975, "TimerThree::stop()"},
                  {242'975, "TimerThree::setPeriod(9739)"},
                  {242'975, "TimerThree::start()"},
                  {252'714, "digitalWrite(10, HIGH)"},
                  {252'714, "TimerThree::stop()"},
                  {252'714, "TimerThree::setPeriod(8186)"},
                  {252'714, "TimerThree::start()"},
                  {260'900, "digitalWrite(10, LOW)"},
                  {260'900, "TimerThree::stop()"},
                  {260'900, "TimerThree::setPeriod(7219)"},
                  {260'900, "TimerThree::start()"},
                  {268'119, "digitalWrite(10, HIGH)"},
                  {268'119, "TimerThree::stop()"},
                  {268'119, "TimerThree::setPeriod(6537)"},
                  {268'119, "TimerThree::start()"},
                  {274'656, "digitalWrite(10, LOW)"},
                  {274'656, "TimerThree::stop()"},
                  {274'656, "TimerThree::setPeriod(6022)"},
                  {274'656, "TimerThree::start()"},
                  {280'678, "digitalWrite(10, HIGH)"},
                  {280'678, "TimerThree::stop()"},
                  {280'678, "TimerThree::setPeriod(5615)"},
                  {280'678, "TimerThree::start()"},
                  {286'293, "digitalWrite(10, LOW)"},
                  {286'293, "TimerThree::stop()"},
                  {286'293, "TimerThree::setPeriod(5282)"},
                  {286'293, "TimerThree::start()"},
                  {291'575, "digitalWrite(10, HIGH)"},
                  {291'575, "TimerThree::stop()"},
                  {291'575, "TimerThree::setPeriod(5003)"},
                  {291'575, "TimerThree::start()"},
                  {296'578, "digitalWrite(10, LOW)"},
                  {296'578, "TimerThree::stop()"},
                  {296'578, "TimerThree::setPeriod(5000)"},
                  {296'578, "TimerThree::start()"},
              });
            }
          }
        }
      }
    }
  }
}
