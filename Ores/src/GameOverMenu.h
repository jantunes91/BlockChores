#pragma once
#include<memory>

namespace SDL
{
	class Text;
	class Image;
}

class Engine;
class Button;

class GameOverMenu
{
public:
	GameOverMenu(std::shared_ptr<Engine> e, int level, int score);
	~GameOverMenu();

	void Draw();

	bool PlayAgainPressed(int mouseX, int mouseY);

private:
	std::unique_ptr<SDL::Image> _backgroundImg = nullptr;
	std::shared_ptr<SDL::Image> _scoreImg = nullptr;
	std::shared_ptr<SDL::Image> _levelImg = nullptr;

	std::unique_ptr<Button> _playAgainButton;

	std::unique_ptr<SDL::Text> _fontUI = nullptr;

	std::shared_ptr<Engine> _engine = nullptr;

	int CenterImgHorizontallyValue(SDL::Image img);
};
