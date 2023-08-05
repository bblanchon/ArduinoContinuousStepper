add_library(TestFixtures
  Arduino.cpp
  Arduino.h
  Clock.cpp
  Clock.hpp
  EventLog.cpp
  EventLog.hpp
  main.cpp
  Teensy_PWM.h
  TeensyTimerTool.h
  TestFixtures.hpp
  TimerOne.h
  TimerThree.h
)

target_include_directories(TestFixtures
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(TestFixtures
  PUBLIC
    dtl
    Catch2::Catch2
)