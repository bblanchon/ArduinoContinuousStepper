add_executable(ContinuousStepperTests
  begin.cpp
  powerOff.cpp
  powerOn.cpp
  setEnablePin.cpp
  spin.cpp
  stop.cpp

  ContinuousStepper_AWF.cpp
  ContinuousStepper_KhoiH.cpp
  ContinuousStepper_TeensyTimerTool.cpp
  ContinuousStepper_Tone.cpp
  ContinuousStepper_Timer1.cpp
  ContinuousStepper_Timer3.cpp
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