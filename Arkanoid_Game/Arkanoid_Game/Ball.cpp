#include "Ball.h"

Ball::Ball()
{
	ballType = BallType::NORMAL;
	speed = 1;
}

void Ball::Load()
{
	getScreenSize(sWidth, sHeight);
	size = sWidth / 30;	

	minX = speed * 2;
	minY = 1;

	sprite = createSprite(assetPath.at("ballSizeMax"));

	resetPos();
}

void Ball::DrawSprites()
{
	switch (ballType)
	{
	case BallType::MAX:
		size = sWidth / 20;
		maxX = sWidth - size;
		maxY = sHeight - size;
				
		setSpriteSize(sprite, size, size);
		drawSprite(sprite, ballPos.first, ballPos.second);
		break;

	case BallType::NORMAL:
		size = sWidth / 30;
		maxX = sWidth - size;
		maxY = sHeight - size;

		setSpriteSize(sprite, size, size);
		drawSprite(sprite, ballPos.first, ballPos.second);
		break;

	case BallType::SMALL:
		size = sWidth / 40;
		maxX = sWidth - size;
		maxY = sHeight - size;

		setSpriteSize(sprite, size, size);
		drawSprite(sprite, ballPos.first, ballPos.second);
		break;

	case BallType::MIN:
		size = sWidth / 60;
		maxX = sWidth - size;
		maxY = sHeight - size;

		setSpriteSize(sprite, size, size);
		drawSprite(sprite, ballPos.first, ballPos.second);
		break;
	}
}

void Ball::setX(int x)
{
	ballPos.first = x;
}

void Ball::setY(int y)
{
	ballPos.second = y;
}

void Ball::ChangeSprite(BallType bt)
{
	ballType = bt;
}

int Ball::getX() const
{
	return ballPos.first;
}

int Ball::getY() const
{
	return ballPos.second;
}

int Ball::getSize() const
{
	return size;
}

int Ball::getSpeed() const
{
	return speed;
}

void Ball::setSpeed(int _speed)
{
	speed = _speed;
	minX = _speed * 2;
	//minY = _speed;
}

void Ball::resetPos()
{
	ballPos.first = sWidth / 2 - size / 2;
	ballPos.second = sHeight - 3.5 * size;
}

BallType Ball::getBallType() const
{
	return ballType;
}

