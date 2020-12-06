#pragma once

#include <string>
#include <memory>

#include "Window.h"

class Scene;

class Engine : public SDL::Window, public std::enable_shared_from_this<Engine>
{
public:
	enum class SceneId
	{
		None,
		MainMenu,
		Game
	};

	Engine();
	~Engine();

	void Close() override;
	void Update();
	void Draw();

	void Run();

	void MouseButtonDown(Uint8 button);

	void SwitchScene(SceneId sceneID);

private:
	std::unique_ptr<Scene> _currentScene = nullptr;
	SceneId _currentSceneId = SceneId::None;
};
