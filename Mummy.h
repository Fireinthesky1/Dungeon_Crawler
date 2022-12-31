//Mummy is a mini boss and will be worth 100000 xp have area of effect damage
#pragma once
#include "Monster.h"

class Mummy : public Monster
{
public:
	//constructor
	Mummy();

	//methods
	std::vector<int> areaOfEffectCoordinates();
};