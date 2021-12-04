#pragma once

#include <glad.h>
#include "./oglvertexlayout.h"
#include "../../api/rendering/buffers/vertexbuffer.h"
#include "../../api/rendering/buffers/indexbuffer.h"

#include <iostream>

namespace Rune
{
    class OGLVertexBuffer : public VertexBuffer
    {
    private:
        unsigned int _vboBufferId;
        unsigned int _vaoBufferId;
        IndexBuffer* _index;

    public:
        OGLVertexBuffer();
        ~OGLVertexBuffer();
        virtual void Bind() override;
        virtual void Unbind() override;
        // TODO: Interface should consider buffer type: e.g: GL_STATIC_DRAW
        virtual void SetData(const void* data, unsigned int dataByteSize, VertexLayout* layout) override;
        virtual void SetIndices(IndexBuffer* index) override;
        virtual inline IndexBuffer* GetIndices() const override;
        virtual inline bool HasIndices() const override;
    };
}