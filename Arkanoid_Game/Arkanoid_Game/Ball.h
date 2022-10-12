#include "Framework.h"
#include "Assets.h"
#pragma once

enum class BallType
{
	MIN,
	SMALL,
	NORMAL,
	MAX,
	COUNT
};

class Ball
{
private:
	// ball size
	int size;

	// screen width
	int sWidth;

	// screen height
	int sHeight;

	// ball speed
	float speed;

	// ball sprite
	Sprite* sprite;
	BallType ballType;

	// ball position
	std::pair<uint16_t, uint16_t> ballPos;

public:
	int maxY;
	int maxX;
	int minY;
	int minX;

	Ball();

	void Load();

	void DrawSprites();

	void setX(int x);

	void setY(int y);

	void ChangeSprite(BallType bt);

	int getX() const;

	int getY() const;

	int getSize() const;

	int getSpeed() const;

	void resetPos();

	BallType getBallType() const;
};

