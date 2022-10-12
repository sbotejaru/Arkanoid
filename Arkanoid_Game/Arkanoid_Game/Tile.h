#include "Framework.h"
#include "Assets.h"

#pragma once
struct Tile
{
protected:
	int score;
	int toughness;
	int x;
	int y;
	int w;
	int h;
	Sprite* sprite;
	Sprite* brokenSprite;

public:
	void setScore(uint8_t _score)
	{
		score = _score;
	}
	void setSize(int w, int h)
	{
		setSpriteSize(sprite, w, h);
	}
	void changeToBrokenSprite()
	{
		sprite = brokenSprite;
		setSize(w, h);
	}
	void setX(int _x)
	{
		x = _x;
	}
	void setY(int _y)
	{
		y = _y;
	}
	void decreaseToughness()
	{
		--toughness;
	}
	Sprite* getSprite() const
	{
		return sprite;
	}
	int getScore() const
	{
		return score;
	}
	int getToughness() const
	{
		return toughness;
	}
	int getX() const
	{
		return x;
	}
	int getY() const
	{
		return y;
	}
};

struct RedTile : public Tile
{
public:
	RedTile(int _w, int _h)
	{
		w = _w;
		h = _h;
		score = 40;
		toughness = 2;
		sprite = createSprite(assetPath.at("redTile"));
		brokenSprite = createSprite(assetPath.at("redTileBroken"));

		setSize(w, h);
	}
};

struct OrangeTile : public Tile
{
public:
	OrangeTile(int _w, int _h)
	{
		w = _w;
		h = _h;
		score = 40;
		toughness = 2;
		sprite = createSprite(assetPath.at("orangeTile"));
		brokenSprite = createSprite(assetPath.at("orangeTileBroken"));

		setSize(w, h);
	}
};

struct LimeTile : public Tile
{
public:
	LimeTile(int _w, int _h)
	{
		w = _w;
		h = _h;
		score = 20;
		toughness = 1;
		sprite = createSprite(assetPath.at("limeTile"));

		setSize(w, h);
	}
};

struct GreenTile : public Tile
{
public:
	GreenTile(int _w, int _h)
	{
		w = _w;
		h = _h;
		score = 20;
		toughness = 1;
		sprite = createSprite(assetPath.at("greenTile"));

		setSize(w, h);
	}
};

struct BlueTile : public Tile
{
public:
	BlueTile(int _w, int _h)
	{
		w = _w;
		h = _h;
		score = 10;
		toughness = 1;
		sprite = createSprite(assetPath.at("blueTile"));

		setSize(w, h);
	}
};

struct AquaTile : public Tile
{
public:
	AquaTile(int _w, int _h)
	{
		w = _w;
		h = _h;
		score = 10;
		toughness = 1;
		sprite = createSprite(assetPath.at("aquaTile"));

		setSize(w, h);
	}
};

struct GoldenTile : public Tile
{
public:
	GoldenTile(int _w, int _h)
	{
		w = _w;
		h = _h;
		score = 0;
		toughness = -1;
		sprite = createSprite(assetPath.at("goldenTile"));

		setSize(w, h);
	}
};
