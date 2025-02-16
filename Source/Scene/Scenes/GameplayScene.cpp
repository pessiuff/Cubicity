#include "GameplayScene.h"

GameplayScene::GameplayScene()
	: m_shader(), m_texture(), m_cubeRenderer(&m_shader, &m_texture)
{
}

void GameplayScene::Init(SceneManager* sceneManager)
{
	m_sceneManager = sceneManager;

	m_shader.Initialize("shaders/default_cube.vert", "shaders/default_cube.frag");
	// m_texture.Initialize("textures/wooden_crate.jpg");
	m_cubeRenderer.Initialize();

	for (int x = 0; x < 10; x += 2)
	{
		for (int z = 0; z < 10; z += 2)
		{
			m_cubeRenderer.AddCube(glm::vec3(x, 0, z));
		}
	}
}

void GameplayScene::Update(float frameTime)
{

}

void GameplayScene::Draw()
{
	m_cubeRenderer.Render();
}

void GameplayScene::CleanUp()
{
}
