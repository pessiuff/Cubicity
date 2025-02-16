#include "MultiMesh.h"

#include "../Constants.h"

MultiCubeRenderer::MultiCubeRenderer(ShaderProgram* shader, Texture2D* m_texture)
    : m_shader(shader)
    , m_texture(m_texture)
    , m_vertexArrayObject(0)
    , m_vertexBufferObject(0)
    , m_elementBufferObject(0)
    , m_positionBufferObject(0)
    , m_dirty(false)
{
}

MultiCubeRenderer::~MultiCubeRenderer()
{
    // Clean up the allocated buffers and VAO.
    glDeleteBuffers(1, &m_vertexBufferObject);
    glDeleteBuffers(1, &m_elementBufferObject);
    glDeleteBuffers(1, &m_positionBufferObject);
    glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void MultiCubeRenderer::Initialize()
{
    // Create and bind a Vertex Array Object.
    glGenVertexArrays(1, &m_vertexArrayObject);
    glBindVertexArray(m_vertexArrayObject);

    // Create and bind the Vertex Buffer Object.
    glGenBuffers(1, &m_vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(CUBE_VERTICES), CUBE_VERTICES, GL_STATIC_DRAW);

    // Create and bind the Element Buffer Object.
    // The EBO binding is stored inside the VAO, so we keep it bound.
    glGenBuffers(1, &m_elementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(CUBE_INDICES), CUBE_INDICES, GL_STATIC_DRAW);

    // Set up the vertex attribute pointers.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    // Create and bind the Position Buffer Object.
    glGenBuffers(1, &m_positionBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, m_positionBufferObject);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);

    // Set up the instance attribute pointers.
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribDivisor(1, 1);

    // It's safe to unbind the array buffer now; the EBO remains associated with the VAO.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void MultiCubeRenderer::AddCube(const glm::vec3& position)
{
    m_positions.push_back(position);
    m_dirty = true;
}

void MultiCubeRenderer::Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
    // Update the instance buffer if necessary.
    UpdateInstanceBuffer();

    // Bind the shader and texture.
    m_shader->Use();
    // m_texture->Bind(); // Uncomment when Texture2D provides a Bind method.

    m_shader->SetMatrix4("u_ViewProjection", projectionMatrix * viewMatrix);

    // Bind the VAO which already includes the EBO binding.
    glBindVertexArray(m_vertexArrayObject);

    // Draw all instances using instanced rendering.
    glDrawElementsInstanced(GL_TRIANGLES, sizeof(CUBE_INDICES) / sizeof(CUBE_INDICES[0]), GL_UNSIGNED_INT, nullptr, m_positions.size());

    // Unbind the VAO and shader.
    glBindVertexArray(0);
    m_shader->Unuse();
	// m_texture->Unbind(); // Uncomment when Texture2D provides an Unbind method.
}

void MultiCubeRenderer::UpdateInstanceBuffer()
{
    if (!m_dirty)
    {
        return;
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_positionBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_positions.size(), m_positions.data(), GL_DYNAMIC_DRAW);
    m_dirty = false;
}