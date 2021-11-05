#include <string>
#include <unordered_map>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/glm.hpp>

class ShaderProgram
{
private:
    unsigned int m_programId;
    bool m_compiled;
    std::string m_filePath;
    std::unordered_map<std::string, int> m_uniformLocations;

    bool CheckForCompileErrors(const unsigned int shader, unsigned int type) const;
    const int GetAndCacheUniform(const std::string& name);
public:
    ShaderProgram(const char* shaderFilePath);
    ~ShaderProgram();
    void Use();

    bool Compile();
    void setInt(const std::string& name, int value);
    void setBool(const std::string& name, bool value);
    void setFloat(const std::string& name, float value);

    void SetVec2(const std::string& name, float x, float y);
    void SetVec3(const std::string& name, float x, float y, float z);
    void SetVec4(const std::string& name, float x, float y, float z, float w);

    void SetVec2(const std::string& name, const glm::vec2& value);
    void SetVec3(const std::string& name, const glm::vec3& value);
    void SetVec4(const std::string& name, const glm::vec4& value);

    void SetMat2(const std::string& name, const glm::mat2& mat);
    void SetMat3(const std::string& name, const glm::mat3& mat);
    void SetMat4(const std::string& name, const glm::mat4& mat);
};