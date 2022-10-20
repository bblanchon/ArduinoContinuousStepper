Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.1.1
)
FetchContent_MakeAvailable(Catch2)

add_library(dtl INTERFACE)
target_include_directories(dtl
  INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/dtl/dtl
)