//Bugbears have crossbows do 4D6 damage and have 35 hp worth 500 xp
#include "Bugbear.h"

Bugbear::Bugbear()
{
	m_armorClass = 8;
	m_maxHealth = 35;
	m_currentHealth = m_maxHealth;
	m_range = true;
	m_doDamageMin = 1;
	m_doDamageMax = 8;
	m_name = "Bugbear";
	m_type = "Bugbear";
	m_xpValue = 350;
	m_monsterType = 6;
}
