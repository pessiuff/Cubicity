#include "Game.h"

#include "Constants.h"

Game::Game()
    : m_window(nullptr)
    , m_shader()
    , m_texture()
    , m_cubeRenderer(&m_shader, &m_texture)
{
}

int Game::Run()
{
    if (!Initialize())
        return 1;

    while (!glfwWindowShouldClose(m_window))
    {
        Update();
        Render();
    }

    Shutdown();
    return 0;
}

bool Game::Initialize()
{
    // Initialize GLFW
    if (!glfwInit())
        return false;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create the window
    m_window = glfwCreateWindow(VIEWPORT_WIDTH, VIEWPORT_HEIGHT, WINDOW_TITLE, nullptr, nullptr);
    if (!m_window)
    {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_window);

    // Load OpenGL functions
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwDestroyWindow(m_window);
        glfwTerminate();
        return false;
    }

    // Setup viewport and enable depth testing
    glfwSwapInterval(1);
    glViewport(0, 0, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);
    glEnable(GL_DEPTH_TEST);

    // Initialize shader and cube renderer
    m_shader.Initialize("shaders/default_cube.vert", "shaders/default_cube.frag");
    m_cubeRenderer.Initialize();

    // Add cubes spread over the XZ-plane
    for (int i = 0; i < 256; i += 2)
    {
        for (int j = 0; j < 256; j += 2)
        {
            m_cubeRenderer.AddCube(glm::vec3(i, 0, j)); // Spread in XZ-plane
        }
    }

    return true;
}

void Game::Update()
{
    glfwPollEvents();
}

void Game::Render()
{
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_cubeRenderer.Render();

    glfwSwapBuffers(m_window);
}

void Game::Shutdown()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}