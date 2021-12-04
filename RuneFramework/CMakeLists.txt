cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_STANDARD 17)
project(RuneFramework VERSION 0.1.0)

add_library(
    RuneFramework STATIC

    src/api/input/keyboard.cpp 
    src/api/input/inputmanager.cpp 

    src/api/rendering/shaders/shaderprogram.cpp 
    src/api/rendering/window/window.cpp 
    src/api/rendering/buffers/buffers.cpp 
    
    src/platforms/windows/input/windowskeyboard.cpp 
    src/platforms/windows/window/windowswindow.cpp

    src/platforms/opengl/oglindexbuffer.cpp 
    src/platforms/opengl/oglvertexbuffer.cpp 
    src/platforms/opengl/oglvertexlayout.cpp 
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
