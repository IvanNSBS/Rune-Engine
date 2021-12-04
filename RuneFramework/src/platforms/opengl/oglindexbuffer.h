#pragma once

#include <glad.h>
#include "../../api/rendering/buffers/indexbuffer.h"

namespace Rune
{
    class OGLIndexBuffer : public IndexBuffer
    {
    private:
        unsigned int _bufferId;
        unsigned int _length;

    public:
        OGLIndexBuffer();
        ~OGLIndexBuffer();
        virtual void Bind() override;
        virtual void Unbind() override;
        // TODO: Interface should consider buffer type: e.g: GL_STATIC_DRAW
        virtual void SetData(unsigned int* indices, unsigned int indicesByteSize) override;
        virtual unsigned int Length() const;
    };
}