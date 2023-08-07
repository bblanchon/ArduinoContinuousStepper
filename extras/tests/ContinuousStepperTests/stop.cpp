#include <ContinuousStepper.h>
#include <TestFixtures.hpp>

TEST_CASE("ContinuousStepper<StepperDriver>::stop()") {
  ContinuousStepper<StepperDriver> stepper;

  GIVEN("begin(10, 11) was called)") {
    stepper.begin(10, 11);

    AND_GIVEN("spin(100) was called") {
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
              {101'640, "digitalWrite(10, HIGH)"}, // 5.263 ms
              {106'903, "digitalWrite(10, LOW)"},  // 5.571 ms
              {112'474, "digitalWrite(10, HIGH)"}, // 5.94 ms
              {118'414, "digitalWrite(10, LOW)"},  // 6.391 ms
              {124'805, "digitalWrite(10, HIGH)"}, // 6.96 ms
              {131'765, "digitalWrite(10, LOW)"},  // 7.707 ms
              {139'472, "digitalWrite(10, HIGH)"}, // 8.746 ms
              {148'218, "digitalWrite(10, LOW)"},  // 10.325 ms
              {158'543, "digitalWrite(10, HIGH)"}, // 13.124 ms
              {171'667, "digitalWrite(10, LOW)"},  // ...
          })
        }
      }
    }
  }
}

TEST_CASE("ContinuousStepper<FourWireStepper>::stop()") {
  ContinuousStepper<FourWireStepper> stepper;

  GIVEN("begin(2, 3, 4, 5) was called)") {
    stepper.begin(2, 3, 4, 5);

    AND_GIVEN("spin(100) was called") {
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
              {100'986, "digitalWrite(2, HIGH)"}, // 11.111 ms
              {100'986, "digitalWrite(3, LOW)"},  //
              {112'097, "digitalWrite(4, HIGH)"}, // 12.676 ms
              {112'097, "digitalWrite(5, LOW)"},  //
              {124'773, "digitalWrite(2, LOW)"},  // 15.102 ms
              {124'773, "digitalWrite(3, HIGH)"}, //
              {139'875, "digitalWrite(4, LOW)"},  // 19.565 ms
              {139'875, "digitalWrite(5, HIGH)"}, //
              {159'440, "digitalWrite(2, HIGH)"}, // ...
              {159'440, "digitalWrite(3, LOW)"},  //
          })
        }
      }
    }
  }
}
