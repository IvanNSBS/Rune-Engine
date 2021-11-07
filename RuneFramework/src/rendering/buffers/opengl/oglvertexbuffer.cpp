#include "./oglvertexbuffer.h"

namespace Rune
{
        OGLVertexBuffer::OGLVertexBuffer()
        {
            _index = nullptr;
            glGenBuffers(1, &_vboBufferId);
            glGenVertexArrays(1, &_vaoBufferId);
        }

        OGLVertexBuffer::~OGLVertexBuffer()
        {
            glDeleteBuffers(1, &_vboBufferId);
            glDeleteVertexArrays(1, &_vaoBufferId);
        }

        void OGLVertexBuffer::Bind()
        {
            glBindVertexArray(_vaoBufferId);
            if(HasIndices())
                _index->Bind();
        }

        void OGLVertexBuffer::Unbind()
        {
            glBindVertexArray(0);
            if(HasIndices())
                _index->Unbind();
        }

        // TODO: Interface should consider buffer type: e.g: GL_STATIC_DRAW
        void OGLVertexBuffer::SetData(const void* data, unsigned int dataByteSize, VertexLayout* layout)
        {
            Bind();
            glBindBuffer(GL_ARRAY_BUFFER, _vboBufferId);
            glBufferData(GL_ARRAY_BUFFER, dataByteSize, data, GL_STATIC_DRAW);

            auto layoutData = layout->GetLayoutData();
            auto stride = layout->GetLayoutSize();
            unsigned int offset = 0;

            for(int i = 0; i < layoutData.size(); i++)
            {
                OGLDataLayout* element = reinterpret_cast<OGLDataLayout*>(layoutData[i]);

                glVertexAttribPointer(i, element->typeCount, element->type, element->normalized, stride, (void*)(uintptr_t)offset);
                glEnableVertexAttribArray(i);
                offset += element->offset;
            }

            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        void OGLVertexBuffer::SetIndices(IndexBuffer* index) { _index = index; }
        inline IndexBuffer* OGLVertexBuffer::GetIndices() const { return _index; }
        inline bool OGLVertexBuffer::HasIndices() const { return _index != nullptr; }
}