#include "./oglvertexlayout.h"

namespace Rune
{
    inline OGLDataLayout* OGLVertexLayout::CreateLayout(unsigned int typeSize, GLenum type, unsigned int count)
    {
        OGLDataLayout* layout = new OGLDataLayout();

        layout->type = type;
        layout->typeCount = count;
        layout->normalized = GL_FALSE;
        layout->offset = typeSize*count;

        return layout;
    }

    OGLVertexLayout::~OGLVertexLayout()
    {
        while(!_layoutData.empty())
        {
            delete _layoutData.back();
            _layoutData.pop_back();
        }

        _layoutData.clear();
    }

    unsigned int OGLVertexLayout::GetLayoutSize() const { return _stride; }

    void OGLVertexLayout::PushInt(unsigned int count)
    {	
        unsigned int typeSize = sizeof(GLint);

        _layoutData.push_back((void*)CreateLayout(typeSize, GL_INT, count));
        _stride += typeSize * count;
    }

    void OGLVertexLayout::PushUInt(unsigned int count)
    {
        unsigned int typeSize = sizeof(GLuint);

        _layoutData.push_back((void*)CreateLayout(typeSize, GL_UNSIGNED_INT, count));
        _stride += typeSize * count;
    } 

    void OGLVertexLayout::PushFloat(unsigned int count)
    {
        unsigned int typeSize = sizeof(GLfloat);

        _layoutData.push_back((void*)CreateLayout(typeSize, GL_FLOAT, count));
        _stride += typeSize * count;
    }

    void OGLVertexLayout::PushChar(unsigned int count)
    {
        unsigned int typeSize = sizeof(GLbyte);

        _layoutData.push_back((void*)CreateLayout(typeSize, GL_BYTE, count));
        _stride += typeSize * count;
    }
    
    void OGLVertexLayout::PushUnsignedChar(unsigned int count) { PushChar(count); }
}