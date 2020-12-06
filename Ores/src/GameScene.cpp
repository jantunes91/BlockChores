#include "GameScene.h"
#include "Engine.h"
#include "Image.h"
#include "Sound.h"
#include "Button.h"

#include "GameStats.h"
#include "GameGrid.h"
#include "GameOverMenu.h"

#include <iostream>

static const int k_blockValue = 15;

GameScene::GameScene(std::shared_ptr<Engine> engine):Scene(engine)
{
	_backgroundImg = std::make_unique<SDL::Image>(_engine, "Assets/Images/gameBackground.png");

	_pushButton = std::make_unique<Button>(_engine, "Assets/Images/pushButton.png");
	_pushButton->SetPosition(720, 530);

	_backgroundMusic = std::make_unique<SDL::Sound>("Assets/Sounds/background.mp3");
	_backgroundMusic->Play(0.4,true);

	_gameGrid = std::make_unique<GameGrid>(_engine);
	_stats = std::make_unique<GameStats>(_engine);

	_level = 1;
	_score = 0;
	_initialTicks = SDL_GetTicks();
	_pushInterval = CalculatePushInterval();
	_gameOver = false;
}

GameScene::~GameScene() = default;

void GameScene::Update()
{
	_gameGrid->Update();

	//The only thing we let update in a game over state is the game grid
	//so any pending animation can finish
	if (_gameOver)
	{
		return;
	}

	HandleGameState();
}

void GameScene::HandleGameState()
{
	GameGrid::GameState gState = _gameGrid->State();

	//Only count the next push after the level up sequence is done
	if (gState == GameGrid::GameState::LevelUp || gState == GameGrid::GameState::GenerateGrid)
	{
		_initialTicks = SDL_GetTicks();
		return;
	}

	if (gState == GameGrid::GameState::GameOver)
	{
		ShowGameOver();
	}
	else
	{
		MaybePushGrid();
	}
}

void GameScene::MaybePushGrid()
{
	int currentTicks = SDL_GetTicks();
	if (currentTicks - _initialTicks >= _pushInterval)
	{
		_initialTicks = currentTicks;
		_gameGrid->Push();
	}
	_stats->UpdatePushBar(_pushInterval, currentTicks - _initialTicks);
}

void GameScene::ShowGameOver()
{
	_gameOver = true;
	_gameOverMenu.reset();
	_gameOverMenu = std::make_unique<GameOverMenu>(_engine, _level, _score);
}

void GameScene::Draw()
{
	_backgroundImg->Draw(0, 0, 1);

	_pushButton->Draw();

	_gameGrid->Draw();
	_stats->Draw();

	if (_gameOver)
	{
		_gameOverMenu->Draw();
	}
}

void GameScene::MouseButtonDown(Uint8 button)
{
	GameGrid::GameState gstate = _gameGrid->State();

	//Only handle input when the game is Idle or
	//in the Game Over Menu
	if (gstate != GameGrid::GameState::Idle && gstate != GameGrid::GameState::GameOver)
	{
		return;
	}

	if (button == SDL_BUTTON_LEFT)
	{
		int y = _engine->MouseY();
		int x = _engine->MouseX();

		if (_gameOver && _gameOverMenu->PlayAgainPressed(x, y))
		{
			ResetGame();
			return;
		}

		if (_pushButton->IsInside(x,y))
		{
			_gameGrid->Push();
			_initialTicks = SDL_GetTicks();
			return;
		}

		SDL_Point arrayPos = ConvertMousePosIntoGridPos(x, y);

		//Check if the press was on the game board
		if (arrayPos.x >= 0 && arrayPos.x < k_boardWidth && arrayPos.y >= 0 && arrayPos.y < k_boardHeight)
		{
			int blocksDestroyed = _gameGrid->HandleBlockClick(arrayPos.x, arrayPos.y);

			if (blocksDestroyed != 0)
			{
				UpdateScore(blocksDestroyed);
			}
		}

	}
}

SDL_Point GameScene::ConvertMousePosIntoGridPos(int x, int y)
{
	SDL_Point result = { 0,0 };
	int resultX = (x - k_gameDrawOffsetX) / k_blockDrawSize;	
	int resultY = (y - k_gameDrawOffsetY) / k_blockDrawSize;
	result = { resultX, resultY };

	return result;
}

int GameScene::CalculatePushInterval()
{
	return 9000 - 100 * (_level - 1);
}

void GameScene::UpdateScore(int blocksDestroyed)
{
	_score += blocksDestroyed * k_blockValue * _level;
	CheckLevelUp();

	//Update the stats on screen
	_stats->UpdateScore(_score);
	_stats->UpdateLevelBar(_score, ScoreToLevelUp(_level - 1), ScoreToLevelUp(_level));
}

void GameScene::CheckLevelUp()
{
	if (ScoreToLevel() > _level)
	{
		_level++;
		CalculatePushInterval();
		_initialTicks = SDL_GetTicks();

		_gameGrid->LevelUp();
		_stats->UpdateLevel(_level);
	}
}

int GameScene::ScoreToLevel()
{
	//Calculate actual score needed to level up
	int toLevelUp = ScoreToLevelUp(_level);

	if (toLevelUp <= _score) {
		return _level + 1;
	}

	return _level;
}

int GameScene::ScoreToLevelUp(int lvl)
{
	switch (lvl)
	{
	case 0:
		return 0;
		break;
	case 1:
		return 600;
		break;
	default:
		return ((lvl + 1) * k_blockValue) * (lvl - 1) * 100;
		break;
	}
}

void GameScene::ResetGame()
{
	//Set the initial score and level values
	_level = 1;
	_score = 0;
	
	//Calculate the new push interval and reset the push counter
	_initialTicks = SDL_GetTicks();
	_pushInterval = CalculatePushInterval();

	_gameOver = false;

	//Reset the game
	_gameGrid->Reset();

	//Update the stats
	_stats->UpdateLevel(_level);
	_stats->UpdateScore(_score);
}


