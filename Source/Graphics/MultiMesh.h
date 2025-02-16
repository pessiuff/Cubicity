#pragma once

#include "ShaderProgram.h"
#include "Texture2D.h"
#include <vector>
#include <glm/glm.hpp>

class MultiCubeRenderer
{
public:
    MultiCubeRenderer(ShaderProgram* shader, Texture2D* m_texture);
    ~MultiCubeRenderer();

    void Initialize();
    void AddCube(const glm::vec3& position);
    void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);

private:
    ShaderProgram* m_shader;
    Texture2D* m_texture;
    GLuint m_vertexArrayObject, m_vertexBufferObject, m_positionBufferObject, m_textureCoordinateBufferObject, m_elementBufferObject;
    bool m_dirty;
    std::vector<glm::vec3> m_positions;

    void UpdateInstanceBuffer();
};