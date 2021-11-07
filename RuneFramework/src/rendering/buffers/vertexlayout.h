#pragma once

#include <vector>

namespace Rune 
{
    class VertexLayout
    {
    protected:
        std::vector<void*> _layoutData;

    public:
        virtual ~VertexLayout() = 0;
        inline std::vector<void*> GetLayoutData() { return _layoutData; }
        virtual unsigned int GetLayoutSize() const = 0;

        // TODO: Remove count in favor of vec2i, vec3i, etc ?
        virtual void PushInt(unsigned int count) = 0;
        virtual void PushUInt(unsigned int count) = 0;
        virtual void PushFloat(unsigned int count) = 0;
        virtual void PushChar(unsigned int count) = 0;
        virtual void PushUnsignedChar(unsigned int count) = 0;

        static VertexLayout* VertexLayout::Create();
    };
}