add_executable(ContinuousStepperTests
  begin.cpp
  powerOff.cpp
  powerOn.cpp
  setEnablePin.cpp
  spin.cpp
  stop.cpp
)

target_link_libraries(ContinuousStepperTests
  PRIVATE
    TestFixtures
    ContinuousStepper
)

if(MSVC)
  target_compile_options(ContinuousStepperTests
    PRIVATE
      /W4
  )
else()
  target_compile_options(ContinuousStepperTests
    PRIVATE
      -Wno-deprecated-declarations
      -Wall
      -Werror
  )
endif()

add_test(
  NAME
    ContinuousStepperTests
  COMMAND
    ContinuousStepperTests
)