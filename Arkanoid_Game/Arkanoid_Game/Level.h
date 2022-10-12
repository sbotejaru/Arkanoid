#include "Tile.h"

#pragma once
class Level
{
protected:
	int screenWidth;
	int screenHeight;
	uint8_t tileWidth;
	uint8_t tileHeight;
	uint16_t maxY;
	const uint8_t lineTileCount = 10;
	bool cleared;

	// maps for storing each sprite pointer and their position

	// "unhittable" tiles
	std::unordered_map<Tile*, std::pair<uint16_t, uint16_t>> immuneTiles;
	// "hittable" tiles
	std::unordered_map<Tile*, std::pair<uint16_t, uint16_t>> visibleTiles;

public:
	//Level();

	virtual void LoadSprites() = 0;

	void DrawSprites();

	virtual bool VerifyGameState() = 0;

	void checkVisibleTiles();

	std::unordered_map<Tile*, std::pair<uint16_t, uint16_t>> getVisibleTiles();

	std::unordered_map<Tile*, std::pair<uint16_t, uint16_t>> getimmuneTiles();

	bool destroyTile(Tile* tile);

	uint16_t getPlatformWidth();

	uint16_t getPlatformHeight();

	uint16_t getMaxPlatformPos();

	bool isCleared();

	int getTileWidth() const;

	int getTileHeight() const;
};

class Level_1 : public Level
{
public:
	virtual void LoadSprites()
	{
		getScreenSize(screenWidth, screenHeight);
		int diff;

		if (screenWidth > screenHeight)
			diff = screenWidth / screenHeight;
		else
			diff = screenHeight / screenWidth;

		tileWidth = screenWidth / lineTileCount;
		tileHeight = tileWidth / (diff * 3);

		uint16_t startX = 0;
		uint16_t startY = tileHeight;

		for (int index = 0; index < lineTileCount; ++index)
		{
			immuneTiles.insert(std::make_pair(
				new RedTile(tileWidth, tileHeight), std::make_pair(startX, startY + tileHeight)
			));

			immuneTiles.insert(std::make_pair(
				new OrangeTile(tileWidth, tileHeight), std::make_pair(startX, startY + tileHeight * 2)
			));

			immuneTiles.insert(std::make_pair(
				new LimeTile(tileWidth, tileHeight), std::make_pair(startX, startY + tileHeight * 3)
			));

			immuneTiles.insert(std::make_pair(
				new GreenTile(tileWidth, tileHeight), std::make_pair(startX, startY + tileHeight * 4)
			));

			startX += tileWidth;
		}

		checkVisibleTiles();
	}

	bool Level::VerifyGameState()
	{
		if (visibleTiles.empty())
		{
			std::cout << "\n\nLEVEL CLEARED\n\n";
			return true;
		}

		return false;
	}
};

class Level_2 : public Level
{
	virtual void LoadSprites()
	{
		int godTilesPerLine = 4;

		getScreenSize(screenWidth, screenHeight);
		int diff;

		if (screenWidth > screenHeight)
			diff = screenWidth / screenHeight;
		else
			diff = screenHeight / screenWidth;

		tileWidth = screenWidth / lineTileCount;
		tileHeight = tileWidth / (diff * 3);

		uint16_t startX = 0;
		uint16_t startY = tileHeight;

		for (int index = 0; index < lineTileCount; ++index)
		{
			if (index < 2 || index >= 4 && index < 6 || index >= 8)
			{
				immuneTiles.insert(std::make_pair(
					new RedTile(tileWidth, tileHeight), std::make_pair(startX, startY + tileHeight)
				));

				immuneTiles.insert(std::make_pair(
					new LimeTile(tileWidth, tileHeight), std::make_pair(startX, startY + tileHeight * 3)
				));

				immuneTiles.insert(std::make_pair(
					new BlueTile(tileWidth, tileHeight), std::make_pair(startX, startY + tileHeight * 5)
				));

				immuneTiles.insert(std::make_pair(
					new OrangeTile(tileWidth, tileHeight), std::make_pair(startX, startY + tileHeight * 2)
				));

				immuneTiles.insert(std::make_pair(
					new GreenTile(tileWidth, tileHeight), std::make_pair(startX, startY + tileHeight * 4)
				));

				immuneTiles.insert(std::make_pair(
					new AquaTile(tileWidth, tileHeight), std::make_pair(startX, startY + tileHeight * 6)
				));
			}
			else
			{
				immuneTiles.insert(std::make_pair(
					new GoldenTile(tileWidth, tileHeight), std::make_pair(startX, startY + tileHeight * 2)
				));

				immuneTiles.insert(std::make_pair(
					new GoldenTile(tileWidth, tileHeight), std::make_pair(startX, startY + tileHeight * 6)
				));

				immuneTiles.insert(std::make_pair(
					new GoldenTile(tileWidth, tileHeight), std::make_pair(startX, startY + tileHeight * 4)
				));

				immuneTiles.insert(std::make_pair(
					new GoldenTile(tileWidth, tileHeight), std::make_pair(startX, startY + tileHeight)
				));

				immuneTiles.insert(std::make_pair(
					new GoldenTile(tileWidth, tileHeight), std::make_pair(startX, startY + tileHeight * 3)
				));

				immuneTiles.insert(std::make_pair(
					new GoldenTile(tileWidth, tileHeight), std::make_pair(startX, startY + tileHeight * 5)
				));
			}

			startX += tileWidth;
		}

		checkVisibleTiles();
	}

	bool Level::VerifyGameState()
	{
		bool onlyGold = true;

		for (auto const& it : visibleTiles)
		{
			if (it.first->getToughness() != -1)
				onlyGold = false;
		}

		// level cleared
		if (onlyGold)
		{
			//std::cout << "\n\nYOU WIN\n\n";
			return true;
		}

		return false;
	}
};