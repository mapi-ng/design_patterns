cmake_minimum_required(VERSION 3.28.2)
project(test_builder)
include(CTest)

add_executable(${PROJECT_NAME}
    test_builder.cpp
)

add_test(NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
    WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    gtest_main
    builder
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
)