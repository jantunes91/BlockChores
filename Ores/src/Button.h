#pragma once

#include "Image.h"
#include <memory>

class Engine;

class Button
{
public:
	Button(std::shared_ptr<Engine> engine, std::string imgFilePath);
	~Button();

	void Draw();

	bool IsInside(int x, int y);

	void CenterHorizontally(int windowWidth);
	void SetPosition(int x, int y);

	int Height();
	int Width();

private:
	std::unique_ptr<SDL::Image> _image = nullptr;

	std::shared_ptr<Engine> _engine = nullptr;

	int _posX;
	int _posY;
};
