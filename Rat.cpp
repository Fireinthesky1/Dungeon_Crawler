//Rat will do 1d6 damage be worth 100 xp and have 6 hp
#include "Rat.h"

Rat::Rat()
{
	m_armorClass = 5;
	m_baseDifficulty = 12;
	m_maxHealth = 6;
	m_currentHealth = m_maxHealth;
	m_range = false;
	m_doDamageMin = 1;
	m_doDamageMax = 6;
	m_name = "Rat    ";
	m_type = "Rat    ";
	m_xpValue = 100;
	m_monsterType = 9;
}