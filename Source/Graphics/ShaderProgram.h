#pragma once

#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>

class ShaderProgram
{
public:
    ShaderProgram();
    ~ShaderProgram();

    void Initialize(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    void SetMatrix4(const std::string& name, const glm::mat4& value) const;
    void Use() const;
    void Unuse() const;

private:
    GLuint m_programHandle;
};