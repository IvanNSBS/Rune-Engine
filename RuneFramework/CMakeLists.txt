cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_STANDARD 17)
project(RuneFramework VERSION 0.1.0)

add_executable(
    RuneFramework 
    src/main.cpp 
    src/rendering/shaders/shaderprogram.cpp 
    src/rendering/window/window.cpp 
    src/rendering/window/windows/windowswindow.cpp 

    src/application/input/keyboard.cpp 
    src/application/input/windows/windowskeyboard.cpp 
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(EXECUTABLE_OUTPUT_PATH ../../build/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../build/)

add_subdirectory(vendor/glad)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glm)

target_include_directories(
    ${PROJECT_NAME} PRIVATE vendor/glad
    ${PROJECT_NAME} PRIVATE vendor/glfw
    ${PROJECT_NAME} PRIVATE vendor/glm/glm
)

target_link_directories(
    ${PROJECT_NAME} PRIVATE libtest
    ${PROJECT_NAME} PRIVATE newlib
)

target_link_libraries(${PROJECT_NAME} glfw glad glm)
