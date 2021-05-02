set(MODULE builders)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
    src/HtmlBuilder.cpp
    src/HtmlElement.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC include)

add_subdirectory(test)