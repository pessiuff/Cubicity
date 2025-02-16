#include "ShaderProgram.h"

#include "../Utility/FileUtils.h"
#include <iostream>

ShaderProgram::ShaderProgram()
	: m_programHandle(0)
{
}

ShaderProgram::~ShaderProgram()
{
    if (m_programHandle != 0)
    {
        glDeleteProgram(m_programHandle);
    }
}

void ShaderProgram::Initialize(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
    // 1. Read both shader sources
    std::string vertexShaderSource;
    if (!FileUtils::ReadFile(vertexShaderPath, &vertexShaderSource))
    {
        std::cerr << "Failed to read vertex shader file: " << vertexShaderPath << std::endl;
        return;
    }

    std::string fragmentShaderSource;
    if (!FileUtils::ReadFile(fragmentShaderPath, &fragmentShaderSource))
    {
        std::cerr << "Failed to read fragment shader file: " << fragmentShaderPath << std::endl;
        return;
    }

    // 2. Create and compile vertex shader
    GLuint vertexHandle = glCreateShader(GL_VERTEX_SHADER);
    const GLchar* vertexSourceCStr = vertexShaderSource.c_str();
    glShaderSource(vertexHandle, 1, &vertexSourceCStr, nullptr);
    glCompileShader(vertexHandle);

    // 3. Check vertex shader compile status
    GLint compileStatus;
    glGetShaderiv(vertexHandle, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus == GL_FALSE)
    {
        GLint logLength;
        glGetShaderiv(vertexHandle, GL_INFO_LOG_LENGTH, &logLength);
        std::string log(logLength, ' ');
        glGetShaderInfoLog(vertexHandle, logLength, nullptr, &log[0]);
        std::cerr << "Failed to compile vertex shader: " << log << std::endl;
        glDeleteShader(vertexHandle);
        return;
    }

    // 4. Create and compile fragment shader
    GLuint fragmentHandle = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar* fragmentSourceCStr = fragmentShaderSource.c_str();
    glShaderSource(fragmentHandle, 1, &fragmentSourceCStr, nullptr);
    glCompileShader(fragmentHandle);

    // 5. Check fragment shader compile status
    glGetShaderiv(fragmentHandle, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus == GL_FALSE)
    {
        GLint logLength;
        glGetShaderiv(fragmentHandle, GL_INFO_LOG_LENGTH, &logLength);
        std::string log(logLength, ' ');
        glGetShaderInfoLog(fragmentHandle, logLength, nullptr, &log[0]);
        std::cerr << "Failed to compile fragment shader: " << log << std::endl;
        glDeleteShader(vertexHandle);
        glDeleteShader(fragmentHandle);
        return;
    }

    // 6. Link the shader program
    m_programHandle = glCreateProgram();
    glAttachShader(m_programHandle, vertexHandle);
    glAttachShader(m_programHandle, fragmentHandle);
    glLinkProgram(m_programHandle);

    // 7. Check program link status
    GLint linkStatus;
    glGetProgramiv(m_programHandle, GL_LINK_STATUS, &linkStatus);
    if (linkStatus == GL_FALSE)
    {
        GLint logLength;
        glGetProgramiv(m_programHandle, GL_INFO_LOG_LENGTH, &logLength);
        std::string log(logLength, ' ');
        glGetProgramInfoLog(m_programHandle, logLength, nullptr, &log[0]);
        std::cerr << "Failed to link shader program: " << log << std::endl;
        glDeleteShader(vertexHandle);
        glDeleteShader(fragmentHandle);
        glDeleteProgram(m_programHandle);
        m_programHandle = 0;
        return;
    }

    // 8. Clean up shaders, we've linked them
    glDeleteShader(vertexHandle);
    glDeleteShader(fragmentHandle);
}

void ShaderProgram::SetMatrix4(const std::string& name, const glm::mat4& value) const
{
	if (m_programHandle == 0)
	{
		return;
	}

	GLint location = glGetUniformLocation(m_programHandle, name.c_str());
	if (location != -1)
	{
		glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
	}
}

void ShaderProgram::Use() const
{
    if (m_programHandle == 0)
    {
        return;
    }

    glUseProgram(m_programHandle);
}

void ShaderProgram::Unuse() const
{
    glUseProgram(0);
}