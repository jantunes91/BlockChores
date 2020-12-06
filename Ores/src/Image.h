#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <string>
#include <memory>
using namespace std;

namespace SDL {
	class Window;

	class Image {

	public:
		Image(std::shared_ptr<SDL::Window> window, std::string filePath);
		Image(std::shared_ptr<SDL::Window> window, SDL_Texture* tex);
		~Image();

		int Width();
		int Height();

		int XPosition();
		int YPosition();

		bool Draw(int x, int y, int z, double factorX = 1, double factorY = 1);

	private:
		std::shared_ptr<SDL::Window> _containingWindow = nullptr;

		int _width;
		int _height;

		int _posX; 
		int _posY;

		std::string _path;

		/**
		@brief The texture of the Image
		We're holding it in a shared pointer so it's easier to copy into other Images
		*/
		std::shared_ptr<SDL_Texture> _texture = nullptr;

		/**
		@brief The destroyer for the texture, called when there's no more entities pointing
		to the texture
		*/
		struct DestroyTexture
		{
			void operator()(SDL_Texture * texture) const
			{
				if (texture)
				{
					SDL_DestroyTexture(texture);
				}
			}
		};

		void SetWindow(std::shared_ptr<SDL::Window> window);

		void SetPath(std::string filePath);

		void SetTexture(SDL_Texture* tex);

		bool VerifyParameters();

		bool LoadTexture();
	};
}