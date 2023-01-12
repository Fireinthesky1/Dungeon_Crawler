
#pragma once
#include <vector>
#include "Board.h"
#include "Utility.h"

class Entity
{
public:
	//DATA MEMBERS
	std::string m_name;
	int m_yCoord, m_xCoord, m_direction, m_doDamageMin, m_doDamageMax, m_maxHealth, m_currentHealth, m_armorClass;
	char m_symbol;
	bool m_range;



	//Implemented
	Entity();
	char getSymbol();
	int setVars(int min, int max, int var);
	std::vector<int> getLocation();
	std::vector<int> newIncrement(Board board);
	std::vector<int> incrementNorth(Board board);
	std::vector<int> incrementEast(Board board);
	std::vector<int> incrementSouth(Board board);
	std::vector<int> incrementWest(Board board);
	bool isAlive();
	void changeDirection(int direction);
	void hit(int damage);
	void move(Board board);



	//Virtual
	virtual std::string getName();
	virtual std::vector<int> attack(Board board, int armorClass, bool range);
};
