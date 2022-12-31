//The fighter class will do more damage with melee attacks
#pragma once
#include "Player.h"

class Fighter : public Player
{
public:
	//member variables
	int m_numAttacks;
	int m_currentNumAttacks;



	//constructor
	Fighter();



	//methods
	void displayStats() override;



	void levelUp() override;
};