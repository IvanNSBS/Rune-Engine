#pragma once

#include <glad.h>
#include <vector>
#include "../../api/rendering/buffers/vertexlayout.h"

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

		inline OGLDataLayout* CreateLayout(unsigned int typeSize, GLenum type, unsigned int count);
    public:
		~OGLVertexLayout();
		virtual unsigned int GetLayoutSize() const override;
        virtual void PushInt(unsigned int count) override;
        virtual void PushUInt(unsigned int count) override;
		virtual void PushFloat(unsigned int count) override;
        virtual void PushChar(unsigned int count) override;
        virtual void PushUnsignedChar(unsigned int count) override;
    };
}