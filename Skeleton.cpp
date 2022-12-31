//Skeletons will have range attacks and default 15 HP, 200 XP
#include "Skeleton.h"

Skeleton::Skeleton()
{
	m_armorClass = 12;
	m_baseDifficulty = 8;
	m_maxHealth = 15;
	m_currentHealth = m_maxHealth;
	m_range = true;
	m_doDamageMin = 1;
	m_doDamageMax = 6;
	m_name = "Skelli ";
	m_type = "Skelli ";
	m_xpValue = 200;
	m_monsterType = 1;
}
