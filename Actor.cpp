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

StudentWorld* Actor::getWorld() const
{
	return myWorld;
}

bool Actor::isAlive() const
{
	return alive;
}

bool Actor::changeAlive()
{
	if (alive == true)
	{
		alive = false;
		setVisible(false);
	}
	else
	{
		alive = true;
		setVisible(true);
	}
	return alive;
}

Extras::Extras(int imgID, int x, int y, StudentWorld* world)
	:Actor(imgID, x, y, world)
{
}

Extras::~Extras()
{}

void Extras::doSomething()
{
	StudentWorld* tempWorld = getWorld();
	if ((tempWorld->StudentWorld::returnCurrentPlayer()->getX() == this->getX()) && (tempWorld->StudentWorld::returnCurrentPlayer()->getY() == this->getY()))
	{
		this->changeStats();
		changeAlive();
	}
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
	int input;
	StudentWorld* tempWorld = getWorld();
	Level* tempLevel = tempWorld->getLevelPointer();
	if (tempWorld -> getKey(input))
	{
		switch (input)
		{
		case KEY_PRESS_DOWN:
		{			
			setDirection(down);
			Actor* temp = tempWorld->getActorsAtLoc(getX(), getY() - 1);
			if (temp != nullptr)
			{
				Boulder* temp1 = dynamic_cast<Boulder*> (temp);
				if (temp1 != nullptr)
				{
					if (temp1->boulderMovePossible(getX(), getY() - 2))
					{
						moveTo(getX(), getY() - 1);
						break;
					}
				}
			}
			else
				moveTo(getX(), getY() - 1);
			break;
		}
			
			//}
			//{
			//	for (int i = 0; i < tempWorld->getActors().size(); i++)
			//	{
			//		if (tempWorld->getActors()->)
			//			Boulder* temp = ;
			//	}
			//	if ((temp->boulderMovePossible(getX(), getY() - 1)))  //CHECK have to point it to that boulder
			//	{
			//		temp->doSomething();
			//	}
			//}
			//else
			//if ((tempLevel->getContentsOf(getX(), getY() - 1)) != (tempLevel->wall))
		//	{
			//	moveTo(getX(), getY() - 1);
			//}
			//break;

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

void Player::restore()
{
	hitPoints = 20;
}

//void Player::addHitPoints(int a)
//{
//	hitPoints += a;
//}

void Player::subtractHitPoints(int a)
{
	hitPoints -= a;
}

void Player::restoreAmmo()
{
	ammo = 20;
}

void Player::addAmmo(int a)
{
	ammo += a;
}

void Player::subtractAmmo(int a)
{
	ammo -= a;
}

Jewel::Jewel(int imgID, int x, int y, StudentWorld* world)
	: Extras(imgID, x, y, world)
{
}

Jewel::~Jewel()
{}

void Jewel::changeStats()
{
	StudentWorld* tempWorld = getWorld();
	tempWorld->increaseScore(50);
	getWorld()->playSound(SOUND_GOT_GOODIE);
}

ExtraLife::ExtraLife(int imgID, int x, int y, StudentWorld* world)
	:Extras(imgID, x, y, world)
{
}

ExtraLife::~ExtraLife()
{}

void ExtraLife::changeStats()
{
	StudentWorld* tempWorld = getWorld();
	tempWorld->increaseScore(1000);
	tempWorld->incLives();
	getWorld()->playSound(SOUND_GOT_GOODIE);
}

RestoreHealth::RestoreHealth(int imgID, int x, int y, StudentWorld* world)
	:Extras(imgID, x, y, world)
{
}

RestoreHealth::~RestoreHealth()
{}

void RestoreHealth::changeStats()
{
	StudentWorld* tempWorld = getWorld();
		tempWorld->increaseScore(500);
		tempWorld->returnCurrentPlayer()->restore();
		getWorld()->playSound(SOUND_GOT_GOODIE);
		//CHECK - inform to return to full health means??
}

Ammo::Ammo(int imgID, int x, int y, StudentWorld* world)
	:Extras(imgID, x, y, world)
{

}

Ammo::~Ammo()
{}

void Ammo::changeStats()
{
	StudentWorld* tempWorld = getWorld();
		tempWorld->increaseScore(100);
		tempWorld->returnCurrentPlayer()->restoreAmmo();
		getWorld()->playSound(SOUND_GOT_GOODIE);
}

Boulder::Boulder(int imgID, int x, int y, StudentWorld* world)
	:Actor(imgID, x, y, world)
{

}
Boulder::~Boulder()
{}

void Boulder::doSomething()
{
}

bool Boulder::boulderMovePossible(int x, int y)
{
	StudentWorld* tempWorld = getWorld();
	if ((tempWorld->getActorsAtLoc(x,y)) == nullptr)
	{
		moveTo(x, y);
		return true;
	}
	return false;
}

Hole::Hole(int imgID, int x, int y, StudentWorld* world)
	: Actor(imgID, x, y, world)
{
}

Hole::~Hole()
{
}

void Hole::doSomething()
{
	/*StudentWorld* tempWorld = getWorld();
	for (int i = 0; i < tempWorld->getActors.size(); i++)
	{

	}
	if ((tempWorld->StudentWorld::returnCurrentPlayer()->getX() == this->getX()) && (tempWorld->StudentWorld::returnCurrentPlayer()->getY() == this->getY()))
	{
		this->changeStats();
		changeAlive();
	}*/
}
