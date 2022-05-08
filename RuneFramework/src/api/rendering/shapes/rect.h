#pragma once

#include "api/rendering/buffers/indexbuffer.h"
#include "api/rendering/buffers/vertexbuffer.h"
#include "./shape.h"

namespace Rune
{
    float uvs[] = {
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f
    };

    unsigned int indices[] = {  
        0, 1, 2,  // first Triangle
        1, 3, 2   // second Triangle
    };

    float vertices[] = {
         0.5f,  0.5f, // top right
         0.5f, -0.5f, // bottom right
        -0.5f, -0.5f, // bottom left
        -0.5f,  0.5f, // top left 
    };

    struct Rect
    {
    private:
    public:
        Rect(float width, float height)
        {
        }

        static Shape* CreateRect(float width, float height) 
        {
            float h = height * 0.5f;
            float w = width * 0.5f;

            float vertices[] = {
                -w,  h, 1.0f, 1.0f, // top-left
                -w, -h, 1.0f, 0.0f, // bottom-left
                 w,  h, 0.0f, 0.0f, // top-right
                 w, -h, 0.0f, 1.0f  // bottom-right
            };

            VertexLayout* l = VertexLayout::Create();
            l->PushFloat(2); 
            l->PushFloat(2); 


            VertexBuffer* vert = VertexBuffer::Create(); 
            IndexBuffer* idxs = IndexBuffer::Create();
            idxs->SetData(indices, sizeof(indices));
            vert->SetData(vertices, sizeof(vertices), l);
            vert->SetIndices(idxs);

            delete l;
            return new Shape(vert, idxs);
        }
    };
}