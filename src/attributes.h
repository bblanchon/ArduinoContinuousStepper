#pragma once

#ifdef _MSC_VER // Visual Studio

#  define CONTINUOUSSTEPPER_DEPRECATED(msg) __declspec(deprecated(msg))

#elif defined(__GNUC__) // GCC or Clang

#  define CONTINUOUSSTEPPER_DEPRECATED(msg) __attribute__((deprecated(msg)))

#else // Other compilers

#  define CONTINUOUSSTEPPER_DEPRECATED(msg)

#endif
