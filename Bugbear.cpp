#include "Bugbear.h"

Bugbear::Bugbear()
{
	m_armorClass = 7;
	m_maxHealth = 15;
	m_currentHealth = m_maxHealth;
	m_range = true;
	m_doDamageMin = 1;
	m_doDamageMax = 8;
	m_name = "Bugbear";
	m_type = "Bugbear";
	m_xpValue = 350;
	m_monsterType = 6;
}
