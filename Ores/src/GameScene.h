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
class GameStats;
class GameGrid;
class GameOverMenu;

class GameScene : public Scene {

public:
	GameScene(std::shared_ptr<Engine> engine);
	~GameScene();

	void Update();
	void Draw();

	void MouseButtonDown(Uint8 button);

private:
	std::unique_ptr<SDL::Image> _backgroundImg;

	std::unique_ptr<Button> _pushButton;

	std::unique_ptr<SDL::Sound> _backgroundMusic;

	std::unique_ptr<GameGrid> _gameGrid;
	std::unique_ptr<GameStats> _stats ;
	std::unique_ptr<GameOverMenu> _gameOverMenu;

	int _level;
	int _score;

	int _initialTicks;
	int _pushInterval;

	bool _gameOver;

	void HandleGameState();
	void ShowGameOver();
	void MaybePushGrid();

	int CalculatePushInterval();

	void UpdateScore(int blocksDestroyed);

	void CheckLevelUp();

	int ScoreToLevel();

	int ScoreToLevelUp(int lvl);

	void ResetGame();

	SDL_Point ConvertMousePosIntoGridPos(int x, int y);
};