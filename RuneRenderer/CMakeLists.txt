cmake_minimum_required(VERSION 3.10.0)
project(RuneRenderer VERSION 0.1.0)

add_executable(RuneRenderer src/main.cpp)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(EXECUTABLE_OUTPUT_PATH ../../build/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../build/)

add_subdirectory(vendor/glad)
add_subdirectory(vendor/glfw)

target_include_directories(
    ${PROJECT_NAME} PRIVATE vendor/glad
    ${PROJECT_NAME} PRIVATE vendor/glfw
)

target_link_directories(
    ${PROJECT_NAME} PRIVATE libtest
    ${PROJECT_NAME} PRIVATE newlib
)

target_link_libraries(${PROJECT_NAME} glfw glad)
