#include "Window.h"

#include <iostream>
#include <stdexcept>

using namespace std;

SDL::Window::Window(unsigned width, unsigned height, std::string title)
{
	_width = width;
	_height = height;
	_title = title;

	Setup();
}

SDL::Window::~Window()
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	_renderer = nullptr;
	_window = nullptr;

	QuitSDL();
}

void SDL::Window::QuitSDL()
{
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

void SDL::Window::Setup()
{
	StartSDL();
	SetLinearTextureFiltering();
	InitPNGLoading();
	InitTTF();
	InitMixer();
	SetupWindow();
}

void SDL::Window::SetupWindow()
{
	_window = SDL_CreateWindow(_title.c_str(),
								SDL_WINDOWPOS_UNDEFINED,
								SDL_WINDOWPOS_UNDEFINED,
								_width,
								_height,
								SDL_WINDOW_SHOWN);

	if (_window == nullptr)
	{
		throw std::runtime_error(SDL_GetError());
	}

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (_renderer == nullptr)
	{
		throw std::runtime_error(SDL_GetError());
	}

	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
}

void SDL::Window::InitTTF()
{
	TTF_Init();
}

void SDL::Window::InitMixer()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		throw std::runtime_error(Mix_GetError());
	}
}

void SDL::Window::InitPNGLoading()
{
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		throw std::runtime_error(IMG_GetError());
	}
}

void SDL::Window::SetLinearTextureFiltering()
{
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		cerr << "Warning: Linear texture filtering not enabled!" << endl;
	}
}

void SDL::Window::StartSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		throw std::runtime_error(SDL_GetError());
	}
}

void SDL::Window::Show()
{
	// Show the window
	SDL_ShowWindow(_window);

	_runGame = true;

	RunGameLoop();
}

void SDL::Window::RunGameLoop()
{
	// Event to catch
	SDL_Event event;

	while (_runGame)
	{
		bool shouldQuit;
		HandleSDLEvents(event, shouldQuit);
		if (shouldQuit)
		{
			return;
		}

		Update();

		// Render the background clear
		SDL_RenderClear(_renderer);

		Draw();

		// Update the screen
		SDL_RenderPresent(_renderer);
	}
}

void SDL::Window::HandleSDLEvents(SDL_Event& event, bool& shouldQuit)
{
	shouldQuit = false;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			Close();
			shouldQuit = true;

		case SDL_MOUSEBUTTONDOWN:
			MouseButtonDown(event.button.button);
			break;
		}
	}
}

void SDL::Window::Close()
{
	_runGame = false;
}

int SDL::Window::MouseX()
{
	int x;
	SDL_GetMouseState(&x, nullptr);

	return x;
}

int SDL::Window::MouseY()
{
	int y;
	SDL_GetMouseState(nullptr, &y);

	return y;
}

SDL_Renderer* SDL::Window::Renderer()
{
	return _renderer;
}

int SDL::Window::Width()
{
	return _width;
}

int SDL::Window::Height()
{
	return _height;
}
