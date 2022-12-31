//The priest class will do be able to heal
#pragma once
#include "Player.h"

class Priest : public Player
{
public:
	//member variables
	int m_healSpellsRemaining;



	//constructor
	Priest();



	//methods
	void displayStats() override;
	std::string getHealSpellsRemaining();



	void heal();



	void levelUp() override;
};