#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
//base, player, Wall declarations

class Actor
	: public GraphObject
{
public:
	Actor();
	virtual ~Actor();
	virtual doSomething() = 0;
};

class Wall
{
public:
	Wall();
	virtual ~Wall();
};

class Player
{
public:
	Player();
	virtual ~Player();
	virtual doSomething();
};

#endif // ACTOR_H_
