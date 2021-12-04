#pragma once

#include "./vertexlayout.h"
#include "./indexbuffer.h"

namespace Rune 
{
    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() = 0;
        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void SetData(const void* data, unsigned int dataByteSize, VertexLayout* layout) = 0;
        virtual void SetIndices(IndexBuffer* index) = 0;
        virtual bool HasIndices() const = 0;
        virtual IndexBuffer* GetIndices() const = 0;

        static VertexBuffer* Create();
    };
}