//Bats will be cool bad guys have 10 hp do 2D6 damage and have move of 2 worth 100 xp
#include "Bat.h"

//NEED TO FIGURE OUT HOW TO GET A MOVE OF 2
Bat::Bat()
{
	m_armorClass = 5;
	m_maxHealth = 10;
	m_currentHealth = m_maxHealth;
	m_range = false;
	m_doDamageMin = 2;
	m_doDamageMax = 12;
	m_name = "Bat    ";
	m_type = "Bat    ";
	m_xpValue = 100;
	m_monsterType = 10;
}
