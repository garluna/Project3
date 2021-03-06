#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor
	: public GraphObject
{
public:
	Actor(int imgID, int x, int y, StudentWorld* world);
	virtual ~Actor();
	virtual void doSomething() = 0;
	StudentWorld* getWorld() const;
	virtual bool isAlive() const;
	virtual bool changeAlive();
	void setAlive(bool a);
	virtual void damage(Actor* toHurt);  //CHECK
	//void restore();
	virtual void subtractHitPoints(int a);
	virtual int getHitPoints() const;
	virtual void setHitPoints(int points);
	//void addAmmo();
	virtual void setAmmo(int ammoToBe);
	virtual int getAmmo() const;
private:
	StudentWorld* myWorld;
	bool alive = true;
	int hitPoints = 0;
	int ammo = 0;
};

class Extras 
	:public Actor
{
public:
	Extras(int imgID, int x, int y, StudentWorld* world);
	virtual ~Extras();
	virtual void doSomething();
	virtual void changeStats() = 0;
private:
};

class Robot
	:public Actor
{
public:
	Robot(int imgID, int x, int y, Direction dir, StudentWorld* world);
	~Robot();
	virtual void doSomething();
	bool isCurrentTickGood();
	void increaseTick();
	bool playerInSight(int x, int y, int playerX, int playerY, Direction dir);
	bool moveToNextPossible(Direction dir);
private:
	int maxTick;
	int currentTick;
};

class Wall
	: public Actor
{
public:
	Wall(int imgID, int x, int y, StudentWorld* world);
	virtual ~Wall();
	virtual void doSomething(); //empty body
	//always alive so isAlive stays
};

class Player
	: public Actor
{
public:
	Player(int imgID, int x, int y, StudentWorld* world);
	virtual ~Player();
	virtual void doSomething();
	void restore();
	void addAmmo(int a);
	void subtractAmmo(int a);
	void addHitPoints(int a);
	/*virtual void subtractHitPoints(int a);
	virtual int getHitPoints() const;
	virtual void setHitPoints(int points);
	virtual void setAmmo(int ammoToBe);
	virtual int getAmmo() const;*/
private:
	int hitPoints = 20;
	int ammo = 20;
};

class Jewel
	:public Extras
{
public:
	Jewel(int imgID, int x, int y, StudentWorld* world);
	virtual ~Jewel();
	virtual void changeStats();
};

class ExtraLife
	:public Extras
{
public:
	ExtraLife(int imgID, int x, int y, StudentWorld* world);
	virtual ~ExtraLife();
	virtual void changeStats();
};

class RestoreHealth
	:public Extras
{
public:
	RestoreHealth(int imgID, int x, int y, StudentWorld* world);
	virtual ~RestoreHealth();
	virtual void changeStats();
};

class Ammo
	:public Extras
{
public:
	Ammo(int imgID, int x, int y, StudentWorld* world);
	virtual ~Ammo();
	virtual void changeStats();
};

class Boulder
	:public Actor
{
public:
	Boulder(int imgID, int x, int y, StudentWorld* world);
	virtual ~Boulder();
	virtual void doSomething();
	virtual bool boulderMovePossible(int x, int y);
	virtual bool changeAlive();
};

class Hole
	:public Actor
{
public:
	Hole(int imgID, int x, int y, StudentWorld* world);
	virtual ~Hole();
	virtual void doSomething();
	virtual bool changeAlive();
};

class Exit
	:public Actor
{
public:
	Exit(int imgID, int x, int y, StudentWorld* world);
	virtual ~Exit();
	virtual void doSomething();
};

class Bullet
	:public Actor
{
public:
	Bullet(int imgID, int x, int y, Direction dir, StudentWorld* world, bool fromPlayer);
	~Bullet();
	virtual void doSomething();
	bool reutrnsComesFromPlayer();
private:
	bool comesFromPlayer = true;
};

class SnarlBot
	:public Robot
{
public:
	SnarlBot(int imgID, int x, int y, Direction dir, StudentWorld* world);
	~SnarlBot();
	//virtual bool changeAlive();
	//virtual void doSomething();
};

class KleptoBot
	:public Robot
{
public:
	KleptoBot(int imgID, int x, int y, Direction dir, StudentWorld* world);
	~KleptoBot();
	virtual void doSomething() = 0;
private:
	int distanceBeforeTurning;
};
#endif // ACTOR_H_
