add_library(TestFixtures
  Arduino.h
  Arduino.cpp
  EventLog.cpp
  EventLog.hpp
  main.cpp
  TestFixtures.hpp
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