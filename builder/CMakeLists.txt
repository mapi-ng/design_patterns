project(builder)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
    src/YamlBuilder.cpp
    src/YamlElement.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC include)

add_subdirectory(test)