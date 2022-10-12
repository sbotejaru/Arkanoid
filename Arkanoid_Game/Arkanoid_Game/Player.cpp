#include "Player.h"

Player::Player()
{
	totalLives = 4;
	totalScore = 0;
	platformSpeed = platform.getSpeed();
	up = true;
	start = false;
	level = new Level_1;
	levelNumber = 1;
	abilityDropChance = 10; // 10%
}

void Player::LoadSprites()
{
	level->LoadSprites();
	platform.LoadSprites();
	loadLifeSprites();
	ball.Load();
}

void Player::DrawSprites()
{
	platform.DrawSprites();
	ball.DrawSprites();
	level->DrawSprites();

	for (auto const& it : liveSprites)
	{
		uint16_t x, y;
		x = it.second.first;
		y = it.second.second;
		drawSprite(it.first, x, y);
	}

	for (auto& it : abilities)
	{
		uint16_t x, y;
		x = it.second.first;
		y = it.second.second;
		drawSprite(it.first->getSprite(), x, y);
		if (ball.getX() % 3 == 0)
			++it.second.second;
	}

	checkAbilityCollision();
}

void Player::changePlatform(PlatformType pt)
{
	platform.ChangeSprite(pt);
	//printScore();
}

void Player::changeBall(BallType bt)
{
	ball.ChangeSprite(bt);
	//printScore();
}

void Player::MovePlatformUp()
{
	int y = platform.getY();
	if (y - platformSpeed >= platform.maxY)
	{
		platform.setY(y - platformSpeed);
	}

	if (!start)
	{
		ball.setX(platform.getX() + platform.getW() / 2 - ball.getSize() / 2);
		ball.setY(platform.getY() - ball.getSize());
	}
}

void Player::MovePlatformDown()
{
	int y = platform.getY();
	if (y + platformSpeed <= platform.minY)
	{
		platform.setY(y + platformSpeed);
	}

	if (!start)
	{
		ball.setX(platform.getX() + platform.getW() / 2 - ball.getSize() / 2);
		ball.setY(platform.getY() - ball.getSize());
	}
}

void Player::MovePlatformLeft()
{
	int x = platform.getX();
	if (x - platformSpeed >= platform.minX)
	{
		platform.setX(x - platformSpeed);
	}

	if (!start)
	{
		ball.setX(platform.getX() + platform.getW() / 2 - ball.getSize() / 2);
		ball.setY(platform.getY() - ball.getSize());
	}
}

void Player::MovePlatformRight()
{
	int x = platform.getX();
	if (x + platformSpeed <= platform.maxX)
	{
		platform.setX(x + platformSpeed);
	}

	if (!start)
	{
		ball.setX(platform.getX() + platform.getW() / 2 - ball.getSize() / 2);
		ball.setY(platform.getY() - ball.getSize());
	}
}

void Player::MoveBall()
{
	int y = ball.getY();
	int x = ball.getX();

	if (start)
	{
		if (up)
		{
			if (y - ball.getSpeed() < ball.minY || tileCollisionDown(x, y))
			{
				up = false;
				down = true;
			}
			else
				ball.setY(y - ball.getSpeed());
		}
		if (down)
		{
			if (y + ball.getSpeed() > ball.maxY)
			{
				decreaseLife();
				reset();
			}
			else if (platformCollisionUp(x, y, left, right) || tileCollisionUp(x, y))
			{
				up = true;
				down = false;
			}
			else
				ball.setY(y + ball.getSpeed());

		}
		if (left)
		{
			if (x + ball.getSpeed() <= ball.minX || platformCollisionRight(x, y) || tileCollisionRight(x, y))
			{
				left = false;
				right = true;
			}
			else
				ball.setX(x - ball.getSpeed());
		}
		if (right)
		{
			if (x - ball.getSpeed() > ball.maxX || platformCollisionLeft(x, y) || tileCollisionLeft(x, y))
			{
				left = true;
				right = false;
			}
			else
				ball.setX(x + ball.getSpeed());
		}
	}
}

