#pragma once

#include "../Scene.h"
#include "../SceneManager.h"
#include "../../Graphics/ShaderProgram.h"
#include "../../Graphics/MultiMesh.h"
#include "../../Graphics/Texture2D.h"

class GameplayScene : public Scene
{
public:
    GameplayScene();
    ~GameplayScene() = default;

    void Init(SceneManager* sceneManager) override;
    void Update(GLFWwindow* window, float deltaTime) override;
    void Draw() override;
    void CleanUp() override;

private:
    SceneManager* m_sceneManager = nullptr;

    ShaderProgram m_shader;
    Texture2D m_texture;
    MultiCubeRenderer m_cubeRenderer;

    glm::mat4 m_viewMatrix;
    glm::mat4 m_projectionMatrix;

    glm::vec3 m_cameraPos;
    glm::vec3 m_cameraFront;
    glm::vec3 m_cameraUp;
    float m_yaw = -90.0f;   // Initial yaw (faces -Z)
    float m_pitch = 0.0f;
    float m_cameraSpeed = 5.0f;
    float m_sensitivity = 0.1f;
};
