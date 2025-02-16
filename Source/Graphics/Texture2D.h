#pragma once

#include <glad/glad.h>
#include <string>

class Texture2D
{
public:
	Texture2D() = default;
	~Texture2D() = default;

	void Load(const std::string& path);
	void Bind() const;
	void Unbind() const;

private:
	GLuint m_handle = 0;
	int m_width = 0;
	int m_height = 0;
	int m_channels = 0;
};
