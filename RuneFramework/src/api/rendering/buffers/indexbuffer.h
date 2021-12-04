#pragma once

namespace Rune 
{
    class IndexBuffer 
    {
    public:
        virtual ~IndexBuffer() = 0;
        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual void SetData(unsigned int* indices, unsigned int indicesByteSize) = 0;
        virtual unsigned int Length() const = 0;
    
        static IndexBuffer* Create();
    };
}