//Bugbears have crossbows do 4D6 damage and have 35 hp worth 500 xp
#include "Bugbear.h"

Bugbear::Bugbear()
{
	m_armorClass = 15;
	m_baseDifficulty = 10;
	m_maxHealth = 35;
	m_currentHealth = m_maxHealth;
	m_range = true;
	m_doDamageMin = 4;
	m_doDamageMax = 24;
	m_name = "Bugbear";
	m_type = "Bugbear";
	m_xpValue = 500;
	m_monsterType = 6;
}
