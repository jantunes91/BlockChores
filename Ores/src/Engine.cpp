#include "Engine.h"
#include "Scene.h"

#include "MainMenuScene.h"
#include "GameScene.h"

static const int k_windowWidth = 800;
static const int k_windowHeight = 600;

Engine::Engine() : SDL::Window(k_windowWidth, k_windowHeight, "Block Chores") {};

Engine::~Engine() = default;

void Engine::Close()
{
	Window::Close();
	_currentScene.reset();
}

void Engine::Update()
{
	if (_currentScene != nullptr)
	{
		_currentScene->Update();
	}
}

void Engine::Draw()
{
	if (_currentScene != nullptr)
	{
		_currentScene->Draw();
	}
}

void Engine::Run()
{
	SwitchScene(SceneId::MainMenu);
	Show();
}

void Engine::MouseButtonDown(Uint8 button)
{
	if (_currentScene != nullptr)
	{
		_currentScene->MouseButtonDown(button);
	}
}

void Engine::SwitchScene(SceneId sceneId)
{
	if (sceneId != _currentSceneId)
	{
		auto const wptr = std::shared_ptr<Engine>(this, [](Engine*) {});

		switch (sceneId)
		{
		case SceneId::MainMenu:
			_currentScene = std::make_unique<MainMenuScene>(shared_from_this());
			_currentSceneId = sceneId;
			break;
		case SceneId::Game:
			_currentScene = std::make_unique<GameScene>(shared_from_this());
			_currentSceneId = sceneId;
			break;
		default:
			break;
		}
	}
}
