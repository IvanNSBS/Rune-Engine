#include "../../platformdetector.h"

#include "./vertexbuffer.h"
#include "./vertexlayout.h"
#include "./indexbuffer.h"

#ifdef RUNE_PLATFORM_WINDOWS
    #include "./opengl/oglvertexbuffer.h"
    #include "./opengl/oglvertexlayout.h"
    #include "./opengl/oglindexbuffer.h"
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