#include <ContinuousStepper.h>
#include <TestFixtures.hpp>

TEST_CASE("ContinuousStepper::stop()") {
  ContinuousStepper stepper;

  GIVEN("a spinning stepper") {
    stepper.begin(10, 11);
    stepper.spin(100);
    loop_for(stepper, 100'000);
    REQUIRE(stepper.isSpinning() == true);
    REQUIRE(stepper.speed() == 100);

    WHEN("stop() is called") {
      CLEAR_ARDUINO_LOG();
      stepper.stop();

      THEN("it should deccelerate") {

        loop_for(stepper, 100'000);

        REQUIRE(stepper.isSpinning() == false);
        REQUIRE(stepper.speed() == 0);
        CHECK_ARDUINO_LOG({
            {100'173, "digitalWrite(10, LOW)"},  // 5 ms
            {105'173, "digitalWrite(10, HIGH)"}, // 5.555 ms
            {110'728, "digitalWrite(10, LOW)"},  // 5.555 ms
            {116'283, "digitalWrite(10, HIGH)"}, // 6.338 ms
            {122'621, "digitalWrite(10, LOW)"},  // 6.338 ms
            {128'959, "digitalWrite(10, HIGH)"}, // 7.551 ms
            {136'510, "digitalWrite(10, LOW)"},  // 7.551 ms
            {144'061, "digitalWrite(10, HIGH)"}, // 9.782 ms
            {153'843, "digitalWrite(10, LOW)"},  // 9.782 ms
            {163'625, "digitalWrite(10, HIGH)"}, // ...
        })
      }
    }
  }
}
