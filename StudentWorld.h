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

	Actor* getActorsAtLoc(int x, int y) const;
	int loadLevel();
	Level* getLevelPointer() const;
	Player* returnCurrentPlayer() const;
	void setDisplayText();
	int getCurrentScore() const;
	int getCurrentGameLevel() const;
	std::string format(int score, int lvl, int lives, int health, int ammo, int bonus);
	int getJewelNum() const;
	void decJewels();
	//void changeExitUsed();
	void setExitUsed(bool a);
	void removeActor(Actor* a);
	void addBullet(int x, int y, GraphObject::Direction dir, bool fromPlayer);
	/*void setHitPoints(int points);
	void subtractHitPoints(int a);
	int getHitPoints() const;
	void setAmmo(int ammoToBe);
	int getAmmo() const;*/
	
private:
	std::vector<Actor*> actors; //DEVAN
	Player* currentPlayer = nullptr;  //CHECK
	Level*	lev = new Level(assetDirectory());
	int bonus = 1000;
	int numJewels;
	bool exitUsed;

	/*int playerHitPoints = 20;
	int playerAmmo = 20;*/
};

#endif // STUDENTWORLD_H_
