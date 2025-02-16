#include "GameplayScene.h"

#include <glm/gtc/matrix_transform.hpp>
#include "../../Constants.h"
#include <GLFW/glfw3.h>

GameplayScene::GameplayScene()
    : m_shader(), m_texture(), m_cubeRenderer(&m_shader, &m_texture), m_viewMatrix(), m_projectionMatrix()
{
    m_cameraPos = glm::vec3(0.0f, 0.0f, 10.0f);
    m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    m_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

void GameplayScene::Init(SceneManager* sceneManager)
{
    m_sceneManager = sceneManager;

    m_shader.Initialize("shaders/default_cube.vert", "shaders/default_cube.frag");
    m_texture.Load("textures/wooden_crate.jpg");
    m_cubeRenderer.Initialize();

    for (int x = 0; x < 1024 * 2; x += 2)
    {
        for (int z = 0; z < 1024 * 2; z += 2)
        {
            m_cubeRenderer.AddCube(glm::vec3(x, 0, z));
        }
    }

    m_viewMatrix = glm::lookAt(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    m_projectionMatrix = glm::perspective(glm::radians(90.0f), (float) VIEWPORT_WIDTH / VIEWPORT_HEIGHT, 0.1f, 100.0f);
}

void GameplayScene::Update(GLFWwindow* window, float frameTime)
{
    // Camera movement
    float velocity = m_cameraSpeed * frameTime;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        m_cameraPos += m_cameraFront * velocity;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        m_cameraPos -= m_cameraFront * velocity;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        m_cameraPos -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * velocity;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        m_cameraPos += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * velocity;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        m_cameraPos += m_cameraUp * velocity;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        m_cameraPos -= m_cameraUp * velocity;

    // Camera rotation
    float rotationSpeed = 50.0f * frameTime;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        m_pitch += rotationSpeed;
        m_pitch = glm::clamp(m_pitch, -89.0f, 89.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        m_pitch -= rotationSpeed;
        m_pitch = glm::clamp(m_pitch, -89.0f, 89.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        m_yaw -= rotationSpeed;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        m_yaw += rotationSpeed;

    // Update camera vectors
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_cameraFront = glm::normalize(front);

    // Update view matrix
    m_viewMatrix = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
}

void GameplayScene::Draw()
{
    m_cubeRenderer.Render(m_viewMatrix, m_projectionMatrix);
}

void GameplayScene::CleanUp()
{
}
