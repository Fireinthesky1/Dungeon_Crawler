//goblins have 4 hp and do d4 damage worth 50 xp
#include "Goblin.h"

Goblin::Goblin()
{
	m_armorClass = 6;
	m_baseDifficulty = 5;
	m_maxHealth = 4;
	m_currentHealth = m_maxHealth;
	m_range = false;
	m_doDamageMin = 1;
	m_doDamageMax = 4;
	m_name = "Goblin ";
	m_type = "Goblin ";
	m_xpValue = 50;
	m_monsterType = 4;
}
