#pragma once

#include <glad.h>
#include "../indexbuffer.h"

namespace Rune
{
    class OGLIndexBuffer : public IndexBuffer
    {
    private:
        unsigned int _bufferId;
        unsigned int _length;

    public:
        OGLIndexBuffer()
        {
            _length = 0;
            glGenBuffers(1, &_bufferId);
        }

        virtual ~OGLIndexBuffer()
        {
            glDeleteBuffers(1, &_bufferId);
        }

        virtual void Bind() override
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _bufferId);
        }

        virtual void Unbind() override
        {
		    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        // TODO: Interface should consider buffer type: e.g: GL_STATIC_DRAW
        virtual void SetData(unsigned int* indices, unsigned int indicesByteSize) override
        {
            this->Bind();
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesByteSize, indices, GL_STATIC_DRAW);
            _length = indicesByteSize/sizeof(unsigned int);
        }

        virtual unsigned int Length() const
        {
            return _length;
        };
    };
}