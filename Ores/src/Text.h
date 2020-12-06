#pragma once

#include <string>
#include <memory>

#include <SDL_ttf.h>

namespace SDL
{
	class Window;
	class Image;
}

class Engine;

namespace SDL
{
	class Text
	{
	public:
		Text(std::shared_ptr<Window> window, std::string path, int fontSize);
		~Text();

		std::shared_ptr<SDL::Image> RenderText(std::string text, SDL_Color color);

	private:
		std::shared_ptr<Window> _window = nullptr;

		std::string _filePath;

		int _size = 0;

		TTF_Font* _font = nullptr;

		void SetParams(std::shared_ptr<Window> window, std::string path, int fontSize);

		std::shared_ptr<SDL::Image> ToImage(SDL_Surface* surf);
	};
}
