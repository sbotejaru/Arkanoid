#include "Assets.h"
#include "Framework.h"

#pragma once
enum class AbilityType
{
	PLATFORM_LONG,
	PLATFORM_SHORT,
	BALL_BIG,
	BALL_SMALL,
	COUNT
};

class Ability
{
protected:
	AbilityType abilityType;
	Sprite* sprite;
	int w;
	int h;

public:
	Sprite* getSprite() const
	{
		return sprite;
	}

	AbilityType getAbilityType() const
	{
		return abilityType;
	}

	void destroyAbility()
	{
		destroySprite(sprite);
	}

	void setSize(int w, int h)
	{
		setSpriteSize(sprite, w, h);
	}

	int getW() const
	{
		return w;
	}

	int getH() const
	{
		return h;
	}
};

class AbilityPlatformLong : public Ability
{
public:
	AbilityPlatformLong(int w, int h)
	{
		abilityType = AbilityType::PLATFORM_LONG;
		sprite = createSprite(assetPath.at("abilityPlatformLong"));

		this->w = w;
		this->h = h;
		
		setSize(w, h);
	}
};

class AbilityPlatformShort : public Ability
{
public:
	AbilityPlatformShort(int w, int h)
	{
		abilityType = AbilityType::PLATFORM_SHORT;
		sprite = createSprite(assetPath.at("abilityPlatformShort"));

		this->w = w;
		this->h = h;

		setSize(w, h);
	}
};

class AbilityBallBig : public Ability
{
public:
	AbilityBallBig(int w, int h)
	{
		abilityType = AbilityType::BALL_BIG;
		sprite = createSprite(assetPath.at("abilityBallBig"));

		this->w = w;
		this->h = h;

		setSize(w, h);
	}
};

class AbilityBallSmall : public Ability
{
public:
	AbilityBallSmall(int w, int h)
	{
		abilityType = AbilityType::BALL_SMALL;
		sprite = createSprite(assetPath.at("abilityBallSmall"));

		this->w = w;
		this->h = h;

		setSize(w, h);
	}
};

