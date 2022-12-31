//The wizard class can use scrolls and has spell attacks
//Come in and customize more
#pragma once
#include "Player.h"

class Wizard : public Player
{
public:
	//constructor
	Wizard();



	//methods
	void displayStats() override;



	void levelUp() override;
};