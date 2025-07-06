cmake_minimum_required(VERSION 3.25)
project(SGuitar)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/Dependencies.cmake)
include(cmake/Sources.cmake)

# Platform-specific build
if (EMSCRIPTEN)
    include(cmake/Platform_WebAssembly)
elseif (ANDROID)
    include(cmake/Platform_Android.cmake)
elseif (IOS)
    include(cmake/Platform_iOS.cmake)
else ()
    include(cmake/Platform_Native.cmake)
endif ()

# Tests
include(cmake/Tests.cmake)
