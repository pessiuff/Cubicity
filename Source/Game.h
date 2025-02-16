#pragma once

#include "Graphics/ShaderProgram.h"
#include "Graphics/Texture2D.h"
#include "Graphics/MultiMesh.h"
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
    Game();
    ~Game() = default;

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    GLFWwindow* m_window;

    ShaderProgram m_shader;
    Texture2D m_texture;
    MultiCubeRenderer m_cubeRenderer;

    bool Initialize();
    void Update();
    void Render();
    void Shutdown();
};