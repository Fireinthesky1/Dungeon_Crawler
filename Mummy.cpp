//Mummy is a mini boss and will be worth 1000 xp have area of effect damage
//THIS CLASS NEEDS WORK
#include "Mummy.h"



Mummy::Mummy()
{
	m_armorClass = 17;
	m_baseDifficulty = 5;
	m_maxHealth = 99;
	m_currentHealth = m_maxHealth;
	m_range = false;
	m_doDamageMin = 10;
	m_doDamageMax = 50;
	m_name = "Mummy  ";
	m_type = "Mummy  ";
	m_xpValue = 1000;
	m_monsterType = 8;
}



//IMPLEMENT
std::vector<int> Mummy::areaOfEffectCoordinates()
{
	//returns all of the squares in which area of effect damage will apply to
	//format will be
	//y1, x1, y2, x2, y3, x3, y4, x4
	std::vector<int> coordinates;
	return coordinates;
}