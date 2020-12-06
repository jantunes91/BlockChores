#include "Text.h"
#include "Window.h"
#include "Image.h"

#include <iostream>

SDL::Text::Text(std::shared_ptr<Window> window, std::string path, int fontSize)
{
	SetParams(window, path, fontSize);
}

SDL::Text::~Text()
{
	TTF_CloseFont(_font);
	_font = nullptr;
}

void SDL::Text::SetParams(std::shared_ptr<Window> window, std::string path, int fontSize)
{
	_window = window;
	_filePath = path;
	_size = fontSize;

	_font = TTF_OpenFont(_filePath.c_str(), _size);
	if (_font == nullptr)
	{
		cerr << TTF_GetError();
	}
}

std::shared_ptr<SDL::Image> SDL::Text::RenderText(std::string text, SDL_Color color)
{
	SDL_Surface* surf = TTF_RenderUTF8_Blended(_font, text.c_str(), color);
	return ToImage(surf);
}

std::shared_ptr<SDL::Image> SDL::Text::ToImage(SDL_Surface * surf)
{
	SDL_Texture* text = SDL_CreateTextureFromSurface(_window->Renderer(), surf);

	SDL_FreeSurface(surf);

	std::shared_ptr<SDL::Image> resultImg = std::make_shared<SDL::Image>(_window, text);

	return resultImg;
}
