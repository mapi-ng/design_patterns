project(specification)
add_library(specification INTERFACE)

target_include_directories(specification INTERFACE include)

add_subdirectory(test)