cmake_minimum_required(VERSION 3.28.3)
project(design_patterns_course)

set(CMAKE_CXX_STANDARD 23)

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -O0 -g3")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -O2 -g0")
endif()

add_subdirectory(specification_pattern)