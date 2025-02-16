#include "Game.h"

#include "Constants.h"
#include "Scene/Scenes/GameplayScene.h"

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

	// Set up input callbacks
	glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		
	});

	// Framebuffer size callback
	glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	});

    // Setup viewport and enable depth testing
    glfwSwapInterval(1);
    glViewport(0, 0, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);
    glEnable(GL_DEPTH_TEST);

	// Initialize the scene manager and start the game
	m_sceneManager.ChangeScene(std::make_unique<GameplayScene>());

    return true;
}

void Game::Update()
{
    glfwPollEvents();
	m_sceneManager.Update(0.0f);
}

void Game::Render()
{
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_sceneManager.Draw();

    glfwSwapBuffers(m_window);
}

void Game::Shutdown()
{
	m_sceneManager.CleanUp();
    glfwDestroyWindow(m_window);
    glfwTerminate();
}