bool Player::platformCollisionUp(int x, int y, bool& left, bool& right)
{
	if (y + ball.getSpeed() >= platform.maxY - ball.getSize() - speed * 2)
	{
		if (( // collision on the left edge			
			x + ball.getSize() >= platform.getX() &&
			x + ball.getSize() <= platform.getX() + platform.getW() / 4 &&
			y - ball.getSpeed() + ball.getSize() >= platform.getY() - speed * 2 &&
			y - ball.getSpeed() + ball.getSize() <= platform.getY() + speed * 2
			))
		{
			left = true;
			right = false;

			return true;
		}
		else if (( // collision on right edge
			x >= platform.getX() + platform.getW() / 1.25 &&
			x <= platform.getX() + platform.getW() &&
			y - ball.getSpeed() + ball.getSize() >= platform.getY() - speed * 2 &&
			y - ball.getSpeed() + ball.getSize() <= platform.getY() + speed * 2
			))
		{
			right = true;
			left = false;

			return true;
		}
		else if ((
			x >= platform.getX() &&
			x <= platform.getX() + platform.getW() &&
			y - ball.getSpeed() + ball.getSize() >= platform.getY() - speed * 2 &&
			y - ball.getSpeed() + ball.getSize() <= platform.getY() + speed * 2) ||
			(
				x + ball.getSize() >= platform.getX() &&
				x + ball.getSize() <= platform.getX() + platform.getW() &&
				y - ball.getSpeed() + ball.getSize() >= platform.getY() - speed * 2 &&
				y - ball.getSpeed() + ball.getSize() <= platform.getY() + speed * 2
				))
			return true;
	}

	return false;
}

bool Player::platformCollisionLeft(int x, int y)
{
	if (y + ball.getSpeed() >= platform.maxY - ball.getSize() - speed * 2)
	{
		if ((
			// collision on the left side of the platform
			y >= platform.getY() &&
			y <= platform.getY() + platform.getH() &&
			x + ball.getSpeed() + ball.getSize() >= platform.getX() - speed * 2 &&
			x + ball.getSpeed() + ball.getSize() <= platform.getX() + speed * 2) ||
			(
				y + ball.getSize() >= platform.getY() &&
				y + ball.getSize() <= platform.getY() + platform.getH() &&
				x + ball.getSpeed() + ball.getSize() >= platform.getX() - speed * 2 &&
				x + ball.getSpeed() + ball.getSize() <= platform.getX() + speed * 2
				))
			return true;
	}

	return false;
}

bool Player::platformCollisionRight(int x, int y)
{
	if (y + ball.getSpeed() >= platform.maxY - ball.getSize() - speed * 2)
	{
		if ((
			y >= platform.getY() &&
			y <= platform.getY() + platform.getH() &&
			x - ball.getSpeed() >= platform.getX() + platform.getW() - speed * 2 &&
			x - ball.getSpeed() <= platform.getX() + platform.getW() + speed * 2) ||
			(
				y + ball.getSize() >= platform.getY() &&
				y + ball.getSize() <= platform.getY() + platform.getH() &&
				x - ball.getSpeed() >= platform.getX() + platform.getW() - speed * 2 &&
				x - ball.getSpeed() <= platform.getX() + platform.getW() + speed * 2
				))
			return true;
	}

	return false;
}

bool Player::tileCollisionDown(int x, int y)
{
	auto tiles = level->getVisibleTiles();

	if (y - ball.getSpeed() <= level->getMaxPlatformPos() + ball.getSize() + speed * 2)
	{
		for (auto const& it : tiles)
		{
			uint16_t tileX = it.second.first;
			uint16_t tileY = it.second.second;
			uint16_t tileW = level->getPlatformWidth();
			uint16_t tileH = level->getPlatformHeight();

			if ((
				x >= tileX &&
				x <= tileX + tileW &&
				y + ball.getSpeed() >= tileY + tileH - speed * 2 &&
				y + ball.getSpeed() <= tileY + tileH + speed * 2) ||
				(
					x + ball.getSize() >= tileX &&
					x + ball.getSize() <= tileX + tileW &&
					y + ball.getSpeed() >= tileY + tileH - speed * 2 &&
					y + ball.getSpeed() <= tileY + tileH + speed * 2
					))
			{
				if (level->destroyTile(it.first))
				{
					totalScore += it.first->getScore();
					printScore();

					std::random_device rd;
					std::mt19937 gen(rd());
					std::uniform_int_distribution<> distrib(1, 100);

					int _rand = distrib(gen);

					if (abilityDropChance >= _rand)
						spawnAbility(tileX, tileY);
				}

				if (level->VerifyGameState())
					LevelChange();
				return true;
			}
		}
	}

	return false;
}

bool Player::tileCollisionUp(int x, int y)
{
	auto tiles = level->getVisibleTiles();

	if (y - ball.getSpeed() <= level->getMaxPlatformPos() + ball.getSize() + speed * 2)
	{
		for (auto const& it : tiles)
		{
			uint16_t tileX = it.second.first;
			uint16_t tileY = it.second.second;
			uint16_t tileW = level->getPlatformWidth();
			uint16_t tileH = level->getPlatformHeight();

			if ((
				x >= tileX &&
				x <= tileX + tileW &&
				y - ball.getSpeed() + ball.getSize() >= tileY - speed * 2 &&
				y - ball.getSpeed() + ball.getSize() <= tileY + speed * 2) ||
				(
					x + ball.getSize() >= tileX &&
					x + ball.getSize() <= tileX + tileW &&
					y - ball.getSpeed() + ball.getSize() >= tileY - speed * 2 &&
					y - ball.getSpeed() + ball.getSize() <= tileY + speed * 2
					))
			{
				if (level->destroyTile(it.first))
				{
					totalScore += it.first->getScore();
					printScore();

					std::random_device rd;
					std::mt19937 gen(rd());
					std::uniform_int_distribution<> distrib(1, 100);

					int _rand = distrib(gen);

					if (abilityDropChance >= _rand)
						spawnAbility(tileX, tileY);
				}

				if (level->VerifyGameState())
					LevelChange();
				return true;
			}
		}
	}

	return false;
}

