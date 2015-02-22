#include <iostream>
using namespace std;

#include "Actor.h"
#include "StudentWorld.h"

#include "GameWorld.h"

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(int imgID, int x, int y, StudentWorld* world)
	:GraphObject(imgID, x, y)
{
	setVisible(true);
	myWorld = world;
}

Actor::~Actor()
{
}

StudentWorld* Actor::getWorld()
{
	return myWorld;
}

Wall::Wall(int imgID, int x, int y, StudentWorld* world)
	:Actor(imgID, x, y, world)
{
}

Wall::~Wall()
{
}

void Wall::doSomething()
{
}

Player::Player(int imgID, int x, int y, StudentWorld* world)
	:Actor(imgID, x, y, world)
{
	setDirection(right);
}

Player::~Player()
{
}

void Player::doSomething()
{
	/*It must have a limited version of a doSomething() method that lets the
user pick a direction by hitting a directional key. If the Player hits a
directional key during the current tick and the target square does not
contain a Wall, it updates the Player’s location to the target square and 49
the Player’s direction. All this doSomething() method has to do is
properly adjust the Player’s x,y coordinates and direction, and our
graphics system will automatically animate its movement it around the
maze! */
	//if () user presses a key
	//check if wall is there, if not update position
	//update direction
	int input;
	StudentWorld* tempWorld = getWorld();
	Level* tempLevel = tempWorld->getLevel();
	if (tempWorld -> getKey(input))
	{
		switch (input)
		{
		case KEY_PRESS_DOWN:
			setDirection(down);
			if ((tempLevel->getContentsOf(getX(), getY() - 1)) != (tempLevel->wall))
			{
				moveTo(getX(), getY() - 1);
			}
			break;
		case KEY_PRESS_LEFT:
			setDirection(left);
			if ((tempLevel->getContentsOf(getX() - 1, getY())) != (tempLevel->wall))
			{
				moveTo(getX() - 1, getY());
			}
			break;
		case KEY_PRESS_RIGHT:
			setDirection(right);
			if ((tempLevel->getContentsOf(getX() + 1, getY())) != (tempLevel->wall))
			{
				moveTo(getX() + 1, getY());
			}
			break;
		case KEY_PRESS_UP:
			setDirection(up);
			if ((tempLevel->getContentsOf(getX(), getY() + 1)) != (tempLevel->wall))
			{
				moveTo(getX(), getY() + 1);
			}
			break;
		}
	}
}
