#include "shaderprogram.h"

#include "../filesystem/fileloader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <glad.h>

ShaderProgram::ShaderProgram(const char* shaderFilePath) : 
    m_programId(0), m_filePath(shaderFilePath), m_compiled(false) 
{

}

ShaderProgram::~ShaderProgram()
{
    if (m_compiled)
        glDeleteProgram(m_programId);
}

bool ShaderProgram::Compile() 
{
    bool vertexPresent = false;
    bool fragmentPresent = false;

    std::stringstream vShaderStream, fShaderStream;
    std::string line;

    int state = 0; // 0 = both shaders, 1 = vertex, 2 = fragment

    const char* file_bytes = (char*)FileLoader::ReadFile(m_filePath.c_str());
    std::istringstream shaderFile = std::istringstream(file_bytes);

    while (getline(shaderFile, line))
    {
        if (line.find("END_VERTEX") != std::string::npos || line.find("END_FRAG") != std::string::npos) {
            state = 0;
            continue;
        }
        if (line.find("BEGIN_VERTEX") != std::string::npos) {
            if (state != 0) {
                std::cout << "ERROR::SHADER::CANT_BEGIN_VERTEX_WITHOUT_FINISHNG_FRAGMENT\n" << std::endl;
                return m_compiled;
            }

            vertexPresent = true;
            state = 1;
            continue;
        }
        if (line.find("BEGIN_FRAG") != std::string::npos) {
            if (state != 0) {
                std::cout << "ERROR::SHADER::CANT_BEGIN_FRAGMENT_WITHOUT_FINISHNG_VERTEX\n" << std::endl;
                return m_compiled;
            }

            fragmentPresent = true;
            state = 2;
            continue;
        }

        size_t index = 0;
        switch (state)
        {
        case 0:
            vShaderStream << line << '\n';
            fShaderStream << line << '\n';
            break;

        case 1:
            index = line.find("vertMain");
            if (index != std::string::npos)
                line.replace(index, 8, "main");

            vShaderStream << line << '\n';
            break;

        case 2:
            index = line.find("fragMain");
            if (index != std::string::npos)
                line.replace(index, 8, "main");

            fShaderStream << line << '\n';
            break;
        }
    }
    delete file_bytes;
    shaderFile.clear();

    if (!vertexPresent || !fragmentPresent)
    {
        std::cout << "ERROR::SHADER::NEED_BOTH_FRAGMENT_AND_VERTEX_DEFINED\n" << std::endl;
        return m_compiled;
    }

    std::string vertexCode = vShaderStream.str();
    std::string fragmentCode = fShaderStream.str();
    const char* vertexShaderSource = vertexCode.c_str();
    const char* fragmentShaderSource = fragmentCode.c_str();

    unsigned int vertexShader, fragmentShader;

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    bool vertexCompiled = CheckForCompileErrors(vertexShader, 0);
    bool fragmentCompiled = CheckForCompileErrors(fragmentShader, 0);

    if (!vertexCompiled || !fragmentCompiled) 
        return m_compiled;

    m_programId = glCreateProgram();
    glAttachShader(m_programId, vertexShader);
    glAttachShader(m_programId, fragmentShader);
    glLinkProgram(m_programId);

    bool programLinked = CheckForCompileErrors(m_programId, 1);
    if (!programLinked)
        return false;

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    m_compiled = true;
    return m_compiled;
}

bool ShaderProgram::CheckForCompileErrors(const unsigned int shader, unsigned int type) const
{
    int  success;
    char infoLog[512];

    // Vertex and Fragment
    if (type == 0) {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
            glDeleteShader(shader);
            return false;
        }
    }
    else if (type == 1) {
        glGetProgramiv(m_programId, GL_LINK_STATUS, &success);

        if (!success)
        {
            glGetProgramInfoLog(m_programId, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
            glDeleteProgram(m_programId);

            return false;
        }
    }

    return true;
}

void ShaderProgram::Use() 
{ 
    glUseProgram(m_programId); 
}

const int ShaderProgram::GetAndCacheUniform(const std::string& name) 
{
    int uniformLocation = -1;

    if (m_uniformLocations.find(name) != m_uniformLocations.end())
        uniformLocation = m_uniformLocations[name];
    else {
        uniformLocation = glGetUniformLocation(m_programId, name.c_str());
        if(uniformLocation != -1)
            m_uniformLocations[name] = uniformLocation;
    }

    return uniformLocation;
}

void ShaderProgram::setBool(const std::string& name, bool value)
{
    int uniformLocation = GetAndCacheUniform(name);
    glUniform1i(glGetUniformLocation(m_programId, name.c_str()), (int)value);
}

void ShaderProgram::setInt(const std::string& name, int value)
{
    int uniformLocation = GetAndCacheUniform(name);
    glUniform1i(glGetUniformLocation(m_programId, name.c_str()), value);
}

void ShaderProgram::setFloat(const std::string& name, float value) 
{
    int uniformLocation = GetAndCacheUniform(name);
    glUniform1f(uniformLocation, value);
}

void ShaderProgram::SetVec2(const std::string& name, float x, float y)
{
    int uniformLocation = GetAndCacheUniform(name);
    glUniform2f(uniformLocation, x, y);
}

void ShaderProgram::SetVec3(const std::string& name, float x, float y, float z)
{
    int uniformLocation = GetAndCacheUniform(name);
    glUniform3f(uniformLocation, x, y, z);
}

void ShaderProgram::SetVec4(const std::string& name, float x, float y, float z, float w)
{
    int uniformLocation = GetAndCacheUniform(name);
    glUniform4f(uniformLocation, x, y, z, w);
}

void ShaderProgram::SetVec2(const std::string& name, const glm::vec2& value)
{
    int uniformLocation = GetAndCacheUniform(name);
    glUniform2fv(uniformLocation, 1, &value[0]);
}

void ShaderProgram::SetVec3(const std::string& name, const glm::vec3& value)
{
    int uniformLocation = GetAndCacheUniform(name);
    glUniform3fv(uniformLocation, 1, &value[0]);
}

void ShaderProgram::SetVec4(const std::string& name, const glm::vec4& value)
{
    int uniformLocation = GetAndCacheUniform(name);
    glUniform4fv(uniformLocation, 1, &value[0]);
}

void ShaderProgram::SetMat2(const std::string& name, const glm::mat2& mat)
{
    int uniformLocation = GetAndCacheUniform(name);
    glUniformMatrix2fv(uniformLocation, 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::SetMat3(const std::string& name, const glm::mat3& mat)
{
    int uniformLocation = GetAndCacheUniform(name);
    glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::SetMat4(const std::string& name, const glm::mat4& mat)
{
    int uniformLocation = GetAndCacheUniform(name);
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &mat[0][0]);
}