bool Player::tileCollisionLeft(int x, int y)
{
	auto tiles = level->getVisibleTiles();

	if (y - ball.getSpeed() <= level->getMaxPlatformPos() + ball.getSize() + speed * 2)
	{
		for (auto const& it : tiles)
		{
			uint16_t tileX = it.second.first;
			uint16_t tileY = it.second.second;
			uint16_t tileW = level->getPlatformWidth();
			uint16_t tileH = level->getPlatformHeight();

			if ((
				y >= tileY &&
				y <= tileY + tileH &&
				x + ball.getSpeed() + ball.getSize() >= tileX - speed * 2 &&
				x + ball.getSpeed() + ball.getSize() <= tileX + speed * 2) ||
				(
					y + ball.getSize() >= tileY &&
					y + ball.getSize() <= tileY + tileH &&
					x + ball.getSpeed() + ball.getSize() >= tileX - speed * 2 &&
					x + ball.getSpeed() + ball.getSize() <= tileX + speed * 2
					))
			{
				if (level->destroyTile(it.first))
				{
					totalScore += it.first->getScore();
					printScore();

					std::random_device rd;
					std::mt19937 gen(rd());
					std::uniform_int_distribution<> distrib(1, 100);

					int _rand = distrib(gen);

					if (abilityDropChance >= _rand)
						spawnAbility(tileX, tileY);
				}

				if (level->VerifyGameState())
					LevelChange();
				return true;
			}
		}
	}

	return false;
}

bool Player::tileCollisionRight(int x, int y)
{
	auto tiles = level->getVisibleTiles();

	if (y - ball.getSpeed() <= level->getMaxPlatformPos() + ball.getSize() + speed * 2)
	{
		for (auto const& it : tiles)
		{
			uint16_t tileX = it.second.first;
			uint16_t tileY = it.second.second;
			uint16_t tileW = level->getPlatformWidth();
			uint16_t tileH = level->getPlatformHeight();

			if ((
				y >= tileY &&
				y <= tileY + tileH &&
				x - ball.getSpeed() >= tileX + tileW - speed * 2 &&
				x - ball.getSpeed() <= tileX + tileW + speed * 2) ||
				(
					y + ball.getSize() >= tileY &&
					y + ball.getSize() <= tileY + tileH &&
					x - ball.getSpeed() >= tileX + tileW - speed * 2 &&
					x - ball.getSpeed() <= tileX + tileW + speed * 2
					))
			{
				if (level->destroyTile(it.first))
				{
					totalScore += it.first->getScore();
					printScore();

					std::random_device rd;
					std::mt19937 gen(rd());
					std::uniform_int_distribution<> distrib(1, 100);

					int _rand = distrib(gen);

					if (abilityDropChance >= _rand)
						spawnAbility(tileX, tileY);
				}

				if (level->VerifyGameState())
					LevelChange();
				return true;
			}
		}
	}

	return false;
}

void Player::reset()
{
	changePlatform(PlatformType::NORMAL);
	changeBall(BallType::NORMAL);
	platform.LoadSprites();
	ball.Load();
	abilities.clear();

	platform.resetPos();
	ball.resetPos();

	up = true;
	left = false;
	right = false;
	down = false;
	start = false;

	//printScore();
}

void Player::StartBallMovement(bool _left)
{
	if (!start)
	{
		start = true;
		left = _left;
		right = !_left;
	}
}

void Player::LevelChange()
{
	if (levelNumber == 1)
	{
		reset();
		level = new Level_2;
		level->LoadSprites();
		++levelNumber;
		totalScore += 100;
		printScore();
	}
	else
	{
		reset();
		totalScore = 0;
		level = new Level_1;
		level->LoadSprites();
		totalLives = 4;
		liveSprites.clear();
		loadLifeSprites();
		levelNumber = 1;
		//std::cout << "\x1B[2J\x1B[H";
		std::cout << "\n\nYou win!!!\n\n";
	}


}

void Player::decreaseLife()
{
	--totalLives;

	if (totalLives == 0)
	{
		totalScore = 0;
		level = new Level_1;
		level->LoadSprites();
		totalLives = 4;
		liveSprites.clear();
		loadLifeSprites();
		reset();
		levelNumber = 1;
	}
	else
	{
		Sprite* sprite;
		int maxX = 0;

		for (auto const& it : liveSprites)
		{
			if (maxX < it.second.first)
			{
				maxX = it.second.first;
				sprite = it.first;
			}
		}

		liveSprites.erase(sprite);
		destroySprite(sprite);

		printScore();
	}
}

