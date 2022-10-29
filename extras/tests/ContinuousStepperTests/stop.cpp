#include <Arduino.h>
#include <ContinuousStepper.h>

#include "helpers.hpp"

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
            {100'173, "digitalWrite(10, LOW)"},
            {105'173, "digitalWrite(10, HIGH)"},
            {110'728, "digitalWrite(10, LOW)"},
            {116'283, "digitalWrite(10, HIGH)"},
            {122'620, "digitalWrite(10, LOW)"},
            {128'957, "digitalWrite(10, HIGH)"},
            {136'508, "digitalWrite(10, LOW)"},
            {144'059, "digitalWrite(10, HIGH)"},
            {153'841, "digitalWrite(10, LOW)"},
            {163'623, "digitalWrite(10, HIGH)"},
        })
      }
    }
  }
}
