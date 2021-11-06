cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_STANDARD 17)
project(RuneApplication VERSION 0.1.0)

add_executable(
    RuneApplication 
    src/main.cpp
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(EXECUTABLE_OUTPUT_PATH ../../build/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../build/)

add_subdirectory(../RuneFramework ../../config-runefw)

target_include_directories(
    ${PROJECT_NAME} PRIVATE ../RuneFramework/src
    ${PROJECT_NAME} PRIVATE ../RuneFramework/vendor/glad
    ${PROJECT_NAME} PRIVATE ../RuneFramework/vendor/glfw
    ${PROJECT_NAME} PRIVATE ../RuneFramework/vendor/glm/glm
)

target_link_libraries(${PROJECT_NAME} RuneFramework)
