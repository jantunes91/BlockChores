#include "MainMenuScene.h"

#include "Engine.h"
#include "Image.h"
#include "Sound.h"
#include "Button.h"

MainMenuScene::MainMenuScene(std::shared_ptr<Engine> engine) : Scene(engine)
{
	_backgroundImg = std::make_unique<SDL::Image>(_engine, "Assets/Images/menuBackground.png");

	_playButton = std::make_unique<Button>(_engine, "Assets/Images/playButton.png");
	_playButton->SetPosition(0, _engine->Height() - _playButton->Height() - 20);
	_playButton->CenterHorizontally(_engine->Width());

	_introSound = std::make_unique<SDL::Sound>("Assets/Sounds/intro.wav");
	_introSound->Play();
}

MainMenuScene::~MainMenuScene() = default;

void MainMenuScene::Update() { }

void MainMenuScene::Draw()
{
	_backgroundImg->Draw(0, 0, 1);
	_playButton->Draw();
}

void MainMenuScene::MouseButtonDown(Uint8 button)
{
	if (button == SDL_BUTTON_LEFT)
	{
		int y = _engine->MouseY();
		int x = _engine->MouseX();

		if (_playButton->IsInside(x, y))
		{
			// Starts the game
			_engine->SwitchScene(Engine::SceneId::Game);
		}
	}
}
