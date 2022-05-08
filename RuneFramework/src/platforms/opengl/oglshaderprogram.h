#pragma once

#include "api/rendering/shaders/shaderprogram.h"

namespace Rune
{
    class OGLShaderProgram : public ShaderProgram
    {
    private:
        unsigned int m_programId;
        bool m_compiled;
        std::string m_filePath;
        std::unordered_map<std::string, int> m_uniformLocations;

        bool CheckForCompileErrors(const unsigned int shader, unsigned int type) const;
        const int GetAndCacheUniform(const std::string& name);
    public:
        OGLShaderProgram(const char* shaderFilePath);
        ~OGLShaderProgram();
        void Use();

        virtual bool Compile();
        virtual void setInt(const std::string& name, int value) override;
        virtual void setBool(const std::string& name, bool value) override;
        virtual void setFloat(const std::string& name, float value) override;

        virtual void SetVec2(const std::string& name, float x, float y) override ;
        virtual void SetVec3(const std::string& name, float x, float y, float z) override;
        virtual void SetVec4(const std::string& name, float x, float y, float z, float w) override;

        virtual void SetVec2(const std::string& name, const glm::vec2& value) override;
        virtual void SetVec3(const std::string& name, const glm::vec3& value) override;
        virtual void SetVec4(const std::string& name, const glm::vec4& value) override;

        virtual void SetMat2(const std::string& name, const glm::mat2& mat) override;
        virtual void SetMat3(const std::string& name, const glm::mat3& mat) override;
        virtual void SetMat4(const std::string& name, const glm::mat4& mat) override;
    };
}