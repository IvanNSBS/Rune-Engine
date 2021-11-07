#include "platformdetector.h"
#ifdef RUNE_PLATFORM_WINDOWS
    #include <glad.h>
    #include <GLFW/glfw3.h>
#endif

#include "application/application.h"
#include "rendering/shaders/shaderprogram.h"
#include "rendering/buffers/vertexbuffer.h"
#include "rendering/buffers/vertexlayout.h"

#include <iostream>