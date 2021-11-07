#pragma once

#include <glad.h>
#include <vector>
#include "../vertexlayout.h"

namespace Rune
{
	typedef struct
	{
		GLenum type;
		GLsizei typeCount; // size
		GLboolean normalized;
		unsigned int offset;
	} OGLDataLayout;

    class OGLVertexLayout : public VertexLayout
    {
    private:
		unsigned int _stride;

		inline OGLDataLayout CreateLayout(unsigned int typeSize, GLenum type, unsigned int count)
		{
			OGLDataLayout layout;
			layout.type = type;
			layout.typeCount = count;
			layout.normalized = GL_FALSE;
			layout.offset = typeSize*count;

			return layout;
		}

    public:
		virtual unsigned int GetLayoutSize() const override { return _stride; }

        virtual void PushInt(unsigned int count)
		{	
			unsigned int typeSize = sizeof(GLint);
			OGLDataLayout layout = CreateLayout(typeSize, GL_INT, count);

			_layoutData.push_back((void*)&layout);
			_stride += typeSize * count;
		}

        virtual void PushUInt(unsigned int count) override
		{
			unsigned int typeSize = sizeof(GLuint);
			OGLDataLayout layout = CreateLayout(typeSize, GL_UNSIGNED_INT, count);

			_layoutData.push_back((void*)&layout);
			_stride += typeSize * count;
		} 

		virtual void PushFloat(unsigned int count) override
		{
			unsigned int typeSize = sizeof(GLfloat);
			OGLDataLayout layout = CreateLayout(typeSize, GL_FLOAT, count);

			_layoutData.push_back((void*)&layout);
			_stride += typeSize * count;
		}

        virtual void PushChar(unsigned int count) override
		{
			unsigned int typeSize = sizeof(GLbyte);
			OGLDataLayout layout = CreateLayout(typeSize, GL_BYTE, count);

			_layoutData.push_back((void*)&layout);
			_stride += typeSize * count;
		}
		
        virtual void PushUnsignedChar(unsigned int count) override
		{
			PushChar(count);
		}
    };
}