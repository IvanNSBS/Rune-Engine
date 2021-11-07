#pragma once

#include <glad.h>
#include "./oglvertexlayout.h"
#include "../indexbuffer.h"
#include "../vertexbuffer.h"

namespace Rune
{
    class OGLVertexBuffer : public VertexBuffer
    {
    private:
        unsigned int _vboBufferId;
        unsigned int _vaoBufferId;
        IndexBuffer* _index;

    public:
        OGLVertexBuffer()
        {
            _index = nullptr;
            glGenBuffers(1, &_vboBufferId);
            glGenVertexArrays(1, &_vaoBufferId);
        }

        virtual ~OGLVertexBuffer()
        {
            glDeleteBuffers(1, &_vboBufferId);
            glDeleteVertexArrays(1, &_vaoBufferId);
        }

        virtual void Bind() override
        {
            glBindVertexArray(_vaoBufferId);
            glBindBuffer(GL_ARRAY_BUFFER, _vboBufferId);
            if(HasIndices())
                _index->Bind();
        }

        virtual void Unbind() override
        {
            glBindVertexArray(0);
		    glBindBuffer(GL_ARRAY_BUFFER, 0);
            if(HasIndices())
                _index->Unbind();
        }

        // TODO: Interface should consider buffer type: e.g: GL_STATIC_DRAW
        virtual void SetData(const void* data, unsigned int dataByteSize, VertexLayout* layout) override
        {
            this->Bind();
            glBufferData(GL_ARRAY_BUFFER, dataByteSize, data, GL_STATIC_DRAW);

            auto layoutData = layout->GetLayoutData();
            auto stride = layout->GetLayoutSize();
            unsigned int offset = 0;

            for(int i = 0; i < layoutData.size(); i++)
            {
                OGLDataLayout data = reinterpret_cast<OGLDataLayout&>(layoutData[i]);

                glVertexAttribPointer(i, data.typeCount, data.type, data.normalized, stride, (void*)(uintptr_t)offset);
                glEnableVertexAttribArray(i);
                offset += data.offset;
            }
        }

        virtual void SetIndices(IndexBuffer* index) override
        {
            Bind();
            index->Bind();
            _index = index;
        }

        virtual inline IndexBuffer* GetIndices() const override
        {
            return _index;
        }

        virtual inline bool HasIndices() const override { return _index != nullptr; }
    };
}