#include "StudentWorld.h"
#include <string>
using namespace std;

//#include "Level.h"
#include <iomanip>
#include <sstream>

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

int StudentWorld::init()
{
	if (loadLevel() == -1)
	{
		return GWSTATUS_PLAYER_WON;
	}
	else
	{
		return GWSTATUS_CONTINUE_GAME;
	}
}

int StudentWorld::move()
{
	setDisplayText();
	if (!currentPlayer->isAlive())
	{
		decLives();
		return GWSTATUS_PLAYER_DIED;
	}
	if (bonus > 0)
	{
		bonus--;
	}
	currentPlayer->doSomething();
	for (int i = 0; i < actors.size(); i++)
	{
		if (!(actors[i]->isAlive()))
		{
			removeActor(actors[i]);
		}
	}
	for (int i = 0; i < actors.size(); i++)
	{
		actors[i]->doSomething();
	}
	/*int count = 0;  //CHECK - use iterator???
	for (int i = 0; i < actors.size(); i++)
	{
		if (!(actors[i]->isAlive()))
		{
			actors[i] = actors[actors.size() - 1];
		}
	}*/
	if (getLives() == 0)
	{
		return GWSTATUS_PLAYER_DIED;  //CHECK
	}
	if (exitUsed)
	{
		increaseScore(2000 + bonus);
		setExitUsed(false);
		return GWSTATUS_FINISHED_LEVEL;
	}
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
	delete currentPlayer;   //CHECK - deleting pointer or memory at pointer as well or don't have to at all?
	/*vector<Actor*>::iterator it;
	it = actors.begin();*/ 
	/*for (int i = 0; i < actors.size(); i++)
	{
		Actor *t;
		t = actors[i];
		delete t;
	}
	for (int i = 0; !actors.empty(); i++)
	{
		actors.pop_back();
	}*/

	while (!actors.empty())
	{
		Actor *t = actors.back();
		delete t;
		actors.pop_back();
	}
}

int StudentWorld::loadLevel()
{
	ostringstream levelNameToStore;
	levelNameToStore << "level";
	levelNameToStore.fill('0');
	levelNameToStore << setw(2) << getLevel() << ".dat";
	//	levelNumber++;
	//
	//	string	curLevel = levelNameToStore.str();
	//	cout << curLevel;
	//	Level	lev(assetDirectory());
	//	Level::LoadResult result = lev.loadLevel(curLevel);
	std::string curLevel = levelNameToStore.str();
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
			case Level::jewel:
				actors.push_back(new Jewel(IID_JEWEL, x, y, this));
				numJewels++;
				break;
			case Level::extra_life:
				actors.push_back(new ExtraLife(IID_EXTRA_LIFE, x, y, this));
				break;
			case Level::restore_health:
				actors.push_back(new RestoreHealth(IID_RESTORE_HEALTH, x, y, this));
				break;
			case Level::ammo:
				actors.push_back(new Ammo(IID_AMMO, x, y, this));
				break;
			case Level::boulder:
				actors.push_back(new Boulder(IID_BOULDER, x, y, this));
				break;
			case Level::hole:
				actors.push_back(new Hole(IID_HOLE, x, y, this));
				break;
			case Level::exit:
				actors.push_back(new Exit(IID_EXIT, x, y, this));
				break;
			}
		}
	}
	return 0;
}

Level* StudentWorld::getLevelPointer() const
{
	return lev;
}
Player* StudentWorld::returnCurrentPlayer() const
{
	return currentPlayer;
}

void StudentWorld::removeActor(Actor* a)
{
	vector<Actor*>::iterator it;
	it = actors.begin();
	while (it != actors.end())
	{
		if (*it == a)
		{
			//cerr << "remove\n";
			Actor* temp;
			temp = *it;
			it = actors.erase(it);
			delete temp;
			return;
		}
		else
		{
			it++;
		}
	}
}

Actor* StudentWorld::getActorsAtLoc(int x, int y) const
{
	for (int i = 0; i < actors.size(); i++)
	{
		if ((actors[i]->getX() == x) && (actors[i]->getY() == y))
		{
			return actors[i];
		}
	}
	return nullptr;
}

int StudentWorld::getCurrentScore() const
{
	return getScore();
}

int StudentWorld::getCurrentGameLevel() const
{
	return getLevel();
}

void StudentWorld::setDisplayText() 
{
	int score = getScore();
	int level = getLevel();
	int livesLeft = getLives();

	string display = format(score, level, livesLeft, currentPlayer->getHitPoints(), currentPlayer->getAmmo(), bonus);

	setGameStatText(display);
}

string StudentWorld::format(int score, int lvl, int lives, int health, int ammo, int bonus)
{
	ostringstream scoreDisplay;
	scoreDisplay << "Score: ";
	scoreDisplay.fill('0');
	scoreDisplay << setw(7) << score << "  ";

	ostringstream levelDisplay;
	levelDisplay << "Level: ";
	levelDisplay.fill('0');
	levelDisplay << setw(2) << lvl << "  ";

	ostringstream livesDisplay;
	livesDisplay << "Lives: ";
	livesDisplay.fill(' ');
	livesDisplay << setw(2) << lives << "  ";

	health *= 5;
	ostringstream healthDisplay;
	healthDisplay << "Health: ";
	healthDisplay.fill(' ');
	healthDisplay << setw(3) << health << "%  ";

	ostringstream ammoDisplay;
	ammoDisplay << "Ammo: ";
	ammoDisplay.fill(' ');
	ammoDisplay << setw(3) << ammo << "  ";

	ostringstream bonusDisplay;
	bonusDisplay << "Bonus: ";
	bonusDisplay.fill(' ');
	bonusDisplay << setw(4) << bonus << "  ";

	string toDisplay;
	toDisplay = scoreDisplay.str() + levelDisplay.str() + livesDisplay.str() + healthDisplay.str() + ammoDisplay.str() + bonusDisplay.str();
	return toDisplay;
}

int StudentWorld::getJewelNum() const
{
	return numJewels;
}

void StudentWorld::decJewels()
{
	numJewels--;
}

void StudentWorld::setExitUsed(bool a)
{
	exitUsed = a;
}

void StudentWorld::addBullet(int x, int y, GraphObject::Direction dir)
{
	actors.push_back(new Bullet(IID_BULLET, x, y, dir, this));
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
