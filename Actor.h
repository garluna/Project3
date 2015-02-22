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
	StudentWorld* getWorld();
private:
	StudentWorld* myWorld;
};

class Wall
	: public Actor
{
public:
	Wall(int imgID, int x, int y, StudentWorld* world);
	virtual ~Wall();
	virtual void doSomething(); //empty body
};

class Player
	: public Actor
{
public:
	Player(int imgID, int x, int y, StudentWorld* world);
	virtual ~Player();
	virtual void doSomething();
private:
};

#endif // ACTOR_H_
