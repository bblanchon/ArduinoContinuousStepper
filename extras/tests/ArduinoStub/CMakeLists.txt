add_library(ArduinoStub
  Arduino.h
  Arduino.cpp
)

target_include_directories(ArduinoStub
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(ArduinoStub
  PUBLIC
    EventLog
)