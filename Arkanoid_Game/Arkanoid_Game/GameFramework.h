#include "Player.h"
#include <conio.h>

#pragma once
class GameFramework : public Framework
{
private:
	// preferred: 800x600, <960x720>, 1024x768, 1280x960
	uint16_t m_width;
	uint16_t m_height;
	int speed = 1;

	Player player;

	// platform movement
	bool moveLeft;
	bool moveRight;
	bool moveUp;
	bool moveDown;

	bool left = false;

public:

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{		
		
		fullscreen = false;	

		printInstructions();

		std::cout << "Input screen width: ";
		std::cin >> m_width;
		std::cout << "Input screen height: ";
		std::cin >> m_height;

		std::cout << "\nThis game was made with uncapped FPS. If you have capped FPS the game might have slower speeds.";
		std::cout << "\nIf the game is moving too slow, input a higher speed value (default = 1): ";
		std::cin >> speed;

		width = m_width;
		height = m_height;

		system("cls");		
	}

	virtual bool Init() {
		std::cout << "Idle time after library initialization: " << getTickCount() << "ms\n\n";
		player.LoadSprites();
		player.SetGameSpeed(speed);
		return true;
	}

	virtual void Close() {
		// garbage management if needed
	}

	virtual bool Tick() {
		//drawTestBackground();
		player.DrawSprites();

		if (moveLeft)
			player.MovePlatformLeft();
		if (moveRight)
			player.MovePlatformRight();
		if (moveUp)
			player.MovePlatformUp();
		if (moveDown)
			player.MovePlatformDown();

		player.MoveBall();

		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {
		
		if (x < m_width / 2)
			left = true;
		else
			left = false;
	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {		
		switch (button)
		{
		case FRMouseButton::LEFT:
			if (isReleased)
				player.StartBallMovement(left);
			break;
		case FRMouseButton::MIDDLE:
			if (!isReleased)
				player.LevelChange();
			break;
		case FRMouseButton::RIGHT:
			if (!isReleased)
				player.SpawnBoughtAbility();
		}
	}

	virtual void onKeyPressed(FRKey k) {		
		switch (k)
		{
		case FRKey::UP:
			moveUp = true;
			moveDown = false;
			break;
		case FRKey::DOWN:
			moveDown = true;
			moveUp = false;
			break;
		case FRKey::LEFT:
			moveLeft = true;
			moveRight = false;
			break;
		case FRKey::RIGHT:
			moveRight = true;
			moveLeft = false;
			break;
		}
	}

	virtual void onKeyReleased(FRKey k) {
		switch (k)
		{
		case FRKey::UP:
			moveUp = false;
			break;
		case FRKey::DOWN:
			moveDown = false;
			break;
		case FRKey::LEFT:
			moveLeft = false;
			break;
		case FRKey::RIGHT:
			moveRight = false;
			break;
		}
	}

	virtual const char* GetTitle() override
	{
		return "Arkanoid";
	}

	void printInstructions()
	{
		std::cout << "Welcome to Arkanoid!\n\n **INSTRUCITONS**\n---Use the arrow keys to move the platform up/down/left/right.\n" <<
			"---Position your cursor on a side of the screen (left/right) and use left click to launch the ball in that direction.\n" <<
			"---The game consists of two levels. To advance to the second level you need to destroy all the tiles in the first level.\n" <<
			"---Completing the second level will restart the game.\n" <<
			"---The player gets rewarded 100 points for completing a level.\n" <<
			"---The player has 4 lives to complete both levels. If the platform does not catch the ball, the player will lose a life.\n" <<
			"---If no lives are left, the game restarts to the first level.\n" <<
			"---The tiles will randomly drop one buff or one debuff. The player can use right click to buy one for 100 points.\n" <<
			"---The bought ability has a 50-50 chance to be applied instantly or to fall from the ceiling.\n" <<
			"---The game should be started for the ability to be bought.\n" <<
			"---BUFFS: Long platform, Ball size increase. They can be stacked.\n" <<
			"---DEBUFFS: Short platform, Ball size decrease. They can be stacked.\n" <<
			"---Orange and red tiles take 2 hits to be destroyed. Golden tiles are unbreakable.\n" <<
			"---Each tile has a different score value : Aqua & Blue - 10 points, Lime & Green - 20 points, Orange & Red - 40 points.\n" <<
			"\n**CHEAT**\n---Press middle mouse to clear level.\n" <<
			"\nENJOY!!\n\n" <<
			"Please input your desired screen size (RECOMMENDED 4:3 RESOLUTION e.g 800x600, 960x720, 1024x768, 1280x960)\n\n" <<
			"Any resolution will work, but it will either make the game harder or easier.\n\n";
	}
};

