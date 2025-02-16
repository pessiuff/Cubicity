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
    void Update(float deltaTime) override;
    void Draw() override;
    void CleanUp() override;

private:
	SceneManager* m_sceneManager = nullptr;
	ShaderProgram m_shader;
	Texture2D m_texture;
	MultiCubeRenderer m_cubeRenderer;
};
