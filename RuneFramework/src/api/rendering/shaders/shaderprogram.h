#pragma once

#include <string>
#include <unordered_map>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/glm.hpp>

namespace Rune
{
    class ShaderProgram
    {
    public:
        static ShaderProgram* Load(const char* shaderFilePath);
        virtual ~ShaderProgram() = 0;
        virtual void Use() = 0;

        virtual bool Compile() = 0;
        virtual void setInt(const std::string& name, int value) = 0;
        virtual void setBool(const std::string& name, bool value) = 0;
        virtual void setFloat(const std::string& name, float value) = 0;

        virtual void SetVec2(const std::string& name, float x, float y) = 0;
        virtual void SetVec3(const std::string& name, float x, float y, float z) = 0;
        virtual void SetVec4(const std::string& name, float x, float y, float z, float w) = 0;

        virtual void SetVec2(const std::string& name, const glm::vec2& value) = 0;
        virtual void SetVec3(const std::string& name, const glm::vec3& value) = 0;
        virtual void SetVec4(const std::string& name, const glm::vec4& value) = 0;

        virtual void SetMat2(const std::string& name, const glm::mat2& mat) = 0;
        virtual void SetMat3(const std::string& name, const glm::mat3& mat) = 0;
        virtual void SetMat4(const std::string& name, const glm::mat4& mat) = 0;
    };
}