#include "Image.h"
#include "Window.h"

SDL::Image::Image(std::shared_ptr<SDL::Window> window, std::string filePath)
{
	SetWindow(window);
	SetPath(filePath);
}

SDL::Image::Image(std::shared_ptr<SDL::Window> window, SDL_Texture* tex)
{
	SetWindow(window);
	SetTexture(tex);
}

SDL::Image::~Image()
{
	_containingWindow = nullptr;
	_texture = nullptr;
}

void SDL::Image::SetWindow(std::shared_ptr<SDL::Window> window)
{
	_containingWindow = window;
}

void SDL::Image::SetPath(std::string filePath)
{
	_path = filePath;
	LoadTexture();
}

void SDL::Image::SetTexture(SDL_Texture* tex)
{
	//In practice, what reset does is call the destructor of the texture,
	//ensuring memory is well managed, and then copies the new value
	_texture.reset(tex, DestroyTexture());

	//This function will get the texture's dimensions
	SDL_QueryTexture(_texture.get(), nullptr, nullptr, &_width, &_height);
}

int SDL::Image::Width()
{
	return _width;
}

int SDL::Image::Height()
{
	return _height;
}

int SDL::Image::XPosition()
{
	return _posX;
}

int SDL::Image::YPosition()
{
	return _posY;
}

bool SDL::Image::Draw(int x, int y, int z, double factorX, double factorY)
{
	SDL_Rect destRect;
	destRect.w = _width * factorX;
	destRect.h = _height * factorY;
	destRect.x = x;
	destRect.y = y;

	int success = SDL_RenderCopyEx(_containingWindow->Renderer(), _texture.get(), nullptr, &destRect, 0, nullptr, SDL_FLIP_NONE);

	if (success == 0)
	{
		_posX = x;
		_posY = y;
	}
	
	return success == 0;
}

bool SDL::Image::VerifyParameters()
{
	return _containingWindow == nullptr && _path != "";
}

bool SDL::Image::LoadTexture()
{
	//load texture from the file path
	SDL_Texture* tex = IMG_LoadTexture(_containingWindow->Renderer(), _path.c_str());

	if (tex == nullptr)
	{
		return false;
	}

	SetTexture(tex);

	return true;
}
