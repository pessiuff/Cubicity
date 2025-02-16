#pragma once

class SceneManager;
struct GLFWwindow;

class Scene {
public:
    virtual ~Scene() = default;

    // Called when the scene is initialized
    virtual void Init(SceneManager* sceneManager) = 0;

    // Called every frame to update the logic of the scene
    virtual void Update(GLFWwindow* window, float frameTime) = 0;

    // Called every frame to render the scene
    virtual void Draw() = 0;

    // Called when the scene is being switched out and should clean up resources
    virtual void CleanUp() = 0;
};