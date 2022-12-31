#pragma once
#include "Board.h"
#include "Entity.h"
//NEED TO CLEAN UP THIS FILE


class Player : public Entity
{
//protected:
public:				//<- CHANGE THIS BACK TO PROTECTED
	std::string m_weapon, m_armor, m_class;
	int m_level, m_xp, m_gold;
	std::vector<std::string> m_inventory;
	

public:
	//constructor
	Player();

	Player(std::string name, std::string weapon, std::string armor, int maxHealth, int yCoord, int xCoord, int baseDifficulty, int doDamageMax, int doDamageMin, int direction, bool range, int level, int xp, int gold, int armorClass);



	//Location/Movement
	std::vector<int> attack(Board board, int armorClass, bool range);
	std::string getName();



protected:
	//STATS INFORMATION
	std::string getFacing();
	std::string getHealth();
	std::string getLevel();
	std::string getXP();
	std::string getGold();
	std::string getArmorClass();
	std::string getClass();
	bool hasInventorySpace();



public:
	//VIRTUAL
	virtual void displayStats();
	virtual void levelUp();
	


	//PURE VIRTUAL
	//virtual std::string getArmor()  = 0;
	//virtual std::string getWeapon() = 0;
	//virtual void levelUp() = 0;

};