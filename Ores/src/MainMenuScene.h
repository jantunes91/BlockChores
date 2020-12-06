#pragma once

#include <memory>

#include "Scene.h"

namespace SDL
{
	class Image;
	class Sound;
}

class Engine;
class Button;

class MainMenuScene : public Scene
{
public:
	MainMenuScene(std::shared_ptr<Engine> engine);
	~MainMenuScene();

	void Update();
	void Draw();

	void MouseButtonDown(Uint8 button);

private:
	std::unique_ptr<SDL::Image> _backgroundImg = nullptr;

	std::unique_ptr<Button> _playButton = nullptr;

	std::unique_ptr<SDL::Sound> _introSound = nullptr;
};
