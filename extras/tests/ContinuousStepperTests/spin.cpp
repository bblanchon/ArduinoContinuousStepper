#include <Arduino.h>
#include <ContinuousStepper.h>

#include "helpers.hpp"

TEST_CASE("ContinuousStepper::spin()") {
  ContinuousStepper stepper;

  GIVEN("an initialized stepper") {
    stepper.begin(10, 11, 12);
    stepper.setAcceleration(1000);

    WHEN("spin() is called") {
      CLEAR_ARDUINO_LOG();
      stepper.spin(100);

      THEN("it should accelerate and reach target speed") {
        loop_till(stepper, 100'000);
        REQUIRE(stepper.speed() == 100);

        CHECK_ARDUINO_LOG({
            {15'811, "digitalWrite(11, HIGH)"},
            {15'811, "digitalWrite(10, HIGH)"},
            {23'716, "digitalWrite(10, LOW)"},
            {31'621, "digitalWrite(11, HIGH)"},
            {31'621, "digitalWrite(10, HIGH)"},
            {37'945, "digitalWrite(10, LOW)"},
            {44'269, "digitalWrite(11, HIGH)"},
            {44'269, "digitalWrite(10, HIGH)"},
            {49'721, "digitalWrite(10, LOW)"},
            {55'173, "digitalWrite(11, HIGH)"},
            {55'173, "digitalWrite(10, HIGH)"},
            {60'173, "digitalWrite(10, LOW)"},
            {65'173, "digitalWrite(11, HIGH)"},
            {65'173, "digitalWrite(10, HIGH)"},
            {70'173, "digitalWrite(10, LOW)"},
            {75'173, "digitalWrite(11, HIGH)"},
            {75'173, "digitalWrite(10, HIGH)"},
            {80'173, "digitalWrite(10, LOW)"},
            {85'173, "digitalWrite(11, HIGH)"},
            {85'173, "digitalWrite(10, HIGH)"},
            {90'173, "digitalWrite(10, LOW)"},
            {95'173, "digitalWrite(11, HIGH)"},
            {95'173, "digitalWrite(10, HIGH)"},
        });

        AND_WHEN("spin() is called with a negative speed") {
          CLEAR_ARDUINO_LOG();
          stepper.spin(-100);

          THEN("it should deccelerate and reverse the rotation") {
            loop_till(stepper, 7'150'000);
            REQUIRE(stepper.speed() == -100);

            CHECK_ARDUINO_LOG({
                {100'173, "digitalWrite(10, LOW)"},
                {105'173, "digitalWrite(11, HIGH)"},
                {105'173, "digitalWrite(10, HIGH)"},
                {110'728, "digitalWrite(10, LOW)"},
                {116'283, "digitalWrite(11, HIGH)"},
                {116'283, "digitalWrite(10, HIGH)"},
                {122'620, "digitalWrite(10, LOW)"},
                {128'957, "digitalWrite(11, HIGH)"},
                {128'957, "digitalWrite(10, HIGH)"},
                {136'508, "digitalWrite(10, LOW)"},
                {144'059, "digitalWrite(11, HIGH)"},
                {144'059, "digitalWrite(10, HIGH)"},
                {153'841, "digitalWrite(10, LOW)"},
                {163'623, "digitalWrite(11, HIGH)"},
                {163'623, "digitalWrite(10, HIGH)"},
                {179'470, "digitalWrite(10, LOW)"},
                {195'317, "digitalWrite(11, HIGH)"},
                {195'317, "digitalWrite(10, HIGH)"},
                {3'667'539, "digitalWrite(10, LOW)"}, // issue #7
                {7'139'761, "digitalWrite(11, LOW)"},
                {7'139'761, "digitalWrite(10, HIGH)"},
                {7'144'761, "digitalWrite(10, LOW)"},
                {7'149'761, "digitalWrite(11, LOW)"},
                {7'149'761, "digitalWrite(10, HIGH)"},
            });
          }
        }
      }
    }
  }
}
