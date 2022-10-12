#include "Platform.h"
#include "Ball.h"
#include "Level.h"
#include "Ability.h"
#include <random> // for random number generator
#pragma once

// consists out of the platform, the ball, total lives and score
class Player
{
private:
	int platformSpeed;
	int levelNumber;
	int sWidth;
	int sHeight;
	int liveSize;
	int abilityDropChance;
	uint16_t totalLives;
	uint16_t totalScore;
	Platform platform;
	Ball ball;
	Level* level;
	bool start;
	int speed;

	bool up;
	bool down;
	bool left;
	bool right;

	std::unordered_map<Sprite*, std::pair<uint16_t, uint16_t>> liveSprites;
	std::unordered_map<Ability*, std::pair<uint16_t, uint16_t>> abilities;

	void changePlatform(PlatformType pt);
	void changeBall(BallType bt);
	bool platformCollisionUp(int x, int y, bool& left, bool& right);
	bool platformCollisionLeft(int x, int y);
	bool platformCollisionRight(int x, int y);
	bool tileCollisionDown(int x, int y);
	bool tileCollisionUp(int x, int y);
	bool tileCollisionLeft(int x, int y);
	bool tileCollisionRight(int x, int y);
	void reset();	
	void decreaseLife();
	void printScore();
	void loadLifeSprites();
	void spawnAbility(int x, int y);
	void checkAbilityCollision();
	void applyAbility(Ability* ability);

public:
	Player();

	void LoadSprites();

	void DrawSprites();	

	void MovePlatformUp();

	void MovePlatformDown();

	void MovePlatformLeft();

	void MovePlatformRight();

	void MoveBall();

	void LevelChange();

	void StartBallMovement(bool _left);	

	void SpawnBoughtAbility();	

	void SetGameSpeed(int _speed);
};

