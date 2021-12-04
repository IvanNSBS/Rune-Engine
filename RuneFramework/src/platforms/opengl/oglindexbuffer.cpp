#include "./oglindexbuffer.h"
#include "../../api/rendering/buffers/vertexbuffer.h"

namespace Rune
{
    OGLIndexBuffer::OGLIndexBuffer()
    {
        _length = 0;
        glGenBuffers(1, &_bufferId);
    }

    OGLIndexBuffer::~OGLIndexBuffer()
    {
        glDeleteBuffers(1, &_bufferId);
    }

    void OGLIndexBuffer::Bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _bufferId);
    }

    void OGLIndexBuffer::Unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    // TODO: Interface should consider buffer type: e.g: GL_STATIC_DRAW
    void OGLIndexBuffer::SetData(unsigned int* indices, unsigned int indicesByteSize)
    {
        // buf->Bind();
        // buf->SetIndices(this);

        this->Bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesByteSize, indices, GL_STATIC_DRAW);
        _length = indicesByteSize/sizeof(unsigned int);
    }

    unsigned int OGLIndexBuffer::Length() const
    {
        return _length;
    };
}