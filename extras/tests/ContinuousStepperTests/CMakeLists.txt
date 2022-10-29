add_executable(ContinuousStepperTests
  begin.cpp
  powerOff.cpp
  powerOn.cpp
  setEnablePin.cpp
  spin.cpp
  stop.cpp

  helpers.hpp
  helpers.cpp
)

target_link_libraries(ContinuousStepperTests
  PRIVATE
    ArduinoStub
    EventLog
    ContinuousStepper
    Catch2::Catch2WithMain
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