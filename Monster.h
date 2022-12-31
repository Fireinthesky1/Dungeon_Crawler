#pragma once
#include "Board.h"
#include "Entity.h"



class Monster : public Entity
{
public:
	std::string m_type;
	int m_baseDifficulty;
	int m_xpValue;
	int m_monsterType;



	//constructor
	Monster();

	Monster(std::string type, int maxHealth, int yCoord, int xCoord, int baseDifficulty, int doDamageMax, int doDamageMin, int direction, bool range, int armorClass);



	//Location/Movement
	std::vector<int> attack(Board board, int armorClass, bool range);



protected:
	//stats information
	std::string getFacing();
	std::string getHealth();
	std::string getType();
	std::string getArmorClass();



public:
	//virtual
	virtual void displayStats();

};