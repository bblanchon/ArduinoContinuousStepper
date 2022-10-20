add_library(EventLog
  EventLog.cpp
  EventLog.hpp
)

target_include_directories(EventLog
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(EventLog
  PRIVATE
    dtl
)