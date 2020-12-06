#include "Block.h"
#include "Image.h"
#include <iostream>

Block::Block()
{
	_animDestX = 0;
	_animDestY = 0;
	_animMaxMove = 0;
	_animOrientation = AnimationOrientation::Horizontal;
	_animOrigX = 0;
	_animOrigY = 0;
	_animStartTime = 0;

	_posX = 0;
	_posY = 0;
	_origX = 0;
	_origY = 0;
	_destX = 0;
	_destY = 0;

	_drawPosX = 0;
	_drawPosY = 0;

	_updatePosition = false;
	_updatePositionsCount = 0;

	Type = BlockType::Red;
	Empty = false;
	ToDestroy = false;
}

void Block::Update()
{
	float animationSpeed = 0.f;

	//We calculate the animation speed according to height of the Block and orientation
	switch (_animOrientation)
	{
	case AnimationOrientation::Horizontal:
		animationSpeed = 200.f;
		break;
	case AnimationOrientation::Vertical:
		animationSpeed = 100.f * (_animDestY - _animOrigY);
		break;
	default:
		break;
	}

	if (_updatePosition)
	{
		Animate(animationSpeed);
	}

}

void Block::Draw(int offsetX, int offsetY)
{
	if (!Empty)
	{
		_image->Draw((int)_drawPosX + offsetX, (int)_drawPosY + offsetY, 1);
	}
}

void Block::SetPosition(float x, float y)
{
	_posX = x;
	_posY = y;

	_drawPosX = _posX * k_blockDrawSize;
	_drawPosY = _posY * k_blockDrawSize;
}

bool Block::ToUpdate()
{
	return _updatePosition;
}

void Block::IncrementUpdatePositionsCount()
{
	_updatePositionsCount++;
}

void Block::SetUpdatePositionsCount(int drop)
{
	_updatePositionsCount = drop;
}

int Block::UpdatePositionsCount()
{
	return _updatePositionsCount;
}

void Block::SetImg(std::shared_ptr<SDL::Image> img)
{
	_image = img;
}

void Block::Drop(int maxDrop)
{
	_animOrientation = AnimationOrientation::Vertical;
	_updatePosition = true;
	_animOrigX = _posX;
	_animOrigY = _posY;
	_animDestX = _posX;
	_animDestY = _posY + static_cast<float>(_updatePositionsCount);

	_animMaxMove = maxDrop;

	_animStartTime = SDL_GetTicks();
}

void Block::ShiftLeft(int origX, int origY, int value, int maxShift)
{
	_animOrientation = AnimationOrientation::Horizontal;
	_updatePosition = true;
	_animOrigX = (float)origX;
	_animOrigY = (float)origY;
	_animDestX = (float)origX - value;
	_animDestY = (float)origY;

	_animMaxMove = maxShift;

	_animStartTime = SDL_GetTicks();
}

void Block::ShiftRight(int origX, int origY, int value, int maxShift)
{
	_animOrientation = AnimationOrientation::Horizontal;
	_updatePosition = true;
	_animOrigX = (float)origX;
	_animOrigY = (float)origY;
	_animDestX = (float)origX + value;
	_animDestY = (float)origY;

	_animMaxMove = maxShift;

	_animStartTime = SDL_GetTicks();
}

void Block::ResetState()
{
	ToDestroy = false;
	Empty = false;
}

void Block::RectLerp(float f)
{
	float t = 1.0f - f;
	float x = _animOrigX == _animDestX ? _animOrigX : (float)_animOrigX * t + (float)_animDestX * f;
	float y = _animOrigY == _animDestY ? _animOrigY : (float)_animOrigY * t + (float)_animDestY * f;
	SetPosition(x,y);
}

bool Block::Animate(float totalTime)
{
	int currentTime = SDL_GetTicks();
	bool isAnimationComplete = currentTime > _animStartTime + totalTime;
	if (isAnimationComplete)
	{
		SetPosition(_animDestX, _animDestY);
		_updatePosition = false;
		_updatePositionsCount = 0;
	}
	else
	{
		float factor = ((float)(currentTime - _animStartTime)) / totalTime;
		RectLerp(factor);
	}

	return isAnimationComplete;
}
