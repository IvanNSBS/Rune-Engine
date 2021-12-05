#include "../../platformdetector.h"

#include "../rendering/buffers/vertexbuffer.h"
#include "../rendering/buffers/vertexlayout.h"
#include "../rendering/buffers/indexbuffer.h"

#ifdef RUNE_PLATFORM_WINDOWS
    #include "../../platforms/opengl/oglvertexbuffer.h"
    #include "../../platforms/opengl/oglvertexlayout.h"
    #include "../../platforms/opengl/oglindexbuffer.h"
#endif

namespace Rune
{
    VertexBuffer::~VertexBuffer() { }
    VertexBuffer* VertexBuffer::Create()
    {
        #ifdef RUNE_PLATFORM_WINDOWS
            return new OGLVertexBuffer();
        #else
            #error "Platform does not support VertexBuffer!"
            return nullptr;
        #endif
    }

    VertexLayout::~VertexLayout() { }
    VertexLayout* VertexLayout::Create()
    {
        #ifdef RUNE_PLATFORM_WINDOWS
            return new OGLVertexLayout();
        #else
            #error "Platform does not support VertexLayout!"
            return nullptr;
        #endif 
    }

    IndexBuffer::~IndexBuffer() { }
    IndexBuffer* IndexBuffer::Create()
    {
        #ifdef RUNE_PLATFORM_WINDOWS
            return new OGLIndexBuffer();
        #else
            #error "Platform does not support VertexLayout!"
            return nullptr;
        #endif 
    }
};