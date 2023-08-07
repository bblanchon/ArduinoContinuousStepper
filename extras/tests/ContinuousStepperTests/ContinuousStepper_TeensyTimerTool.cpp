#include <ContinuousStepper.h>
#include <ContinuousStepper/Tickers/TeensyTimerTool.hpp>
#include <TestFixtures.hpp>

TEST_CASE("ContinuousStepper<StepperDriver, TeensyTimerToolTicker>") {
  TeensyTimerTool::PeriodicTimer timer;
  ContinuousStepper<StepperDriver, TeensyTimerToolTicker> stepper(
      timer);

  GIVEN("begin(10, 11) was called") {
    stepper.begin(10, 11);

    THEN("it should configure pins and call PeriodicTimer::begin()") {
      CHECK_ARDUINO_LOG({
          {0'000, "pinMode(10, OUTPUT)"},
          {0'000, "pinMode(11, OUTPUT)"},
          {0'000, "PeriodicTimer::begin(1000, false)"},
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
              {0'000, "PeriodicTimer::stop()"},
              {0'000, "PeriodicTimer::setPeriod(50000)"},
              {0'000, "PeriodicTimer::start()"},
          });

          AND_WHEN("spin(-10) is called") {
            CLEAR_ARDUINO_LOG();
            stepper.spin(-10);

            THEN("it should immediately reverse rotation") {
              REQUIRE(stepper.speed() == -10);

              CHECK_ARDUINO_LOG({
                  {0'000, "digitalWrite(11, LOW)"},
                  {0'000, "PeriodicTimer::stop()"},
                  {0'000, "PeriodicTimer::setPeriod(50000)"},
                  {0'000, "PeriodicTimer::start()"},
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
              {0'000, "PeriodicTimer::stop()"},
              {0'000, "PeriodicTimer::setPeriod(15811)"},
              {0'000, "PeriodicTimer::start()"},
              {15'811, "digitalWrite(10, HIGH)"},
              {15'811, "PeriodicTimer::stop()"},
              {15'811, "PeriodicTimer::setPeriod(10541)"},
              {15'811, "PeriodicTimer::start()"},
              {26'352, "digitalWrite(10, LOW)"},
              {26'352, "PeriodicTimer::stop()"},
              {26'352, "PeriodicTimer::setPeriod(8624)"},
              {26'352, "PeriodicTimer::start()"},
              {34'976, "digitalWrite(10, HIGH)"},
              {34'976, "PeriodicTimer::stop()"},
              {34'976, "PeriodicTimer::setPeriod(7507)"},
              {34'976, "PeriodicTimer::start()"},
              {42'483, "digitalWrite(10, LOW)"},
              {42'483, "PeriodicTimer::stop()"},
              {42'483, "PeriodicTimer::setPeriod(6747)"},
              {42'483, "PeriodicTimer::start()"},
              {49'230, "digitalWrite(10, HIGH)"},
              {49'230, "PeriodicTimer::stop()"},
              {49'230, "PeriodicTimer::setPeriod(6184)"},
              {49'230, "PeriodicTimer::start()"},
              {55'414, "digitalWrite(10, LOW)"},
              {55'414, "PeriodicTimer::stop()"},
              {55'414, "PeriodicTimer::setPeriod(5744)"},
              {55'414, "PeriodicTimer::start()"},
              {61'158, "digitalWrite(10, HIGH)"},
              {61'158, "PeriodicTimer::stop()"},
              {61'158, "PeriodicTimer::setPeriod(5389)"},
              {61'158, "PeriodicTimer::start()"},
              {66'547, "digitalWrite(10, LOW)"},
              {66'547, "PeriodicTimer::stop()"},
              {66'547, "PeriodicTimer::setPeriod(5093)"},
              {66'547, "PeriodicTimer::start()"},
              {71'640, "digitalWrite(10, HIGH)"},
              {71'640, "PeriodicTimer::stop()"},
              {71'640, "PeriodicTimer::setPeriod(5000)"},
              {71'640, "PeriodicTimer::start()"},
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
                  {100'000, "PeriodicTimer::stop()"},
                  {100'000, "PeriodicTimer::setPeriod(5263)"},
                  {100'000, "PeriodicTimer::start()"},
                  {101'903, "digitalWrite(10, HIGH)"},
                  {101'903, "PeriodicTimer::stop()"},
                  {101'903, "PeriodicTimer::setPeriod(5571)"},
                  {101'903, "PeriodicTimer::start()"},
                  {107'474, "digitalWrite(10, LOW)"},
                  {107'474, "PeriodicTimer::stop()"},
                  {107'474, "PeriodicTimer::setPeriod(5940)"},
                  {107'474, "PeriodicTimer::start()"},
                  {113'414, "digitalWrite(10, HIGH)"},
                  {113'414, "PeriodicTimer::stop()"},
                  {113'414, "PeriodicTimer::setPeriod(6391)"},
                  {113'414, "PeriodicTimer::start()"},
                  {119'805, "digitalWrite(10, LOW)"},
                  {119'805, "PeriodicTimer::stop()"},
                  {119'805, "PeriodicTimer::setPeriod(6960)"},
                  {119'805, "PeriodicTimer::start()"},
                  {126'765, "digitalWrite(10, HIGH)"},
                  {126'765, "PeriodicTimer::stop()"},
                  {126'765, "PeriodicTimer::setPeriod(7707)"},
                  {126'765, "PeriodicTimer::start()"},
                  {134'472, "digitalWrite(10, LOW)"},
                  {134'472, "PeriodicTimer::stop()"},
                  {134'472, "PeriodicTimer::setPeriod(8746)"},
                  {134'472, "PeriodicTimer::start()"},
                  {143'218, "digitalWrite(10, HIGH)"},
                  {143'218, "PeriodicTimer::stop()"},
                  {143'218, "PeriodicTimer::setPeriod(10325)"},
                  {143'218, "PeriodicTimer::start()"},
                  {153'543, "digitalWrite(10, LOW)"},
                  {153'543, "PeriodicTimer::stop()"},
                  {153'543, "PeriodicTimer::setPeriod(13124)"},
                  {153'543, "PeriodicTimer::start()"},
                  {166'667, "digitalWrite(10, HIGH)"},
                  {166'667, "PeriodicTimer::stop()"},
                  {166'667, "PeriodicTimer::setPeriod(15811)"},
                  {166'667, "PeriodicTimer::start()"},
                  {182'478, "PeriodicTimer::stop()"},
                  {182'478, "PeriodicTimer::setPeriod(15811)"},
                  {182'478, "PeriodicTimer::start()"},
                  {198'289, "digitalWrite(11, LOW)"},
                  {198'289, "PeriodicTimer::stop()"},
                  {198'289, "PeriodicTimer::setPeriod(15811)"},
                  {198'289, "PeriodicTimer::start()"},
                  {214'100, "PeriodicTimer::stop()"},
                  {214'100, "PeriodicTimer::setPeriod(15811)"},
                  {214'100, "PeriodicTimer::start()"},
                  {229'911, "PeriodicTimer::stop()"},
                  {229'911, "PeriodicTimer::setPeriod(13064)"},
                  {229'911, "PeriodicTimer::start()"},
                  {242'975, "digitalWrite(10, LOW)"},
                  {242'975, "PeriodicTimer::stop()"},
                  {242'975, "PeriodicTimer::setPeriod(9739)"},
                  {242'975, "PeriodicTimer::start()"},
                  {252'714, "digitalWrite(10, HIGH)"},
                  {252'714, "PeriodicTimer::stop()"},
                  {252'714, "PeriodicTimer::setPeriod(8186)"},
                  {252'714, "PeriodicTimer::start()"},
                  {260'900, "digitalWrite(10, LOW)"},
                  {260'900, "PeriodicTimer::stop()"},
                  {260'900, "PeriodicTimer::setPeriod(7219)"},
                  {260'900, "PeriodicTimer::start()"},
                  {268'119, "digitalWrite(10, HIGH)"},
                  {268'119, "PeriodicTimer::stop()"},
                  {268'119, "PeriodicTimer::setPeriod(6537)"},
                  {268'119, "PeriodicTimer::start()"},
                  {274'656, "digitalWrite(10, LOW)"},
                  {274'656, "PeriodicTimer::stop()"},
                  {274'656, "PeriodicTimer::setPeriod(6022)"},
                  {274'656, "PeriodicTimer::start()"},
                  {280'678, "digitalWrite(10, HIGH)"},
                  {280'678, "PeriodicTimer::stop()"},
                  {280'678, "PeriodicTimer::setPeriod(5615)"},
                  {280'678, "PeriodicTimer::start()"},
                  {286'293, "digitalWrite(10, LOW)"},
                  {286'293, "PeriodicTimer::stop()"},
                  {286'293, "PeriodicTimer::setPeriod(5282)"},
                  {286'293, "PeriodicTimer::start()"},
                  {291'575, "digitalWrite(10, HIGH)"},
                  {291'575, "PeriodicTimer::stop()"},
                  {291'575, "PeriodicTimer::setPeriod(5003)"},
                  {291'575, "PeriodicTimer::start()"},
                  {296'578, "digitalWrite(10, LOW)"},
                  {296'578, "PeriodicTimer::stop()"},
                  {296'578, "PeriodicTimer::setPeriod(5000)"},
                  {296'578, "PeriodicTimer::start()"},
              });
            }
          }
        }
      }
    }
  }
}
