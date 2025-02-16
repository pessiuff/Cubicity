#pragma once

#include "Scene/SceneManager.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Game
{
public:
    static Game& GetInstance()
    {
        static Game instance;
        return instance;
    }

    int Run();

private:
    Game() = default;
    ~Game() = default;

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    GLFWwindow* m_window = nullptr;
    SceneManager m_sceneManager = {};
    float m_frameTime = 0;

    bool Initialize();
    void Update();
    void Render();
    void Shutdown();
};