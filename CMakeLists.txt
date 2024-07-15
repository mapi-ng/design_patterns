cmake_minimum_required(VERSION 3.28.3)
project(design_patterns_course)
message(STATUS "==== Configuring ${PROJECT_NAME} for ${CMAKE_SYSTEM_NAME} ====")

# Generate compiler commands for C/C++ intellisense, SonarLint, etc.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O0 -g3")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2 -g0")
endif()

include(cmake/fetch_dependencies.cmake)
include(CTest)

add_subdirectory(specification_pattern)