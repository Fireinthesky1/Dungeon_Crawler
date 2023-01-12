//Zombies will have 15 hp 20 XP
#include "Zombie.h"

Zombie::Zombie()
{
	m_armorClass = 10;
	m_maxHealth = 15;
	m_currentHealth = m_maxHealth;
	m_range = false;
	m_doDamageMin = 1;
	m_doDamageMax = 4;
	m_name = "Zombie ";
	m_type = "Zombie ";
	m_xpValue = 150;
	m_monsterType = 2;
}
