#pragma once

#include <SDL.h>
#include <memory>

class Engine;

class Scene
{
protected:
	std::shared_ptr<Engine> _engine;

public:
	Scene(std::shared_ptr<Engine> engine);
	virtual ~Scene() {};

	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual void MouseButtonDown(Uint8) { }
};