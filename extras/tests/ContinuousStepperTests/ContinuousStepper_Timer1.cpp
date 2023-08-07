#include <ContinuousStepper.h>
#include <ContinuousStepper/Tickers/TimerOne.hpp>
#include <TestFixtures.hpp>

TEST_CASE("ContinuousStepper<StepperDriver, TimerOneTicker>") {
  ContinuousStepper<StepperDriver, TimerOneTicker> stepper;

  GIVEN("begin(10, 11) was called") {
    stepper.begin(10, 11);

    THEN("it should configure pins and call PeriodicTimer::begin()") {
      CHECK_ARDUINO_LOG({
          {0'000, "pinMode(10, OUTPUT)"},
          {0'000, "pinMode(11, OUTPUT)"},
          {0'000, "TimerOne::initialize()"},
          {0'000, "TimerOne::attachInterrupt()"},
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
              {0'000, "TimerOne::stop()"},
              {0'000, "TimerOne::setPeriod(50000)"},
              {0'000, "TimerOne::start()"},
          });

          AND_WHEN("spin(-10) is called") {
            CLEAR_ARDUINO_LOG();
            stepper.spin(-10);

            THEN("it should immediately reverse rotation") {
              REQUIRE(stepper.speed() == -10);

              CHECK_ARDUINO_LOG({
                  {0'000, "digitalWrite(11, LOW)"},
                  {0'000, "TimerOne::stop()"},
                  {0'000, "TimerOne::setPeriod(50000)"},
                  {0'000, "TimerOne::start()"},
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
              {0'000, "TimerOne::stop()"},
              {0'000, "TimerOne::setPeriod(15811)"},
              {0'000, "TimerOne::start()"},
              {15'811, "digitalWrite(10, HIGH)"},
              {15'811, "TimerOne::stop()"},
              {15'811, "TimerOne::setPeriod(10541)"},
              {15'811, "TimerOne::start()"},
              {26'352, "digitalWrite(10, LOW)"},
              {26'352, "TimerOne::stop()"},
              {26'352, "TimerOne::setPeriod(8624)"},
              {26'352, "TimerOne::start()"},
              {34'976, "digitalWrite(10, HIGH)"},
              {34'976, "TimerOne::stop()"},
              {34'976, "TimerOne::setPeriod(7507)"},
              {34'976, "TimerOne::start()"},
              {42'483, "digitalWrite(10, LOW)"},
              {42'483, "TimerOne::stop()"},
              {42'483, "TimerOne::setPeriod(6747)"},
              {42'483, "TimerOne::start()"},
              {49'230, "digitalWrite(10, HIGH)"},
              {49'230, "TimerOne::stop()"},
              {49'230, "TimerOne::setPeriod(6184)"},
              {49'230, "TimerOne::start()"},
              {55'414, "digitalWrite(10, LOW)"},
              {55'414, "TimerOne::stop()"},
              {55'414, "TimerOne::setPeriod(5744)"},
              {55'414, "TimerOne::start()"},
              {61'158, "digitalWrite(10, HIGH)"},
              {61'158, "TimerOne::stop()"},
              {61'158, "TimerOne::setPeriod(5389)"},
              {61'158, "TimerOne::start()"},
              {66'547, "digitalWrite(10, LOW)"},
              {66'547, "TimerOne::stop()"},
              {66'547, "TimerOne::setPeriod(5093)"},
              {66'547, "TimerOne::start()"},
              {71'640, "digitalWrite(10, HIGH)"},
              {71'640, "TimerOne::stop()"},
              {71'640, "TimerOne::setPeriod(5000)"},
              {71'640, "TimerOne::start()"},
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
                  {100'000, "TimerOne::stop()"},
                  {100'000, "TimerOne::setPeriod(5263)"},
                  {100'000, "TimerOne::start()"},
                  {101'903, "digitalWrite(10, HIGH)"},
                  {101'903, "TimerOne::stop()"},
                  {101'903, "TimerOne::setPeriod(5571)"},
                  {101'903, "TimerOne::start()"},
                  {107'474, "digitalWrite(10, LOW)"},
                  {107'474, "TimerOne::stop()"},
                  {107'474, "TimerOne::setPeriod(5940)"},
                  {107'474, "TimerOne::start()"},
                  {113'414, "digitalWrite(10, HIGH)"},
                  {113'414, "TimerOne::stop()"},
                  {113'414, "TimerOne::setPeriod(6391)"},
                  {113'414, "TimerOne::start()"},
                  {119'805, "digitalWrite(10, LOW)"},
                  {119'805, "TimerOne::stop()"},
                  {119'805, "TimerOne::setPeriod(6960)"},
                  {119'805, "TimerOne::start()"},
                  {126'765, "digitalWrite(10, HIGH)"},
                  {126'765, "TimerOne::stop()"},
                  {126'765, "TimerOne::setPeriod(7707)"},
                  {126'765, "TimerOne::start()"},
                  {134'472, "digitalWrite(10, LOW)"},
                  {134'472, "TimerOne::stop()"},
                  {134'472, "TimerOne::setPeriod(8746)"},
                  {134'472, "TimerOne::start()"},
                  {143'218, "digitalWrite(10, HIGH)"},
                  {143'218, "TimerOne::stop()"},
                  {143'218, "TimerOne::setPeriod(10325)"},
                  {143'218, "TimerOne::start()"},
                  {153'543, "digitalWrite(10, LOW)"},
                  {153'543, "TimerOne::stop()"},
                  {153'543, "TimerOne::setPeriod(13124)"},
                  {153'543, "TimerOne::start()"},
                  {166'667, "digitalWrite(10, HIGH)"},
                  {166'667, "TimerOne::stop()"},
                  {166'667, "TimerOne::setPeriod(15811)"},
                  {166'667, "TimerOne::start()"},
                  {182'478, "TimerOne::stop()"},
                  {182'478, "TimerOne::setPeriod(15811)"},
                  {182'478, "TimerOne::start()"},
                  {198'289, "digitalWrite(11, LOW)"},
                  {198'289, "TimerOne::stop()"},
                  {198'289, "TimerOne::setPeriod(15811)"},
                  {198'289, "TimerOne::start()"},
                  {214'100, "TimerOne::stop()"},
                  {214'100, "TimerOne::setPeriod(15811)"},
                  {214'100, "TimerOne::start()"},
                  {229'911, "TimerOne::stop()"},
                  {229'911, "TimerOne::setPeriod(13064)"},
                  {229'911, "TimerOne::start()"},
                  {242'975, "digitalWrite(10, LOW)"},
                  {242'975, "TimerOne::stop()"},
                  {242'975, "TimerOne::setPeriod(9739)"},
                  {242'975, "TimerOne::start()"},
                  {252'714, "digitalWrite(10, HIGH)"},
                  {252'714, "TimerOne::stop()"},
                  {252'714, "TimerOne::setPeriod(8186)"},
                  {252'714, "TimerOne::start()"},
                  {260'900, "digitalWrite(10, LOW)"},
                  {260'900, "TimerOne::stop()"},
                  {260'900, "TimerOne::setPeriod(7219)"},
                  {260'900, "TimerOne::start()"},
                  {268'119, "digitalWrite(10, HIGH)"},
                  {268'119, "TimerOne::stop()"},
                  {268'119, "TimerOne::setPeriod(6537)"},
                  {268'119, "TimerOne::start()"},
                  {274'656, "digitalWrite(10, LOW)"},
                  {274'656, "TimerOne::stop()"},
                  {274'656, "TimerOne::setPeriod(6022)"},
                  {274'656, "TimerOne::start()"},
                  {280'678, "digitalWrite(10, HIGH)"},
                  {280'678, "TimerOne::stop()"},
                  {280'678, "TimerOne::setPeriod(5615)"},
                  {280'678, "TimerOne::start()"},
                  {286'293, "digitalWrite(10, LOW)"},
                  {286'293, "TimerOne::stop()"},
                  {286'293, "TimerOne::setPeriod(5282)"},
                  {286'293, "TimerOne::start()"},
                  {291'575, "digitalWrite(10, HIGH)"},
                  {291'575, "TimerOne::stop()"},
                  {291'575, "TimerOne::setPeriod(5003)"},
                  {291'575, "TimerOne::start()"},
                  {296'578, "digitalWrite(10, LOW)"},
                  {296'578, "TimerOne::stop()"},
                  {296'578, "TimerOne::setPeriod(5000)"},
                  {296'578, "TimerOne::start()"},
              });
            }
          }
        }
      }
    }
  }
}
