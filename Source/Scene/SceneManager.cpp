#include "SceneManager.h"

void SceneManager::ChangeScene(std::unique_ptr<Scene> scene)
{
    if (m_currentScene)
    {
        m_currentScene->CleanUp();
    }
    m_currentScene = std::move(scene);
    m_currentScene->Init(this);
}

void SceneManager::Update(GLFWwindow* window, float frameTime)
{
    if (m_currentScene)
    {
        m_currentScene->Update(window, frameTime);
    }
}

void SceneManager::Draw()
{
    if (m_currentScene)
    {
        m_currentScene->Draw();
    }
}

void SceneManager::CleanUp()
{
    if (m_currentScene)
    {
        m_currentScene->CleanUp();
    }
}
