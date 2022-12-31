//Orcs will have 20 HP do 3D6 damage and are worth 250 xp
#include "Orc.h"

Orc::Orc()
{
	m_armorClass = 16;
	m_baseDifficulty = 10;
	m_maxHealth = 20;
	m_currentHealth = m_maxHealth;
	m_range = false;
	m_doDamageMin = 3;
	m_doDamageMax = 18;
	m_name = "Orc    ";
	m_type = "Orc    ";
	m_xpValue = 250;
	m_monsterType = 5;
}