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
	//StudentWorld* tempWorld = getWorld();
	if (alive == true)
	{
		alive = false;
		setVisible(false);  //CHANGED
		//tempWorld->removeActor(this);
	}
	//else
	//{
	//	alive = true;
	//	setVisible(true);
	//}
	return alive;
}

void Actor::setAlive(bool a)
{
	alive = a;
}

void Actor::damage(Actor* toHurt)
{
	toHurt->subtractHitPoints(2);
}

void Actor::restore()
{
	hitPoints = 20;
}

//void Player::addHitPoints(int a)
//{
//	hitPoints += a;
//}

void Actor::subtractHitPoints(int a)
{
	hitPoints -= a;
}

int Actor::getHitPoints() const
{
	return hitPoints;
}

void Actor::setHitPoints(int points)
{
	hitPoints = points;
}

//void Actor::addAmmo()
//{
//	ammo += 20;
//}

void Actor::addAmmo(int a)
{
	ammo += a;
}

void Actor::subtractAmmo(int a)
{
	ammo -= a;
}

void Actor::setAmmo(int ammoToBe)
{
	ammo = ammoToBe;
}

int Actor::getAmmo() const
{
	return ammo;
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
	if ((tempWorld->returnCurrentPlayer()->getX() == this->getX()) && (tempWorld->returnCurrentPlayer()->getY() == this->getY()))
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
	setHitPoints(20);
	setAmmo(20);
}

Player::~Player()
{
}

void Player::doSomething()
{
	int input;
	StudentWorld* tempWorld = getWorld();
	Level* tempLevel = tempWorld->getLevelPointer();
	if (!isAlive())
	{
		return;
	}
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
						else
							break;
						//Actor* temp2 = tempWorld->getActorsAtLoc(getX(), getY() - 2);
						//Hole* temp3 = dynamic_cast<Hole*> (temp2);
						//if (temp3 != nullptr)  //doesn't let you move into upper left corner, still can walk through second hole
						//{
						//	temp2->changeAlive();
						//	temp->changeAlive();
						//	moveTo(getX(), getY() - 1);
						//}
					}
					Hole* temp2 = dynamic_cast<Hole*> (temp);
					if (temp2 != nullptr)
					{
						break;
					}
					Wall* temp4 = dynamic_cast<Wall*> (temp);
					if (temp4 == nullptr)
					{
						moveTo(getX(), getY() - 1);
						break;
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
			{
				setDirection(left);
				Actor* temp = tempWorld->getActorsAtLoc(getX() - 1, getY());
				if (temp != nullptr)
				{
					Boulder* temp1 = dynamic_cast<Boulder*> (temp);
					if (temp1 != nullptr)
					{
						if (temp1->boulderMovePossible(getX() - 2, getY()))
						{
							moveTo(getX() - 1, getY());
							break;
						}
						else
							break;
					}
					Hole* temp3 = dynamic_cast<Hole*> (temp);
					if (temp3 != nullptr)
					{
						break;
					}
					Wall* temp2 = dynamic_cast<Wall*> (temp);
					if (temp2 == nullptr)
					{
						moveTo(getX() - 1, getY());
					}
					break;
				}
				else
					moveTo(getX() - 1, getY());
				break;
			}
				/*if ((tempLevel->getContentsOf(getX() - 1, getY())) != (tempLevel->wall))
				{
					moveTo(getX() - 1, getY());
				}
				break;*/
			case KEY_PRESS_RIGHT:
			{
				setDirection(right);
				Actor* temp = tempWorld->getActorsAtLoc(getX() + 1, getY());
				if (temp != nullptr)
				{
					Boulder* temp1 = dynamic_cast<Boulder*> (temp);
					if (temp1 != nullptr)
					{
						if (temp1->boulderMovePossible(getX() + 2, getY()))
						{
							moveTo(getX() + 1, getY());
							break;
						}
						else
							break;
					}
					Hole* temp3 = dynamic_cast<Hole*> (temp);
					if (temp3 != nullptr)
					{
						break;
					}
					Wall* temp2 = dynamic_cast<Wall*> (temp);
					if (temp2 == nullptr)
					{
						moveTo(getX() + 1, getY());
					}
					break;
				}
				else
					moveTo(getX() + 1, getY());
				break;
			}
				/*if ((tempLevel->getContentsOf(getX() + 1, getY())) != (tempLevel->wall))
				{
					moveTo(getX() + 1, getY());
				}
				break;*/
			case KEY_PRESS_UP:
			{
				setDirection(up);
				/*if ((tempLevel->getContentsOf(getX(), getY() + 1)) != (tempLevel->wall))
				{
				moveTo(getX(), getY() + 1);
				}
				break;*/
				Actor* temp = tempWorld->getActorsAtLoc(getX(), getY() + 1);
				if (temp != nullptr)
				{
					Boulder* temp1 = dynamic_cast<Boulder*> (temp);
					if (temp1 != nullptr)
					{
						if (temp1->boulderMovePossible(getX(), getY() + 2))
						{
							moveTo(getX(), getY() + 1);
							break;
						}
						else
							break;
					}
					Hole* temp3 = dynamic_cast<Hole*> (temp);
					if (temp3 != nullptr)
					{
						break;
					}
					Wall* temp2 = dynamic_cast<Wall*> (temp);
					if (temp2 == nullptr)
					{
						moveTo(getX(), getY() + 1);
					}
					break;
				}
				else
					moveTo(getX(), getY() + 1);
				break;
			}
			case KEY_PRESS_ESCAPE:
			{
				changeAlive();
				break;
			}
			case KEY_PRESS_SPACE:
			{
				if (getAmmo() != 0)
				{
					subtractAmmo(1);
					getWorld()->playSound(SOUND_PLAYER_FIRE);
					Direction dir;
					dir = getDirection();
				/*	int x = 0, y = 0;
					x = getX();
					y = getY();*/
					/*switch (dir)
					{
					case down:
						x = getX();
						y = getY() - 1;
						break;
					case left:
						x = getX() - 1;
						y = getY();
						break;
					case right:
						x = getX() + 1;
						y = getY();
						break;
					case up:
						x = getX();
						y = getY() + 1;
						break;
					}*/
					tempWorld->addBullet(getX(), getY(), dir);
				}
			}
		}
	}
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
	tempWorld->decJewels();
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
	tempWorld->returnCurrentPlayer()->addAmmo(20);
	getWorld()->playSound(SOUND_GOT_GOODIE);
}

