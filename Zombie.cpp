//Zombies will have 15 hp 20 XP
#include "Zombie.h"

Zombie::Zombie()
{
	m_armorClass = 10;
	m_baseDifficulty = 10;
	m_maxHealth = 15;
	m_currentHealth = m_maxHealth;
	m_range = false;
	m_doDamageMin = 2;
	m_doDamageMax = 8;
	m_name = "Zombie ";
	m_type = "Zombie ";
	m_xpValue = 20;
	m_monsterType = 2;
}
