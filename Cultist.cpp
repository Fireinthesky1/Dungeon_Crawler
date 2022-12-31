//Cultist will have a lot of damage, 12 hp and be worth 1000 xp
#include "Cultist.h"

Cultist::Cultist()
{
	m_armorClass = 10;
	m_baseDifficulty = 12;
	m_maxHealth = 12;
	m_currentHealth = m_maxHealth;
	m_range = true;
	m_doDamageMin = 6;
	m_doDamageMax = 36;
	m_name = "Cultist";
	m_type = "Cultist";
	m_xpValue = 1000;
	m_monsterType = 7;
}