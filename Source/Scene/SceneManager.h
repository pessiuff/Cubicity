#pragma once

#include "Scene.h"
#include <memory>

class SceneManager
{
public:
	SceneManager() = default;
	~SceneManager() = default;

	void ChangeScene(std::unique_ptr<Scene> scene);
	void Update(GLFWwindow* window, float frameTime);
	void Draw();
	void CleanUp();

private:
	std::unique_ptr<Scene> m_currentScene;
};

