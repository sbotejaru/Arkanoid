#include "Assets.h"
#pragma once

enum class PlatformType
{
	SHORT,
	NORMAL,
	LONG,
	COUNT
};

class Platform
{
private:
	// platform width
	int w;
	//platform height
	int h;	
	// screen width
	int sWidth;
	// screen height
	int sHeight;

	int diff;

	// platform speed
	float speed;

	// platform sprite
	Sprite* sprite;
	PlatformType platformType;

	// bools for not creating new sprites every tick at sprite change
	bool platformLong;
	bool platformNormal_1;
	bool platformShort;
	
	// platform position
	std::pair<uint16_t, uint16_t> platformPos;

	void resetBools();

public:	
	// min platform x position
	int minX;
	// max platform x position
	int maxX;
	// min platform y position
	int minY;
	// max platform y position
	int maxY;

	Platform();

	void LoadSprites();

	void DrawSprites();

	void ChangeSprite(PlatformType tp);

	int getX() const;

	int getY() const;

	void setX(int x);

	void setY(int y);

	int getH();

	int getW();

	int getSpeed();

	void setSpeed(int speed);

	void resetPos();

	PlatformType getPlatformType() const;
};

