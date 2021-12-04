#include "platformdetector.h"
#ifdef RUNE_PLATFORM_WINDOWS
    #include <glad.h>
    #include <GLFW/glfw3.h>
#endif

#include "api/application.h"
#include "api/rendering/shaders/shaderprogram.h"
#include "api/rendering/buffers/vertexbuffer.h"
#include "api/rendering/buffers/vertexlayout.h"
#include "api/rendering/shapes/rect.h"
#include "api/rendering/shapes/shape.h"
#include "api/rendering/cameras/camera.h"
#include "api/rendering/renderer2d.h"

#include <iostream>