#include "StudentWorld.h"
#include <string>
using namespace std;

//#include "Level.h"
#include <sstream>

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

int StudentWorld::init()
{
	loadLevel();
	return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
	// This code is here merely to allow the game to build, run, and terminate after hitting enter a few times 
	currentPlayer->doSomething();
	decLives();
	return GWSTATUS_CONTINUE_GAME;
	/*
 // Give each actor a chance to do something
for each of the actors in the game world
{
 if (actor[i] is still active/alive)
 {
 // ask each actor to do something (e.g. move)
 actor[i]->doSomething();
if (thePlayerDiedDuringThisTick())
return GWSTATUS_PLAYER_DIED;
if (thePlayerCompletedTheCurrentLevel())
{
increaseScoreAppropriately();
return GWSTATUS_FINISHED_LEVEL;
}
 }
}
 // Remove newly-dead actors after each tick
removeDeadGameObjects(); // delete dead game objects
 // Reduce the current bonus for the Level by one
reduceLevelBonusByOne();
 // If the player has collected all of the Jewels on the level, then we
 // must expose the Exit so the player can advance to the next level
if (thePlayerHasCollectedAllOfTheJewelsOnTheLevel())
exposeTheExitInTheMaze(); // make the exit Active
 // return the proper result
if (thePlayerDiedDuringThisTick())
return GWSTATUS_PLAYER_DIED;
if (thePlayerCompletedTheCurrentLevel())
{
increaseScoreAppropriately();
return GWSTATUS_FINISHED_LEVEL;
}
 // the player hasn’t completed the current level and hasn’t died, so
 // continue playing the current level
return GWSTATUS_CONTINUE_GAME;
 }*/
}

void StudentWorld::cleanUp()
{
}

int StudentWorld::loadLevel()
{
	ostringstream levelNameToStore;
	levelNameToStore << "level" << levelNumber << ".dat";
	//	levelNumber++;
	//
	//	string	curLevel = levelNameToStore.str();
	//	cout << curLevel;
	//	Level	lev(assetDirectory());
	//	Level::LoadResult result = lev.loadLevel(curLevel);
	//	if (result == Level::load_fail_file_not_found ||
	//		result == Level::load_fail_bad_format)
	//		return -1;
	std::string curLevel = "level00.dat";
	/*Level	tempLev(assetDirectory());*/
	/*this->lev = &tempLev;*/
	Level::LoadResult result = lev->loadLevel(curLevel);
	if (result == Level::load_fail_file_not_found ||
		result == Level::load_fail_bad_format)
		return -1;

	for (int x = 0; x < VIEW_WIDTH; x++)
	{
		for (int y = 0; y < VIEW_HEIGHT; y++)
		{
			Level::MazeEntry item = lev->getContentsOf(x, y);
			switch (item)		//DEVAN
			{
			case Level::player:
				 currentPlayer = new Player(IID_PLAYER, x, y, this);  
				break;
			case Level::wall:
				actors.push_back(new Wall(IID_WALL, x, y, this));
				break;
			}
		}
	}
	return 0;
}

Level* StudentWorld::getLevel() const
{
	return lev;
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
