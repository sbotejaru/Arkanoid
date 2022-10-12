#include "Level.h"

void Level::DrawSprites()
{
	for (auto const& it : immuneTiles)
	{
		uint16_t x, y;
		x = it.second.first;
		y = it.second.second;
		drawSprite(it.first->getSprite(), x, y);
	}

	for (auto const& it : visibleTiles)
	{
		uint16_t x, y;
		x = it.second.first;
		y = it.second.second;
		drawSprite(it.first->getSprite(), x, y);
	}
}

void Level::checkVisibleTiles()
{
	maxY = 0;
	uint16_t minY = screenWidth;
	std::unordered_map<Tile*, std::pair<uint16_t, uint16_t>> _visibleTiles;

	for (auto const& it : immuneTiles)
	{
		int y = it.second.second;

		if (y > maxY)
		{
			maxY = y;
			visibleTiles.clear();
			visibleTiles.insert(std::make_pair(
				it.first, it.second
			));
		}
		else if (y == maxY)
		{
			visibleTiles.insert(std::make_pair(
				it.first, it.second
			));
		}

		if (y < minY)
		{
			minY = y;
			_visibleTiles.clear();
			_visibleTiles.insert(std::make_pair(
				it.first, it.second
			));
		}
		else if (y == minY)
		{
			_visibleTiles.insert(std::make_pair(
				it.first, it.second
			));

		}
	}

	for (auto const& it : _visibleTiles)
	{
		visibleTiles.insert(std::make_pair(
			it.first, it.second
		));
	}

	_visibleTiles.clear();

	for (auto const& it : visibleTiles)
	{
		immuneTiles.erase(it.first);
	}
}

std::unordered_map<Tile*, std::pair<uint16_t, uint16_t>> Level::getVisibleTiles()
{
	return visibleTiles;
}

std::unordered_map<Tile*, std::pair<uint16_t, uint16_t>> Level::getimmuneTiles()
{
	return immuneTiles;
}

bool Level::destroyTile(Tile* tile)
{
	if (tile->getToughness() != -1)
		tile->decreaseToughness();
	else
		return false;

	if (tile->getToughness() > 0)
	{
		tile->changeToBrokenSprite();
		return false;
	}
	else if (tile->getToughness() == 0)
	{
		int destroyedX = visibleTiles.at(tile).first;
		int destroyedY = visibleTiles.at(tile).second;

		std::vector<Tile*> toBeDestroyed;

		int x = 1;

		for (auto const& it : immuneTiles)
		{
			int immuneX = it.second.first;
			int immuneY = it.second.second;

			if (immuneX == destroyedX && immuneY == destroyedY - tileHeight || // above
				immuneX == destroyedX && immuneY == destroyedY + tileHeight || // below
				immuneY == destroyedY && immuneX == destroyedX - tileWidth || // left
				immuneY == destroyedY && immuneX == destroyedX + tileWidth) // right
			{
				visibleTiles.insert(std::make_pair(
					it.first, it.second
				));

				toBeDestroyed.push_back(it.first);
			}
		}

		for (auto const& it : toBeDestroyed)
		{
			immuneTiles.erase(it);
		}

		visibleTiles.erase(tile);
		destroySprite(tile->getSprite());
		VerifyGameState();

		return true;
	}
}

uint16_t Level::getPlatformWidth()
{
	return tileWidth;
}

uint16_t Level::getPlatformHeight()
{
	return tileHeight;
}

uint16_t Level::getMaxPlatformPos()
{
	return maxY;
}

bool Level::isCleared()
{
	return cleared;
}

int Level::getTileWidth() const
{
	return tileWidth;
}

int Level::getTileHeight() const
{
	return tileHeight;
}
