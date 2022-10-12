#include "Platform.h"

void Platform::resetBools()
{
	platformLong = false;
	platformNormal_1 = false;
	platformShort = false;
}

Platform::Platform()
{
	speed = 1;

	platformType = PlatformType::NORMAL;	
}

void Platform::LoadSprites()
{
	getScreenSize(sWidth, sHeight);
	if (sWidth > sHeight)
		diff = sWidth / sHeight;
	else
		diff = sHeight / sWidth;

	w = sWidth / 8;
	h = w / (diff * 3);

	// initial position
	platformPos.first = sWidth / 2 - w / 2;
	platformPos.second = sHeight - 2 * h;

	// setting boundaries for up and down movement
	minY = sHeight - 2 * h;
	maxY = sHeight - 5 * h;

	// min value for left movement
	minX = 5;
}

void Platform::DrawSprites()
{
	switch (platformType)
	{
	case PlatformType::LONG:
		if (!platformLong)
		{
			sprite = createSprite(assetPath.at("platformLong"));
			resetBools();
			platformLong = true;
		}	

		// max value for right movement calculated with the platform's width
		w = sWidth / 5;
		h = w / (diff * 4.8);
		maxX = sWidth - w;

		setSpriteSize(sprite, w, h);
		drawSprite(sprite, platformPos.first, platformPos.second);
		break;

	case PlatformType::NORMAL:
		if (!platformNormal_1)
		{
			sprite = createSprite(assetPath.at("platformNormal1"));
			resetBools();
			platformNormal_1 = true;
		}	

		// max value for right movement calculated with the platform's width
		w = sWidth / 8;
		h = w / (diff * 3);
		maxX = sWidth - w;

		setSpriteSize(sprite, w, h);
		drawSprite(sprite, platformPos.first, platformPos.second);
		break;

	case PlatformType::SHORT:
		if (!platformShort)
		{
			sprite = createSprite(assetPath.at("platformShort"));
			resetBools();
			platformShort = true;
		}		

		// max value for right movement calculated with the platform's width
		w = sWidth / 15;
		h = w / (diff * 1.5);
		maxX = sWidth - w;

		setSpriteSize(sprite, w, h);
		drawSprite(sprite, platformPos.first, platformPos.second);
		break;
	}
}

void Platform::ChangeSprite(PlatformType pt)
{
	platformType = pt;
}

int Platform::getX() const
{
	return platformPos.first;
}

int Platform::getY() const
{
	return platformPos.second;
}

void Platform::setX(int x)
{
	platformPos.first = x;
}

void Platform::setY(int y)
{
	platformPos.second = y;
}

// returns platform height
int Platform::getH()
{
	return h;
}

//returns platform width
int Platform::getW()
{
	return w;
}

int Platform::getSpeed()
{
	return speed;
}

void Platform::setSpeed(int speed)
{
	this->speed = speed;
}

void Platform::resetPos()
{
	platformPos.first = sWidth / 2 - w / 2;
	platformPos.second = sHeight - 2 * h;
}

PlatformType Platform::getPlatformType() const
{
	return platformType;
}