Boulder::Boulder(int imgID, int x, int y, StudentWorld* world)
	:Actor(imgID, x, y, world)
{
	setHitPoints(10);
}
Boulder::~Boulder()
{}

void Boulder::doSomething()
{
}

bool Boulder::changeAlive()
{
	StudentWorld* tempWorld = getWorld();
	if (isAlive() == true)
	{
		setAlive(false);
		setVisible(false);
		//Actor* boulderTemp = dynamic_cast<Actor*> (this);
		//tempWorld->removeActor(this);
	}
	//else
	//{
	//	alive = true;
	//	setVisible(true);
	//}
	return isAlive();
}

bool Boulder::boulderMovePossible(int x, int y)
{
	StudentWorld* tempWorld = getWorld();
	Actor* temp = tempWorld->getActorsAtLoc(x, y);
	if (temp == nullptr)
	{
		moveTo(x, y);
		return true;
	}
	Hole* holeTemp = dynamic_cast<Hole*> (temp);
	if (holeTemp != nullptr)
	{
		holeTemp->changeAlive();
		changeAlive();
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
	//check for boulders here???
	/*StudentWorld* tempWorld = getWorld();
	for (int i = 0; i < tempWorld->getActors.size(); i++)
	{

	}
	if ((tempWorld->returnCurrentPlayer()->getX() == this->getX()) && (tempWorld->returnCurrentPlayer()->getY() == this->getY()))
	{
		this->changeStats();
		changeAlive();
	}*/
}

bool Hole::changeAlive()
{
	StudentWorld* tempWorld = getWorld();
	if (isAlive() == true)
	{
		setAlive(false);
		setVisible(false);
		Actor* holeTemp = dynamic_cast<Actor*> (this);
		//tempWorld->removeActor(holeTemp);
	}
	//else
	//{
	//	alive = true;
	//	setVisible(true);
	//}
	return isAlive();
}

Exit::Exit(int imgID, int x, int y, StudentWorld* world)
	:Actor(imgID, x, y, world)
{
	setVisible(false);
}

Exit::~Exit()
{}

void Exit::doSomething()
{
	StudentWorld* tempWorld = getWorld();
	if ((tempWorld->getJewelNum()) == 0)
	{
		this->setVisible(true);
		if ((tempWorld->returnCurrentPlayer()->getX() == this->getX()) && (tempWorld->returnCurrentPlayer()->getY() == this->getY()))
		{
			changeAlive();
			tempWorld->setExitUsed(true); //makes it trues
			getWorld()->playSound(SOUND_FINISHED_LEVEL);
		}
	}
}

Bullet::Bullet(int imgID, int x, int y, Direction dir, StudentWorld* world)
	:Actor(imgID, x, y, world)
{
	setDirection(dir);
}

Bullet::~Bullet()
{}

void Bullet::doSomething()
{
	StudentWorld* tempWorld = getWorld();
	switch (getDirection())
	{
		case down:
		{

			Actor* temp1 = tempWorld->getActorsAtLoc(getX(), getY() - 1);
			if (temp1 == nullptr)
			{
				moveTo(getX(), getY() - 1);
				break;
			}
			else
			{
				if (temp1->getHitPoints() != 0)
				{
					damage(temp1);
					//cerr << temp1->getHitPoints();
					if (temp1->getHitPoints() == 0)
					{
						temp1->changeAlive();
					}
				}
				changeAlive();
			}
			break;
		}
		case left:
		{
			Actor* temp = tempWorld->getActorsAtLoc(getX() - 1, getY());
			if (temp == nullptr)
			{
				moveTo(getX() - 1, getY());
				break;
			}
			else
			{
				if (temp->getHitPoints() != 0)
				{
					damage(temp);
					cerr << temp->getHitPoints();
					if (temp->getHitPoints() == 0)
					{
						temp->changeAlive();
					}
				}
				changeAlive();
			}
			break;
		}
		case right:
		{
			Actor* temp = tempWorld->getActorsAtLoc(getX() + 1, getY());
			if (temp == nullptr)
			{
				moveTo(getX() + 1, getY());
				break;
			}
			else
			{
				if (temp->getHitPoints() != 0)
				{
					damage(temp);
					cerr << temp->getHitPoints();
					if (temp->getHitPoints() == 0)
					{
						temp->changeAlive();
					}
				}
				changeAlive();
			}
			break;
		}
		case up:
		{
			Actor* temp = tempWorld->getActorsAtLoc(getX(), getY() + 1);
			if (temp == nullptr)
			{
				moveTo(getX(), getY() + 1);
				break;
			}
			else
			{
				if (temp->getHitPoints() != 0)
				{
					damage(temp);
					cerr << temp->getHitPoints();
					if (temp->getHitPoints() == 0)
					{
						temp->changeAlive();
					}
				}
				changeAlive();
			}
			break;
		}
	}
}