void Player::printScore()
{
	//system("cls");
	std::cout << "Current level: Level " << levelNumber << "\n";
	std::cout << "\nTotal Score: " << totalScore << "\nLives left: " << totalLives << "\n";
}

void Player::loadLifeSprites()
{
	getScreenSize(sWidth, sHeight);

	liveSize = sWidth / 40;

	int x = liveSize / 2;
	int y = sHeight - liveSize;

	for (int index = 0; index < totalLives; ++index)
	{
		auto currentLife = liveSprites.insert(std::make_pair(
			createSprite(assetPath.at("life")), std::make_pair(x, y)
		)).first->first;

		setSpriteSize(currentLife, liveSize, liveSize);

		x += liveSize;
	}
}

void Player::SpawnBoughtAbility()
{
	int instantApply = 50;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(1, 100);

	int _rand = distrib(gen);

	if (totalScore >= 100 && start)
	{
		if (_rand > instantApply)
		{
			int w = level->getPlatformWidth();
			int h = level->getPlatformHeight();
			int x = sWidth / 2 - w / 2;
			int y = 0;

			spawnAbility(x, y);

			totalScore -= 100;
			printScore();
		}
		else
		{
			int x = platform.getX();
			int y = platform.getY();

			spawnAbility(x, y);
			
			totalScore -= 100;
			printScore();
		}
	}
}

void Player::SetGameSpeed(int _speed)
{
	ball.setSpeed(_speed);
	platform.setSpeed(_speed);
	speed = _speed;
}

void Player::spawnAbility(int x, int y)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<> distrib(0, static_cast<int>(AbilityType::COUNT) - 1);

	int _rand = distrib(gen);

	int w = level->getPlatformWidth();
	int h = level->getPlatformHeight();

	switch (_rand)
	{
	case (static_cast<int>(AbilityType::PLATFORM_LONG)):
		abilities.insert(std::make_pair(
			new AbilityPlatformLong(w, h), std::make_pair(x, y)
		));
		break;

	case (static_cast<int>(AbilityType::PLATFORM_SHORT)):
		abilities.insert(std::make_pair(
			new AbilityPlatformShort(w, h), std::make_pair(x, y)
		));
		break;

	case (static_cast<int>(AbilityType::BALL_BIG)):
		abilities.insert(std::make_pair(
			new AbilityBallBig(w, h), std::make_pair(x, y)
		));
		break;

	case (static_cast<int>(AbilityType::BALL_SMALL)):
		abilities.insert(std::make_pair(
			new AbilityBallSmall(w, h), std::make_pair(x, y)
		));
		break;
	}

	//printScore();
}

void Player::checkAbilityCollision()
{
	for (auto const& it : abilities)
	{
		int x = it.second.first;
		int y = it.second.second;
		auto ability = it.first;

		if (y >= platform.maxY)
		{
			if (y >= sHeight - it.first->getH())
			{
				abilities.erase(ability);
				ability->destroyAbility();
				break;
			}
			if (x < platform.getX() + platform.getW() &&
				x + ability->getW() > platform.getX() &&
				y < platform.getY() + platform.getH() &&
				y + ability->getH() > platform.getY())
			{
				abilities.erase(ability);
				applyAbility(ability);
				ability->destroyAbility();
				break;
			}
		}
	}
}

void Player::applyAbility(Ability* ability)
{
	int ballSize = static_cast<int>(ball.getBallType());
	int platformSize = static_cast<int>(platform.getPlatformType());

	switch (ability->getAbilityType())
	{
	case (AbilityType::PLATFORM_LONG):
		if (platformSize + 1 <= static_cast<int>(PlatformType::LONG))
		{
			PlatformType longer = static_cast<PlatformType>(platformSize + 1);
			changePlatform(longer);
		}
		break;

	case (AbilityType::PLATFORM_SHORT):
		if (platformSize - 1 >= static_cast<int>(PlatformType::SHORT))
		{
			PlatformType shorter = static_cast<PlatformType>(platformSize - 1);
			changePlatform(shorter);
		}
		break;

	case (AbilityType::BALL_BIG):
		if (ballSize + 1 <= static_cast<int>(BallType::MAX))
		{
			BallType bigger = static_cast<BallType> (ballSize + 1);
			changeBall(bigger);
		}
		break;

	case (AbilityType::BALL_SMALL):
		if (ballSize - 1 >= static_cast<int>(BallType::MIN))
		{
			BallType smaller = static_cast<BallType> (ballSize - 1);
			changeBall(smaller);
		}
		break;
	}
}
