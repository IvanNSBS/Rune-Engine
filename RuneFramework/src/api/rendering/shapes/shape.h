#pragma once

#include "../buffers/indexbuffer.h"
#include "../buffers/vertexbuffer.h"

namespace Rune
{
    struct Shape
    {
    public:
        VertexBuffer* vertices;
        IndexBuffer* indices;

        Shape() {}
        ~Shape(){
            delete vertices;
            delete indices;
        }
        Shape(VertexBuffer* verts, IndexBuffer* idxs): vertices(verts), indices(idxs) {}
    };
}