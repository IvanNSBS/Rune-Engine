cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_STANDARD 17)
project(RuneFramework VERSION 0.1.0)

add_library(
    RuneFramework STATIC
    src/rendering/shaders/shaderprogram.cpp 
    src/rendering/window/window.cpp 
    src/rendering/window/windows/windowswindow.cpp 
    src/rendering/buffers/buffers.cpp 
    src/rendering/buffers/opengl/oglindexbuffer.cpp 
    src/rendering/buffers/opengl/oglvertexbuffer.cpp 
    src/rendering/buffers/opengl/oglvertexlayout.cpp 

    src/application/input/keyboard.cpp 
    src/application/input/inputmanager.cpp 
    src/application/input/windows/windowskeyboard.cpp 
)

add_definitions(-DGLFW_BUILD_DOCS=OFF)

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

target_link_libraries(${PROJECT_NAME} glfw glad glm)
