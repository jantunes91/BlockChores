#include "GameOverMenu.h"
#include "Engine.h"
#include "Image.h"
#include "Text.h"
#include "Button.h"

GameOverMenu::GameOverMenu(std::shared_ptr<Engine> engine, int level, int score)
{
	_engine = engine;

	_backgroundImg = std::make_unique<SDL::Image>(_engine, "Assets/Images/gameOverMenu.png");

	_playAgainButton = std::make_unique<Button>(_engine, "Assets/Images/playAgainButton.png");
	_playAgainButton->SetPosition(0, 394);
	_playAgainButton->CenterHorizontally(_engine->Width());

	_fontUI = std::make_unique<SDL::Text>(_engine, "Assets/Fonts/smallfont.ttf", 36);

	_scoreImg = _fontUI->RenderText(std::to_string(score), { 0, 0, 0, 255 });
	_levelImg = _fontUI->RenderText(std::to_string(level), { 0, 0, 0, 255 });
}

GameOverMenu::~GameOverMenu() = default;

void GameOverMenu::Draw()
{
	_backgroundImg->Draw(CenterImgHorizontallyValue(*_backgroundImg), 145, 1);
	_playAgainButton->Draw();
	_scoreImg->Draw(CenterImgHorizontallyValue(*_scoreImg), 340, 1);
	_levelImg->Draw(CenterImgHorizontallyValue(*_levelImg), 265, 1);
}

bool GameOverMenu::PlayAgainPressed(int mouseX, int mouseY)
{
	return _playAgainButton->IsInside(mouseX, mouseY);
}

int GameOverMenu::CenterImgHorizontallyValue(SDL::Image img)
{
	return _engine->Width() / 2 - img.Width() / 2;
}
