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
	/*{
		return GWSTATUS_CONTINUE_GAME;
	}*/

	virtual int move();
	//{
	//	  // This code is here merely to allow the game to build, run, and terminate after hitting enter a few times 
	//	decLives();
	//	return GWSTATUS_PLAYER_DIED;
	//}

	virtual void cleanUp();
	//{
	//}

	int loadLevel();
	Level* getLevel() const;

private:
	int levelNumber = 00;
	std::vector<Actor*> actors; //DEVAN
	Actor* currentPlayer = nullptr;  //CHECK
	//Level* lev = nullptr;
	Level*	lev = new Level(assetDirectory());
};

#endif // STUDENTWORLD_H_
