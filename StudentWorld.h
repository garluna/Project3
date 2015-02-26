#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>

#include <vector>
#include "Actor.h"
#include "Level.h"

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir)
	 : GameWorld(assetDir)
	{
	}

	virtual int init();
	virtual int move();
	virtual void cleanUp();

	Actor* getActorsAtLoc(int x, int y);
	int loadLevel();
	Level* getLevelPointer() const;
	Player* returnCurrentPlayer();
private:
	//int levelNumber = 00;
	std::vector<Actor*> actors; //DEVAN
	Player* currentPlayer = nullptr;  //CHECK
	Level*	lev = new Level(assetDirectory());
};

#endif // STUDENTWORLD_H_
