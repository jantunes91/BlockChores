#pragma once

#include <memory>

namespace SDL
{
	class Image;
	class Text;
}

class Engine;

class GameStats
{
public:
	GameStats(std::shared_ptr<Engine> engine);
	~GameStats();

	void Draw();

	void UpdateScore(int score);
	void UpdateLevel(int level);

	void UpdateLevelBar(int score, int prevLevelScore, int nextLevelScore);
	void UpdatePushBar(int pushTime, int actualTime);

private:
	std::shared_ptr<SDL::Image> _scoreImg = nullptr;
	std::shared_ptr<SDL::Image> _levelImg = nullptr;
	std::unique_ptr<SDL::Image> _levelBar = nullptr;
	std::unique_ptr<SDL::Image> _pushBar = nullptr;

	std::unique_ptr<SDL::Text> _fontUI = nullptr;

	float _pushBarPercentage = 0.0f;
	float _levelBarPercentage = 0.0f;

	std::shared_ptr<Engine> _engine = nullptr;

};
